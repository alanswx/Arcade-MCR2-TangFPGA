// Tang Console 138K Top-Level Wrapper for MCR2 Arcade Core
// Fits all CPU, sound, and graphics ROMs entirely inside on-chip Block RAM (BSRAM)
// Supports HDMI output and RGBS 15kHz cabinet output concurrently
module mcr2_console138k_top (
    input        sys_clk,       // 50 MHz on-board oscillator (pin P16)
    input        s1,            // S1 button, active high (pulldown)
    input        reset2,        // S2 button, active high (pulldown)

    // DVI/HDMI output
    output       tmds_clk_p,
    output       tmds_clk_n,
    output [2:0] tmds_d_p,
    output [2:0] tmds_d_n,

    // 2x20-Pin GPIO Header / Cabinet Arcade wired interface
    input        btn_left,      
    input        btn_right,     
    input        btn_fire,      
    input        btn_shield,    
    input        btn_start,     
    input        btn_coin,      
    input        btn_service,   
    input        btn_tilt,      

    // Cabinet RGBS video output (GPIO)
    output [2:0] cab_r,         
    output [2:0] cab_g,         
    output [2:0] cab_b,         
    output       cab_hs,        
    output       cab_vs,        
    output       cab_csync,     

    // PWM Audio output
    output       audio_l,
    output       audio_r
);

// --- Clock Generation ---
wire clk_sys;  // 40 MHz (Core system clock)
wire clk_p5;   // 100 MHz (HDMI 5x pixel clock)
wire pll_locked;

gowin_pll_mcr2 pll_inst (
    .clkin(sys_clk),
    .clk_sys(clk_sys),
    .clk_p5(clk_p5),
    .lock(pll_locked)
);

// Gowin Clock Divider to generate clk_pixel (20 MHz) from clk_p5 (100 MHz)
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

// --- ROM and RAM Instantiations (Entirely in on-chip Block RAM) ---
wire [15:0] rom_addr;
wire [7:0]  rom_do;
wire [13:0] snd_addr;
wire [7:0]  snd_do;

dpram #(
    .dWidth(8),
    .aWidth(16),
    .INIT_FILE("../src/roms/rom_main.hex")
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
    .q_b()
);

dpram #(
    .dWidth(8),
    .aWidth(14),
    .INIT_FILE("../src/roms/rom_snd.hex")
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
    .q_b()
);

// --- Core Controls & Switch Mapping ---
// Inputs are active-low (pulled up, grounded when pressed)
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
wire [7:0] input_3 = 8'hFF; 
wire [7:0] input_4 = 8'hFF;

always @(*) begin
    // Satan's Hollow input mappings
    input_0 = ~{ m_service, 1'b0, m_tilt, 1'b0, 1'b0, m_start1, 1'b0, m_coin1 };
    input_1 = ~{ 4'b0000, m_fire_a, m_fire_b, m_right, m_left };
end

// --- Core Instantiation ---
wire [2:0] r, g, b;
wire       hblank, vblank;
wire       hs, vs, cs;
wire [15:0] audio_l_val, audio_r_val;

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

    .tv15Khz_mode(1'b0), // Tie to 1'b0 (force 31kHz doubler) or 1'b1 (original 15kHz)
    
    .separate_audio(1'b0), 
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

// --- HDMI Output Wrapper ---
wire [7:0] hdmi_r = {r, 5'b00000};
wire [7:0] hdmi_g = {g, 5'b00000};
wire [7:0] hdmi_b = {b, 5'b00000};
wire       hdmi_de = ~(hblank | vblank);

hdmi_tx hdmi_tx_inst (
    .clk_pixel(clk_pixel),
    .clk_5x_pixel(clk_p5),
    .resetn(~core_reset),
    .rgb_r(hdmi_r),
    .rgb_g(hdmi_g),
    .rgb_b(hdmi_b),
    .de(hdmi_de),
    .hsync(hs),
    .vsync(vs),
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

endmodule
