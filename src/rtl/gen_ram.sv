// Parameterized Single-Port RAM with automatic BSRAM block inference
// Explicitly mapped to block RAM to fit within constraints and avoid distributed RAM warnings.
module gen_ram #(
    parameter dWidth = 8,
    parameter aWidth = 10
) (
    input                 clk,
    input                 we,
    input    [aWidth-1:0] addr,
    input    [dWidth-1:0] d,
    output   [dWidth-1:0] q
);

(* syn_ramstyle = "block_ram" *) reg [dWidth-1:0] ram [0:(2**aWidth)-1];
reg [dWidth-1:0] q_reg;

always @(posedge clk) begin
    if (we) begin
        ram[addr] <= d;
    end
    q_reg <= ram[addr];
end
assign q = q_reg;

endmodule
