// SDRAM memtest timing - Tang Console 60K
create_clock -name sys_clk -period 20 -waveform {0 10} [get_ports {sys_clk}]
// fclk = 65 MHz = sys_clk * 2 (PLLA CLKOUT0)
create_generated_clock -name fclk -source [get_ports {sys_clk}] -multiply_by 13 -divide_by 10 [get_pins {pll/PLLA_inst/CLKOUT0}]
