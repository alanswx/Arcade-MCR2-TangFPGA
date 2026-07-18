// Timing constraints for MCR2 on Tang Primer 25K
// Primary 50MHz input clock on pin sys_clk (period = 20ns).
create_clock -name sys_clk -period 20 -waveform {0 10} [get_ports {sys_clk}]

// Explicitly declare the PLL/CLKDIV generated clocks. Naming them here (rather
// than relying on the tool's auto-derived "default_gen_clk" names, which are not
// queryable at SDC-parse time) lets us reference them in set_clock_groups below.
//   clk_sys   = 40MHz  = sys_clk * 4/5     (PLLA CLKOUT1, core clock)
//   clk_pixel = 25MHz  = sys_clk / 2       (CLKDIV /5 of the 125MHz CLKOUT0)
// Without an explicit clk_pixel the pixel/line-buffer domain would fall back to
// the tool's 100MHz global default and report false setup violations.
create_generated_clock -name clk_sys   -source [get_ports {sys_clk}] -multiply_by 4 -divide_by 5 [get_pins {pll_inst/PLLA_inst/CLKOUT1}]
create_generated_clock -name clk_pixel -source [get_ports {sys_clk}] -divide_by 2 [get_pins {clk_div_inst/CLKOUT}]

// The core clock (clk_sys, 40MHz) and the HDMI pixel clock (clk_pixel, 25MHz)
// only meet inside the two-line ping-pong buffer, whose hand-off is safely
// synchronized. They are logically asynchronous, so cut the false cross-domain
// paths the tool would otherwise flag. (clk_pixel is left synchronous to the
// 125MHz CLKOUT0 so the OSER10 5x serializer stays properly constrained.)
set_clock_groups -asynchronous -group [get_clocks {clk_pixel}] -group [get_clocks {clk_sys}]
