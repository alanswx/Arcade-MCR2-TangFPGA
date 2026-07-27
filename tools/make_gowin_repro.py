#!/usr/bin/env python3
"""Package a standalone, self-contained reproducer to send to Gowin support.

Run from the repo root:   python3 tools/make_gowin_repro.py

Produces gowin_bug_repro/ with a flat src/ (no relative paths outside the
directory), two build scripts, the bug report, and the simulation evidence.
Zip that directory and send it.
"""
import hashlib
import pathlib
import shutil
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
OUT = ROOT / "gowin_bug_repro"

if OUT.exists():
    shutil.rmtree(OUT)
(OUT / "src").mkdir(parents=True)
(OUT / "sim").mkdir()

# ---------------------------------------------------------------- RTL sources
# (source path, destination name)
FILES = [
    ("ascal_test60k/src/ascal_test60k_top.sv", "ascal_test60k_top.sv"),
    ("src/testpat/mcr_testpattern.sv",         "mcr_testpattern.sv"),
    ("src/ascal/ascal_gw.vhd",                 "ascal_gw.vhd"),
    ("src/ascal/ascal_avl_ddr3.sv",            "ascal_avl_ddr3.sv"),
    ("src/rtl/gowin_pll_mcr2.v",               "gowin_pll_mcr2.v"),
    ("src/ddr3fb/pll_27.v",                    "pll_27.v"),
    ("src/ddr3fb/pll_ddr3.v",                  "pll_ddr3.v"),
    ("src/ddr3fb/gowin_pll_hdmi27.v",          "gowin_pll_hdmi27.v"),
    ("src/ddr3fb/pll_mDRP_intf.v",             "pll_mDRP_intf.v"),
    ("src/ddr3fb/ddr3_memory_interface.v",     "ddr3_memory_interface.v"),
    ("src/dvi_tx/dvi_tx_ext.sv",               "dvi_tx_ext.sv"),
    ("src/ddr3fb/hdmi/tmds_channel.sv",        "tmds_channel.sv"),
    ("src/rtl/uart_beacon.sv",                 "uart_beacon.sv"),
    ("ascal_test60k/src/ascal_test60k.cst",    "ascal_test60k.cst"),
    ("ascal_test60k/src/ascal_test60k.sdc",    "ascal_test60k.sdc"),
]

# the two ascal variants: unmodified upstream, and ours with the Gowin patches
ASCAL = [
    ("refs/Template_MiSTer/sys/ascal.vhd", "ascal_upstream.vhd"),
    ("src/ascal/ascal.vhd",                "ascal_gowin.vhd"),
]

missing = []
for src, dst in FILES + ASCAL:
    p = ROOT / src
    if not p.exists():
        missing.append(src)
        continue
    shutil.copy(p, OUT / "src" / dst)
if missing:
    sys.exit("missing sources:\n  " + "\n  ".join(missing))

up_md5 = hashlib.md5((ROOT / ASCAL[0][0]).read_bytes()).hexdigest()

# ------------------------------------------------------------- simulation kit
for src, dst in [
    ("sim/tb_ascal.vhd",            "tb_ascal.vhd"),
    ("sim/tb_ascal_bridge.vhd",     "tb_ascal_bridge.vhd"),
    ("sim/mk_ascal_sim.py",         "mk_ascal_sim.py"),
    ("tools/ascal_sim_check.py",    "ascal_sim_check.py"),
    ("sim/vsynth/synth_top.v",      "vsynth_top.v"),
    ("sim/vsynth/ddr3_model.v",     "vsynth_ddr3_model.v"),
    ("sim/vsynth/sim_main.cpp",     "vsynth_main.cpp"),
]:
    p = ROOT / src
    if p.exists():
        shutil.copy(p, OUT / "sim" / dst)

# mk_ascal_sim.py points at the repo layout; retarget it at the package layout
mk = OUT / "sim" / "mk_ascal_sim.py"
if mk.exists():
    t = mk.read_text()
    t = t.replace('parent.parent / "src/ascal/ascal.vhd"',
                  'parent.parent / "src/ascal_gowin.vhd"')
    mk.write_text(t)

shutil.copy(ROOT / "docs/gowin_bug_report.md", OUT / "BUG_REPORT.md")

# ------------------------------------------------------------- build scripts
COMMON = """set_device GW5AT-LV60PG484AC1/I0 -device_version B

set_option -synthesis_tool gowinsynthesis
set_option -output_base_name {base}
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

{ascal}

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
"""

# ------------------------------------- minimal standalone PA2122 reproducer
# Deliberately does NOT use ascal_gw.vhd: that wrapper exposes debug taps that
# only exist in the patched ascal. This is the smallest thing that shows the
# defect - no video, no DDR3, no board, no constraints.
(OUT / "src" / "pa2122_min.vhd").write_text("""\
--------------------------------------------------------------------------------
-- Minimal reproducer for GowinSynthesis PA2122.
--------------------------------------------------------------------------------
-- Instantiates UNMODIFIED upstream ascal.vhd and does nothing else.
-- Synthesis succeeds; PnR then fails with
--   ERROR (PA2122) : Not support '...'(SPX9) WRITE_MODE = 2'b10,
--                    please change write mode WRITE_MODE = 2'b00 or 2'b01.
-- because GowinSynthesis packs plain register pipelines (o_h_poly_phase_a*,
-- o_hpixq, ...) into block-RAM shift registers and then requests a write mode
-- those primitives reject.
--   gw_sh build_defect2_PA2122.tcl
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY pa2122_min IS
  PORT (
    i_clk, o_clk, avl_clk, reset_na : IN std_logic;
    i_rgb : IN  std_logic_vector(23 DOWNTO 0);
    i_hs, i_vs, i_de, i_ce : IN std_logic;
    o_rgb : OUT std_logic_vector(23 DOWNTO 0);
    o_hs, o_vs, o_de : OUT std_logic;
    mode_i : IN std_logic_vector(4 DOWNTO 0);
    avl_waitrequest   : IN  std_logic;
    avl_readdata      : IN  std_logic_vector(127 DOWNTO 0);
    avl_readdatavalid : IN  std_logic;
    avl_burstcount    : OUT std_logic_vector(7 DOWNTO 0);
    avl_writedata     : OUT std_logic_vector(127 DOWNTO 0);
    avl_address       : OUT std_logic_vector(27 DOWNTO 0);
    avl_write, avl_read : OUT std_logic;
    avl_byteenable    : OUT std_logic_vector(15 DOWNTO 0));
END ENTITY;

ARCHITECTURE rtl OF pa2122_min IS
  SIGNAL o_r, o_g, o_b : unsigned(7 DOWNTO 0);
BEGIN
  o_rgb <= std_logic_vector(o_r) & std_logic_vector(o_g) & std_logic_vector(o_b);

  u_ascal : ENTITY work.ascal
    GENERIC MAP (
      MASK => x"FF", RAMBASE => x"0000_0000", RAMSIZE => x"0080_0000",
      INTER => false, HEADER => false, DOWNSCALE => false, BYTESWAP => false,
      PALETTE => false, PALETTE2 => false, ADAPTIVE => false,
      FRAC => 8, OHRES => 2304, IHRES => 1024,
      N_DW => 128, N_AW => 28, N_BURST => 2048)
    PORT MAP (
      i_r => unsigned(i_rgb(23 DOWNTO 16)),
      i_g => unsigned(i_rgb(15 DOWNTO 8)),
      i_b => unsigned(i_rgb(7 DOWNTO 0)),
      i_hs => i_hs, i_vs => i_vs, i_fl => '0',
      i_de => i_de, i_ce => i_ce, i_clk => i_clk,
      o_r => o_r, o_g => o_g, o_b => o_b,
      o_hs => o_hs, o_vs => o_vs, o_de => o_de,
      o_vbl => OPEN, o_brd => OPEN, o_ce => '1', o_clk => o_clk,
      o_lltune => OPEN, i_hdmax => OPEN, i_vdmax => OPEN,
      iauto => '1', run => '1', freeze => '0',
      mode => unsigned(mode_i),
      htotal => 1650, hsstart => 1390, hsend => 1430, hdisp => 1280,
      hmin => 160, hmax => 1119,
      vtotal => 750, vsstart => 725, vsend => 730, vdisp => 720,
      vmin => 0, vmax => 719,
      format => "01",
      poly_clk => avl_clk, poly_dw => (OTHERS => '0'),
      poly_a => (OTHERS => '0'), poly_wr => '0',
      avl_clk => avl_clk, avl_waitrequest => avl_waitrequest,
      avl_readdata => avl_readdata, avl_readdatavalid => avl_readdatavalid,
      avl_burstcount => avl_burstcount, avl_writedata => avl_writedata,
      avl_address => avl_address, avl_write => avl_write,
      avl_read => avl_read, avl_byteenable => avl_byteenable,
      reset_na => reset_na);
END ARCHITECTURE;
""")

(OUT / "build_defect2_PA2122.tcl").write_text("""\
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
""")

(OUT / "build_defect1_miscompile.tcl").write_text(
    "# DEFECT 1 (silent miscompile). Uses ascal_gowin.vhd = upstream plus the\n"
    "# syn_srlstyle workaround for PA2122 and debug taps.\n"
    "# Expect: builds CLEAN (0 errors, 0 setup/0 hold violations) and produces\n"
    "# a bitstream whose HORIZONTAL scaling is 4x too fast on hardware, while\n"
    "# vertical scaling is perfect. See BUG_REPORT.md section 3.\n"
    "#   gw_sh build_defect1_miscompile.tcl\n\n"
    + COMMON.format(base="ascal_miscompile",
                    ascal="add_file src/ascal_gowin.vhd"))

# ------------------------------------------------------------------- README
(OUT / "README.md").write_text(f"""# GowinSynthesis defect reproducer — ascal on GW5AT-60

Self-contained. Nothing outside this directory is referenced.

Full analysis: **[BUG_REPORT.md](BUG_REPORT.md)**

## Quickest look — no board needed

```sh
gw_sh build_defect2_PA2122.tcl
```

Synthesis succeeds, then PnR fails:

```
ERROR (PA2122) : Not support 'o_h_poly_phase_a.t1_...'(SPX9)
                 WRITE_MODE = 2'b10, please change write mode
                 WRITE_MODE = 2'b00 or 2'b01.
```

GowinSynthesis packs plain register pipelines into block-RAM shift registers
and then asks for a write mode its own placer rejects.

## The important one — silent wrong hardware

```sh
gw_sh build_defect1_miscompile.tcl
```

Builds **clean**: 0 errors, 0 setup violations, 0 hold violations, `hclk`
~83 MHz actual against 74.25 MHz required. The resulting bitstream scales a
512x480 test pattern into a 720p window. **Vertical scaling is pixel-perfect;
horizontal scaling is exactly 4x too fast**, so the image occupies a quarter
of the window and then repeats.

The same VHDL is correct under GHDL behavioural simulation *and* under GHDL's
own synthesis engine simulated gate-level (see `sim/`).

## Hardware setup (for defect 1)

Sipeed Tang Console 60K. HDMI out shows the scaled pattern; a UART beacon on
the USB-C serial port (115200 8N1) reports internal scaler state.
Analog RGB on the J10 header carries the same source at its native timing.

## Contents

| Path | What |
|---|---|
| `src/ascal_upstream.vhd` | Temlib's ascal, **unmodified**. md5 `{up_md5}` |
| `src/ascal_gowin.vhd` | + `syn_srlstyle` workaround for PA2122, + debug taps |
| `src/ascal_gw.vhd` | thin wrapper: fixes generics, exposes debug taps |
| `src/mcr_testpattern.sv` | 512x480 colour-bar source, 31 kHz arcade timing |
| `src/ascal_avl_ddr3.sv` | Avalon-MM burst master -> Gowin DDR3 app interface |
| `src/ddr3_memory_interface.v` | Gowin DDR3 controller IP (your own) |
| `src/dvi_tx_ext.sv`, `src/tmds_channel.sv` | DVI output |
| `sim/` | GHDL + verilator harnesses proving the RTL is correct |

## Licensing

`ascal.vhd` is by Temlib. Its header states *"This code can be freely
distributed and used for any purpose"*, so it may be used freely as a test
case. Upstream:
<https://github.com/MiSTer-devel/Template_MiSTer/blob/master/sys/ascal.vhd>

`tmds_channel.sv` is from hdl-util/hdmi (MIT). The PLL and DDR3 interface
sources were produced by Gowin's own IP generator.
""")

(OUT / "sim" / "README.md").write_text("""# Simulation evidence

Both of these render the test pattern **correctly**, from the same VHDL that
misbehaves on Gowin hardware.

## 1. Behavioural (GHDL)

```sh
python3 mk_ascal_sim.py          # guards 3 `natural` underflows GHDL rejects
ghdl -a --std=08 ascal_sim.vhd ../src/ascal_gw.vhd tb_ascal.vhd
ghdl -r --std=08 tb_ascal --stop-time=90ms
python3 ascal_sim_check.py ascal_out.txt
```

Expected: one full-width image, `[(160, 1119, 960)]`, colour bars 120 px each.

## 2. GHDL's own synthesis engine, simulated gate-level (verilator)

This is the check Gowin's encrypted `.vg` netlist makes impossible.

```sh
ghdl synth --std=08 --out=verilog ascal_gw > ascal_gw_synth.v
verilator --cc --exe --build -O3 -Wno-fatal --top-module synth_top \\
    -o vsynth_sim vsynth_top.v vsynth_ddr3_model.v ascal_gw_synth.v \\
    ../src/mcr_testpattern.sv ../src/ascal_avl_ddr3.sv vsynth_main.cpp
./obj_dir/vsynth_sim
```

Runs in ~2 seconds. Expected, for a 640-wide window (bars should be 80 px):

```
bars at 81-158, 161-238, 241-318, 321-398, 401-478, 481-558, 561-638
```

Note the output raster free-runs faster than the 60 Hz source here, so the
harness dumps a late frame; dumping an early one shows black because the
framebuffer has not been filled yet.
""")

n = sum(1 for _ in OUT.rglob("*") if _.is_file())
print(f"wrote {OUT.relative_to(ROOT)}/  ({n} files)")
print(f"upstream ascal.vhd md5 = {up_md5}")
