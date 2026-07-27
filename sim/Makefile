# Verilator testbenches for the SD/ROM-loader gateware.
#   make        - run every testbench
#   make sd     - SD card init + block read
#   make loader - ROM pack loading, including the missing-pack error path
#
# These run on the host in seconds; use them before spending a build+flash
# cycle on the board.
#
# REQUIRES VERILATOR 5.x - both --binary and --timing arrived in v5, and the
# testbenches use delays/event controls that v4 rejects as UNSUPPORTED. The
# Linux box here has 4.204 from apt, so these do NOT run there; build a v5
# from source or run them on the Mac. `verilator --lint-only` on the RTL
# alone still works under v4 and is worth doing as a cheap syntax check.
#
# The dpram mode tests are separate and use iverilog (any version):
#   cd sim/dpram && see its README

VERILATOR ?= verilator
VFLAGS    := --binary --timing -j 4 -Wno-fatal
RTL       := ../src/rtl

.PHONY: all sd loader memtest clean

all: sd loader memtest

sd: obj_dir/tb_sd_reader
	@./obj_dir/tb_sd_reader | grep -vE '^- '

loader: obj_dir/tb_rom_loader
	@./obj_dir/tb_rom_loader | grep -vE '^- '

memtest: obj_dir/tb_sdram_memtest
	@./obj_dir/tb_sdram_memtest | grep -vE '^- '

obj_dir/tb_sdram_memtest: tb_sdram_memtest.sv sdram_port_model.sv $(RTL)/sdram_memtest.sv
	@$(VERILATOR) $(VFLAGS) --top-module tb_sdram_memtest $^ -o tb_sdram_memtest > /dev/null

obj_dir/tb_sd_reader: tb_sd_reader.sv sd_card_model.sv $(RTL)/sd_reader.sv $(RTL)/sd_spi_phy.sv
	@$(VERILATOR) $(VFLAGS) --top-module tb_sd_reader $^ -o tb_sd_reader > /dev/null

obj_dir/tb_rom_loader: tb_rom_loader.sv sd_card_model.sv $(RTL)/sd_reader.sv $(RTL)/sd_spi_phy.sv $(RTL)/rom_loader.sv
	@$(VERILATOR) $(VFLAGS) --top-module tb_rom_loader $^ -o tb_rom_loader > /dev/null

clean:
	rm -rf obj_dir
