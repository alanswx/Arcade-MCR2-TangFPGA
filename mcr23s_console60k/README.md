# mcr23s_console60k — MCR-2 + MCR-3 + MCR3Scroll in one bitstream

**Purpose: answer "can ONE core run every game?"** This is `mcr23_console60k`
(the shipping 9-game merged core, 114/118 BSRAM) plus the MCR3Scroll family —
Crater Raider, Spy Hunter, Turbo Tag — for 12 games across three families.

It is a separate board directory on purpose: `mcr23_console60k` is the product
and stays untouched while this one is measured.

Scaler: **`ddr3_framebuffer`**, deliberately. `ascal_v` is the better scaler but
costs +10 BSRAM (`docs/scaler_options.md`), and BSRAM is exactly the resource
in question here. Revisit the scaler choice only after the fit is settled.

## Roster → (family, slot)

| OSD idx | Game | Family | Slot |
|---|---|---|---|
| 0–2 | Tapper, Timber, Discs of Tron | MCR-3 (2) | 0–2 |
| 3–8 | Satan's Hollow, Tron, Wacko, Kozmik Kroozr, Two Tigers, Domino Man | MCR-2 (1) | 0–5 |
| 9–11 | Crater Raider, Spy Hunter, Turbo Tag | MCR3Scroll (3) | 0–2 |

Crater Raider is a **landscape** cabinet (upstream sets `landscape=1`), so it is
NOT in `ROT_MASK`; Spy Hunter and Turbo Tag are vertical.

## What is shared, and what MCR3Scroll adds

Shared with the other two cores, at no extra cost:

- the 64 KB CPU ROM RAM and 16 KB sound ROM RAM (`rom_cpu_inst`/`rom_snd_inst`)
- the hoisted **bg tile graphics pair** (2 × 16 KB). `mcr3scroll.vhd`'s bg RAMs
  were moved into the top exactly as `mcr3.vhd`'s were on 2026-07-27
- the **128 KB sprite region in SDRAM**, including the write swizzle. The
  sprite fetch in `mcr3scroll.vhd` is byte-identical to `mcr3.vhd`'s
  (`sp_graphx32_do_r` mux, `sp_addr` advance), so `merge_roms` assembles its
  gfx2 by plane into four 32 KB slots and the existing port2 write path is
  reused unchanged. `core_sp_addr` is muxed by `run_is_scroll`

Genuinely new:

| Thing | Where | Cost |
|---|---|---|
| char/alpha plane, 4 KB | inside `mcr3scroll.vhd`, `LOADABLE` | 2 BSRAM |
| CSD 68000 ROM, 32 KB | **SDRAM** (port1 write, cpu2 read) | 0 BSRAM |
| Cheap Squeak Deluxe: FX68K + PIA + 2×2 KB work RAM | `cheap_squeak_deluxe.vhd` | ~2 BSRAM + FX68K's 4 |
| the core's own video/sprite/work RAMs | `mcr3scroll.vhd` | the rest |

**The CSD ROM cannot be BSRAM here**: 32 KB is 16 blocks and the merged build
has 4 spare. Upstream MiSTer also runs it from SDRAM (its `cpu2` port), and the
68000's DTACK handshake absorbs the latency — unlike the main Z80, which is why
TODO 4c's CPU-ROM-in-SDRAM attempt failed. Banks 0/1 (the port1 group) are
otherwise completely idle in this design, so it cannot steal cycles from the
sprite read in banks 2/3.

## Download map, family 3 (288 KB — needs a 19-bit dl_addr)

```
0x00000  CPU        64K
0x10000  sound      16K
0x14000  bg plane1  16K   -> shared bg1_ram
0x18000  bg plane2  16K   -> shared bg2_ram
0x1C000  sprites   128K   -> SDRAM banks 2/3 (port2), same swizzle as MCR-3
0x3C000  char        4K   -> core dl 0x8000
0x40000  CSD ROM    32K   -> SDRAM banks 0/1 (port1); decode is just dl_addr[18]
```

That is past the 256 KB an 18-bit `dl_addr` covers, so `rom_loader` gained a
`DL_AW` parameter (default 18 — the single-family boards are unchanged) and this
top passes 19. The 12 KB hole at 0x3D000 buys the clean `dl_addr[18]` decode.

## Build

```sh
tools/gw_build.sh mcr23s_console60k
```

`SCROLL_CSD` at the top of `mcr23s_console60k_top.sv` is the measurement lever:
`1` = all three titles, `0` = Crater Raider only (SSIO sound), which removes the
whole FX68K stack. Two PnR runs give the CSD's real cost instead of arithmetic —
this project has got that arithmetic wrong twice (TODO 4a).

## Gowin-specific fixes this board needed

- **FX68K cannot be bound the upstream way.** `use work.fx68k.all` + a
  `COMPONENT` in a package *also* named `fx68k` gives
  `ERROR (EX4806) Primary unit of binding component 'fx68k' is not an entity`
  (the binder resolves to the package), and mixed-language port matching is
  **case sensitive**, so `extReset`/`enPhi1`/`iEdb` all fail with
  `ERROR (EX4968) Cannot find port 'extreset'`. Fix:
  `src/rtl/FX68K/fx68k_lc.sv`, a lower-case-port wrapper instantiated by
  direct entity instantiation (`entity work.fx68k_lc`) — the same route
  `mcr2.vhd` uses to reach `dpram.sv`. `fx68k.vhd` is deliberately not compiled.
- `microrom.mem` / `nanorom.mem` must stay next to `fx68k.sv`: `$readmemb`
  resolves relative to the source file's directory.
- FX68K's `ccrMask` **latches** (`fx68kAlu.sv:833`) draw `DI0003` at synthesis
  and then `TA1132 "was determined to be a clock but was not created"` at PnR,
  because the latch enable looks like a clock to the timing engine. Upstream's
  `FX68K/fx68k.sdc` addresses the related paths, but it is Quartus-only
  (`get_keepers`, `*fx68k:*|Ir[*]`) — four `set_multicycle_path -start` pairs
  relaxing `Ir -> microAddr/nanoAddr` and `nanoLatch/oper -> pswCcr` to 2
  cycles. **Not ported.** So on any build with `SCROLL_CSD = 1` those CSD paths
  are unconstrained: read the timing report for the CSD domain specifically
  before believing a clean TNS, and translate the four rules to Gowin SDC
  syntax if they show up as violations.

## Fixed here, still open in mcr23_console60k

The merged `mcr23` top has an unconditional `input_4 = 8'hFF;` **after** the
input-mux `endcase`, which overrides every per-game IP4 the case sets — Wacko's
aim stick, Kozmik Kroozr's synthesised Y axis and Two Tigers' player-2 dial all
read 0xFF. `mcr2_console60k` (single family) does not have the line; it arrived
with the merge. Removed in this top.

## Measured (PnR, V1.9.11.03, `place_option 2`)

| | |
|---|---|
| BSRAM | **117 / 118** |
| Logic | 35,700 / 59,904 (60%), incl. 418 RAM16 |
| Register | 14,897 / 60,780 (25%) |
| Setup / hold violated endpoints | **0 / 0**, TNS 0.000 on every clock |
| `clk_sys` worst slack | **+0.027 ns** (Fmax 40.086 vs 40.000 MHz) |
| PLLA | 5 / 8 |
| PA1019 | none |
| "Undeclared symbol" | none |

**The 0.027 ns is the number to watch.** The critical path is
`core_reset_s1 → scroll_core/palette` — reset fanout, not game logic — so
registering `core_reset` per core is the cheap relief if anything more goes in.

How it got there: first build 127 (over by 9), sprite line buffers → LUT RAM
125, sound ROM → SDRAM **117**. Removing the CSD/FX68K (`SCROLL_CSD = 0`) does
**not** change the BSRAM count at all — the 68000 is free in block RAM terms.

Bitstream staged as `bitstreams/console60k_mcr23s_12game_UNTESTED.fs`. Flash it
**without** `-f` (SRAM only) until it has been exercised, so a power cycle
returns to the known-good 9-game core in flash.

## Not done / unverified

- Nothing here has run on hardware. This board exists to answer the fit
  question first.
- **Two SDRAM regions are load-bearing and neither is hardware-verified**: the
  CSD 68000 ROM (`cpu2`) and the sound ROM (`cpu3`). If the merged core comes up
  silent on every game, set `SND_IN_SDRAM = 0` first — that costs 8 blocks and
  puts it back over budget, but it isolates the sound path from the fit
  question. If only Spy Hunter and Turbo Tag are silent, suspect the CSD ROM.
- The card must be rewritten: `python3 tools/make_pack_v2.py` then
  `write_pack_v2.py`. The image is now 15 games / 2.7 MB and the MCR3Scroll
  entries are new; the nine existing games keep their (family, slot) numbers,
  so the saved preference survives.
- **bg plane order for all three games is a guess.** `mcr3scroll.vhd` wires its
  bg dprams UNCROSSED (unlike `mcr3.vhd`), so `merge_roms` gives `gfx1_1` the
  pair MAME loads first. If bg tiles show right shapes with wrong colours, swap
  `gfx1_1_files`/`gfx1_2_files` — that exact symptom cost a day on Timber.
- DIP bytes are the MRA `switches default` (0xFF); not cross-checked per game
  against MAME.
- Spy Hunter's **lamp panel** (`show_lamps`, tied 0 here) wants the shield's
  second 74HC595. Its wheel/pedal use `steering_control.vhd` on the d-pad; a
  real wheel/pedal would come in on the shield's ADC.
- Turbo Tag has no SSIO sound board at all (`mod_turbo` disables it), so it is
  silent unless the CSD works.
