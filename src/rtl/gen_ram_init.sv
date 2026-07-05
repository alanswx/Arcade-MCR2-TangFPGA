// Single-Port RAM with optional distributed/shadow RAM implementation
module gen_ram_init #(
    parameter dWidth = 8,
    parameter aWidth = 10,
    parameter DISTRIBUTED = 0
) (
    input                     clk,
    input                     we,
    input      [aWidth-1:0]   addr,
    input      [dWidth-1:0]   d,
    output reg [dWidth-1:0]   q
);

if (DISTRIBUTED) begin
    (* ram_style = "distributed" *) reg [dWidth-1:0] ram [0:(2**aWidth)-1];
    always @(posedge clk) begin
        if (we) begin
            ram[addr] <= d;
            q         <= d;
        end else begin
            q         <= ram[addr];
        end
    end
end else begin
    reg [dWidth-1:0] ram [0:(2**aWidth)-1];
    always @(posedge clk) begin
        if (we) begin
            ram[addr] <= d;
            q         <= d;
        end else begin
            q         <= ram[addr];
        end
    end
end

endmodule
