// Testbench for src/rtl/shield_io.sv against a behavioural model of the
// AS-FABBED shield chains (MCR_prototype_PCB, Sept 8 2026):
//   '165 order U1 -> U2 -> U3 -> U4 -> U6 -> U7 -> IN_DATA, U1.SER = GND
//   U1: J4-1..8 -> H..A (reversed)   U2: J4 D0..D7 -> A..H
//   U3: J5-1..8 -> A..H              U4: J6 1-7,9  -> A..H
//   U6: SW1 pos1..8 -> A..H          U7: SW2 pos1..8 -> A..H
//   '595: U8.QH' -> U9.SER
// Run: iverilog -g2012 -o tb sim/shield_io/tb_shield_io.sv src/rtl/shield_io.sv && vvp tb
`timescale 1ns/1ps
module tb;
reg clk = 0; always #12.5 clk = ~clk;
reg rst = 1;
wire in_clk, in_load_n, out_clk, out_data, out_latch, out_clear_n, out_en_n;
reg  [15:0] out_bits = 16'h0000;
wire [7:0] ip0, ip1, ip2, ip4, sw1, sw2;
wire scan_tick;

// harness / switch state (1 = idle/open)
reg [7:0] j4_ip0 = 8'hFF;   // bit k = J4 pin k+1
reg [7:0] j4_ip1 = 8'hFF;   // bit k = D(k)
reg [7:0] j5     = 8'hFF;   // bit k = J5 pin k+1
reg [7:0] j6     = 8'hFF;   // bit k = J6 D(k)
reg [7:0] s1     = 8'hFF;   // bit k = SW1 position k+1
reg [7:0] s2     = 8'hFF;

// parallel inputs per device, index = input letter A(0)..H(7)
wire [7:0] u1 = {j4_ip0[0], j4_ip0[1], j4_ip0[2], j4_ip0[3],
                 j4_ip0[4], j4_ip0[5], j4_ip0[6], j4_ip0[7]};
wire [7:0] u2 = j4_ip1, u3 = j5, u4 = j6, u6 = s1, u7 = s2;

// '165 model: PL low loads (async), CP rising shifts toward H; QH = reg[7]
reg [7:0] r1, r2, r3, r4, r6, r7;
always @(*) if (!in_load_n) begin r1 = u1; r2 = u2; r3 = u3; r4 = u4; r6 = u6; r7 = u7; end
always @(posedge in_clk) if (in_load_n) begin
    r7 <= {r7[6:0], r6[7]};
    r6 <= {r6[6:0], r4[7]};
    r4 <= {r4[6:0], r3[7]};
    r3 <= {r3[6:0], r2[7]};
    r2 <= {r2[6:0], r1[7]};
    r1 <= {r1[6:0], 1'b0};
end
wire in_data = r7[7];

// '595 model: shift on SRCLK, latch on RCLK. q[0]=QA ... q[7]=QH
reg [7:0] s8 = 0, s9 = 0, q8 = 0, q9 = 0;
always @(posedge out_clk) begin
    s9 <= {s9[6:0], s8[7]};
    s8 <= {s8[6:0], out_data};
end
always @(posedge out_latch) begin q8 <= s8; q9 <= s9; end
wire [15:0] outs = {q9, q8};

shield_io dut (.clk(clk), .rst(rst),
    .in_clk(in_clk), .in_load_n(in_load_n), .in_data(in_data),
    .out_clk(out_clk), .out_data(out_data), .out_latch(out_latch),
    .out_clear_n(out_clear_n), .out_en_n(out_en_n), .out_bits(out_bits),
    .ip0(ip0), .ip1(ip1), .ip2(ip2), .ip4(ip4), .sw1(sw1), .sw2(sw2),
    .scan_tick(scan_tick));

integer errs = 0;
task scans(input integer n); integer i; begin
    for (i = 0; i < n; i = i + 1) @(posedge scan_tick);
end endtask
task check(input [7:0] got, input [7:0] exp, input [8*8-1:0] name); begin
    if (got !== exp) begin errs = errs + 1; $display("FAIL %0s got %02h exp %02h", name, got, exp); end
end endtask

integer t;
initial begin
    repeat (10) @(posedge clk); rst = 0;
    if (out_en_n !== 1'b1) begin errs++; $display("FAIL OE active before first scan"); end
    scans(2);
    check(ip0, 8'hFF, "idle ip0"); check(sw2, 8'hFF, "idle sw2");
    for (t = 0; t < 20; t = t + 1) begin
        j4_ip0 = $random; j4_ip1 = $random; j5 = $random; j6 = $random;
        s1 = $random; s2 = $random; out_bits = $random;
        scans(3);   // one scan to sample, one to publish, one for the '595 latch
        check(ip0, j4_ip0, "ip0"); check(ip1, j4_ip1, "ip1");
        check(ip2, j5, "ip2");     check(ip4, j6, "ip4");
        check(sw1, s1, "sw1");     check(sw2, s2, "sw2");
        if (outs !== out_bits) begin errs++; $display("FAIL outs %04h exp %04h", outs, out_bits); end
    end
    if (out_en_n !== 1'b0) begin errs++; $display("FAIL OE never enabled"); end
    if (out_clear_n !== 1'b1) begin errs++; $display("FAIL SRCLR not high"); end
    if (errs == 0) $display("PASS shield_io: 20 random vectors, all six bytes + 16 outputs");
    else $display("%0d errors", errs);
    $finish;
end
endmodule
