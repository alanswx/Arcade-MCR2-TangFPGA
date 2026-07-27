# DEFECT 1 (silent miscompile). Uses ascal_gowin.vhd = upstream plus the
# syn_srlstyle workaround for PA2122 and debug taps.
# Expect: builds CLEAN (0 errors, 0 setup/0 hold violations) and produces
# a bitstream whose HORIZONTAL scaling is 4x too fast on hardware, while
# vertical scaling is perfect. See BUG_REPORT.md section 3.
#   gw_sh build_defect1_miscompile.tcl

set_device GW5AT-LV60PG484AC1/I0 -device_version B

set_option -synthesis_tool gowinsynthesis
set_option -output_base_name ascal_miscompile
set_option -top_module ascal_test60k_top
set_option -verilog_std sysv2017
set_option -vhdl_std vhd2008
set_option -rw_check_on_ram 0
set_option -place_option 2
set_option -ireg_in_iob 1
set_option -oreg_in_iob 1
set_option -ioreg_in_iob 1

# the J10 header overlaps the CPU-mode config pins on this board
set_option -use_cpu_as_gpio 1
set_option -use_mspi_as_gpio 1
set_option -use_sspi_as_gpio 1
set_option -use_ready_as_gpio 1
set_option -use_done_as_gpio 1
set_option -use_i2c_as_gpio 1

add_file src/ascal_gowin.vhd

add_file src/ascal_gw.vhd
add_file src/ascal_test60k_top.sv
add_file src/mcr_testpattern.sv
add_file src/ascal_avl_ddr3.sv
add_file src/gowin_pll_mcr2.v
add_file src/pll_27.v
add_file src/pll_ddr3.v
add_file src/gowin_pll_hdmi27.v
add_file src/pll_mDRP_intf.v
add_file src/ddr3_memory_interface.v
add_file src/dvi_tx_ext.sv
add_file src/tmds_channel.sv
add_file src/uart_beacon.sv

add_file -type cst src/ascal_test60k.cst
add_file -type sdc src/ascal_test60k.sdc

run all
