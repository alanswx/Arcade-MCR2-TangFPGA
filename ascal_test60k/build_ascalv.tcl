# Gowin TCL build for the ascal / 15-31 kHz video bring-up rig, Console 60K.
# Run headless:  tools/gw_build.sh ascal_test60k

set_device GW5AT-LV60PG484AC1/I0 -device_version B

set_option -synthesis_tool gowinsynthesis
set_option -output_base_name ascalv
set_option -top_module ascalv_top
set_option -verilog_std sysv2017
set_option -vhdl_std vhd2008
set_option -rw_check_on_ram 0

# Same placer/IOB settings as the working DDR3 design. place_option 2 is NOT
# optional: option 0 builds clean and meets timing but the DDR3 never trains,
# so HDMI stays black (see CLAUDE.md).
set_option -ireg_in_iob 1
set_option -oreg_in_iob 1
set_option -ioreg_in_iob 1
set_option -place_option 2

# J10 (SDRAM1 bus) overlaps the CPU-mode config DBUS and the SSPI/MSPI pins.
set_option -use_cpu_as_gpio 1
set_option -use_mspi_as_gpio 1
set_option -use_sspi_as_gpio 1
set_option -use_ready_as_gpio 1
set_option -use_done_as_gpio 1
set_option -use_i2c_as_gpio 1

# Top + test source
add_file src/ascalv_top.sv
add_file ../src/video/ascal_v.sv
add_file ../src/testpat/mcr_testpattern.sv

# ascal (unmodified upstream) + our wrapper and Avalon->Gowin DDR3 bridge
add_file ../src/ascal/ascal_avl_ddr3.sv

# Clocks + DDR3 controller, reused from the gbatang framebuffer vendor drop
add_file ../src/rtl/gowin_pll_mcr2.v
add_file ../src/ddr3fb/pll_27.v
add_file ../src/ddr3fb/pll_ddr3.v
add_file ../src/ddr3fb/gowin_pll_hdmi27.v
add_file ../src/ddr3fb/pll_mDRP_intf.v
add_file ../src/ddr3fb/ddr3_memory_interface.v

# DVI transmitter - takes EXTERNAL de/hs/vs, which is exactly what ascal emits
# hdl-util HDMI stack (replaces dvi_tx_ext: raw DVI dropped sync 6.5% of the
# time, this is the module the nine shipping games already use, and it carries
# audio). tmds_channel was already here; the rest is the packet/infoframe path.
add_file ../src/ddr3fb/hdmi/tmds_channel.sv
add_file ../src/ddr3fb/hdmi/serializer.sv
add_file ../src/ddr3fb/hdmi/packet_assembler.sv
add_file ../src/ddr3fb/hdmi/packet_picker.sv
add_file ../src/ddr3fb/hdmi/audio_clock_regeneration_packet.sv
add_file ../src/ddr3fb/hdmi/audio_info_frame.sv
add_file ../src/ddr3fb/hdmi/audio_sample_packet.sv
add_file ../src/ddr3fb/hdmi/auxiliary_video_information_info_frame.sv
add_file ../src/ddr3fb/hdmi/source_product_description_info_frame.sv
add_file ../src/ddr3fb/hdmi/hdmi.sv
add_file ../src/audio/sine_gen.sv

add_file ../src/rtl/uart_beacon.sv

add_file -type cst src/ascal_test60k.cst
add_file -type sdc src/ascal_test60k.sdc

run all
