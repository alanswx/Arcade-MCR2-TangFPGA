// Gowin-style DDR3 app-interface model: in-order reads, fixed latency,
// cmd_ready dropping periodically for refresh. addr counts 2-byte units,
// one command moves 16 bytes = 8 addr units.
module ddr3_model #(parameter LAT = 12) (
    input  wire         clk,
    output wire         cmd_ready,
    input  wire [2:0]   cmd,
    input  wire         cmd_en,
    input  wire [27:0]  addr,
    output wire         wr_data_rdy,
    input  wire [127:0] wr_data,
    input  wire         wr_data_en,
    output reg  [127:0] rd_data,
    output reg          rd_data_valid
);
    reg [127:0] ram [0:(1<<18)-1];
    reg [3:0]   cnt = 0;
    reg         rdy = 1;
    reg [18:0]  pipe [0:LAT];        // bit18 = valid
    integer i;
    initial begin
        rd_data = 0; rd_data_valid = 0;
        for (i = 0; i <= LAT; i = i + 1) pipe[i] = 0;
    end
    always @(posedge clk) begin
        cnt <= cnt + 1'b1;
        rdy <= (cnt < 13);
    end
    assign cmd_ready   = rdy;
    assign wr_data_rdy = rdy;
    always @(posedge clk) begin
        rd_data_valid <= 1'b0;
        if (pipe[LAT][18]) begin
            rd_data       <= ram[pipe[LAT][17:0]];
            rd_data_valid <= 1'b1;
        end
        for (i = LAT; i > 0; i = i - 1) pipe[i] <= pipe[i-1];
        pipe[0] <= 0;
        if (cmd_en && rdy) begin
            if (cmd == 3'b000) begin
                if (wr_data_en) ram[addr[20:3]] <= wr_data;
            end else begin
                pipe[0] <= {1'b1, addr[20:3]};
            end
        end
    end
endmodule
