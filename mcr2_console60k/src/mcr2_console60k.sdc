// Timing constraints for MCR2 on Tang Console 60K
// Primary 50MHz input clock on pin sys_clk (period = 20ns).
create_clock -name sys_clk -period 20 -waveform {0 10} [get_ports {sys_clk}]

// Explicitly declare the PLL generated core clock. Naming it here (rather
// than relying on the tool's auto-derived "default_gen_clk" names, which are
// not queryable at SDC-parse time) lets us reference it in set_clock_groups.
//   clk_sys = 40MHz = sys_clk * 4/5   (PLLA CLKOUT1, core clock)
create_generated_clock -name clk_sys -source [get_ports {sys_clk}] -multiply_by 4 -divide_by 5 [get_pins {pll_inst/PLLA_inst/CLKOUT1}]

// DDR3 framebuffer clocks (per nand2mario gbatang_ddr.sdc): the DDR3 PLL is
// mDRP-reconfigured at runtime, so its outputs are declared explicitly.
//   clk4x = 297MHz DDR3 memory clock, clk1x = 74.25MHz pixel/user clock.
// The framebuffer crosses clk_sys -> clk1x through its internal async FIFO,
// so these domains are asynchronous to the core clock.
create_clock -name clk4x -period 3.367 -waveform {0 1.684} [get_nets {fb_inst/memory_clk}]
create_clock -name clk1x -period 13.47 -waveform {0 6.734} [get_nets {fb_inst/clk_x1}]
set_clock_groups -asynchronous -group [get_clocks {clk_sys}] -group [get_clocks {clk4x}]
set_clock_groups -asynchronous -group [get_clocks {clk4x}] -group [get_clocks {clk1x}]
set_clock_groups -asynchronous -group [get_clocks {clk_sys}] -group [get_clocks {clk1x}]

// USB HID host clock: 12MHz from the second PLLA (50 * 6/25). The pad outputs
// are 2FF-synchronized into clk_sys, so the domains are asynchronous.
create_generated_clock -name clk_usb -source [get_ports {sys_clk}] -multiply_by 6 -divide_by 25 [get_pins {pll_usb_inst/PLLA_inst/CLKOUT0}]
set_clock_groups -asynchronous -group [get_clocks {clk_usb}] -group [get_clocks {clk_sys}]
