//-----------------------------------------------------------------------------
// ascal_avl_ddr3 - Avalon-MM burst master (ascal) -> Gowin DDR3 IP app port
//-----------------------------------------------------------------------------
// ascal talks Avalon-MM.  The Gowin DDR3 controller ("DDR3_Memory_Interface_Top")
// speaks a Xilinx-MIG-like app interface.  This is the shim.
//
// ADDRESS UNITS - the thing that will bite you.  Three different granularities
// are in play:
//   * ascal's avl_address is a WORD address, one word = N_DW bits = 16 bytes.
//     (ascal internally does `avl_address <= byte_adr(N_AW+NB_LA-1 : NB_LA)`
//     with NB_LA = log2(N_DW/8) = 4.)
//   * the Gowin controller's `addr` counts 16-BIT DDR words, i.e. 2 bytes.
//   * one Gowin command moves a full BL8 burst = 8x16 bits = 16 bytes.
//   => one command consumes EIGHT address units, and app_addr = avl_address*8.
// Derived from gbatang's ddr3_framebuffer.v, which steps its address by 8 per
// 4-pixel (128-bit) access - the only place this ratio is written down.
//
// BURSTS.  ascal issues bursts of BLEN = N_BURST/N_DW*8 = 256/128*8 = 16 words.
// The Gowin controller has no multi-beat burst at the app layer (one command =
// one 128-bit transfer), so this shim expands each Avalon burst into BLEN
// sequential commands with the address walking by 8.  There is no bandwidth
// penalty: BL8 is already the DDR3 burst, and commands issue back-to-back.
//
// Avalon semantics as ascal actually drives them (verified against ascal.vhd's
// `Avaloir` process):
//   WRITE - avl_write held high for the whole burst, address presented once,
//           one data word consumed per cycle that waitrequest is low, BLEN times.
//   READ  - avl_read held until ONE cycle of waitrequest low (the command is
//           accepted), then data returns later via readdatavalid, BLEN words.
// So the shim must keep waitrequest high while it is still issuing the tail of
// a read burst, or ascal would start a second transaction underneath it.
//-----------------------------------------------------------------------------
`default_nettype none

module ascal_avl_ddr3 #(
    parameter N_DW    = 128,
    parameter N_AW    = 25,
    parameter N_BURST = 256,              // bytes
    parameter BLEN    = N_BURST/N_DW*8    // = 16 words per burst
)(
    input  wire                 clk,        // = clk_x1 (74.25 MHz, DDR3 app clock)
    input  wire                 rst,        // active high, synchronous

    // ---- Avalon-MM slave side (faces ascal) ----
    input  wire [N_AW-1:0]      avl_address,
    input  wire                 avl_write,
    input  wire                 avl_read,
    input  wire [N_DW-1:0]      avl_writedata,
    input  wire [7:0]           avl_burstcount,
    input  wire [N_DW/8-1:0]    avl_byteenable,
    output wire                 avl_waitrequest,
    output wire [N_DW-1:0]      avl_readdata,
    output wire                 avl_readdatavalid,

    // ---- Gowin DDR3 app side ----
    input  wire                 app_rdy,       // cmd_ready
    output wire                 app_en,        // cmd_en
    output wire [2:0]           app_cmd,       // 0 = write, 1 = read
    output wire [27:0]          app_addr,
    input  wire                 app_wdf_rdy,   // wr_data_rdy
    output wire                 app_wdf_wren,  // wr_data_en
    output wire                 app_wdf_end,
    output wire [N_DW-1:0]      app_wdf_data,
    output wire [N_DW/8-1:0]    app_wdf_mask,
    input  wire                 app_rd_data_valid,
    input  wire [N_DW-1:0]      app_rd_data
);

    localparam ST_IDLE  = 2'd0;
    localparam ST_WRITE = 2'd1;
    localparam ST_READ  = 2'd2;

    reg [1:0]        state = ST_IDLE;
    reg [N_AW-1:0]   addr_q = 0;      // walking word address
    reg [7:0]        beat   = 0;      // words transferred so far this burst
    reg [7:0]        blen_q = BLEN;   // latched burstcount

    // A transfer happens this cycle when the controller is ready.  Writes need
    // both the command and the write-data channel; reads only the command.
    wire wr_go = (state == ST_WRITE) && app_rdy && app_wdf_rdy;
    wire rd_go = (state == ST_READ)  && app_rdy;

    // waitrequest is LOW only on cycles that actually move a word.  For reads
    // that is just the FIRST command of the burst - ascal wants exactly one
    // acknowledge, then we keep it stalled while the remaining BLEN-1 commands
    // go out.
    assign avl_waitrequest = !(wr_go || (rd_go && beat == 8'd0));

    assign app_en       = wr_go || rd_go;
    assign app_cmd      = (state == ST_READ) ? 3'b001 : 3'b000;
    assign app_addr     = {addr_q, 3'b000};   // word address * 8 (see header)
    assign app_wdf_wren = wr_go;
    assign app_wdf_end  = 1'b1;               // one 128-bit beat per command
    assign app_wdf_data = avl_writedata;
    assign app_wdf_mask = ~avl_byteenable;    // Gowin mask is active-high

    assign avl_readdata      = app_rd_data;
    assign avl_readdatavalid = app_rd_data_valid;

    always @(posedge clk) begin
        if (rst) begin
            state  <= ST_IDLE;
            beat   <= 0;
            addr_q <= 0;
            blen_q <= BLEN;
        end else begin
            case (state)
                // One idle cycle per burst to register the address; the cost is
                // 1 cycle in 17, and it keeps app_addr off a combinational path
                // from avl_address.
                ST_IDLE: begin
                    beat   <= 0;
                    addr_q <= avl_address;
                    blen_q <= (avl_burstcount == 8'd0) ? BLEN : avl_burstcount;
                    if (avl_write)     state <= ST_WRITE;
                    else if (avl_read) state <= ST_READ;
                end

                ST_WRITE: if (wr_go) begin
                    addr_q <= addr_q + 1'b1;
                    beat   <= beat + 1'b1;
                    if (beat == blen_q - 1) state <= ST_IDLE;
                end

                ST_READ: if (rd_go) begin
                    addr_q <= addr_q + 1'b1;
                    beat   <= beat + 1'b1;
                    if (beat == blen_q - 1) state <= ST_IDLE;
                end

                default: state <= ST_IDLE;
            endcase
        end
    end

endmodule

`default_nettype wire
