# CLAUDE.md

Bally Midway MCR arcade cores (MiSTer/Cyclone V origin) ported to Sipeed Tang
Gowin FPGA boards.

**ROMs stream from the user's SD card — the 60K bitstreams contain NO ROM
data.** This is a licensing requirement (a distributed bitstream must not
embed copyrighted ROM data), not just an optimisation, and it is what makes
the planned merged core possible. The 25K is the exception: it stays a
fixed-function baked single-game board. See `TODO.md` item 2.

Games: **MCR-2** — all six (Domino Man default on the 25K; the 60K holds
the whole family behind its OSD). **MCR-3 (91490)** — all three titles
hardware-verified and playable: Tapper, Timber and Discs of Tron (the
latter mirrored, which is correct - the real cabinet has a mirror). **MCR-1** —
Kick/Kickman/Solar Fox; Kickman verified on hardware 2026-07-27 (first ever
MCR-1 run), Kick and Solar Fox not yet exercised. One pack-v2 SD card carries every
game for every family (`tools/make_pack_v2.py`); the product roadmap toward
the full-series jukebox is at the top of `TODO.md`.

**MCR-2 + MCR-3 ARE MERGED** (`mcr23_console60k`, 9 games, flashed as the
power-on default 2026-07-27). MCR-1 folds in once its sprite gfx move to
SDRAM - see TODO item 4a.
**Direction (agreed 2026-07-27): MCR-1/2/3 will be MERGED into one
bitstream** rather than switched by Gowin multiboot — core switching then
becomes the same instant SD reload that game switching already is. Multiboot
was investigated and is deferred to MCR3Scroll/MCR3Mono; the full decode is
preserved in `TODO.md` item 4b. Budget and plan: `TODO.md` item 4a.

## Board projects

| Dir | Board | FPGA | Status |
|---|---|---|---|
| `mcr1_console60k/` | Tang Console 60K | GW5AT-LV60PG484 | **Working** — MCR-1 core; Kickman verified on hardware 2026-07-27 (colours matched vs MAME), loading entirely from the card. ROT90 cabinet, so the picture is rotated on a normal monitor — correct. Kick/Solar Fox not yet run |
| `mcr2_primer25k/` | Tang Primer 25K | GW5A-LV25MG121 | **Working** — Domino Man attract over HDMI, 56/56 BSRAM, timing met. **Deliberately still BAKED** (fixed-function board, not part of the jukebox) |
| `mcr2_console60k/` | Tang Console 60K | GW5AT-LV60PG484 | **Working** — USB HID gamepad; all six games, OSD (Select+Start) switches at runtime via the SD pack; DDR3 framebuffer → 720p HDMI w/ audio; analog VGA on J10 with 15/31 kHz strap. No baked ROMs — Wacko verified loading from the card 2026-07-27 |
| `mcr3_console60k/` | Tang Console 60K | GW5AT-LV60PG484 | **Working** — all three titles verified on hardware: Tapper, Timber, Discs of Tron (sprites from the Tang SDRAM module at 225-deg pin clock, colours verified vs MAME); HALT-watchdog boot (<10 s cold); no baked ROMs, full-from-SD; INSERT CARD screen + hot-insert recovery verified |
| `mcr23_console60k/` | Tang Console 60K | GW5AT-LV60PG484 | **Working — MERGED MCR-2 + MCR-3, 9 games in one bitstream.** This is what the SPI flash holds (power-on default). Roster index <-> (family, slot) translation in the top; both cores instantiated, inactive one held in reset; CPU/sound ROM + bg gfx pair shared. 114/118 BSRAM. **All nine games verified on hardware** (Tapper, Timber, Discs of Tron, Satan's Hollow, Tron, Wacko, Kozmik Kroozr, Two Tigers, Domino Man) |
| `mcr2_console138k/` | Tang Console 138K | GW5AST-LV138 | Stale pre-fix top; needs same backport as 60K. Still baked |

Shared, platform-independent code lives in `src/`:
- `src/rtl/` — MCR2 core (`mcr2.vhd`), T80 Z80, Z80CTC, PLL (`gowin_pll_mcr2.v`), RAM wrappers (`dpram.sv`)
- `src/dvi_tx/` — TMDS encoder + OSER10-based HDMI serializer
- `src/audio/` — delta-sigma PWM DAC
- `src/usb/` — nand2mario `usb_hid_host` (MIT, vendored 2026-07) + 12 MHz
  PLLA (`gowin_pll_usb.v`). Keep `usb_hid_host_rom.hex` next to its `.v` —
  `$readmemh`/`INIT_FILE` resolve relative to the source file's directory.
- `src/ddr3fb/` — nand2mario/gbatang DDR3 framebuffer (vendored 2026-07,
  GPLv3 — see LICENSE.gbatang): `ddr3_framebuffer.v` + Gowin DDR3 IP +
  27 MHz/DDR3/HDMI PLLAs + hdl-util HDMI stack with audio. Used by the 60K
  only (`dvi_tx/` remains the 25K's HDMI path).
- Each board dir has only: `.gprj`, `build.tcl`, `src/<board>_top.sv`, `.cst`, `.sdc`

Because the PLL and `mcr2.vhd` are shared, fixes there apply to every board
automatically; the per-board top/SDC/CST must be kept in sync by hand (the 25K
top is the reference implementation).

## Build (headless)

Use the wrapper — it applies the per-host environment fix-ups below and
optionally regenerates the ROM hex first:

```sh
tools/gw_build.sh mcr2_console60k domino   # merge_roms domino, then build
tools/gw_build.sh mcr2_primer25k           # build with the current hex
```

Set `GOWIN_HOME` if the IDE isn't at the default location for the host.

**Two toolchains are installed.** `tools/gw_build.sh` uses the free
**V1.9.11.03 Education** in `~/IDE` — this is the one that works and the
default for all boards. `tools/gw_build_1912.sh` uses the commercial
**V1.9.12.03** in `~/gowin_1.9.12.03` (node-locked licence at
`~/gowin_1.9.12.03/gowin.lic`, `IDE/bin/gwlicense.ini` points at it).
**Do not use 1.9.12.03 for ascal work: GowinSynthesis crashes with SIGFPE
during "Running inference"** on the same sources 1.9.11.03 builds cleanly
(see the ascal section of `TODO.md` and `docs/gowin_bug_report.md`).

**macOS.** GowinIDE bundles Tcl; the CLI needs dylib/framework paths set
(`$ORIGIN` doesn't resolve on macOS):

```sh
GWLIB=/Applications/GowinIDE.app/Contents/Resources/Gowin_EDA/IDE/lib
GW=/Applications/GowinIDE.app/Contents/Resources/Gowin_EDA/IDE/bin/gw_sh
cd mcr2_primer25k        # or mcr2_console60k
DYLD_LIBRARY_PATH="$GWLIB" DYLD_FRAMEWORK_PATH="$GWLIB" "$GW" build.tcl
```

**Linux** (tarball untarred to `~/IDE` + `~/Programmer`; same
V1.9.11.03 Education build as the Mac, so reports and device support match).
Three separate things must be fixed or `gw_sh` dies before printing anything:

```sh
cd mcr2_console60k
LD_LIBRARY_PATH=$HOME/IDE/lib \
LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libfreetype.so.6 \
QT_QPA_PLATFORM=offscreen \
$HOME/IDE/bin/gw_sh build.tcl
```

| Symptom | Cause / fix |
|---|---|
| `symbol lookup error: libfontconfig.so.1: undefined symbol: FT_Done_MM_Var` | gw_sh's RPATH prefers its own ancient `libfreetype.so.6`; the system fontconfig can't link against it. `LD_PRELOAD` the system freetype. |
| `Cannot mix incompatible Qt library (5.15.13) with this library (5.15.14)` | the bundled Qt **plugins** carry no RPATH, so they pull in the *system* Qt. `LD_LIBRARY_PATH=$HOME/IDE/lib`. |
| `no Qt platform plugin could be initialized` | `gw_sh` builds a QApplication even headless. `QT_QPA_PLATFORM=offscreen`. |

Placement is not bit-identical across hosts — a Linux-built `.fs` differs in
size/checksum from the Mac's for the same sources. That is normal Gowin
placer variation, not a config mismatch; judge builds by the sanity checks
below, not by diffing bitstreams.

Bitstream lands at `<board>/impl/pnr/<board>.fs`. Flash with Gowin Programmer
(GUI) or `openFPGALoader`. To make a build the POWER-ON default (survives
power cycles, replaces whatever is in the SPI flash - e.g. NESTang):
`openFPGALoader -b tangconsole -f bitstreams/console60k_<game>.fs`.
For a volatile test load (SRAM only, lost at power-off) drop the `-f`.

**openFPGALoader must be built from source — do not `apt install` it.**
Ubuntu 24.04 ships v0.12.0, whose board list stops at `tangmega138k`: there
is no `tangconsole`, so the 60K (the main target) cannot be flashed by it.
Build master instead (v1.1.1 verified working here, `~/openFPGALoader`):

```sh
sudo apt install -y libftdi1-dev libusb-1.0-0-dev libhidapi-dev zlib1g-dev
git clone https://github.com/trabucayre/openFPGALoader.git && cd openFPGALoader
cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build -j$(nproc)
sudo cmake --install build
# udev rules are NOT installed by cmake -- copy them by hand:
sudo cp 99-openfpgaloader.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules && sudo udevadm trigger
```

Use the `99-` rules file, not `70-`: only `99-` sets `GROUP="plugdev"`, and
at priority 99 the `TAG+="uaccess"` in both files is already inert (systemd's
`73-seat-late.rules` has run). So membership in `plugdev` is what actually
grants access — and unlike `uaccess` it also works over SSH with no local
seat. The Console 60K enumerates as FTDI FT2232 (`0403:6010`).

Sanity check with no board attached: `openFPGALoader --detect` should exit 1
with `unable to open ftdi device: -3 (device not found)`. There is no offline
dry-run — the cable is opened before the `.fs` is ever parsed.

### Post-build sanity checks (do these every build)
1. **No `PA1019`** (PLL VCO out of range) warning in the log — **NO
   EXCEPTIONS.** Any PA1019, naming any PLL, is a build-breaker.
   **This reverses earlier guidance (corrected 2026-07-28).** `gowin_pll_hdmi`
   used to warn (27 MHz x 55 = 1485 MHz VCO, outside the GW5A 700–1400 MHz
   range) and that was written off as "NESTang's standard config, confirmed
   working". **It was not working.** It was the cause of the long-standing
   HDMI dropout: the link held sync perfectly for a few minutes after
   configuration, then went marginal (black/frozen frames), and recovered on
   every reconfig — which is why every measurement taken just after flashing
   looked clean. Analog VGA never dropped, because it runs off
   `gowin_pll_mcr2`, not this chain, and picture CONTENT stayed correct
   throughout, so only the link was failing.
   Fixed in `src/ddr3fb/gowin_pll_hdmi27.v`: `MDIV_SEL=41, MDIV_FRAC_SEL=2`
   (41.25) with `ODIV0_SEL=3` gives the SAME 371.25 MHz TMDS clock from a
   VCO of 1113.75 MHz, in spec. **Soak-verified: 30 min with no
   reconfiguration, 0 black intervals, 0.000% black** (the old PLL degraded
   within minutes), confirmed on the monitor as well as the capture card.
   The PLL is shared, so this fixes `mcr2_console60k`, `video_test60k`,
   `merge_probe` and `ascal_test60k` alike.
   **Measuring dropouts:** record TIME SINCE CONFIGURATION and soak for tens
   of minutes — a fresh flash hides this class of fault. Give ffmpeg
   exclusive use of the capture device (a second process on `/dev/video4`
   manufactures dropouts), and discard events before t=0.5 s (capture-card
   lock-up).
2. 25K only: `BSRAM ... 56/56` in `impl/pnr/*.rpt.txt` — must not exceed 56.
3. Positive SETUP and HOLD slack in `impl/pnr/*.timing_paths`.
4. **`grep -i "Undeclared symbol" impl/gwsynthesis/*.log` must be empty.**
   Gowin turns use-before-declaration into an implicit **1-bit wire** with
   only a warning. A multi-bit signal referenced above its declaration
   becomes one floating bit — this produced a perfectly synced, entirely
   black HDMI picture (rgb input dead, its FIFO swept as unused) while the
   build reported zero errors. Declare before use, always.

## ROMs

MAME ROM zips live in `roms/` — **gitignored, so a fresh clone has none**;
copy them in by hand on each machine (the script now aborts with exit 1 and
leaves `game_config.vh` alone if the zip is missing, rather than producing a
half-switched build). Generate the hex tables from the **repo root**:

```sh
python3 tools/merge_roms.py domino    # default (MCR-2)
python3 tools/merge_roms.py tron      # MCR-2
python3 tools/merge_roms.py kick      # MCR-1 -> mcr1_console60k/
python3 tools/merge_roms.py solarfox  # MCR-1
```

Each game carries a `family` (`mcr1`/`mcr2`); merge_roms writes that
family's board dir(s) only, so an MCR-1 build never clobbers the MCR-2
boards' `game_config.vh` (and vice versa). The MCR-1 core lives in
`src/rtl/mcr1.vhd` (vendored from Arcade-MCR1_MiSTer, patched: exposes
`hcnt_out`/`vcnt_out` and INIT_FILE-bakes its gfx dprams, same as
`mcr2.vhd`). Its download/ROM map differs (CPU 0x0000, sound 0x8000,
sprites 0x10000, bg 0x18000/0x19000) — the `mcr1_console60k` top and
merge_roms both follow it.

Writes `rom_*.hex` into every board's `src/` and into `src/rtl/`, **and**
generates `game_config.vh` in the console board dirs.

**The 60K boards no longer USE those hex files** — they build with no baked
ROMs at all (licensing). `merge_roms` still emits them because the 25K/138K
tops do use them, and because `game_config.vh` is still needed: it sets
`GAME_DEFAULT`, the slot the loader falls back to when the SD prefs sector
has no valid entry. On the 60K all per-game input/DIP maps are compiled in
and muxed at runtime by `game_id` (owned by `src/rtl/osd.sv`), so ROMs and
input map always match — both follow whatever slot the loader actually
loaded.

**Bake control is per board, via generics** (`GFX1_1_INIT`, `GFX1_2_INIT`,
`GFX2_INIT`, `GFX_LOADABLE`) on `mcr1.vhd` / `mcr2.vhd`. Defaults bake, so
the shared cores keep the 25K and 138K working unchanged; the 60K tops pass
empty names + `GFX_LOADABLE(1)`. Their CPU/sound dprams likewise use
`.LOADABLE(1)` instead of `.INIT_FILE(...)`.
**Never drop an `INIT_FILE` without setting `LOADABLE`** — see the dpram
warning in the BSRAM section; port B goes read-only and the download dies
silently.

Gowin resolves `INIT_FILE`/`include` relative to the **instantiating source
file's directory**: the board tops (`rom_main.hex`, `rom_snd.hex`,
`game_config.vh`) resolve next to themselves; gfx ROMs instantiated inside
`mcr2.vhd` resolve against `src/rtl/`. That's why the script writes to
multiple dirs. (`src/roms/*.hex` is a stale Satan's Hollow set from the
initial port — do not point new code at it.)

### gfx1 background plane order is PER-CORE (cost a day, 2026-07-27)
`merge_roms`' `gfx1_1_file`/`gfx1_2_file` are the two bg BITPLANES, and the
right order depends on which core, because `mcr2.vhd` and `mcr3.vhd` wire
their bg dprams differently:

| Core | `gfx1_1` = | Verified by |
|---|---|---|
| MCR-3 (`mcr3.vhd`) | the ROM MAME loads **second** (higher offset) | tapper, timber |
| MCR-2 (`mcr2.vhd`) | the ROM MAME loads **first** (offset 0) | domino, shollow, tron, wacko, kroozr |

### MCR-3 sprite ROMs are FOUR 32 KB BITPLANE SLOTS, not a blob
The sprite engine fetches each 32-bit word as `{Q3[i],Q2[i],Q1[i],Q0[i]}`
from the four quarters of the 128 KB region, so every bitplane owns a fixed
32 KB slot. `merge_roms` assembles gfx2 **by plane**, padding each pair of
files to its slot. Concatenating and padding at the end only works for a
full 128 KB set; a 64 KB set (Discs of Tron) then leaves Q2/Q3 empty and
sprites draw with 2 of 4 planes — striped, missing interior pixels. This is
MCR-3 only: MCR-1/MCR-2 sprites are a FLAT 32 KB region (one `aWidth=15`
dpram read 8 bits at a time), and padding their planes overflows it and
shifts every later game in the pack.

Check a new game with `mame -listxml <game> | grep 'region="gfx1"'` — the
`offset=` attributes are the authority. Getting it backwards gives **correct
shapes with wrong colours on bg tiles only** (sprites/sky/ground look fine),
because both ROMs share `bg_code_line` and supply only the low 2 bits of
`bg_palette_addr`. That exact symptom hit Timber and Discs of Tron.

**openFPGALoader on this board**: SRAM loads fail SILENTLY ~1/3 of the
time ("DONE" prints regardless) - confirm every load took via a per-build
beacon marker before trusting results. Flash writes corrupt without
verification - always `-f --verify`, retry until clean (first attempt
usually fails just past byte 0x30000).

Prebuilt flashable images are kept in `bitstreams/` (e.g.
`console60k_tron.fs`, `console60k_domino.fs`). These date from the era when
a game was chosen by BAKING its ROMs, so most are now only useful as
archives — on the 60K the game is chosen from the card via the OSD, and one
bitstream per FAMILY covers every game in it. Regenerate after RTL changes;
the per-game names are historical.

Per-game notes (bit maps verified against MAME `mcr.cpp`):
- **Domino Man** — 4-way stick (IP1), Button 1 = IP0 bit 4, DIPs 0x3E.
- **Tron** — 8-way stick on **IP2**, aim dial (absolute 8-bit spinner) on
  IP1 via `spinner.sv` (pad X/Y rotate; `spin_in` reserved for a USB mouse),
  trigger = IP0 bit 4, DIPs 0x80. MAME marks the dial PORT_REVERSE — if aim
  feels inverted, swap the spinner's minus/plus hookup.
- **Satan's Hollow** — fire/shield/right/left on IP1 low nibble, DIPs 0xFF.
- **Wacko** — trackball X/Y on IP1/IP2 (two `spinner.sv` instances driven by
  the d-pad); aim joystick on the face buttons via IP4.
- **Kozmik Kroozr** — spinner bits packed into IP1 (bit6=dial[7],
  bits2:0=dial[6:4], active **high**); analogue stick synthesised on
  IP2/IP4 (ramps toward 0x30/0x98, recentres to 0x64 on release).
- **Two Tigers** — the `twotigerc` conversion set; dial on IP1, fire
  buttons on IP2[3:0]. The dedicated set needs a videoram remap we lack.

All six MCR-2 games fit the same core: `merge_roms.py` has ROM specs for
each and `make_pack_v2.py` packs every family's games into one card image.

MCR-3 per-game notes:
- **Tapper** — hardware-verified. The reference for MCR-3 gfx1 plane order.
- **Timber** — WORKS (plays perfectly when chosen from the OSD). Needed the
  gfx1 plane-order correction above. One caveat open: a BOOT load renders
  corrupt bg tiles while an OSD load is fine — see TODO item 3.
- **Discs of Tron** — WORKS (verified 2026-07-27). Screen is mirrored,
  which is CORRECT — the real cabinet uses a mirror. Needed the gfx1
  plane-order fix AND the sprite bitplane-padding fix (its 64 KB sprite set
  left two of four planes empty — see the sprite note below). Aim dial not
  wired; aim uses the dedicated IP2 buttons via `spinner.sv`.

## Hard-won constraints — do not regress these

### PLL (`src/rtl/gowin_pll_mcr2.v`)
GW5A PLLA VCO **must stay within 700–1400 MHz**. Current config: 50 MHz in,
MDIV 20 → VCO 1000 MHz; ODIV0 8 → `clk_p5` 125 MHz (TMDS 5× bit clock);
ODIV1 25 → `clk_sys` 40 MHz (core). `clk_pixel` = 25 MHz via `CLKDIV`
DIV_MODE=5. A 1500 MHz VCO was the root cause of the original "rolling screen"
(every derived clock silently wrong, core at ~75 MHz).

### SDC (per board)
The `create_generated_clock` lines for `clk_sys`/`clk_pixel` and the
`set_clock_groups -asynchronous` between them are **required**. Without them
the pixel domain falls back to a 100 MHz default and reports false setup
violations. Do not remove; instance names (`pll_inst/PLLA_inst/CLKOUT1`,
`clk_div_inst/CLKOUT`) must match the top.

### HDMI video — 60K: DDR3 framebuffer (current)
**Two structural rules, both learned the hard way:**
1. **`clk_g` (50 MHz DDR3-controller/mDRP clock) MUST come from a PLL
   output, not the raw clock pad** — pad-fed clk_g put a derived controller
   clock on generic routing (PR1014) and the DDR3 IP never started.
2. **The TMDS serializer clocks MUST be one chain**: 27 MHz → gowin_pll_hdmi
   → 371.25 MHz → CLKDIV÷5 → 74.25 MHz (NESTang's arrangement). Upstream
   gbatang clocks the hdmi module from the DDR3 controller's `clk_x1` and
   the serializer from a second PLL — the OSER10 PCLK/FCLK phase is then
   routing luck, and it produced synced-but-dead TMDS here even in a
   minimal design. The scanout still runs on `clk_x1`; pixels cross into
   `hclk` via a shadow raster (720p counters re-aligned each frame, running
   32 px ahead) into a 64-deep async FIFO — drift-free because both clocks
   descend from the same 27 MHz.

The 60K top streams the core's native pixels (512×480, RGB444, one `fb_we`
per 20 MHz pixel, `cap_delay` capture-window shift — live-tunable with
Select+D-pad, current value in the UART beacon as `dXX`) into
`ddr3_framebuffer` (gbatang), which upscales to 1280×720@60 HDMI with audio
— fully decoupled from core timing: no shimmer, no genlock, and HDMI stays
alive in 15 kHz mode (capture height switches to 240). `disp_width=960`
gives 4:3. The framebuffer generates its own 297 MHz DDR3 + 74.25/371.25 MHz
HDMI clocks from a 27 MHz PLLA; the SDC declares `clk4x`/`clk1x` on
`fb_inst/` nets and cuts them from `clk_sys` (the internal async FIFO is the
crossing). Costs ~15 BSRAM + ~3.5k LUT; 5/8 PLLAs used.

### HDMI video pipeline — 25K only (legacy line-buffer approach)
The core natively emits 634×525 @ 20 MHz (512×480 active, 31.5 kHz/60.09 Hz)
in `tv15Khz_mode=0`. The 25K conforms it to 640×480@~60 via a 2-line
ping-pong buffer (clk_sys → clk_pixel). Three deliberate oddities:
- **`H_TOTAL = 793`** (not 800): matches output line rate to the core within
  0.06%, minimizing mid-line buffer switches (shimmer). Don't "fix" to 800.
- **Vertical genlock**: output vcnt restarts on core vblank falling edge —
  prevents slow vertical roll from the residual rate mismatch.
- **`CAP_DELAY = 13`**: compensates the core's RGB-vs-hcnt pipeline lag.
  Tuning: sliver on left edge → increase; on right edge → decrease.

Residual faint shimmer is a known limit of the line-buffer approach on the
25K (no room for a frame buffer there).

### BSRAM budget (25K)
56 blocks total. Domino Man fits exactly (CPU 16 + sound 8 + bg 2×4 + sprites
16 + core RAM/line buffer ~8). Satan's Hollow's 48 KB CPU ROM forces dropping
the bg tile ROMs.

### `dpram` has three modes and the wrong one fails SILENTLY
| Parameters | Behaviour | Use for |
|---|---|---|
| `INIT_FILE` set | dual-port RAM, port B writable, preloaded from hex | baked game (25K/138K) |
| `LOADABLE(1)`, no `INIT_FILE` | same but starts blank — SD is the only source | **all 60K ROMs** (licensing) |
| neither | dual-port RAM, writes on **port A only** | scratch RAM nothing downloads to |

**`INIT_FILE` is a power-on DEFAULT, not a ROM** — port B takes writes
normally, which is how the SD loader overwrites a baked ROM at boot. (An
older revision did tie port B off; anything claiming the `dl_*` bus is
"inert" is stale.) The trap: **dropping an `INIT_FILE` without setting
`LOADABLE` silently selects the third mode**, port B goes read-only, and the
download dies with no error anywhere. Always pair the two. All three modes
are pinned by `sim/dpram/` — run those if you touch it.

### Tang SDRAM module (J9): pin clock MUST be phase-shifted ~225 deg
The module (Winbond W9825G6KH) is fine; a 0-deg forwarded SDRAM_CLK puts
the chip's command sampling on the exact instant commands change, and the
margin drifts with temperature/activity. Symptom: data "decays" to all-FF
within ~30-100 s of idle regardless of refresh (v5's white sprite boxes;
two handoffs of wrong theories). Every nand2mario design ships this
discipline (snestang: `assign O_sdram_clk = fclk_p` at ~225 deg). Ours:
`gowin_pll_core80` CLKOUT3 = 80 MHz @225 deg (PE 6+2/8) -> `sdram_gw`'s
`clk_fwd`. Keep `sdram_gw`'s read states at upstream values (READ1=2,
READ1b=3, CL2) - moving them past RAS1 breaks its oe_latch clearing.
Retention harnesses to re-verify any change:
`mcr2_console60k/diag/build_retention.tcl` (nand2mario reference) and
`build_gwret.tcl` (sdram_gw), write-once-verify-every-30s over UART.

### Buttons / diagnostics
25K: S1 = reset, S2 = color-bar test pattern + Coin 1.
60K: key AA13 = reset, key AB13 = Coin 1. **Select+Start opens the OSD
game-select menu** (Up/Down move, A loads the highlighted game from the SD
pack, B exits; all game inputs are masked while it is open; the raster
stops during the ~1 s reload, so the screen freezes/drops sync — expected).
Selections persist: the loader writes the chosen slot to SD sector 2047
("MCRPREF1", CMD24) and consults it at power-on, so the cabinet boots back
into the owner's game; the OSD-commanded reload path bypasses the pref.
The menu draws in the core raster domain, so it appears on HDMI and analog
video alike, rotated on Tron/Shollow (ROT90 cabinets). UART beacon on U15
(→ USB-C serial, 115200): `FB c<calib> r<ddr_rst> x<clk_x1 cnt> q<27M cnt>
d<aux>` every ~0.5 s, where `d`'s high 3 bits = running `game_id` and low
5 bits = cap_delay — frozen counters identify a dead clock domain with the
case closed. Select+D-pad Right/Left tunes the capture delay live (D-pad is
masked from the game while Select is held).

### Analog video (60K): PmodVGA on J10
`vga_r/g/b[3:0]` (3:3:3 core color MSB-replicated to 4:4:4) + `vga_hs/vs`,
jumper-wired per the recipe in `mcr2_console60k.cst`. `mode15_n` strap
(J10-37): open = 31 kHz progressive; GND = native 15 kHz (HS pin carries
csync, HDMI intentionally falls back to color bars because the line-buffer
scaler can't track 15 kHz timing). The J10/SDRAM1 balls overlap CPU/SSPI
config pins → `build.tcl` needs the `-use_*_as_gpio` option block (already
there; the IDE JSON equivalents are the CPU/MSPI/SSPI/etc. booleans).

## Docs map

- `docs/bench_wiring.md` — **what the current bitstream drives on J10**
  (VGA, straps, debug pins, audio) for temporary bench hookups. Wire from
  this, not from the shield spec's §4b cabinet plan.
- `TODO.md` — **open issues and known gaps, consolidated**. Check (and
  update) this before starting anything; per-doc "open items" sections feed
  into it.

- `TODO.md` items 2 and 4 — **start here for current direction**: the
  everything-from-SD status and the merge-vs-multiboot decision with its
  measured BSRAM budget. These supersede the handoffs for "what next".
- `handoff_v8_sprite_shift.md` — the MCR-3 sprite "detached handle"
  investigation. **RESOLVED 2026-07-27** (see its header): the cause was a
  pipeline-depth mismatch in the top's sprite dl→SDRAM write, not anything
  in the core. Its "instance dependence", "leading suspects" and "next
  steps" sections are superseded — read the header, not the body.
- `handoff_v7_jukebox.md` — previous handoff: platform state after
  the MCR-3 bring-up marathon (SDRAM 225-deg fix, boot watchdog, pack v2,
  Timber/DoT, roadmap progress). Start here.
- `handoff_v6_sdram_refresh.md` / `handoff_v5_mcr3_sprites.md` —
  historical MCR-3 sprite debugging. **v6's root cause (refresh
  starvation) and v5's suspects were all DISPROVED** — the real fault was
  the SDRAM pin-clock phase (see the 225-deg section above and commit
  3dbe824). Kept for the record; do not act on their conclusions.
- `handoff_v4_60k_multicore.md` — the 60K multi-core platform design and
  family porting plan (still accurate for platform structure).
- `handoff_v3_video_and_domino.md` — historical: the 25K HDMI pipeline
  deep-dive + Domino POC (its "paths forward" are all done).
- `handoff_v2_design.md` — SDRAM/V2 plan, shield electrical spec, MCR
  J2/J3/J4/J5 connector pinouts.
- `board_comparison_and_bom.md` — board comparison + shield BOM.
- `pcb_design.md` — Universal MCR shield PCB spec; generator at
  `tools/generate_pcb.py` (run with KiCad's bundled python) →
  `mcr_shield.kicad_pcb`.
- `docs/universal_mcr_shield_spec.md` — **consolidated shield spec** (net
  table, electrical, pin budget); supersedes the electrical sections of the
  two docs above for new work.
- `docs/shield_j10_pinout.md` — **the frozen 40-pin J10 header sheet for
  the shield PCB** (video + controls on one header via 74HC165/595
  chains); the authority over spec §4b for any pin question. Change this
  file first if a pin must move.
- `docs/shield_wiring.md` — **cabinet-side build companion**: the MCR
  connector footprints the harness plugs into, chip-wiring diagrams
  (74AHC165 input chain, 74HC595 output chain, sync buffer, DAC), the
  analog/ADC design (Spy Hunter + Max RPM only, switchable), and the BOM.
- `docs/sd_card_layout_v2.md` — **planned** SD card format (unified ROM +
  core directory across MCR-1/2/3). **DEFERRED — do not implement, and do
  not change the on-card format or `rom_loader.sv`, until MCR-3 Tapper
  renders sprites from the current card.** Records the live
  `PACK_BASE = 2048` collision between `make_rompack.py` and
  `make_sprite_pack.py` and its no-format-change workaround.
- `docs/mcr_game_input_matrix.md` — machine-readable transcription of the
  pinout matrix PDF + MAME-verified SSIO bit maps; use it when porting a
  new game.
- `docs/MCR_Master_Pinouts.pdf` — master MCR cabinet pinout matrix (the
  original source for the two docs above). Confirms per-game J2/J3/
  J4/J5 usage; e.g. Domino Man = 4-way joystick + 1 button ("Place/Strike").
- `refs/` — **gitignored** local checkouts of the five MiSTer MCR cores
  (MCR1/MCR2/MCR3/MCR3Mono/MCR3Scroll), the source material for the
  porting plan in `docs/mcr_core_roadmap.md`. Copy files out deliberately
  (with a dated comment) — never point the build at them directly.
- `docs/pinrefs/` — known-good Tang Console 60K / Mega 60K constraint files
  fetched from nand2mario's nestang/snestang/gbatang and Sipeed's NEO_DOCK
  examples; the authority for 60K pin questions (USB, SD, SDRAM, DDR3,
  PMODs, UART).
- `docs/Tang_Mega_60K_Console_32001{A,C}__Schematics.pdf` — official dock
  schematics (rev A and C). Sheet 4/6 = SOM connector ball maps, sheet 8 =
  the two 2×20 headers (J9 "SDRAM0" near PCIe, J10 "SDRAM1"/GBA near
  PMODs). J10's full pin↔ball table is transcribed in
  `universal_mcr_shield_spec.md` §4a.
- `README.md` / `walkthrough.md` — overview + GUI build steps (partly stale:
  written before the 60K/138K backlog was known).

## Gotchas

- **The IDE and `build.tcl` are separate config paths, and the IDE rewrites
  its JSON with GUI defaults on save** — settings put there by hand get
  clobbered. Everything `build.tcl` sets must be mirrored in
  `impl/<project>_process_config.json` for IDE builds:
  | build.tcl | JSON key | symptom if wrong |
  |---|---|---|
  | `-top_module` | `TopModule` | synthesis picks `T80pa`; PnR error PA2024 |
  | `-verilog_std sysv2017` | `Verilog_Standard` = **`"Vlg_Std_Sysv2017"`** (exact token; an invalid value silently falls back to Verilog-2001) | `.sv` parsed as Verilog-2001: "single value range not allowed" (usb_hid_host.v:42), or "Instantiating unknown module 'uart_beacon'" because its ANSI port initializer won't parse |
  | `-place_option 2` | `Place_Option` = `"2"` | **CONFIRMED on hardware: `"0"` (the IDE default) yields a bitstream that builds clean and meets timing but whose DDR3 never trains → HDMI stays black.** Always 2 for this design. |
  | `-use_cpu_as_gpio` etc. | `CPU`,`MSPI`,`SSPI`,`READY`,`DONE`,`I2C` = true | "location is a dedicated pin (CPU)" on J10/`vga_*` pins (GUI: Place & Route → Dual-Purpose Pin) |
  Never set `JTAG` true — that removes the programming interface.
  **The headless `build.tcl` flow is immune to all of this** and is the
  recommended path on any machine (`gw_sh build.tcl` from the board dir).

  Also: **`gw_sh` rewrites this JSON after a build and does NOT persist
  `place_option` / `rw_check_on_ram` / `multi_boot`** — it writes their
  defaults back regardless of what build.tcl passed. So the file is not a
  record of how a CLI build was made (build.tcl is), it churns in `git
  status` after every build, and its values matter *only* to IDE builds.
  If you build in the IDE, verify **Place & Route → Place Option = 2**
  yourself; that one silently costs you all HDMI output.
- **Bank 9 is a 1.5 V bank on the 60K once DDR3 is used** (the DDR3 data
  group lives there). Anything on Bank 9 balls (user keys AA13/AB13, Y12,
  Y13, Y14, W11…) must be `IO_TYPE=LVCMOS15 BANK_VCCIO=1.5` — LVCMOS33
  there fails PnR with CT1136 bank conflicts.
- Tang Console 60K quirks: user keys are **active low** (the 60K top inverts
  them; the 25K's are active high), clock is 50 MHz on V22, and
  `-device_version B` is required. The USB-A D+/D− lines land on FPGA pins
  (usb1: H13/G13, usb2: M15/M16) with the 15 kΩ host pulldowns already on the
  board — ready for nand2mario's `usb_hid_host`. Tang SDRAM module chip
  select is F21 on the Console (F19 on the Mega 60K dock), and F19/F20 are
  currently used as PMOD1 button inputs — reassign if the SDRAM module goes in.
- Cabinet video/audio pins in the 60K CST are marked PROVISIONAL — re-verify
  header positions against the Sipeed schematic before wiring a shield.
- The 138K project top/SDC are still the pre-fix architecture (direct
  core→HDMI, no line buffer). Port from the 60K top when needed.
- `impl/` outputs are committed in this repo; expect large binary diffs after
  builds.
- Working-tree changes are often intentionally uncommitted during bring-up;
  check `git status` before assuming HEAD reflects the working design.
