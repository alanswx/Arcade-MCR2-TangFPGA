// Gowin PLLA for the SDRAM RETENTION experiment (2026-07-24):
// 50 MHz in, VCO = 50*16 = 800 MHz; CLKOUT0 = 80 MHz (sdram_gw at the
// MCR-3 rate); CLKOUT1 = 80 MHz shifted 225 degrees (PE 6+2/8 of the
// 10-VCO-cycle period) for the SDRAM pin clock via sdram_gw's clk_fwd.
module gowin_pll_ret80 (
    input  clkin,
    output fclk,
    output fclk_p,
    output lock
);

wire clkout2_o, clkout3_o, clkout4_o, clkout5_o, clkout6_o;
wire clkfbout_o;
wire [7:0] mdrdo_o;
wire gw_gnd = 1'b0;

PLLA PLLA_inst (
    .LOCK(lock),
    .CLKOUT0(fclk),     // 65 MHz
    .CLKOUT1(fclk_p),   // 65 MHz +225deg
    .CLKOUT2(clkout2_o),
    .CLKOUT3(clkout3_o),
    .CLKOUT4(clkout4_o),
    .CLKOUT5(clkout5_o),
    .CLKOUT6(clkout6_o),
    .CLKFBOUT(clkfbout_o),
    .MDRDO(mdrdo_o),
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
defparam PLLA_inst.ODIV0_SEL = 10;  // 80 MHz
defparam PLLA_inst.ODIV0_FRAC_SEL = 0;
defparam PLLA_inst.ODIV1_SEL = 10;  // 80 MHz shifted
defparam PLLA_inst.ODIV2_SEL = 8;
defparam PLLA_inst.ODIV3_SEL = 8;
defparam PLLA_inst.ODIV4_SEL = 8;
defparam PLLA_inst.ODIV5_SEL = 8;
defparam PLLA_inst.ODIV6_SEL = 8;
defparam PLLA_inst.MDIV_SEL = 16;   // VCO 800
defparam PLLA_inst.CLKOUT0_EN = "TRUE";
defparam PLLA_inst.CLKOUT1_EN = "TRUE";  // the 225-deg pin clock
defparam PLLA_inst.CLKOUT1_PE_COARSE = 6;   // 225deg = 6.25/10 of period
defparam PLLA_inst.CLKOUT1_PE_FINE = 2;
defparam PLLA_inst.MDIV_FRAC_SEL = 0;
defparam PLLA_inst.ODIV0_FRAC_SEL = 0;
defparam PLLA_inst.DYN_DPA_EN = "false";
defparam PLLA_inst.DYN_PE0_SEL = "false";
defparam PLLA_inst.DYN_PE1_SEL = "false";
defparam PLLA_inst.DYN_PE2_SEL = "false";

endmodule
