//-----------------------------------------------------------------------------
// ddr3_top - the SAME dropout test, driven through the DDR3 framebuffer
//-----------------------------------------------------------------------------
// Matched pair with bram_top.sv. Identical source pattern, identical 1 kHz
// test tone, identical HDMI stack (ddr3_framebuffer instantiates the same
// hdl-util hdmi module internally). The ONLY difference is the framebuffer
// architecture, so any difference in dropout behaviour is attributable to it.
//
// This path contains everything bram_top.sv does without: DDR3 controller and
// its runtime-reconfigured PLL, a single shared memory port with reads
// prioritised over writes, an 8-deep write FIFO, a 32-entry prefetch buffer,
// a shadow raster on clk_x1, and a 64-deep async FIFO into hclk.
//
// Beacon: "FB c<calib> r<ddr_rst> x<..> q<..> dXX LXX"
//   c1 r0 = DDR3 trained. d = source frame counter (advances ~60/s).
//-----------------------------------------------------------------------------
`default_nettype none

module ddr3_top (
    input  wire        sys_clk,
    input  wire        s1,
    input  wire        mode15_n,

    output wire [3:0]  vga_r,
    output wire [3:0]  vga_g,
    output wire [3:0]  vga_b,
    output wire        vga_hs,
    output wire        vga_vs,

    output wire        tmds_clk_p,
    output wire        tmds_clk_n,
    output wire [2:0]  tmds_d_p,
    output wire [2:0]  tmds_d_n,
    output wire        hpd_en,

    output wire        uart_tx,
    output wire [3:0]  debug_o,

    output wire [14:0] ddr_addr,
    output wire [2:0]  ddr_bank,
    output wire        ddr_cs,
    output wire        ddr_ras,
    output wire        ddr_cas,
    output wire        ddr_we,
    output wire        ddr_ck,
    output wire        ddr_ck_n,
    output wire        ddr_cke,
    output wire        ddr_odt,
    output wire        ddr_reset_n,
    output wire [1:0]  ddr_dm,
    inout  wire [15:0] ddr_dq,
    inout  wire [1:0]  ddr_dqs,
    inout  wire [1:0]  ddr_dqs_n
);

    assign hpd_en = 1'b1;

    //-------------------------------------------------------------- clocks
    wire clk_sys, clk_p5_unused, clk50_pll, pll_lock;
    gowin_pll_mcr2 pll_inst (
        .clkin(sys_clk), .clk_sys(clk_sys),
        .clk_p5(clk_p5_unused), .clk_50(clk50_pll), .lock(pll_lock)
    );
    wire clk27;
    pll_27 pll27_inst (.clkin(sys_clk), .clkout0(clk27));

    reg [23:0] por = 0;
    always @(posedge clk_sys) if (!por[23]) por <= por + 1'b1;
    wire rst_sys = !por[23] || ~s1;

    //-------------------------------------------------- source: test pattern
    reg mode15_s1 = 0, mode15 = 0;
    always @(posedge clk_sys) begin
        mode15_s1 <= ~mode15_n;
        mode15    <= mode15_s1;
    end

    wire       ce_pix, p_hs, p_vs, p_de, p_hb, p_vb;
    wire [7:0] p_r, p_g, p_b;
    mcr_testpattern pattern (
        .clk(clk_sys), .rst(rst_sys), .mode15(mode15),
        .ce_pix(ce_pix), .r(p_r), .g(p_g), .b(p_b),
        .hs(p_hs), .vs(p_vs), .de(p_de),
        .hblank(p_hb), .vblank(p_vb), .hcnt_o(), .vcnt_o()
    );

    wire blanked = p_hb | p_vb;
    assign vga_r  = blanked ? 4'h0 : p_r[7:4];
    assign vga_g  = blanked ? 4'h0 : p_g[7:4];
    assign vga_b  = blanked ? 4'h0 : p_b[7:4];
    assign vga_hs = p_hs;
    assign vga_vs = p_vs;

    // framebuffer write stream: RGB444, one write per active source pixel
    wire [11:0] fb_data = {p_r[7:4], p_g[7:4], p_b[7:4]};
    wire        fb_we   = ce_pix & p_de;

    reg vb_r = 1'b1;
    always @(posedge clk_sys) if (ce_pix) vb_r <= p_vb;
    wire fb_vsync = p_vb & ~vb_r;      // rising edge of vblank

    //----------------------------------------------------- audio test tone
    // ddr3_framebuffer makes its own clk_audio internally, so derive the
    // sample tick here from the same 32 kHz cadence to feed the generator.
    localparam int AUDIO_RATE = 32000;
    localparam int TICK_DIV   = 40000000 / AUDIO_RATE;   // on clk_sys
    reg [$clog2(TICK_DIV)-1:0] tick_cnt = 0;
    reg audio_tick = 0;
    always @(posedge clk_sys) begin
        audio_tick <= 1'b0;
        if (tick_cnt == TICK_DIV[$clog2(TICK_DIV)-1:0] - 1) begin
            tick_cnt <= 0; audio_tick <= 1'b1;
        end else
            tick_cnt <= tick_cnt + 1'b1;
    end

    wire signed [15:0] sine_l, sine_r;
    sine_gen #(.SAMPLE_RATE(AUDIO_RATE), .TONE_HZ(1000)) tone (
        .clk(clk_sys), .sample_en(audio_tick), .left(sine_l), .right(sine_r)
    );

    //-------------------------------------------------- DDR3 framebuffer
    wire fb_clk_x1, fb_ddr_rst, fb_calib, fb_hclk;

    ddr3_framebuffer #(
        .WIDTH(512), .HEIGHT(480), .COLOR_BITS(12),
        .PREFETCH_DELAY(44), .DVI_MODE(0)
    ) fb_inst (
        .hclk_dbg(fb_hclk),
        .clk_27(clk27), .pll_lock_27(1'b1), .clk_g(clk50_pll),
        .clk_out(fb_clk_x1),
        .rst_n(por[23]),
        .ddr_rst(fb_ddr_rst),
        .init_calib_complete(fb_calib),
        .ddr_prefetch_delay(6'd44),

        .clk(clk_sys),
        .fb_width(11'd512),
        .fb_height(mode15 ? 10'd240 : 10'd480),
        .disp_width(11'd960),
        .fb_vsync(fb_vsync), .fb_we(fb_we), .fb_data(fb_data),

        .sound_left(sine_l), .sound_right(sine_r),

        .ddr_addr(ddr_addr), .ddr_bank(ddr_bank), .ddr_cs(ddr_cs),
        .ddr_ras(ddr_ras), .ddr_cas(ddr_cas), .ddr_we(ddr_we),
        .ddr_ck(ddr_ck), .ddr_ck_n(ddr_ck_n), .ddr_cke(ddr_cke),
        .ddr_odt(ddr_odt), .ddr_reset_n(ddr_reset_n), .ddr_dm(ddr_dm),
        .ddr_dq(ddr_dq), .ddr_dqs(ddr_dqs), .ddr_dqs_n(ddr_dqs_n),

        .tmds_clk_n(tmds_clk_n), .tmds_clk_p(tmds_clk_p),
        .tmds_d_n(tmds_d_n), .tmds_d_p(tmds_d_p)
    );

    //-------------------------------------------------------- diagnostics
    reg [7:0] src_frames = 0;
    reg       pvs_r = 1;
    always @(posedge clk_sys) if (ce_pix) begin
        pvs_r <= p_vs;
        if (!p_vs && pvs_r) src_frames <= src_frames + 1'b1;
    end

    reg [25:0] hb_x1 = 0;
    reg [24:0] hb_27 = 0, hb_h = 0;
    always @(posedge fb_clk_x1) hb_x1 <= hb_x1 + 1'b1;
    always @(posedge clk27)     hb_27 <= hb_27 + 1'b1;
    always @(posedge fb_hclk)   hb_h  <= hb_h + 1'b1;
    assign debug_o = {fb_ddr_rst, hb_27[24], hb_x1[25], fb_calib};

    reg calib_s1 = 0, calib_s2 = 0, ddrrst_s1 = 1, ddrrst_s2 = 1;
    reg [7:0] sf_s = 0;
    always @(posedge clk_sys) begin
        calib_s1 <= fb_calib;    calib_s2  <= calib_s1;
        ddrrst_s1 <= fb_ddr_rst; ddrrst_s2 <= ddrrst_s1;
        sf_s <= src_frames;
    end

    uart_beacon #(.CLK_HZ(40_000_000), .BAUD(115200)) beacon (
        .clk(clk_sys),
        .calib(calib_s2), .ddr_rst(ddrrst_s2),
        .cnt_x({hb_h[24:21], hb_x1[25:14]}), .cnt_q(hb_27[24:17]),
        .aux(sf_s), .aux2(8'hDD),
        .txd(uart_tx)
    );

endmodule

`default_nettype wire
