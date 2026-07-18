// Tang Primer 25K Top-Level Wrapper for MCR2 Arcade Core
// Standalone hardcoded Version 1 (Satan's Hollow)
// Supports HDMI output and RGBS 15kHz cabinet output concurrently
module mcr2_primer25k_top (
    input        sys_clk,       // 50 MHz on-board oscillator (pin E2)
    input        s1,            // S1 button (pin H11), active high (pulldown)
    input        reset2,        // S2 button (pin H10), active high (pulldown)

    // DVI/HDMI output
    output       tmds_clk_p,
    output       tmds_clk_n,
    output [2:0] tmds_d_p,
    output [2:0] tmds_d_n,

    // PMOD 1 / Cabinet Arcade wired interface
    input        btn_left,      // PMOD1 pin 4 (L5)
    input        btn_right,     // PMOD1 pin 3 (K11)
    input        btn_fire,      // PMOD1 pin 2 (E11)
    input        btn_shield,    // PMOD1 pin 1 (A11)
    input        btn_start,     // PMOD1 pin 10 (K5)
    input        btn_coin,      // PMOD1 pin 9 (L11)
    input        btn_service,   // PMOD1 pin 8 (E10)
    input        btn_tilt,      // PMOD1 pin 7 (A10)

    // Cabinet RGBS video output (GPIO)
    output [2:0] cab_r,         // R[2:0]
    output [2:0] cab_g,         // G[2:0]
    output [2:0] cab_b,         // B[2:0]
    output       cab_hs,        // HSync
    output       cab_vs,        // VSync
    output       cab_csync,     // Composite Sync (CSync)

    // PWM Audio output (headphone/speaker jack pins or PMOD)
    output       audio_l,
    output       audio_r,

    // Debug LED
    output       led
);

// --- Clock Generation ---
wire clk_sys;  // 40 MHz  (Core system clock, generates 20 MHz pixel enable)
wire clk_p5;   // 125 MHz (HDMI 5x pixel clock)
wire pll_locked;

gowin_pll_mcr2 pll_inst (
    .clkin(sys_clk),
    .clk_sys(clk_sys),
    .clk_p5(clk_p5),
    .lock(pll_locked)
);

// Gowin Clock Divider to generate clk_pixel (25 MHz) from clk_p5 (125 MHz)
wire clk_pixel;
CLKDIV clk_div_inst (
    .CLKOUT(clk_pixel),
    .HCLKIN(clk_p5),
    .RESETN(pll_locked),
    .CALIB(1'b0)
);
defparam clk_div_inst.DIV_MODE = "5";

// --- Reset Generation ---
reg [7:0] reset_cnt = 255;
wire core_reset = (reset_cnt != 0);

always @(posedge clk_sys) begin
    if (s1 || !pll_locked) begin
        reset_cnt <= 255;
    end else if (reset_cnt != 0) begin
        reset_cnt <= reset_cnt - 8'd1;
    end
end

// The main Z80 ROM (48KB) and Sound Z80 ROM (16KB) are instantiated as separate Single-Port ROMs
// to ensure clean Gowin BSRAM block inference with hex initialization.
wire [15:0] rom_addr;
wire [7:0]  rom_do;
wire [13:0] snd_addr;
wire [7:0]  snd_do;

dpram #(
    .dWidth(8),
    .aWidth(16),
    .INIT_FILE("rom_main.hex")
) rom_cpu_inst (
    .clk_a(clk_sys),
    .we_a(1'b0),
    .addr_a(rom_addr),
    .d_a(8'h00),
    .q_a(rom_do),

    .clk_b(clk_sys),
    .we_b(1'b0),
    .addr_b(16'h0000),
    .d_b(8'h00),
    .q_b() // Port B is unused
);

dpram #(
    .dWidth(8),
    .aWidth(14),
    .INIT_FILE("rom_snd.hex")
) rom_snd_inst (
    .clk_a(clk_sys),
    .we_a(1'b0),
    .addr_a(snd_addr),
    .d_a(8'h00),
    .q_a(snd_do),

    .clk_b(clk_sys),
    .we_b(1'b0),
    .addr_b(14'h0000),
    .d_b(8'h00),
    .q_b() // Port B is unused
);

// --- Core Controls & Switch Mapping ---
// Buttons are active-low on cabinet (pulled up, grounded when pressed).
// S2 board button is mapped to Coin 1 as well.
wire m_left    = ~btn_left;
wire m_right   = ~btn_right;
wire m_fire_a  = ~btn_fire;
wire m_fire_b  = ~btn_shield;
wire m_start1  = ~btn_start;
wire m_coin1   = ~btn_coin | reset2;
wire m_service = ~btn_service;
wire m_tilt    = ~btn_tilt;

reg [7:0] input_0;
reg [7:0] input_1;
wire [7:0] input_2 = 8'hFF;
wire [7:0] input_3 = 8'hFF; // default DIP switches
wire [7:0] input_4 = 8'hFF;

always @(*) begin
    // Satan's Hollow input mappings:
    // input_0 = ~{ service, 1'b0, tilt, 1'b0, start2, start1, 1'b0, coin1 }
    input_0 = ~{ m_service, 1'b0, m_tilt, 1'b0, 1'b0, m_start1, 1'b0, m_coin1 };
    
    // input_1 = ~{ P2_fire, P2_shield, P2_right, P2_left, P1_fire, P1_shield, P1_right, P1_left }
    input_1 = ~{ 4'b0000, m_fire_a, m_fire_b, m_right, m_left };
end

// --- Core Instantiation ---
wire [2:0] r, g, b;
wire       hblank, vblank;
wire       hs, vs, cs;
wire [15:0] audio_l_val, audio_r_val;

wire [9:0] core_hcnt;
wire [9:0] core_vcnt;

mcr2 mcr2_core (
    .clock_40(clk_sys),
    .reset(core_reset),

    // Video outputs
    .video_r(r),
    .video_g(g),
    .video_b(b),
    .video_vblank(vblank),
    .video_hblank(hblank),
    .video_hs(hs),
    .video_vs(vs),
    .video_csync(cs),
    .hcnt_out(core_hcnt),
    .vcnt_out(core_vcnt),

    // Force 31kHz mode for HDMI debugging, or use 15kHz mode for CRT.
    // We tie tv15Khz_mode to 1'b0 (force 31kHz scan-doubled VGA mode) for Version 1.
    // To support CRT later, we can map tv15Khz_mode to a DIP switch/GPIO pin.
    .tv15Khz_mode(1'b0),
    
    .separate_audio(1'b0), // mono mix
    .audio_out_l(audio_l_val),
    .audio_out_r(audio_r_val),

    .input_0(input_0),
    .input_1(input_1),
    .input_2(input_2),
    .input_3(input_3),
    .input_4(input_4),

    // CPU ROM interface
    .cpu_rom_addr(rom_addr),
    .cpu_rom_do(rom_do),
    .snd_rom_addr(snd_addr),
    .snd_rom_do(snd_do),

    // Disable HPS download interface
    .dl_addr(17'd0),
    .dl_wr(1'b0),
    .dl_data(8'd0),
    .dl_nvram_wr(1'b0),
    .dl_din(),
    .dl_nvram(1'b0)
);

// --- Cabinet Video Output (RGBS) ---
assign cab_r     = r;
assign cab_g     = g;
assign cab_b     = b;
assign cab_hs    = hs;
assign cab_vs    = vs;
assign cab_csync = cs;

// --- HDMI Output Wrapper: native MCR video -> standard 640x480@60 (VGA) ---
// The MCR2 core in 31kHz progressive mode already emits a 512x480 active image
// at a 31.5kHz line rate / 60Hz frame rate (634x525 total @ 20MHz). That maps
// cleanly onto DMT 640x480@60 (800x525 total @ 25MHz, negative H/V sync) - a
// mode every HDMI display supports. We just conform the horizontal blanking to
// the 800-pixel standard and center the 512-wide game inside the 640 active
// pixels. A two-line ping-pong buffer crosses the 20MHz->25MHz clock domains.

// Dual-port line buffer: 2 lines x 512 pixels of 9-bit RGB
reg [8:0] line_buffer [1023:0];

// The core's RGB output lags its hcnt by a fixed pipeline delay (tile fetch ->
// gfx ROM -> palette -> output registers). Indexing the buffer by raw hcnt makes
// the first CAP_DELAY entries capture the PREVIOUS line still draining through
// the pipeline -> the garbled strip on the left edge. Compensate by shifting the
// write index back by CAP_DELAY, and let the capture run a few pixels into hblank
// so the last CAP_DELAY real pixels (which emerge during early hblank) are kept.
// Tune CAP_DELAY by +/-1 if a thin sliver remains on the left/right edge.
localparam [9:0] CAP_DELAY = 10'd13;
wire [9:0] cap_idx = core_hcnt - CAP_DELAY;

// Write side: game core writes active pixels at clk_sys (40 MHz / 20 MHz pixel)
always @(posedge clk_sys) begin
    if (!vblank && (core_hcnt >= CAP_DELAY) && (core_hcnt < CAP_DELAY + 10'd512)) begin
        line_buffer[{core_vcnt[0], cap_idx[8:0]}] <= {r, g, b};
    end
end

// Synchronize the write-line select into the clk_pixel (25 MHz) domain
reg core_vcnt0_sync1 = 0;
reg core_vcnt0_sync2 = 0;
always @(posedge clk_pixel) begin
    core_vcnt0_sync1 <= core_vcnt[0];
    core_vcnt0_sync2 <= core_vcnt0_sync1;
end

// Read side: read the line NOT currently being written
wire read_buffer_idx = ~core_vcnt0_sync2;

// --- 640x480@~60 (VGA-like) sync/scan coordinate generator @ 25 MHz ---
// Horizontal: 640 active + 16 FP + 96 sync + 41 BP = 793 total
// Vertical:   480 active + 10 FP +  2 sync + 33 BP = 525 total
// Both H and V sync are ACTIVE LOW per the DMT 640x480@60 standard.
//
// H total is 793 (not the standard 800) on purpose: the game core emits one
// line every 634 core-pixels @ 20MHz = 31.55kHz, and 634*(25/20) = 792.5, so
// 793 output pixels @ 25MHz makes the output line rate track the core to within
// 0.06% (vs 0.94% at 800). That near-lock stops the ping-pong line buffer from
// switching buffers mid-visible-line, which is what caused the wobble / left-edge
// echo. 793 (rounding up) keeps the output slightly slower than the core, so the
// line being read is always already complete. Monitors still lock (640 active,
// ~31.5kHz/~60Hz, just slightly tighter blanking than DMT).
localparam H_TOTAL = 793;
reg [9:0] test_hcnt = 0;
reg [9:0] test_vcnt = 0;

// --- Vertical genlock ---------------------------------------------------------
// The core frame rate (20MHz/(634*525) = 60.09Hz) does not exactly equal the
// free-running 640x480 output rate (25MHz/(800*525) = 59.52Hz), so a free-running
// output would slip ~0.56 lines-of-phase per frame and slowly roll vertically.
// Lock the output frame to the core: restart the output vertical counter at the
// start of every core frame (falling edge of core vblank = first active line).
// The horizontal counter is never disturbed, so HSync/refresh stay clean; only
// the vertical phase is corrected, and only on a line boundary. This is bypassed
// in test-pattern mode (S2) so the color bars are a standalone 640x480 signal.
reg core_vbl_s1 = 1, core_vbl_s2 = 1, core_vbl_s3 = 1;
always @(posedge clk_pixel) begin
    core_vbl_s1 <= vblank;
    core_vbl_s2 <= core_vbl_s1;
    core_vbl_s3 <= core_vbl_s2;
end
wire core_frame_start = core_vbl_s3 & ~core_vbl_s2; // core vblank 1->0 : new frame

reg frame_start_pending = 0;
always @(posedge clk_pixel) begin
    if (core_frame_start)              frame_start_pending <= 1'b1;
    else if (test_hcnt == H_TOTAL - 1) frame_start_pending <= 1'b0;
end

always @(posedge clk_pixel) begin
    if (test_hcnt == H_TOTAL - 1) begin
        test_hcnt <= 0;
        // ~reset2 == game mode: genlock vertical restart to the core frame.
        if (frame_start_pending && !reset2) begin
            test_vcnt <= 0;
        end else if (test_vcnt == 524) begin
            test_vcnt <= 0;
        end else begin
            test_vcnt <= test_vcnt + 1;
        end
    end else begin
        test_hcnt <= test_hcnt + 1;
    end
end

wire test_de    = (test_hcnt < 640) && (test_vcnt < 480);
wire test_hsync = ~((test_hcnt >= 640 + 16) && (test_hcnt < 640 + 16 + 96)); // active low
wire test_vsync = ~((test_vcnt >= 480 + 10) && (test_vcnt < 480 + 10 + 2));  // active low

// Simple color-bars diagnostic pattern (fills the full 640x480 active area)
wire [7:0] bar_r = test_de ? {test_hcnt[8:6], 5'b00000} : 8'd0;
wire [7:0] bar_g = test_de ? {test_hcnt[5:3], 5'b00000} : 8'd0;
wire [7:0] bar_b = test_de ? {test_vcnt[6:4], 5'b00000} : 8'd0;

// Game centering: 512-wide game inside 640 active -> 64px left margin.
// 480 game lines fill the 480 active lines exactly.
wire game_active_h = (test_hcnt >= 64) && (test_hcnt < 64 + 512); // 64..575
wire game_active_v = (test_vcnt < 480);
wire game_active   = game_active_h && game_active_v;

// Read address leads the display window by one pixel to absorb the registered
// BRAM read latency, so column 0 lands exactly at test_hcnt == 64.
wire [9:0] test_hcnt_core = test_hcnt - 10'd63; // pixel (test_hcnt-64) is presented next cycle

reg [8:0] buffer_out;
always @(posedge clk_pixel) begin
    buffer_out <= line_buffer[{read_buffer_idx, test_hcnt_core[8:0]}];
end

wire [7:0] game_r = game_active ? {buffer_out[8:6], 5'b00000} : 8'd0;
wire [7:0] game_g = game_active ? {buffer_out[5:3], 5'b00000} : 8'd0;
wire [7:0] game_b = game_active ? {buffer_out[2:0], 5'b00000} : 8'd0;

// Multiplex output based on reset2 button (H10) being pressed (default to game core, S2 toggles test pattern)
wire use_test_pattern = reset2;

wire [7:0] final_r = use_test_pattern ? bar_r : game_r;
wire [7:0] final_g = use_test_pattern ? bar_g : game_g;
wire [7:0] final_b = use_test_pattern ? bar_b : game_b;
wire       final_de = test_de;
wire       final_hs = test_hsync;
wire       final_vs = test_vsync;

hdmi_tx hdmi_tx_inst (
    .clk_pixel(clk_pixel),
    .clk_5x_pixel(clk_p5),
    .resetn(1'b1), // Force transmitter active to bypass reset lock issues
    .rgb_r(final_r),
    .rgb_g(final_g),
    .rgb_b(final_b),
    .de(final_de),
    .hsync(final_hs),
    .vsync(final_vs),
    .tmds_clk_p(tmds_clk_p),
    .tmds_clk_n(tmds_clk_n),
    .tmds_d_p(tmds_d_p),
    .tmds_d_n(tmds_d_n)
);

// --- PWM Audio Modulators ---
ds_dac dac_l (
    .clk(clk_sys),
    .resetn(~core_reset),
    .din(audio_l_val),
    .dout(audio_l)
);

ds_dac dac_r (
    .clk(clk_sys),
    .resetn(~core_reset),
    .din(audio_r_val),
    .dout(audio_r)
);

// --- Debug LED (Active Low) ---
assign led = ~pll_locked; // LED turns ON (low) when PLL locks successfully

endmodule
