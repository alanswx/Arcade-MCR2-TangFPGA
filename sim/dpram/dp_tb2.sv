module tb;
  reg clk=0; always #5 clk=~clk;
  reg [1:0] aa=0; wire [7:0] qa; reg we_b=0; reg [1:0] ab=0; reg [7:0] db=0;
  dpram #(.dWidth(8), .aWidth(2), .INIT_FILE("init4.hex")) u (
    .clk_a(clk), .we_a(1'b0), .addr_a(aa), .d_a(8'd0), .q_a(qa),
    .clk_b(clk), .we_b(we_b), .addr_b(ab), .d_b(db), .q_b());
  initial begin
    aa=2'd2; @(negedge clk); @(negedge clk);
    $display("INIT_FILE preload    -> mem[2]=0x%02h (want 33) : %s", qa, (qa==8'h33)?"PASS":"FAIL");
    @(negedge clk); we_b=1; ab=2'd2; db=8'h99; @(negedge clk); we_b=0;
    @(negedge clk); @(negedge clk);
    $display("SD overwrite of bake -> mem[2]=0x%02h (want 99) : %s", qa, (qa==8'h99)?"PASS":"FAIL");
    $finish;
  end
endmodule
