# Gowin TCL Build Script for MCR3 Arcade Core on Tang Console 60K
# Run headless from mcr3_console60k/ (see CLAUDE.md for the gw_sh invocation).

# Set device details
set_device GW5AT-LV60PG484AC1/I0 -device_version B

# Set synthesis options
set_option -synthesis_tool gowinsynthesis
set_option -output_base_name mcr123s_console60k
set_option -top_module mcr123s_console60k_top
set_option -verilog_std sysv2017
set_option -rw_check_on_ram 1
set_option -multi_boot 1

# Match nand2mario/gbatang's build settings (DDR3 IP donor design):
# IOB register packing + placer algorithm 2.
set_option -ireg_in_iob 1
set_option -oreg_in_iob 1
set_option -ioreg_in_iob 1
set_option -place_option 2
# TIMING-CLOSURE OPTIONS (2026-07-30). The 15-game build fails clk_sys setup by
# -6.3 ns over 25 endpoints and has 3 hold violations in the DDR3 framebuffer,
# and none of these were ever enabled - they cost only build time.
#   -route_option 2        highest routing effort; this design's problem is
#                          congestion at 75% logic, so routing effort is the
#                          most direct lever
#   -retiming 1            let the tool move registers across long combinational
#                          paths
#   -timing_driven 1       explicit rather than relying on the default
#   -correct_hold_violation 1
#                          aimed squarely at the clk1x hold failures; hold is
#                          fixed by INSERTING delay, which the router will not
#                          do unless asked
# NOTE place_option stays at 2. CLAUDE.md records that 0 builds clean and meets
# timing yet produces a bitstream whose DDR3 never trains - CONFIRMED on
# hardware - so this knob is not a free experiment. 3 and 4 exist and are
# untried; only change it with a board in front of you.
set_option -route_option 2
set_option -retiming 1
set_option -timing_driven 1
set_option -correct_hold_violation 1

# Free the dual-purpose config pins as regular GPIO. The J10 header
# (SDRAM1 bus) overlaps the CPU-mode config DBUS (R19/P19/U21/T21 = D0-D3)
# and the SSPI/MSPI pins (V17/AB20/AA19); without these options PnR fails
# with PR2017 "dedicated pin (CPU)".
set_option -use_cpu_as_gpio 1
set_option -use_mspi_as_gpio 1
set_option -use_sspi_as_gpio 1
set_option -use_ready_as_gpio 1
set_option -use_done_as_gpio 1
set_option -use_i2c_as_gpio 1

# Add source files
add_file src/mcr123s_console60k_top.sv
add_file ../src/rtl/dpram.sv
add_file ../src/rtl/gen_ram.sv
add_file ../src/rtl/gowin_pll_core80.v
add_file ../src/rtl/sdram_gw.sv
add_file ../src/usb/gowin_pll_usb.v
add_file ../src/usb/usb_hid_host.v
add_file ../src/usb/usb_hid_host_rom.v
add_file ../src/audio/ds_dac.sv
add_file ../src/rtl/uart_beacon.sv
add_file ../src/rtl/sd_spi_phy.sv
add_file ../src/rtl/sd_reader.sv
add_file ../src/rtl/rom_loader.sv
add_file ../src/rtl/osd.sv

# DDR3 framebuffer + 720p HDMI w/ audio (vendored from nand2mario/gbatang)
add_file ../src/ddr3fb/ddr3_framebuffer.v
add_file ../src/ddr3fb/ddr3_memory_interface.v
add_file ../src/ddr3fb/pll_27.v
add_file ../src/ddr3fb/pll_ddr3.v
add_file ../src/ddr3fb/gowin_pll_hdmi27.v
add_file ../src/ddr3fb/pll_mDRP_intf.v
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

# Add core files (VHDL/SystemVerilog)
add_file ../src/rtl/mcr3.vhd
add_file ../src/rtl/mcr2.vhd
add_file ../src/rtl/mcr1.vhd
add_file ../src/rtl/mcr3scroll.vhd
add_file ../src/rtl/steering_control.vhd
# Cheap Squeak Deluxe (68000 music board) - Spy Hunter / Turbo Tag.
# fx68k_lc.sv is a lower-case-port wrapper; upstream's fx68k.vhd PACKAGE +
# COMPONENT route does NOT bind under GowinSynthesis (EX4806 resolves the
# component to the same-named package, EX4968 matches mixed-language ports
# case-sensitively). fx68k.vhd is deliberately NOT compiled.
# microrom.mem/nanorom.mem must stay next to fx68k.sv: $readmemb resolves
# relative to the source file's directory.
add_file ../src/rtl/FX68K/fx68k_lc.sv
add_file ../src/rtl/FX68K/fx68k.sv
add_file ../src/rtl/FX68K/fx68kAlu.sv
add_file ../src/rtl/FX68K/uaddrPla.sv
add_file ../src/rtl/pia6821.vhd
add_file ../src/rtl/cheap_squeak_deluxe.vhd
add_file ../src/rtl/mcr_sound_board.vhd
add_file ../src/rtl/YM2149_linmix_sep.vhd
add_file ../src/rtl/midssio_82s123.vhd
add_file ../src/rtl/cmos_ram.vhd
add_file ../src/rtl/spinner.sv

# Add CPU/CTC VHDL files
add_file ../src/rtl/T80/t80_1_alu.vhd
add_file ../src/rtl/T80/t80_2_mcode.vhd
add_file ../src/rtl/T80/t80_3_reg.vhd
add_file ../src/rtl/T80/t80_4_core.vhd
add_file ../src/rtl/T80/t80_5_pa.vhd
add_file ../src/rtl/T80/t80_6_s.vhd
add_file ../src/rtl/Z80CTC/ctc_controler.vhd
add_file ../src/rtl/Z80CTC/ctc_counter.vhd
add_file ../src/rtl/Z80CTC/z80ctc_top.vhd

# Add constraints files
add_file -type cst src/mcr123s_console60k.cst
add_file -type sdc src/mcr123s_console60k.sdc

# Run synthesis, map, and place-and-route
run all
