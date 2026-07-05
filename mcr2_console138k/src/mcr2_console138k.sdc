// Timing constraints for MCR2 on Tang Console 138K
// Define primary input 50MHz clock on pin sys_clk (period = 20ns)
create_clock -name sys_clk -period 20 -waveform {0 10} [get_ports {sys_clk}]
