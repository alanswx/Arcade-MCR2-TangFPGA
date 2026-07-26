//-----------------------------------------------------------------------------
// avl_ddr3_memtest - exercise ascal_avl_ddr3 the way ascal does, with no ascal
//-----------------------------------------------------------------------------
// WHY THIS EXISTS.  Three GHDL simulations (ideal memory; bridge + DDR3 model
// at 12-cycle latency; bridge + DDR3 model at 40-cycle latency with 50%
// backpressure) all render the test pattern pixel-exact, while the same RTL on
// real silicon renders it 4x too narrow and repeated every 512 output pixels.
// So either GowinSynthesis miscompiles ascal, or the real DDR3 controller
// deviates from the app-interface contract the model assumes.
//
// This module settles that.  It speaks the SAME Avalon-MM burst protocol ascal
// does, into the SAME bridge and the SAME controller, but writes a known
// pattern and reads it back.  No scaler, no video, nothing to misinterpret:
//   errors = 0  -> the Avalon/DDR3 path is sound, and the fault is Gowin's
//                  compilation of ascal itself.
//   errors > 0  -> the memory path is broken and this is the bug, now
//                  reproducible in a few hundred lines instead of a scaler.
//
// Protocol, matching ascal's `Avaloir` process exactly:
//   WRITE - hold avl_write for the whole burst, address presented once, one
//           word consumed per cycle that waitrequest is low, BLEN times.
//   READ  - hold avl_read until ONE cycle of waitrequest low, then collect
//           BLEN words as readdatavalid arrives.
//-----------------------------------------------------------------------------
`default_nettype none

module avl_ddr3_memtest #(
    parameter N_DW    = 128,
    parameter N_AW    = 25,
    parameter N_BURST = 2048,
    parameter BLEN    = N_BURST/N_DW*8,   // words per burst
    parameter BURSTS  = 256               // bursts per pass
)(
    input  wire                 clk,
    input  wire                 rst,

    output reg  [N_AW-1:0]      avl_address = 0,
    output reg                  avl_write = 0,
    output reg                  avl_read = 0,
    output wire [N_DW-1:0]      avl_writedata,
    output wire [7:0]           avl_burstcount,
    output wire [N_DW/8-1:0]    avl_byteenable,
    input  wire                 avl_waitrequest,
    input  wire [N_DW-1:0]      avl_readdata,
    input  wire                 avl_readdatavalid,

    output reg  [7:0]           err_cnt = 0,   // saturating
    output reg  [6:0]           pass_cnt = 0,
    output reg                  running = 0
);

    assign avl_burstcount = BLEN[7:0];
    assign avl_byteenable = {(N_DW/8){1'b1}};

    localparam S_IDLE = 3'd0, S_WR = 3'd1, S_WRWAIT = 3'd2,
               S_RD = 3'd3, S_RDDATA = 3'd4, S_DONE = 3'd5;

    reg [2:0]  state = S_IDLE;
    reg [15:0] burst = 0;      // which burst of this pass
    reg [7:0]  beat  = 0;      // word within the burst
    reg [7:0]  rbeat = 0;

    // Word payload is a pure function of its global word index, so a wrong
    // ADDRESS shows up as a mismatch just as loudly as wrong DATA - which is
    // exactly the failure mode matching word counts could not have caught.
    wire [24:0] widx_w = {burst[15:0], 9'd0} + {17'd0, beat};
    wire [24:0] widx_r = {burst[15:0], 9'd0} + {17'd0, rbeat};
    function [N_DW-1:0] payload(input [24:0] i);
        payload = { ~i[24:0], 39'h5A5A5A5A5A,
                     i[24:0], 39'hA5A5A5A5A5 };
    endfunction

    assign avl_writedata = payload(widx_w);

    always @(posedge clk) begin
        if (rst) begin
            state <= S_IDLE; burst <= 0; beat <= 0; rbeat <= 0;
            avl_write <= 0; avl_read <= 0; err_cnt <= 0;
            pass_cnt <= 0; running <= 0;
        end else begin
            case (state)
                S_IDLE: begin
                    running     <= 1;
                    burst       <= 0;
                    avl_address <= 0;
                    beat        <= 0;
                    avl_write   <= 1;
                    state       <= S_WR;
                end

                // ---- write one burst ----
                S_WR: begin
                    if (!avl_waitrequest) begin
                        if (beat == BLEN-1) begin
                            avl_write <= 0;
                            beat      <= 0;
                            state     <= S_WRWAIT;
                        end else begin
                            beat <= beat + 1'b1;
                        end
                    end
                end

                S_WRWAIT: begin
                    if (burst == BURSTS-1) begin
                        // all written: start reading back from the top
                        burst       <= 0;
                        avl_address <= 0;
                        rbeat       <= 0;
                        avl_read    <= 1;
                        state       <= S_RD;
                    end else begin
                        burst       <= burst + 1'b1;
                        avl_address <= avl_address + BLEN;
                        avl_write   <= 1;
                        state       <= S_WR;
                    end
                end

                // ---- read one burst back ----
                S_RD: begin
                    if (!avl_waitrequest) begin
                        avl_read <= 0;
                        state    <= S_RDDATA;
                    end
                end

                S_RDDATA: begin
                    if (avl_readdatavalid) begin
                        if (avl_readdata !== payload(widx_r) &&
                            err_cnt != 8'hFF)
                            err_cnt <= err_cnt + 1'b1;
                        if (rbeat == BLEN-1) begin
                            rbeat <= 0;
                            if (burst == BURSTS-1) begin
                                pass_cnt <= pass_cnt + 1'b1;
                                state    <= S_IDLE;   // loop forever
                            end else begin
                                burst       <= burst + 1'b1;
                                avl_address <= avl_address + BLEN;
                                avl_read    <= 1;
                                state       <= S_RD;
                            end
                        end else begin
                            rbeat <= rbeat + 1'b1;
                        end
                    end
                end

                default: state <= S_IDLE;
            endcase
        end
    end

endmodule

`default_nettype wire
