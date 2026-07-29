# BRAM (nestang-architecture) video dropout test rig, Tang Console 60K.
#   tools/gw_build.sh video_test60k build_bram.tcl
set_device GW5AT-LV60PG484AC1/I0 -device_version B

set_option -synthesis_tool gowinsynthesis
set_option -output_base_name video_bram
set_option -top_module bram_top
set_option -verilog_std sysv2017
set_option -rw_check_on_ram 0
set_option -place_option 2
set_option -ireg_in_iob 1
set_option -oreg_in_iob 1
set_option -ioreg_in_iob 1

set_option -use_cpu_as_gpio 1
set_option -use_mspi_as_gpio 1
set_option -use_sspi_as_gpio 1
set_option -use_ready_as_gpio 1
set_option -use_done_as_gpio 1
set_option -use_i2c_as_gpio 1

add_file src/bram_top.sv
add_file ../src/video/bram_scaler.sv
add_file ../src/audio/sine_gen.sv
add_file ../src/testpat/mcr_testpattern.sv
add_file ../src/rtl/gowin_pll_mcr2.v
add_file ../src/ddr3fb/pll_27.v
add_file ../src/ddr3fb/gowin_pll_hdmi27.v
add_file ../src/rtl/uart_beacon.sv

add_file ../src/ddr3fb/hdmi/hdmi.sv
add_file ../src/ddr3fb/hdmi/audio_clock_regeneration_packet.sv
add_file ../src/ddr3fb/hdmi/audio_info_frame.sv
add_file ../src/ddr3fb/hdmi/audio_sample_packet.sv
add_file ../src/ddr3fb/hdmi/auxiliary_video_information_info_frame.sv
add_file ../src/ddr3fb/hdmi/packet_assembler.sv
add_file ../src/ddr3fb/hdmi/packet_picker.sv
add_file ../src/ddr3fb/hdmi/serializer.sv
add_file ../src/ddr3fb/hdmi/source_product_description_info_frame.sv
add_file ../src/ddr3fb/hdmi/tmds_channel.sv

add_file -type cst src/bram.cst
add_file -type sdc src/bram.sdc

run all
