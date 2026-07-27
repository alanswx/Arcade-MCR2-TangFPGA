# DEFECT 2 (PA2122) - MINIMAL reproducer. NO BOARD REQUIRED.
# Upstream ascal.vhd, unmodified, plus a wrapper that does nothing else.
# Expect: synthesis succeeds, PnR fails with
#   ERROR (PA2122) : Not support '...'(SPX9) WRITE_MODE = 2'b10 ...
#   gw_sh build_defect2_PA2122.tcl
set_device GW5AT-LV60PG484AC1/I0 -device_version B
set_option -synthesis_tool gowinsynthesis
set_option -output_base_name ascal_pa2122
set_option -top_module pa2122_min
set_option -vhdl_std vhd2008
add_file src/ascal_upstream.vhd
add_file src/pa2122_min.vhd
run all
