// SDRAM RETENTION experiment (2026-07-24).
//
// Question: does nand2mario's KNOWN-GOOD controller (snestang sdram_cl2_2ch,
// written for exactly this Tang SDRAM module / Winbond W9825G6KH) retain
// data across long IDLE periods on our board, where our MiSTer-derived
// sdram_gw loses everything within ~30-100s?
//
//   YES (errors stay 0 across passes)  -> the module is FINE and sdram_gw's
//        usage/clocking is at fault; adopt this controller/arrangement.
//   NO  (errors climb with age)        -> module/hardware confirmed bad.
//
// Test: write 4096 words once, then every ~30s read all back and count
// mismatches. UART beacon line (115200 on U15):
//   FB c<busy> r<state> x<err count last pass> q<pass#> d<first-bad-hi> L5E
module sdram_retention_top (
    input        sys_clk,      // 50 MHz V22
    input        s1,           // AA13 active-low key: reset
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

wire fclk, fclk_p, pll_locked;
gowin_pll_sneslike pll (.clkin(sys_clk), .fclk(fclk), .fclk_p(fclk_p), .lock(pll_locked));

// snestang's arrangement verbatim: the pin clock is the shifted PLL output
assign O_sdram_clk = fclk_p;

// power-on + key reset
reg [7:0] rst_cnt = 8'hFF;
always @(posedge fclk) begin
    if (!pll_locked || !s1 == 1'b1 && 1'b0) rst_cnt <= 8'hFF;   // key unused; keep it simple
    else if (rst_cnt != 0) rst_cnt <= rst_cnt - 8'd1;
end
wire resetn = (rst_cnt == 0);

// clkref = fclk/6 square wave (posedge every 6 fclk), per the controller doc
reg [2:0] cref_div = 0;
reg clkref = 0;
always @(posedge fclk) begin
    if (cref_div == 3'd2) begin cref_div <= 0; clkref <= ~clkref; end
    else cref_div <= cref_div + 3'd1;
end

// controller (vendored, unmodified)
wire        busy;
reg  [15:0] cpu_din;
reg  [22:1] cpu_addr;
reg         cpu_req = 0, cpu_we;
wire        cpu_req_ack;
wire [15:0] cpu_port0, cpu_port1;

sdram_snes #(.FREQ(65_000_000)) sdram (
    .SDRAM_DQ(O_sdram_dq_io), .SDRAM_A(O_sdram_addr), .SDRAM_DQM(O_sdram_dqm),
    .SDRAM_BA(O_sdram_ba), .SDRAM_nCS(O_sdram_cs_n), .SDRAM_nWE(O_sdram_wen_n),
    .SDRAM_nRAS(O_sdram_ras_n), .SDRAM_nCAS(O_sdram_cas_n), .SDRAM_CKE(),

    .clk(fclk), .mclk(1'b0), .clkref(clkref), .resetn(resetn), .busy(busy),

    .cpu_din(cpu_din), .cpu_port(1'b0), .cpu_port0(cpu_port0), .cpu_port1(cpu_port1),
    .cpu_addr(cpu_addr), .cpu_req(cpu_req), .cpu_req_ack(cpu_req_ack),
    .cpu_we(cpu_we), .cpu_ds(2'b11),

    .bsram_addr(20'd0), .bsram_din(8'd0), .bsram_dout(),
    .bsram_req(1'b0), .bsram_req_ack(), .bsram_we(1'b0),

    .aram_16(1'b0), .aram_addr(16'd0), .aram_din(16'd0), .aram_dout(),
    .aram_req(1'b0), .aram_req_ack(), .aram_we(1'b0),

    .rv_addr(22'd0), .rv_din(16'd0), .rv_ds(2'b00), .rv_dout(),
    .rv_req(1'b0), .rv_req_ack(), .rv_we(1'b0),

    .total_refresh()
);

function [15:0] pat(input [11:0] i);
    pat = {i, 4'h5} ^ 16'hA5C3;
endfunction

// test FSM
localparam S_WAIT = 0, S_WR = 1, S_WR_ACK = 2, S_IDLE = 3,
           S_RD = 4, S_RD_ACK = 5, S_DONE_PASS = 6, S_RD_SETTLE = 7;
reg [2:0]  st = S_WAIT;
reg [3:0]  settle = 0;
reg [11:0] widx = 0;
reg [30:0] idle_cnt = 0;
reg [15:0] errs = 0, errs_l = 16'hFFFF;
reg [7:0]  pass_n = 0;
reg [7:0]  firstbad = 0;
localparam [30:0] IDLE_CYCLES = 31'd1_950_000_000;  // 30 s @65MHz

always @(posedge fclk) begin
    if (!resetn) begin
        st <= S_WAIT; widx <= 0; pass_n <= 0; errs_l <= 16'hFFFF; cpu_req <= 0;
    end else case (st)
    S_WAIT: if (!busy) begin widx <= 0; st <= S_WR; end
    S_WR: begin
        cpu_addr <= {10'd0, widx};      // bank 0, word addresses 0..4095
        cpu_din  <= pat(widx);
        cpu_we   <= 1'b1;
        cpu_req  <= ~cpu_req;
        st <= S_WR_ACK;
    end
    S_WR_ACK: if (cpu_req_ack == cpu_req) begin
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
        cpu_addr <= {10'd0, widx};
        cpu_we   <= 1'b0;
        cpu_req  <= ~cpu_req;
        st <= S_RD_ACK;
    end
    S_RD_ACK: if (cpu_req_ack == cpu_req) begin
        settle <= 4'd10;                 // ack = request ACCEPTED; data lands
        st <= S_RD_SETTLE;               // in cpu_port0 ~5 cycles later
    end
    S_RD_SETTLE: begin
        settle <= settle - 4'd1;
        if (settle == 0) begin
        if (cpu_port0 != pat(widx)) begin
            errs <= errs + 16'd1;
            if (errs == 0) firstbad <= cpu_port0[15:8];
        end
        if (widx == 12'hFFF) st <= S_DONE_PASS;
        else begin widx <= widx + 12'd1; st <= S_RD; end
        end
    end
    S_DONE_PASS: begin
        errs_l <= errs;
        pass_n <= pass_n + 8'd1;
        idle_cnt <= 0;
        st <= S_IDLE;
    end
    endcase
end

assign debug_o = {pll_locked, busy, st[1:0]};

// Beacon on the RAW 50 MHz pin clock so it reports even if the PLL is dead
// (first bring-up of this build was silent - diagnose from the beacon).
// aux2: {5E marker high nibble is replaced} -> {1'lock,1'busy,st[2:0],3'b0}? no:
// keep L = {pll_locked, busy, st[2:0], 3'b101} readable by eye.
uart_beacon #(.CLK_HZ(50_000_000), .BAUD(115200)) beacon (
    .clk(sys_clk),
    .calib(pll_locked),
    .ddr_rst(busy),
    .cnt_x(errs_l),
    .cnt_q(pass_n),
    .aux(firstbad),
    .aux2({pll_locked, busy, st, 3'b110}),
    .txd(uart_tx)
);

endmodule
