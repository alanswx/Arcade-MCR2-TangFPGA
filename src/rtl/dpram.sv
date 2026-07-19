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
        // Initialised dual-port RAM: port A is the core's read port, port B
        // takes ROM downloads (SD loader). The INIT_FILE contents act as the
        // power-on default, so a bitstream still boots a baked-in game when
        // no card is present and the loader simply overwrites it when there
        // is one. Leaving we_b tied low reproduces the old ROM behaviour
        // exactly.
        initial begin
            $readmemh(INIT_FILE, ram);
        end
        always @(posedge clk_a) begin
            if (we_a) begin
                ram[addr_a] <= d_a;
            end
            q_a <= ram[addr_a];
        end
        always @(posedge clk_b) begin
            if (we_b) begin
                ram[addr_b] <= d_b;
            end
            q_b <= ram[addr_b];
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
