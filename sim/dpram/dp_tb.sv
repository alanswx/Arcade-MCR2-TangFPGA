// Check all three dpram modes actually behave as documented.
module tb;
  reg clk=0; always #5 clk=~clk;
  reg we_b=0; reg [3:0] ab=0; reg [7:0] db=0;
  reg [3:0] aa=0; wire [7:0] qa_load, qa_plain;

  dpram #(.dWidth(8), .aWidth(4), .LOADABLE(1)) u_load (
    .clk_a(clk), .we_a(1'b0), .addr_a(aa), .d_a(8'd0), .q_a(qa_load),
    .clk_b(clk), .we_b(we_b), .addr_b(ab), .d_b(db), .q_b());
  dpram #(.dWidth(8), .aWidth(4)) u_plain (
    .clk_a(clk), .we_a(1'b0), .addr_a(aa), .d_a(8'd0), .q_a(qa_plain),
    .clk_b(clk), .we_b(we_b), .addr_b(ab), .d_b(db), .q_b());

  initial begin
    @(negedge clk); we_b=1; ab=4'd5; db=8'hA7; @(negedge clk); we_b=0;
    aa=4'd5; @(negedge clk); @(negedge clk);
    $display("LOADABLE=1 port-B write -> port A reads 0x%02h (want A7) : %s",
             qa_load, (qa_load==8'hA7)?"PASS":"FAIL");
    $display("no-init/no-LOADABLE     -> port A reads 0x%02h (want not A7) : %s",
             qa_plain, (qa_plain!==8'hA7)?"PASS (port B correctly read-only)":"FAIL");
    $finish;
  end
endmodule
