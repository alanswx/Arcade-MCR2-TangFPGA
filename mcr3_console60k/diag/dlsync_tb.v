// Model the MCR-3 top's dl -> SDRAM port2 sprite write path.
// Reproduces the byte-shift and checks the fix, for both the OLD (address from
// _s2, data live) and NEW (everything from _s2) wiring.
`timescale 1ns/1ps
module tb;
  reg clk_sdram = 0;               // 80 MHz

  always #6.25 clk_sdram = ~clk_sdram;


  // --- loader (clk_sys): one byte every BYTE_GAP clk_sys cycles ---
  parameter BYTE_GAP = 8;
  reg [16:0] dl_addr = 0;
  reg [7:0]  dl_data = 0;
  reg        dl_wr   = 0;
  integer    gap = 0, nbytes = 0;
  reg [7:0]  blob [0:255];
  integer k;
  initial for (k = 0; k < 256; k = k + 1) blob[k] = k;   // blob[j] = j

  always @(posedge clk_sys_real) begin
    dl_wr <= 1'b0;
    if (nbytes < 32) begin
      if (gap == 0) begin
        dl_addr <= nbytes;
        dl_data <= blob[nbytes];
        dl_wr   <= 1'b1;
        nbytes  <= nbytes + 1;
        gap     <= BYTE_GAP - 1;
      end else gap <= gap - 1;
    end
  end

  // real clk_sys: divide clk_sdram by 2 with aligned posedges
  reg clk_sys_real = 0;
  always @(posedge clk_sdram) clk_sys_real <= ~clk_sys_real;

  // --- clk_sdram side ---
  reg        dl_wr_s1 = 0, dl_wr_s2 = 0;
  reg [16:0] dl_off_s1 = 0, dl_off_s2 = 0;
  reg [7:0]  dl_data_s1 = 0, dl_data_s2 = 0;
  reg [7:0]  mem_old [0:255];
  reg [7:0]  mem_new [0:255];
  integer    w_old = 0, w_new = 0;

  always @(posedge clk_sdram) begin
    dl_wr_s1   <= dl_wr;    dl_wr_s2   <= dl_wr_s1;
    dl_off_s1  <= dl_addr;  dl_off_s2  <= dl_off_s1;
    dl_data_s1 <= dl_data;  dl_data_s2 <= dl_data_s1;
    if (dl_wr_s1 && !dl_wr_s2) begin
      mem_old[dl_off_s2] <= dl_data;      // BUGGY: addr from _s2, data LIVE
      mem_new[dl_off_s2] <= dl_data_s2;   // FIXED: both from _s2
      w_old = w_old + 1; w_new = w_new + 1;
    end
  end

  integer i, bad_old = 0, bad_new = 0;
  initial begin
    for (i = 0; i < 256; i = i + 1) begin mem_old[i] = 8'hxx; mem_new[i] = 8'hxx; end
    #20000;
    $display("writes issued: %0d", w_old);
    for (i = 1; i < 30; i = i + 1) begin      // skip i=0 (no predecessor byte)
      if (mem_old[i] !== blob[i]) begin
        bad_old = bad_old + 1;
        if (bad_old <= 3) $display("  OLD mem[%0d] = %0d (blob[%0d]=%0d, blob[i+1]=%0d)",
                                   i, mem_old[i], i, blob[i], blob[i+1]);
      end
      if (mem_new[i] !== blob[i]) begin
        bad_new = bad_new + 1;
        if (bad_new <= 3) $display("  NEW mem[%0d] = %0d (expected %0d)", i, mem_new[i], blob[i]);
      end
    end
    $display("OLD wiring mismatches: %0d", bad_old);
    $display("NEW wiring mismatches: %0d", bad_new);
    $finish;
  end
endmodule
