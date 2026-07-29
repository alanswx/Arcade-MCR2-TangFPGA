// Timing constraints for the ascal video bring-up rig, Tang Console 60K.
// Structure follows mcr2_console60k.sdc - see the long note there about why
// hclk5 MUST be declared: an unconstrained 371.25 MHz OSER10 path is routed
// with no requirement at all and silently produces dead TMDS.

create_clock -name sys_clk -period 20 -waveform {0 10} [get_ports {sys_clk}]

// clk_sys = 40 MHz = sys_clk * 4/5 (PLLA CLKOUT1) - the core's clock, and
// here the test pattern generator's.
create_generated_clock -name clk_sys -source [get_ports {sys_clk}] -multiply_by 4 -divide_by 5 [get_pins {pll_inst/PLLA_inst/CLKOUT1}]

// 27 MHz reference (pll_27 CLKOUT0 = 50 * 27/50).
create_generated_clock -name clk27 -source [get_ports {sys_clk}] -multiply_by 27 -divide_by 50 [get_pins {pll27_inst/PLLA_inst/CLKOUT0}]

// clk_g = the PLL-buffered 50 MHz that clocks the DDR3 controller's control
// side and the mDRP interface (CLKOUT2). It MUST be named: left to the tool
// it becomes "...CLKOUT2.default_gen_clk", which cannot be referenced in
// set_clock_groups, so every path from the DDR3 IP's internal 50 MHz
// registers into clk_sys stays timed as if synchronous - 64 setup-violated
// endpoints, all of them false.
create_generated_clock -name clk_g -source [get_ports {sys_clk}] -multiply_by 1 -divide_by 1 [get_pins {pll_inst/PLLA_inst/CLKOUT2}]

// The DDR3 PLL is mDRP-reconfigured at runtime, so declare its outputs as
// free-standing clocks rather than deriving them.
//   clk4x = 297 MHz memory clock, clk1x = 74.25 MHz app/Avalon clock.
create_clock -name clk4x -period 3.367 -waveform {0 1.684} [get_nets {fb_inst/memory_clk}]
create_clock -name clk1x -period 13.47 -waveform {0 6.734} [get_nets {fb_inst/clk_x1}]

// HDMI chain: 27 -> 371.25 (hclk5) -> CLKDIV/5 -> 74.25 (hclk).
create_clock -name hclk5 -period 2.694  -waveform {0 1.347} [get_nets {fb_inst/hclk5}]
create_clock -name hclk  -period 13.468 -waveform {0 6.734} [get_nets {fb_hclk}]

// ascal spans three of these domains (i_clk = clk_sys, avl_clk = clk1x,
// o_clk = hclk) and does its own synchronising at every crossing - that is
// the whole reason it needs no external pixel FIFO. So every pair is cut.
// (one line - the Gowin SDC parser does not accept backslash continuations)
set_clock_groups -asynchronous -group [get_clocks {clk_sys}] -group [get_clocks {clk27}] -group [get_clocks {clk_g}] -group [get_clocks {clk4x}] -group [get_clocks {clk1x}] -group [get_clocks {hclk5 hclk}]
