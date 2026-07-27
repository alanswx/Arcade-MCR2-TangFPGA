# GowinSynthesis defect reproducer — ascal on GW5AT-60

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
| `src/ascal_upstream.vhd` | Temlib's ascal, **unmodified**. md5 `1b17376e8bf19b5c3c96c42d8d588ae6` |
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
