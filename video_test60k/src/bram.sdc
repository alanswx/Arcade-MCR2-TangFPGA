// Timing constraints - BRAM variant. No DDR3, so no clk4x/clk1x/clk_g.
create_clock -name sys_clk -period 20 -waveform {0 10} [get_ports {sys_clk}]
create_generated_clock -name clk_sys -source [get_ports {sys_clk}] -multiply_by 4 -divide_by 5 [get_pins {pll_inst/PLLA_inst/CLKOUT1}]
create_generated_clock -name clk27 -source [get_ports {sys_clk}] -multiply_by 27 -divide_by 50 [get_pins {pll27_inst/PLLA_inst/CLKOUT0}]

// hclk5 MUST be declared: an unconstrained 371.25 MHz OSER10 path gets routed
// with no requirement at all and silently produces dead TMDS.
create_clock -name hclk5 -period 2.694  -waveform {0 1.347} [get_nets {hclk5}]
create_clock -name hclk  -period 13.468 -waveform {0 6.734} [get_nets {hclk}]

// The BRAM is genuinely dual-clock (write clk_sys, read hclk) - that crossing
// is the ONLY one in the design, and it is the BRAM itself.
set_clock_groups -asynchronous -group [get_clocks {clk_sys}] -group [get_clocks {clk27}] -group [get_clocks {hclk5 hclk}]
