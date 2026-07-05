// Dual-Port RAM with optional initialization file
module dpram_init #(
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

reg [dWidth-1:0] ram [0:(2**aWidth)-1];

initial begin
    if (INIT_FILE != "") begin
        $readmemh(INIT_FILE, ram);
    end
end

always @(posedge clk_a) begin
    if (we_a) begin
        ram[addr_a] <= d_a;
        q_a         <= d_a;
    end else begin
        q_a         <= ram[addr_a];
    end
end

always @(posedge clk_b) begin
    if (we_b) begin
        ram[addr_b] <= d_b;
        q_b         <= d_b;
    end else begin
        q_b         <= ram[addr_b];
    end
end

endmodule
