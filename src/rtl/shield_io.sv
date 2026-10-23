// MCR shield I/O expander: the 74AHC165 input chain and the 74HC595 output
// chain on J10 (docs/shield_j10_pinout.md, docs/shield_bringup.md).
//
// Written 2026-10-22 against the AS-FABBED prototype board
// (MCR_prototype_PCB/, Mitch's "September 8 Version", commit 60363fa). The
// bit order below was traced pad-by-pad from that board's netlist, not from
// the older pin-sheet tables - see shield_bringup.md section 3 if the board
// is ever respun.
//
// Input chain: six '165s, U1 -> U2 -> U3 -> U4 -> U6 -> U7 -> IN_DATA (U1's
// SER is grounded, U7's QH is IN_DATA). After the IN_LOAD_N pulse the bits
// arrive U7.H first ... U1.A last, so after 48 shifts (MSB = first bit in):
//   sr[47:40] U7 = SW2   sr[39:32] U6 = SW1   sr[31:24] U4 = J6 (IP4)
//   sr[23:16] U3 = J5 (IP2)   sr[15:8] U2 = J4 D0-D7 (IP1)   sr[7:0] U1 = J4 1-8
// with bit i of each byte = '165 input A+i. U2/U3/U4 are wired D0 -> A, so
// those bytes ARE the SSIO port. U1 is wired J4-1 -> H ... J4-8 -> A, so IP0
// is U1's byte bit-reversed. SW1/SW2 position n -> input A+(n-1), closed = 0.
//
// Output chain: U8 -> U9 (U8.QH' -> U9.SER). Bits are shifted MSB first, so
// out_bits[15] ends up on U9.QH and out_bits[0] on U8.QA.
//
// Everything idles HIGH (the harness is pulled up to 5 V, the DIPs to 3V3),
// and IN_DATA carries an FPGA pull-up, so a console with no shield fitted
// reads all-ones: every port idle, cabinet mode off.
module shield_io #(
    parameter integer HALF = 16      // clk cycles per half shift-clock:
                                     // 40 MHz / 32 = 1.25 MHz, inside the
                                     // spec's <= 2 MHz chain budget
) (
    input             clk,
    input             rst,

    // J10 pins
    output            in_clk,
    output            in_load_n,
    input             in_data,
    output            out_clk,
    output            out_data,
    output            out_latch,
    output            out_clear_n,
    output            out_en_n,

    input      [15:0] out_bits,     // [7:0] -> U8.QA..QH, [15:8] -> U9.QA..QH

    // Decoded inputs, all raw SSIO polarity (idle = 1)
    output [7:0]  ip0,  // J4 1-8: coin1, coin2, start1, start2,
                                    //         button, tilt, service, test
    output [7:0]  ip1,  // J4 10-13,15-18
    output [7:0]  ip2,  // J5 1-8
    output [7:0]  ip4,  // J6 1-7, 9
    output [7:0]  sw1,  // game DIPs: bit n-1 = position n
    output [7:0]  sw2,  // system DIPs
    output            scan_tick  // one clk per completed scan
);

// Gowin ignores initialisers on output-reg ports (EX2478), so the power-on
// values live on internal registers: chains idle, outputs disabled, every
// decoded input idle-high until the first scan completes.
reg [7:0]  ip0_r = 8'hFF;
reg [7:0]  ip1_r = 8'hFF;
reg [7:0]  ip2_r = 8'hFF;
reg [7:0]  ip4_r = 8'hFF;
reg [7:0]  sw1_r = 8'hFF;
reg [7:0]  sw2_r = 8'hFF;
assign ip0 = ip0_r;
assign ip1 = ip1_r;
assign ip2 = ip2_r;
assign ip4 = ip4_r;
assign sw1 = sw1_r;
assign sw2 = sw2_r;
reg in_clk_r = 1'b0;
reg in_load_n_r = 1'b1;
reg out_clk_r = 1'b0;
reg out_data_r = 1'b0;
reg out_latch_r = 1'b0;
reg out_en_n_r = 1'b1;
reg scan_tick_r = 1'b0;
assign in_clk = in_clk_r;
assign in_load_n = in_load_n_r;
assign out_clk = out_clk_r;
assign out_data = out_data_r;
assign out_latch = out_latch_r;
assign out_en_n = out_en_n_r;
assign scan_tick = scan_tick_r;

// SRCLR must never float or be pulsed: R104 pulls it up, we hold it up.
assign out_clear_n = 1'b1;

reg in_d1 = 1'b1, in_d2 = 1'b1;
always @(posedge clk) begin
    in_d1 <= in_data;
    in_d2 <= in_d1;
end

reg [$clog2(HALF)-1:0] div = 0;
wire step = (div == HALF - 1);
always @(posedge clk) div <= step ? 0 : div + 1'b1;

// One state machine runs both chains in lock-step: phase 0 = load/latch,
// then 48 input bits, of which the first 16 also clock out the '595 word.
// Each bit is two steps: clock low (sample/present data), clock high.
reg [6:0]  bitn  = 0;
reg        half  = 1'b0;      // 0 = clock-low half, 1 = clock-high half
reg        loadp = 1'b1;      // in the load phase
reg [47:0] sr    = {48{1'b1}};
reg [15:0] osr   = 16'd0;
reg        first_done = 1'b0;

function [7:0] rev8(input [7:0] v);
    rev8 = {v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7]};
endfunction

always @(posedge clk) begin
    scan_tick_r <= 1'b0;
    if (rst) begin
        in_clk_r <= 1'b0; in_load_n_r <= 1'b1;
        out_clk_r <= 1'b0; out_latch_r <= 1'b0; out_en_n_r <= 1'b1;
        bitn <= 0; half <= 1'b0; loadp <= 1'b1; first_done <= 1'b0;
    end else if (step) begin
        if (loadp) begin
            // half 0: PL low (parallel load) and RCLK high (latch the word
            // shifted during the previous scan); half 1: release both.
            if (!half) begin
                in_clk_r    <= 1'b0;
                out_clk_r   <= 1'b0;
                in_load_n_r <= 1'b0;
                out_latch_r <= first_done;
                half      <= 1'b1;
            end else begin
                in_load_n_r <= 1'b1;
                out_latch_r <= 1'b0;
                if (first_done) out_en_n_r <= 1'b0;   // outputs now hold real data
                osr       <= out_bits;
                half      <= 1'b0;
                loadp     <= 1'b0;
                bitn      <= 0;
            end
        end else if (!half) begin
            // clock low: QH is stable (it changed on the last rising edge,
            // a whole half-period ago) - sample it, present the next '595 bit
            in_clk_r   <= 1'b0;
            out_clk_r  <= 1'b0;
            sr       <= {sr[46:0], in_d2};
            out_data_r <= osr[15];
            half     <= 1'b1;
        end else begin
            in_clk_r  <= 1'b1;
            if (bitn < 16) begin
                out_clk_r <= 1'b1;
                osr     <= {osr[14:0], 1'b0};
            end
            half <= 1'b0;
            if (bitn == 47) begin
                loadp      <= 1'b1;
                first_done <= 1'b1;
            end else
                bitn <= bitn + 1'b1;
        end
    end

    // Publish a completed scan (sr is complete on the step after bit 47's
    // sample; loadp has just gone high and nothing shifts until bit 0).
    if (step && loadp && !half && !rst) begin
        sw2_r <= sr[47:40];
        sw1_r <= sr[39:32];
        ip4_r <= sr[31:24];
        ip2_r <= sr[23:16];
        ip1_r <= sr[15:8];
        ip0_r <= rev8(sr[7:0]);
        scan_tick_r <= 1'b1;
    end
end

endmodule
