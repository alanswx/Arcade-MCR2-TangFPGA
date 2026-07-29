//-----------------------------------------------------------------------------
// bram_top - video dropout test rig, nestang architecture (on-chip framebuffer)
//-----------------------------------------------------------------------------
// One of a matched pair. This one stores the frame in BRAM, exactly as
// nand2mario's nes2hdmi.sv does; ddr3_top.sv is the identical test driven
// through the gbatang DDR3 framebuffer instead. Same source pattern, same
// test tone, same HDMI stack - so any difference in dropout behaviour is
// attributable to the framebuffer architecture and nothing else.
//
// What this build does NOT contain, compared to the DDR3 one:
//   no DDR3 controller, no DDR3 PLL, no mDRP reconfiguration, no Avalon or
//   app-interface arbitration, no write FIFO, no prefetch buffer, no shadow
//   raster, no clk_x1 domain, and no async FIFO into hclk.
// The entire video path is: pattern (clk_sys) -> dual-port BRAM -> hdmi (hclk).
//
// Clocks (3 PLLAs):
//   50 MHz pad -> gowin_pll_mcr2 -> clk_sys 40 MHz  (pattern generator)
//   50 MHz pad -> pll_27         -> 27 MHz
//   27 MHz     -> gowin_pll_hdmi -> 371.25 MHz -> CLKDIV/5 -> hclk 74.25 MHz
//
// UART beacon on U15 @115200: "FB c0 r0 x<hclk cnt> q<27M cnt> dXX LXX"
//   d = frame counter (advances = raster alive)
//   L = source frame counter (advances = pattern generator alive)
//-----------------------------------------------------------------------------
`default_nettype none

module bram_top (
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
    output wire [3:0]  debug_o
);

    assign hpd_en = 1'b1;

    //-------------------------------------------------------------- clocks
    wire clk_sys, clk_p5_unused, clk50_unused, pll_lock;
    gowin_pll_mcr2 pll_inst (
        .clkin(sys_clk), .clk_sys(clk_sys),
        .clk_p5(clk_p5_unused), .clk_50(clk50_unused), .lock(pll_lock)
    );

    wire clk27;
    pll_27 pll27_inst (.clkin(sys_clk), .clkout0(clk27));

    reg [23:0] por = 0;
    always @(posedge clk_sys) if (!por[23]) por <= por + 1'b1;
    wire rst_sys = !por[23] || ~s1;

    wire hclk5, hclk;
    gowin_pll_hdmi pll_hdmi27_inst (.clkin(clk27), .clkout(hclk5), .lock());
    CLKDIV #(.DIV_MODE(5)) hclk_div (
        .CLKOUT(hclk), .HCLKIN(hclk5), .RESETN(por[23]), .CALIB(1'b0)
    );

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

    // analog RGB carries the source at its native timing, as before
    wire blanked = p_hb | p_vb;
    assign vga_r  = blanked ? 4'h0 : p_r[7:4];
    assign vga_g  = blanked ? 4'h0 : p_g[7:4];
    assign vga_b  = blanked ? 4'h0 : p_b[7:4];
    assign vga_hs = p_hs;
    assign vga_vs = p_vs;

    //------------------------------------------------------- HDMI raster
    wire [10:0] cx;
    wire [9:0]  cy;
    wire [23:0] rgb;

    bram_scaler #(
        .WIDTH(512), .HEIGHT(480), .CBITS(2),   // RGB222 -> 90 BSRAM blocks
        .DISP_WIDTH(960), .OUT_WIDTH(1280), .OUT_HEIGHT(720)
    ) scaler (
        .wr_clk(clk_sys), .wr_en(ce_pix),
        .wr_r(p_r), .wr_g(p_g), .wr_b(p_b),
        .wr_hsync_n(p_hs), .wr_vsync_n(p_vs), .wr_active(p_de),
        .rd_clk(hclk), .cx(cx), .cy(cy), .rgb(rgb)
    );

    //----------------------------------------------------- audio test tone
    localparam int AUDIO_RATE = 32000;
    localparam int AUDIO_CLK_DELAY = 74250000 / AUDIO_RATE / 2;
    reg [$clog2(AUDIO_CLK_DELAY)-1:0] audio_divider = 0;
    reg clk_audio = 0;
    reg audio_tick = 0;
    always @(posedge hclk) begin
        audio_tick <= 1'b0;
        if (audio_divider != AUDIO_CLK_DELAY[$clog2(AUDIO_CLK_DELAY)-1:0] - 1)
            audio_divider <= audio_divider + 1'b1;
        else begin
            audio_divider <= 0;
            clk_audio  <= ~clk_audio;
            audio_tick <= ~clk_audio;   // one pulse per rising edge
        end
    end

    wire signed [15:0] sine_l, sine_r;
    sine_gen #(.SAMPLE_RATE(AUDIO_RATE), .TONE_HZ(1000)) tone (
        .clk(hclk), .sample_en(audio_tick), .left(sine_l), .right(sine_r)
    );

    logic [15:0] audio_sample_word [1:0];
    always @(posedge hclk) begin
        audio_sample_word[0] <= sine_l;
        audio_sample_word[1] <= sine_r;
    end

    //--------------------------------------------------------------- HDMI
    wire [2:0] tmds;
    wire       tmds_clock;
    hdmi #(
        .VIDEO_ID_CODE(4),               // 1280x720p60
        .DVI_OUTPUT(0),
        .VIDEO_REFRESH_RATE(60.0),
        .IT_CONTENT(1),
        .AUDIO_RATE(AUDIO_RATE),
        .AUDIO_BIT_WIDTH(16),
        .START_X(0), .START_Y(0)
    ) u_hdmi (
        .clk_pixel_x5(hclk5), .clk_pixel(hclk), .clk_audio(clk_audio),
        .reset(1'b0), .rgb(rgb), .audio_sample_word(audio_sample_word),
        .tmds(tmds), .tmds_clock(tmds_clock),
        .cx(cx), .cy(cy), .frame_width(), .frame_height()
    );

    ELVDS_OBUF tmds_bufds [3:0] (
        .I ({hclk, tmds}),
        .O ({tmds_clk_p, tmds_d_p}),
        .OB({tmds_clk_n, tmds_d_n})
    );

    //-------------------------------------------------------- diagnostics
    reg [7:0]  out_frames = 0;
    reg        vs_r = 0;
    always @(posedge hclk) begin
        vs_r <= (cy == 0);
        if ((cy == 0) && !vs_r) out_frames <= out_frames + 1'b1;
    end

    reg [7:0] src_frames = 0;
    reg       pvs_r = 1;
    always @(posedge clk_sys) begin
        if (ce_pix) begin
            pvs_r <= p_vs;
            if (!p_vs && pvs_r) src_frames <= src_frames + 1'b1;
        end
    end

    reg [25:0] hb_h = 0;
    reg [24:0] hb_27 = 0;
    always @(posedge hclk)  hb_h  <= hb_h + 1'b1;
    always @(posedge clk27) hb_27 <= hb_27 + 1'b1;
    assign debug_o = {1'b0, hb_27[24], hb_h[25], 1'b1};

    reg [7:0] of_s, sf_s;
    always @(posedge clk_sys) begin
        of_s <= out_frames;
        sf_s <= src_frames;
    end

    uart_beacon #(.CLK_HZ(40_000_000), .BAUD(115200)) beacon (
        .clk(clk_sys),
        .calib(1'b0), .ddr_rst(1'b0),
        .cnt_x(hb_h[25:10]), .cnt_q(hb_27[24:17]),
        .aux(of_s),    // output frames  - must advance ~60/s
        .aux2(sf_s),   // source frames  - must advance ~60/s
        .txd(uart_tx)
    );

endmodule

`default_nettype wire
