// Gowin-style DDR3 app-interface model: in-order reads, fixed latency,
// cmd_ready dropping periodically for refresh. addr counts 2-byte units,
// one command moves 16 bytes = 8 addr units.
module ddr3_model #(parameter LAT = 12, parameter STALL = 40) (
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
    // Static-source integrity check: once a location has been written, it
    // must never be written a DIFFERENT value. Any mismatch means the WRITE
    // path delivered wrong data (or to the wrong address).
    reg         wrote_flag [0:(1<<18)-1];
    integer     mism = 0, wrs = 0;
    // Explicit init. Reads-before-write must be REPRODUCIBLE, otherwise the
    // harness is not a valid oracle - the same binary produced a glitch in one
    // run and none in the next before this was pinned down.
    initial begin : initmem
        integer j;
        for (j = 0; j < (1<<18); j = j + 1) ram[j] = 128'hDEAD_BEEF_DEAD_BEEF_DEAD_BEEF_DEAD_BEEF;
    end
    initial begin : initflags
        integer k;
        for (k = 0; k < (1<<18); k = k + 1) wrote_flag[k] = 1'b0;
    end
    reg [3:0]   cnt = 0;
    reg         rdy = 1;
    reg [18:0]  pipe [0:LAT];        // bit18 = valid
    integer i;
    // Refresh-like long stalls. Without these the model answers fast enough
    // that a reader racing its own line fill always wins, so the simulation
    // happily passes designs that starve on real DDR3. tRFC is ~260 ns every
    // 7.8 us; at 74.25 MHz that is ~20 cycles every ~580, and bank conflicts
    // and write traffic make the real gaps longer still.
    reg [11:0]  rfc = 0;
    reg [7:0]   rfd = 0;
    always @(posedge clk) begin
        cnt <= cnt + 1'b1;
        rfc <= (rfc == 12'd579) ? 12'd0 : rfc + 1'b1;
        if (rfc == 12'd579) rfd <= STALL;
        else if (rfd != 0)  rfd <= rfd - 1'b1;
        rdy <= (cnt < 13) && (rfd == 0);
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
                if (wr_data_en) begin
                    wrs = wrs + 1;
                    if (wrote_flag[addr[20:3]] && ram[addr[20:3]] !== wr_data) begin
                        mism = mism + 1;
                        if (mism <= 8)
                            $display("DDR3 WRITE MISMATCH #%0d addr=%h old=%h new=%h",
                                     mism, addr[20:3], ram[addr[20:3]], wr_data);
                    end
                    if (wrs == 1 || wrs % 200000 == 0)
                        $display("DDR3 model alive: %0d writes, %0d mismatches", wrs, mism);
                    wrote_flag[addr[20:3]] <= 1'b1;
                    ram[addr[20:3]] <= wr_data;
                end
            end else begin
                pipe[0] <= {1'b1, addr[20:3]};
            end
        end
    end
    final $display("DDR3 model: %0d writes, %0d value-changing rewrites", wrs, mism);
endmodule
