// Parameterized single-port RAM.
//
// RAMSTYLE selects the implementation:
//   "block_ram"       - BSRAM (the default; every existing caller's behaviour)
//   "distributed_ram" - LUT RAM (Gowin RAM16), for arrays far smaller than an
//                       18 Kb block. A 256x8 sprite line buffer wastes a whole
//                       block in BSRAM but costs only 128 RAM16 units in logic,
//                       and the merged 3-family core has TEN of them - 10 of the
//                       118 blocks spent on 2.5 KB of storage. Read behaviour is
//                       unchanged either way: q_reg registers the output, so
//                       LUT RAM's async read still presents one cycle later.
//
// Do NOT drop the attribute and let the tool choose. Without it Gowin has
// inferred registers for small arrays, which is the worst of the three.
module gen_ram #(
    parameter dWidth = 8,
    parameter aWidth = 10,
    parameter RAMSTYLE = "block_ram"
) (
    input                 clk,
    input                 we,
    input    [aWidth-1:0] addr,
    input    [dWidth-1:0] d,
    output   [dWidth-1:0] q
);

(* syn_ramstyle = RAMSTYLE *) reg [dWidth-1:0] ram [0:(2**aWidth)-1];
reg [dWidth-1:0] q_reg;

always @(posedge clk) begin
    if (we) begin
        ram[addr] <= d;
    end
    q_reg <= ram[addr];
end
assign q = q_reg;

endmodule
