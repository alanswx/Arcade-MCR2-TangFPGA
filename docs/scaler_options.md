# Scaler options on the Tang Console 60K — decision guide

Written 2026-07-29 so a newcomer (human or model) can pick a video path without
re-deriving a week of measurements. Numbers here are **measured on this
hardware**, not datasheet claims. Read `ascal_port_notes.md` for the ascal
history and `scaler_features.md` for the feature specs.

---

## The four paths

| | `bram_scaler.sv` | `ddr3_framebuffer.v` | `ascal.vhd` (upstream) | `ascal_v.sv` (our port) |
|---|---|---|---|---|
| Origin | nestang, ported | gbatang, vendored | Temlib / MiSTer | hand Verilog port |
| Language | SystemVerilog | Verilog | VHDL | SystemVerilog |
| Memory | BRAM only | DDR3 | DDR3 (Avalon) | DDR3 (Avalon) |
| Logic (LUT+ALU) | 1788 (3%) | 4593 (8%) | — | 4710 (8%) |
| Registers | 948 (2%) | 4858 (8%) | — | 4970 (9%) |
| CLS | 1187 (4%) | 4308 (15%) | — | 4357 (15%) |
| BSRAM | 90/118 (77%) | 18/118 (16%) | — | 28/118 (24%) |
| DSP | 3 | 3 | — | 4 |
| Scaling correctness | correct | correct | **BROKEN on Gowin** | **correct (0.333, best)** |
| Buffering | single | single | triple | **triple** |
| Interpolation | nearest | nearest | poly/bicubic/bilinear | nearest only |
| Input auto-detect | no | no | yes | **yes** |
| Output timing | fixed | hardwired 720p | parameterised | parameterised |
| Audio | via HDMI stack | **yes, shipping** | n/a | **yes (added 2026-07-28)** |
| Status | works | **ships 9 games** | dead end | **working** |

### Utilisation, measured 2026-07-29

These are **whole-rig** figures for otherwise-identical builds (same test
pattern, same hdl-util HDMI stack, same Gowin DDR3 controller, same UART
beacon), so the difference between columns is essentially the scaler:

| resource | `ddr3_framebuffer` rig | `ascal_v` rig | delta |
|---|---|---|---|
| Logic (LUT+ALU) | 4593 | 4710 | **+117 (+2.5%)** |
| Registers | 4858 | 4970 | +112 |
| CLS | 4308 | 4357 | +49 |
| BSRAM | 18 | 28 | **+10** |
| DSP | 3 | 4 | +1 |

**ascal_v costs about 117 LUTs and 10 BSRAM more than the shipping
framebuffer** — and that is with its debug instrumentation still compiled in
(CDC counters, fetch/latency counters, `short_cnt`, `collide_cnt`), so the
real delta is smaller. For that it adds triple buffering, input auto-detect,
parameterised output timing, and better scaling (0.333 vs 0.385).

The +10 BSRAM is the two-half line buffer (256 x 128 bits) plus the 32-entry
write FIFO. Both are 128 bits wide, and a wide RAM burns blocks on width
rather than depth, which is why it is more than the raw bit count suggests.

`bram_scaler` is the outlier in the other direction: a third of the logic but
**90/118 BSRAM (77%)**, because the whole framebuffer is in block RAM. Cheap
in logic, but it leaves little BSRAM for a game core.

---

## 1. `src/video/bram_scaler.sv` — BRAM, no external memory

Cheapest and highest timing margin (hclk Fmax 106.6 MHz vs ~83 for the DDR3
path), **zero audio dropouts measured over 15 s**. Costs 90/118 BSRAM at
512x480 RGB222, which is most of the device's block RAM — fine for a scaler
test rig, tight alongside a game core. Single-buffered, so it tears.

**Use when:** you want a known-good reference, or a 240p path where BRAM is
cheap. Storing a 6-bit palette index instead of RGB (MCR's palette is 64x9,
nestang's trick) brings 480p into range.

## 2. `src/ddr3fb/ddr3_framebuffer.v` — what ships today

Drives the merged 9-game core. Streaming prefetch (32-entry buffer,
`PREFETCH_DELAY=44`), so it has **no per-line deadline** — the property
`ascal_v` lacks and the reason it is robust. Costs only ~9 BSRAM.

Measured: h-stripe duplicate rate **0.385** (ideal 0.333), **0 wrong rows per
frame pair**, 1 lost audio cycle in 15 s.

**Limits:** single-buffered (tears), hardwired to 720p (`FRAME_W=1650`,
`FRAME_H=750` are literals), no input auto-detect, nearest-neighbour only.
On underrun it silently substitutes grey `0x202020` — an invisible, unlogged
glitch. Adding triple buffering here is ~50 lines (`scaler_features.md` §1).

**Use when:** you need something that works now. This is the safe default.

## 3. `src/ascal/ascal.vhd` — upstream ascal: DO NOT PURSUE

~3000 lines of portable VHDL, heavily proven on Intel. **It does not work on
GowinSynthesis** and roughly ten hypotheses were eliminated by measurement:
horizontal renders the source into a quarter of the window then repeats, with
a repeat period equal to the SOURCE width regardless of output geometry.
The same RTL is **correct** under GHDL behavioural simulation *and* under
GHDL-synth + verilator, so the RTL is fine and the vendor synthesis is not.
Four separate GowinSynthesis defects are involved (see `ascal_port_notes.md`
§4). V1.9.12.03 is worse — it SIGFPEs and cannot build it at all.

**Do not restart this.** The mechanical route (`ghdl synth --out=verilog`) is
also blocked: the generated Verilog is correct but Gowin rejects it (CK3001).

## 4. `src/video/ascal_v.sv` — hand Verilog port (the active work)

Nearest-neighbour, 16 bpp so 8 pixels fill one 128-bit word exactly, which
removes ascal's `o_off`/`o_pshift`/`sSHIFT` burst-offset machinery entirely.

**Working:** pixel-exact scaling — h-stripe duplicate rate **0.333, ideal, and
better than the shipping framebuffer's 0.385**; colour bars land at exactly
120 px; triple buffering; input auto-detect; parameterised output timing;
HDMI + 1 kHz audio verified with 0 dropouts.

**FIXED 2026-07-29** — the wrong-rows defect is gone. It was never the scaler:
`rd_pending` was a one-cycle pulse treated as a level (the 2FF synchroniser
advances `rq_s2` every cycle), so any read issued while the Avalon FSM was busy
was silently dropped; and `avl_waitrequest` went low on write beats, letting a
read be "accepted" by a write. Hardware after the fix: **342/342 clean frame
pairs, 0 wrong rows, band edge stable at 120 across 120 frames**, colour bars
118-120 px, duplicate rate 0.333.

**Use when:** you want ascal's feature set — triple buffering, input
auto-detect, parameterised output timing — with better scaling than the
shipping framebuffer. Still nearest-neighbour only; interpolation is the
remaining ascal feature not ported.

---

## Modes worth adding to `ascal_v`

Ordered by value to THIS project (an arcade jukebox), not by novelty.

### 1. Rotation for ROT90 cabinets — highest value here
Tron, Satan's Hollow and the MCR-1 titles are ROT90, so today they render
sideways on a normal monitor and the cabinet orientation is baked in. The
frame already lives in DDR3, so rotation is a **read-address transform**
(walk the framebuffer transposed) rather than new storage. This is the one
feature that changes what the product can do, and no other scaler here has it.
Cost: address arithmetic plus a deeper prefetch, because transposed reads
destroy burst locality — read a tile (e.g. 8x8) at a time instead of a line.

### 2. Interpolation — nearest -> bilinear -> sharp-bilinear
The only ascal feature not ported. Nearest at 1.5x maps 480->720 as
1,2,1,2..., so motion crawls; this is inherent, not a bug. **Sharp-bilinear is
the accepted sweet spot for arcade content**, so stopping there is legitimate.
Do it cheapest-first and leave bicubic/polyphase last — that is where all the
DSPs go and the likely `CK3001` trigger (see `ascal_port_notes.md` §4), and it
is why the port was scoped to nearest in the first place.

### 3. Scanlines
Cheap, popular, and a natural fit: darken every Nth output line by a selectable
factor. Pure output-stage arithmetic, no memory cost, a few lines of RTL.
Pairs well with integer scaling below.

### 4. Integer / pixel-perfect scaling mode
512x480 into 960x720 is 1.875x/1.5x — non-integer, hence the line duplication.
An integer mode (2x = 1024x960 pillarboxed, or 1440p output at 3x) gives
uniform pixels and no duplication artifacts at all. Cheap: it is a different
constant in the Bresenham setup, plus window maths.

### 5. Aspect / overscan control
Runtime `hmin/hmax/vmin/vmax` already exist and are per-frame parameters, so
4:3 vs stretch vs zoom is nearly free — expose them to the OSD. This also
gives a knob for the "picture not centred" issue, though the real fix for that
is in the core's active window, not here.

### 6. 240p / 15 kHz input mode
`mode15` already switches the capture height to 240 elsewhere in the project.
ascal_v's input auto-detect measures the source, so this should mostly work
already — needs verifying rather than building.

### 7. Genlock / VRR (speculative)
The 60.09 Hz source vs 60.00 Hz output beat repeats or drops a frame roughly
every 11 s. Triple buffering removes the tear but cannot remove the judder;
only matching the output rate to the source can. Worth knowing the limit
exists before someone chases it as a bug.

---

## Using ascal_v in a game core

`src/video/ascal_fb.sv` is a **drop-in replacement for `ddr3_framebuffer`**:
same port list plus two inputs (`i_ce` = pixel tick, `i_de` = active-video
level), because ascal_v needs those separately - `fb_we` is their AND and
drops between pixels, which the input capture would read as one line per
pixel. The MCR tops already have both (`pixel_tick`, `cap_active`).

Proven in `mcr3_console60k` 2026-07-29: **Tapper renders correctly**.
Cost there: Logic 13338 -> 13590, BSRAM 88 -> 98 of 118 (20 spare).
The merged 9-game core at 114/118 will NOT fit (+10 = 124); narrowing `N_DW`
to 64 is the lever, since BSRAM here is width-driven not depth-driven.

### The +10 gets worse as families are merged (measured 2026-07-30)

Adding MCR3Scroll (`mcr23s_console60k`, 12 games) landed at 117/118, and
adding MCR-1 on top (`mcr123s_console60k`, 15 games) at **116/118** - see
`TODO.md` 4a-bis/4a-ter for the levers that got them there.

**15 games IS the complete roster for this board**, so the squeeze is not about
making room for another family: MCR3Mono is parked for a different board rev
because its IP ports route to different cabinet connectors (plus 3-player
wiring and an ADC), not because of capacity. The remaining same-board
candidates are Journey (needs a DDR3 wave port) and Demolition Derby (needs
Turbo Cheap Squeak, and is 4-player so it may hit the same connector wall).

That makes the scaler the ONLY real future claim on headroom, and the trade is
now explicit: at 116/118 there is no room for `ascal_v`'s +10. It is
**15 games on `ddr3_framebuffer`, or 12 games with the better scaler** - unless
`N_DW` is narrowed to 64, which is where the +10 comes from in the first place.

Order of business, therefore: settle the 3-family fit on the cheap scaler
first, then decide whether `ascal_v`'s 10 blocks are affordable — and if they
are not, whether `N_DW=64` (halving the line-buffer and FIFO width, the whole
source of the +10) closes the gap. Do not start the swap while the merge is
still over budget; the two changes would confound each other, which is exactly
the measurement mistake this file's last section warns about.

**Three integration traps, all of which build and time cleanly while failing
silently:**
1. **Hold the scaler in reset until DDR3 has trained** -
   `.reset_n(rst_n & init_calib_complete & ~ddr_rst)`. Traffic on the app
   interface during calibration stops it completing. Symptom: beacon `c0`,
   correct grey pillarbox, black window.
2. **Tie the DDR3 controller's own `rst_n` to `1'b1`**, as both references do.
   Feeding the core reset in also breaks calibration.
3. **`syn_keep` belongs on `clk_x1` ONLY.** Putting it on `hclk` prevents the
   merge with the top's `fb_hclk` net that the SDC constrains, giving
   TA2003/TA2004. Do not add it "for safety".
Also: remove `ddr3_framebuffer.v` from the build file list when using
`ascal_fb`, or the tools compile two copies of the PLLs and DDR3 IP.

## Hard-won facts that outlive the code

* **The HDMI PLL VCO must stay in spec.** `gowin_pll_hdmi27.v` ran at
  1485 MHz (limit 1400) for months as an "accepted PA1019 warning". That was
  the long-standing HDMI dropout: sync held for minutes after configuration
  then went marginal, and recovered on every reconfig. Fixed 2026-07-28 with
  `MDIV_SEL=41, MDIV_FRAC_SEL=2, ODIV0_SEL=3` (VCO 1113.75 MHz, same
  371.25 MHz output). Soak-verified 30 min, 0.000% black. **PA1019 is now a
  build-breaker with no exceptions.**
* **Raw DVI is not enough.** `dvi_tx_ext` emits DVI with no AVI InfoFrames and
  measured 21.7% black; hdl-util `hdmi` with `DVI_OUTPUT(0)` measured 0.00%.
  Use the HDMI module — it also carries audio.
* **MiSTer's audio is NOT transplantable.** `sys_top.v` drives an external
  ADV7513 over parallel RGB + I2S; there is no data-island/ACR/CTS logic
  anywhere in MiSTer's `sys/`, because the chip does it. We generate TMDS
  ourselves, so hdl-util is the only option.
* **`sine_gen`'s `sample_en` is a one-cycle ENABLE, not a clock.** Feeding it
  `clk_audio` produced a 1 kHz tone at 7852 Hz. hdmi needs the clock; the
  generator needs the pulse. Keep them distinct.
* **Use the INTEGER audio divider** `74250*1000/AUDIO_RATE/2`. A
  fractional-exact one made dropouts worse.

## Measuring any of this without fooling yourself

Every wrong conclusion in this project traced to measurement, not reasoning:

* **Record TIME SINCE CONFIGURATION and soak for tens of minutes.** A fresh
  flash resets the PLL and DDR3 calibration, so a test run just after flashing
  hides an entire class of fault. This produced three separate "0.0%" results
  while the user watched the screen drop out.
* **Give ffmpeg exclusive use of the capture device.** A second process on
  `/dev/video4` manufactures dropouts. Check `pgrep -x ffmpeg` first.
* **Discard capture events before t=0.5 s** — the card's lock-up. Seven black
  frames at indices 0-6 of every capture were once mistaken for an 8% dropout
  rate that "matched across all builds".
* **A capture card freezes on signal loss; a monitor goes black.** Detect
  repeated frames as well as black ones.
* **Frame-to-frame consistency is NOT correctness.** A scaler stuck on one
  source line produces perfectly consistent frames. Always check the displayed
  source line against the ideal mapping.
* **The simulation must model TWO independent 74.25 MHz clocks.** Tying
  `avl_clk` to `o_clk` hides every crossing and makes the harness pass broken
  designs — this is exactly what happened for several rounds.
