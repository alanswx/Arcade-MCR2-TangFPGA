// Parameterized Dual-Port RAM / ROM wrapper optimized for Gowin BSRAM block inference
module dpram #(
    parameter dWidth = 8,
    parameter aWidth = 10,
    parameter INIT_FILE = ""
) (
    input                     clk_a,
    input                     we_a,
    input      [aWidth-1:0]   addr_a,
    input      [dWidth-1:0]   d_a,
    output reg [dWidth-1:0]   q_a,

    input                     clk_b,
    input                     we_b,
    input      [aWidth-1:0]   addr_b,
    input      [dWidth-1:0]   d_b,
    output reg [dWidth-1:0]   q_b
);

(* syn_ramstyle = "block_ram" *) reg [dWidth-1:0] ram [0:(2**aWidth)-1];

generate
    if (INIT_FILE != "") begin: rom_mode
        // Single-Port ROM mode (Only Port A is read to guarantee BSRAM inference on Gowin)
        initial begin
            $readmemh(INIT_FILE, ram);
        end
        always @(posedge clk_a) begin
            q_a <= ram[addr_a];
        end
        // Port B is completely unused, return 0 to prevent warnings or synthesis floating wires
        always @(*) begin
            q_b = {dWidth{1'b0}};
        end
    end else begin: ram_mode
        // Simple Dual-Port RAM mode (Writes only on Port A to ensure clean BSRAM inference)
        always @(posedge clk_a) begin
            if (we_a) begin
                ram[addr_a] <= d_a;
            end
            q_a <= ram[addr_a];
        end
        always @(posedge clk_b) begin
            q_b <= ram[addr_b];
        end
    end
endgenerate

endmodule
