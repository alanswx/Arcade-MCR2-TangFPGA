set_device GW5AT-LV60PG484AC1/I0 -device_version B
set_option -synthesis_tool gowinsynthesis
set_option -output_base_name nes_video_selftest
set_option -top_module nes_video_selftest_top
set_option -verilog_std sysv2017
set_option -place_option 2
add_file diag/nes_video_selftest_top.sv
add_file diag/gowin_pll_hdmi27.v
add_file ../src/ddr3fb/pll_27.v
add_file ../src/rtl/uart_beacon.sv
add_file ../src/ddr3fb/hdmi/audio_clock_regeneration_packet.sv
add_file ../src/ddr3fb/hdmi/audio_info_frame.sv
add_file ../src/ddr3fb/hdmi/audio_sample_packet.sv
add_file ../src/ddr3fb/hdmi/auxiliary_video_information_info_frame.sv
add_file ../src/ddr3fb/hdmi/hdmi.sv
add_file ../src/ddr3fb/hdmi/packet_assembler.sv
add_file ../src/ddr3fb/hdmi/packet_picker.sv
add_file ../src/ddr3fb/hdmi/serializer.sv
add_file ../src/ddr3fb/hdmi/source_product_description_info_frame.sv
add_file ../src/ddr3fb/hdmi/tmds_channel.sv
add_file -type cst diag/nes_video_selftest.cst
add_file -type sdc diag/nes_video_selftest.sdc
run all
