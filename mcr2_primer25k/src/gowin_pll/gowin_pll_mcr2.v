// Gowin PLLA clock generator for MCR2 core on Tang Primer 25K
// Input clock: 50 MHz
// Output clocks:
// - clk_sys: 40 MHz (Core system clock)
// - clk_p5: 100 MHz (HDMI 5x pixel clock)
module gowin_pll_mcr2 (
    input  clkin,
    output clk_sys,
    output clk_p5,
    output lock
);

wire gw_gnd = 1'b0;

PLLA PLLA_inst (
    .LOCK(lock),
    .CLKOUT0(clk_p5),   // 100 MHz
    .CLKOUT1(clk_sys),  // 40 MHz
    .CLKOUT2(),
    .CLKOUT3(),
    .CLKOUT4(),
    .CLKOUT5(),
    .CLKOUT6(),
    .CLKFBOUT(),
    .MDRDO(),
    .CLKIN(clkin),
    .CLKFB(gw_gnd),
    .RESET(gw_gnd),
    .PLLPWD(gw_gnd),
    .RESET_I(gw_gnd),
    .RESET_O(gw_gnd),
    .PSSEL({gw_gnd,gw_gnd,gw_gnd}),
    .PSDIR(gw_gnd),
    .PSPULSE(gw_gnd),
    .SSCPOL(gw_gnd),
    .SSCON(gw_gnd),
    .SSCMDSEL({gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd}),
    .SSCMDSEL_FRAC({gw_gnd,gw_gnd,gw_gnd}),
    .MDCLK(gw_gnd),
    .MDOPC({gw_gnd,gw_gnd}),
    .MDAINC(gw_gnd),
    .MDWDI({gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd})
);

defparam PLLA_inst.FCLKIN = "50";
defparam PLLA_inst.IDIV_SEL = 1;
defparam PLLA_inst.FBDIV_SEL = 1;
defparam PLLA_inst.CLKFB_SEL = "INTERNAL";
defparam PLLA_inst.ODIV0_SEL = 8;
defparam PLLA_inst.ODIV0_FRAC_SEL = 0;
defparam PLLA_inst.ODIV1_SEL = 20;
defparam PLLA_inst.MDIV_SEL = 16;
defparam PLLA_inst.MDIV_FRAC_SEL = 0;
defparam PLLA_inst.CLKOUT0_EN = "TRUE";
defparam PLLA_inst.CLKOUT1_EN = "TRUE";
defparam PLLA_inst.CLKOUT2_EN = "FALSE";
defparam PLLA_inst.CLKOUT3_EN = "FALSE";
defparam PLLA_inst.CLKOUT4_EN = "FALSE";
defparam PLLA_inst.CLKOUT5_EN = "FALSE";
defparam PLLA_inst.CLKOUT6_EN = "FALSE";
defparam PLLA_inst.CLKOUT0_DT_DIR = 1'b1;
defparam PLLA_inst.CLKOUT1_DT_DIR = 1'b1;

endmodule
