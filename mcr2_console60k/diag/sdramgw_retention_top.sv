// Retention harness x OUR sdram_gw x 225-degree pin clock (2026-07-24).
// The nand2mario controller retains perfectly with the 225-deg discipline;
// sdram_gw at 0-deg loses everything in ~30-100s. Same harness, our
// controller, snestang's phase: if this passes, MCR-3 sprites are fixed by
// one PLL output. Beacon: FB c<lock> r<busy-ish> x<errs> q<pass> d.. L..
module sdramgw_retention_top (
    input        sys_clk,
    input        s1,
    output [3:0] debug_o,
    output       uart_tx,
    inout [15:0] O_sdram_dq_io,
    output [12:0] O_sdram_addr,
    output [1:0]  O_sdram_ba,
    output [1:0]  O_sdram_dqm,
    output        O_sdram_clk,
    output        O_sdram_cs_n,
    output        O_sdram_wen_n,
    output        O_sdram_ras_n,
    output        O_sdram_cas_n
);

wire clk80, clk80_p, pll_locked;
gowin_pll_ret80 pll (.clkin(sys_clk), .fclk(clk80), .fclk_p(clk80_p), .lock(pll_locked));

reg [7:0] rst_cnt = 8'hFF;
always @(posedge clk80) begin
    if (!pll_locked) rst_cnt <= 8'hFF;
    else if (rst_cnt != 0) rst_cnt <= rst_cnt - 8'd1;
end
wire resetn = (rst_cnt == 0);

reg         p2_req = 0, p2_we = 0;
wire        p2_ack;
reg  [23:1] p2_a = 0;
reg  [15:0] p2_d = 0;
wire [31:0] p2_q;

sdram_gw #(.RFRSH_CYCLES(10'd600)) sdram (
    .SDRAM_DQ(O_sdram_dq_io), .SDRAM_A(O_sdram_addr),
    .SDRAM_DQML(O_sdram_dqm[0]), .SDRAM_DQMH(O_sdram_dqm[1]),
    .SDRAM_BA(O_sdram_ba), .SDRAM_nCS(O_sdram_cs_n), .SDRAM_nWE(O_sdram_wen_n),
    .SDRAM_nRAS(O_sdram_ras_n), .SDRAM_nCAS(O_sdram_cas_n), .SDRAM_CKE(),
    .SDRAM_CLK(O_sdram_clk),
    .init_n(resetn),
    .clk(clk80), .clk_fwd(clk80_p),        // <-- THE EXPERIMENT: 225-deg pin clock
    .port1_req(1'b0), .port1_ack(), .port1_we(1'b0), .port1_a(23'd0),
    .port1_ds(2'b00), .port1_d(16'd0), .port1_q(),
    .cpu1_addr(23'd0), .cpu1_q(), .cpu2_addr(23'd0), .cpu2_q(),
    .cpu3_addr(23'd0), .cpu3_q(),
    .port2_req(p2_req), .port2_ack(p2_ack), .port2_we(p2_we),
    .port2_a(p2_a), .port2_ds(2'b11), .port2_d(p2_d), .port2_q(p2_q),
    .sp_addr(22'd0), .sp_q(),
    .dbg_refresh(), .dbg_blk0(), .dbg_blk1()
);

function [15:0] pat(input [11:0] i);
    pat = {i, 4'h5} ^ 16'hA5C3;
endfunction

localparam S_WAIT=0, S_WR=1, S_WR_ACK=2, S_IDLE=3, S_RD=4, S_RD_ACK=5, S_DONE=6;
reg [2:0]  st = S_WAIT;
reg [11:0] widx = 0;
reg [31:0] boot_wait = 0;
reg [30:0] idle_cnt = 0;
reg [15:0] errs = 0, errs_l = 16'hFFFF;
reg [7:0]  pass_n = 0, firstbad = 0;
localparam [30:0] IDLE_CYCLES = 31'd2_400_000_000;  // 30 s @80MHz

always @(posedge clk80) begin
    if (!resetn) begin
        st <= S_WAIT; widx <= 0; pass_n <= 0; errs_l <= 16'hFFFF;
        p2_req <= 0; boot_wait <= 0;
    end else case (st)
    S_WAIT: begin
        boot_wait <= boot_wait + 1;             // sdram_gw's init is time-based
        if (boot_wait == 32'd8_000_000) begin widx <= 0; st <= S_WR; end  // 100ms
    end
    S_WR: begin
        p2_a   <= {11'd0, widx};
        p2_d   <= pat(widx);
        p2_we  <= 1'b1;
        p2_req <= ~p2_req;
        st <= S_WR_ACK;
    end
    S_WR_ACK: if (p2_ack == p2_req) begin
        if (widx == 12'hFFF) begin idle_cnt <= 0; st <= S_IDLE; end
        else begin widx <= widx + 12'd1; st <= S_WR; end
    end
    S_IDLE: begin
        idle_cnt <= idle_cnt + 31'd1;
        if (idle_cnt == IDLE_CYCLES) begin
            widx <= 0; errs <= 0; firstbad <= 0; st <= S_RD;
        end
    end
    S_RD: begin
        p2_a   <= {11'd0, widx};                // even addresses; 32-bit reads
        p2_we  <= 1'b0;
        p2_req <= ~p2_req;
        st <= S_RD_ACK;
    end
    S_RD_ACK: if (p2_ack == p2_req) begin
        // port2 read: ack toggles AT data commit (READ1b) - no settle race.
        // 32-bit result covers the column pair {widx|1, widx&~1}.
        if (p2_q != {pat(widx | 12'd1), pat(widx & ~12'd1)}) begin
            errs <= errs + 16'd1;
            if (errs == 0) firstbad <= p2_q[15:8];
        end
        if (widx >= 12'hFFE) st <= S_DONE;
        else begin widx <= widx + 12'd2; st <= S_RD; end
    end
    S_DONE: begin
        errs_l <= errs;
        pass_n <= pass_n + 8'd1;
        idle_cnt <= 0;
        st <= S_IDLE;
    end
    endcase
end

assign debug_o = {pll_locked, resetn, st[1:0]};

uart_beacon #(.CLK_HZ(50_000_000), .BAUD(115200)) beacon (
    .clk(sys_clk),
    .calib(pll_locked),
    .ddr_rst(st == S_IDLE),
    .cnt_x(errs_l),
    .cnt_q(pass_n),
    .aux(firstbad),
    .aux2({pll_locked, 1'b0, st, 3'b010}),   // marker: build C (pure upstream + 225deg)
    .txd(uart_tx)
);

endmodule
