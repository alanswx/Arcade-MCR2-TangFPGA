//-----------------------------------------------------------------------------
// tb_ascal_synth - gate-level-ish cross-check of ascal via a SECOND synthesiser
//-----------------------------------------------------------------------------
// Gowin ships its .vg netlist `pragma protect` encrypted, so we cannot simulate
// what GowinSynthesis actually produced. GHDL has its own synthesis engine, so
// this runs ascal through THAT instead and simulates the result:
//
//     ghdl synth --out=verilog ascal_gw  ->  ascal_gw_synth.v
//
// Behavioural GHDL simulation already renders the pattern pixel-exact. If the
// SYNTHESISED netlist also renders correctly, ascal's coding style survives a
// second independent inference engine (memory inference, FSM extraction, the
// lot) and the fault is specific to GowinSynthesis. If it breaks HERE, ascal
// has a latent synthesis-sensitivity that Quartus happens to tolerate - which
// would be a much more interesting result and reportable upstream.
//
// Uses the REAL mcr_testpattern.sv and ascal_avl_ddr3.sv - only the DDR3
// controller is modelled.
//
//   iverilog -g2012 -o tb_synth tb_ascal_synth.v ascal_gw_synth.v \
//            ../src/testpat/mcr_testpattern.sv ../src/ascal/ascal_avl_ddr3.sv
//-----------------------------------------------------------------------------
`timescale 1ns/1ps

module ddr3_model #(parameter LAT = 12) (
    input  wire         clk,
    output wire         cmd_ready,
    input  wire [2:0]   cmd,
    input  wire         cmd_en,
    input  wire [27:0]  addr,
    output wire         wr_data_rdy,
    input  wire [127:0] wr_data,
    input  wire         wr_data_en,
    output reg  [127:0] rd_data,
    output reg          rd_data_valid
);
    reg [127:0] ram [0:(1<<18)-1];
    reg [3:0]   cnt = 0;
    reg         rdy = 1;
    integer     i;
    // in-order read return pipeline; -1 marks an empty slot
    reg signed [31:0] pipe [0:LAT];

    initial begin
        rd_data = 0; rd_data_valid = 0;
        for (i = 0; i <= LAT; i = i + 1) pipe[i] = -1;
    end

    // refuse a command occasionally, standing in for refresh/activate
    always @(posedge clk) begin
        cnt <= cnt + 1'b1;
        rdy <= (cnt < 13);
    end
    assign cmd_ready   = rdy;
    assign wr_data_rdy = rdy;

    always @(posedge clk) begin
        rd_data_valid <= 1'b0;
        if (pipe[LAT] >= 0) begin
            rd_data       <= ram[pipe[LAT][17:0]];
            rd_data_valid <= 1'b1;
        end
        for (i = LAT; i > 0; i = i - 1) pipe[i] <= pipe[i-1];
        pipe[0] <= -1;

        if (cmd_en && rdy) begin
            if (cmd == 3'b000) begin
                if (wr_data_en) ram[addr[20:3]] <= wr_data;   // 8 addr units/word
            end else begin
                pipe[0] <= {14'd0, addr[20:3]};
            end
        end
    end
endmodule


module tb_ascal_synth;

    localparam FRAMES     = 3;    // dump this frame (iverilog is slow)
    localparam DUMP_LINES = 24;

    reg i_clk = 0, o_clk = 0, a_clk = 0;
    reg reset_na = 0, rst = 1;

    always #12.5  i_clk = ~i_clk;   // 40 MHz
    always #6.734 o_clk = ~o_clk;   // 74.25 MHz
    always #6.734 a_clk = ~a_clk;
    initial begin #200 reset_na = 1; rst = 0; end

    // ---- real pattern generator, 31 kHz 512x480 ----
    wire       ce_pix, p_hs, p_vs, p_de;
    wire [7:0] p_r, p_g, p_b;
    mcr_testpattern src (
        .clk(i_clk), .rst(~reset_na), .mode15(1'b0),
        .ce_pix(ce_pix), .r(p_r), .g(p_g), .b(p_b),
        .hs(p_hs), .vs(p_vs), .de(p_de),
        .hblank(), .vblank(), .hcnt_o(), .vcnt_o()
    );

    // ---- Avalon <-> DDR3 ----
    wire [24:0]  avl_address;
    wire         avl_write, avl_read, avl_waitrequest, avl_readdatavalid;
    wire [127:0] avl_writedata, avl_readdata;
    wire [7:0]   avl_burstcount;
    wire [15:0]  avl_byteenable;

    wire         app_rdy, app_en, app_wdf_rdy, app_wdf_wren, app_rd_data_valid;
    wire [2:0]   app_cmd;
    wire [27:0]  app_addr;
    wire [127:0] app_wdf_data, app_rd_data;

    wire [7:0] o_r, o_g, o_b;
    wire       o_hs, o_vs, o_de;

    // ---- the GHDL-SYNTHESISED ascal ----
    ascal_gw dut (
        .i_clk(i_clk), .i_ce(ce_pix),
        .i_r(p_r), .i_g(p_g), .i_b(p_b),
        .i_hs(p_hs), .i_vs(~p_vs), .i_de(p_de), .i_fl(1'b0),
        .o_clk(o_clk),
        .o_r(o_r), .o_g(o_g), .o_b(o_b),
        .o_hs(o_hs), .o_vs(o_vs), .o_de(o_de),
        .mode(5'b00010), .run(1'b1),
        .hmin(12'd160), .hmax(12'd1119), .vmin(12'd0), .vmax(12'd719),
        .i_hdmax(), .i_vdmax(),
        .iauto(1'b1), .himin(12'd0), .himax(12'd0),
        .vimin(12'd0), .vimax(12'd0),
        .dbg_o_hacc(), .dbg_o_dcpt(), .dbg_i_himax(),
        .dbg_i_hsize(), .dbg_o_ihsize(), .dbg_i_hdown(),
        .poly_clk(1'b0), .poly_a(12'd0), .poly_dw(10'd0), .poly_wr(1'b0),
        .avl_clk(a_clk), .avl_waitrequest(avl_waitrequest),
        .avl_readdata(avl_readdata), .avl_readdatavalid(avl_readdatavalid),
        .avl_burstcount(avl_burstcount), .avl_writedata(avl_writedata),
        .avl_address(avl_address), .avl_write(avl_write), .avl_read(avl_read),
        .avl_byteenable(avl_byteenable),
        .reset_na(reset_na)
    );

    ascal_avl_ddr3 #(.N_DW(128), .N_AW(25), .N_BURST(2048)) bridge (
        .clk(a_clk), .rst(rst),
        .avl_address(avl_address), .avl_write(avl_write), .avl_read(avl_read),
        .avl_writedata(avl_writedata), .avl_burstcount(avl_burstcount),
        .avl_byteenable(avl_byteenable), .avl_waitrequest(avl_waitrequest),
        .avl_readdata(avl_readdata), .avl_readdatavalid(avl_readdatavalid),
        .app_rdy(app_rdy), .app_en(app_en), .app_cmd(app_cmd), .app_addr(app_addr),
        .app_wdf_rdy(app_wdf_rdy), .app_wdf_wren(app_wdf_wren), .app_wdf_end(),
        .app_wdf_data(app_wdf_data), .app_wdf_mask(),
        .app_rd_data_valid(app_rd_data_valid), .app_rd_data(app_rd_data),
        .dbg_wr_beat(), .dbg_rd_beat()
    );

    ddr3_model ddr (
        .clk(a_clk), .cmd_ready(app_rdy), .cmd(app_cmd), .cmd_en(app_en),
        .addr(app_addr), .wr_data_rdy(app_wdf_rdy), .wr_data(app_wdf_data),
        .wr_data_en(app_wdf_wren),
        .rd_data(app_rd_data), .rd_data_valid(app_rd_data_valid)
    );

    // ---- dump one frame, same format tools/ascal_sim_check.py expects ----
    integer f, ox = 0, oy = 0, frame = 0;
    reg vs_d = 0, de_d = 0;
    initial f = $fopen("ascal_synth_out.txt", "w");

    always @(posedge o_clk) begin
        if (o_vs && !vs_d) begin frame <= frame + 1; oy <= 0; end
        vs_d <= o_vs;
        if (o_de && !de_d) ox <= 0;
        if (o_de) begin
            if (frame == FRAMES && oy < DUMP_LINES)
                $fwrite(f, "%0d %0d %02x%02x%02x\n", ox, oy, o_r, o_g, o_b);
            ox <= ox + 1;
        end
        if (!o_de && de_d) oy <= oy + 1;
        de_d <= o_de;
        if (frame > FRAMES) begin
            $fclose(f);
            $display("done");
            $finish;
        end
    end

endmodule
