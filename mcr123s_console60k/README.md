# mcr123s_console60k — every MCR game this board can run, in one bitstream

15 games, four families. This is `mcr23s_console60k` plus **MCR-1** (Kick,
Solar Fox, Kickman), which completes the set for the current board/shield
target.

| OSD idx | Games | Family |
|---|---|---|
| 0–2 | Tapper, Timber, Discs of Tron | MCR-3 (2) |
| 3–8 | Satan's Hollow, Tron, Wacko, Kozmik Kroozr, Two Tigers, Domino Man | MCR-2 (1) |
| 9–11 | Crater Raider, Spy Hunter, Turbo Tag | MCR3Scroll (3) |
| 12–14 | Kick, Solar Fox, Kickman | MCR-1 (0) |

ROT90: 3, 4 (MCR-2) and 12–14 (all MCR-1). Crater Raider is landscape.

## What made MCR-1 fit: the shared sprite ROM

MCR-1's marginal cost is dominated by its **32 KB sprite ROM — 16 blocks**, and
this build had 1 spare. The way out is that `mcr1.vhd` and `mcr2.vhd`
instantiate *structurally identical* sprite ROMs:

```
sprite_graphics : dpram( dWidth => 8, aWidth => 15 )
  port A: read on clock_vidn at sp_code_line_mux
  port B: the ROM download
```

Only one core is ever out of reset, so **one RAM serves both** — hoisted into
the top exactly like the bg pair, a pure port move with no timing change. That
is 16 blocks for free, and it avoids the sprites→SDRAM migration that neither
family's 1-phase sprite pipeline can absorb (MCR-3 has 8 phases of slack
between latching the sprite code and drawing; MCR-1 and MCR-2 have 1).

The hoist is behind generics — `SP_EXTERNAL` on both cores, plus `BG_EXTERNAL`
on `mcr1.vhd` — defaulting to 0, so `mcr2_primer25k`, `mcr2_console138k`,
`mcr2_console60k` and `mcr1_console60k` are all bit-identical to before.

**One download-address trap**: MCR-2 writes its sprite ROM through
`{~dl_addr[14], dl_addr[13:0]}` — bit 14 inverted — while MCR-1 writes a plain
`dl_addr[14:0]`. That twist used to live inside `mcr2.vhd`; the top now
reproduces it per loading family (`sp_wr_addr`). Get it wrong and MCR-2's
sprites come back with their 16 KB halves swapped.

## Everything else MCR-1 shares

- **CPU ROM**: its program is 32 KB, so it sits in the bottom half of the
  shared 64 KB RAM. `cpu_rom_addr` is 15-bit, zero-extended.
- **Sound ROM**: the shared 16 KB region, which lives in SDRAM (`cpu3`).
- **bg pair**: its planes are only 4 KB, addressed at the bottom of the shared
  16 KB pair — `bg_addr` widened to 14 bits, top two bits driven 0.
- MCR-1 is the only core emitting **4-bit RGB**; the shared video path is
  3:3:3, so the mux takes `[3:1]` (same truncation `mcr1_console60k` uses).

## Download map, family 0 (unchanged from the existing pack)

```
0x00000  CPU        32K
0x08000  sound      16K   -> SDRAM (cpu3)
0x10000  sprites    32K   -> shared sprite ROM, PLAIN address
0x18000  bg plane1   4K   -> shared bg1_ram, bottom 4K
0x19000  bg plane2   4K   -> shared bg2_ram, bottom 4K
```

No pack change was needed: `make_pack_v2.py` already emits family 0 in exactly
this layout, and the roster order (kick, solarfox, kickman) matches NAME12–14.

## Status

**Nothing here has run on hardware.** It inherits every unverified thing from
`mcr23s_console60k` — read that README too — and adds:

- MCR-1's own bring-up debt, which predates all of this: Kick's spinner
  sensitivity and the `input_3 = 0xFF` DIP placeholder are still guesses, and
  only Kickman has ever run on hardware (2026-07-27). Kick and Solar Fox have
  never been exercised at all.
- the shared sprite ROM and MCR-2's `sp_wr_addr` twist, both new.

Build: `tools/gw_build.sh mcr123s_console60k`.

## HARDWARE 2026-07-30: Wacko, Kick, Kickman, Solar Fox and Spy Hunter all play

Five of the fifteen confirmed on the first session, including **Kick and Solar
Fox for the first time on any build**, and **Spy Hunter WITH SOUND** - which is
the FX68K running on this platform for the first time. Between them they
exercise nearly everything that was unproven:

| Mechanism | Exercised by |
|---|---|
| MCR-1 inside the merged core (roster, decode, input map) | Kick |
| 32 KB sprite ROM SHARED with MCR-2, incl. the bit-14 write twist | Kick + Wacko |
| Scratch RAM shared across all four cores | both - and this is the one that could corrupt a RUNNING game |
| CPU ROM trimmed to 0xE000 | both |
| MCR-1's 4 KB bg planes in the shared 16 KB pair | Kick |
| Timing closure from the new build options | all |
| **FX68K / Cheap Squeak Deluxe**, the `fx68k_lc` binding workaround, `$readmemb` finding the microcode | Spy Hunter sound |
| **CSD 68000 ROM read from SDRAM** (`cpu2`) and its 16-bit byte-lane split (u17/u18 low, u7/u8 high) | Spy Hunter sound |
| MCR3Scroll roster, decode, char plane, sprite plane assembly | Spy Hunter |
| **Sound ROM read from SDRAM (`cpu3`)** - the 8 blocks that made 15 games fit | Kick + Kickman, which are SSIO-ONLY so their audio cannot come from a CSD |

Still open:

* A **regression pass over the nine MCR-2/MCR-3 games** in THIS build (Wacko
  aside) - they were verified in `mcr23_console60k`, but the shared scratch
  RAM, the trimmed CPU ROM and the SDRAM sound ROM are all new since.
* **Turbo Tag** - the harshest CSD test, because `mod_turbo` disables the SSIO
  board entirely, so it is silent unless the Cheap Squeak Deluxe carries it
  alone. Also the only game needing the MRA byte patch at 0x0B2C.
* **Crater Raider** - SSIO-only, no CSD, and the only LANDSCAPE cabinet in the
  roster (not in `ROT_MASK`).
* **MCR3Scroll bg plane order** - Spy Hunter looking right is good evidence the
  uncrossed guess was correct, but Crater Raider and Turbo Tag are separate
  ROM sets and could still be wrong.

## RESULT: 15 games CLOSE CLEANLY on the 60K

```
BSRAM   116/118        Logic 75%        Register 28%
Setup violated endpoints  0
Hold  violated endpoints  0
TNS 0.000 on every clock domain
```

| Clock | Required | Actual Fmax | Margin |
|---|---|---|---|
| clk_sys | 40.000 MHz | 43.008 | +7.5% |
| clk_sdram | 80.000 | 95.345 | +19% |
| clk1x | 74.239 | 130.028 | +75% |

**No bigger FPGA needed.** How it got here, because the path was not obvious:

| Step | clk_sys setup TNS | |
|---|---|---|
| v3: staging RAMs in LUT RAM | -536.088 ns / 459 eps | catastrophic |
| v4: reverted, video_ram shared | -8.093 / 32 | |
| v5: shared-RAM muxes -> true 4:1 | -6.342 / 25 | |
| **A: four toolchain options enabled** | **-0.059 / 1** | the real fix |
| **A+B: three free RTL fixes** | **0.000 / 0** | closes |

### The finding that mattered: build options we had never enabled

`build.tcl` had only ever set `place_option 2`. Four relevant knobs sat at
their defaults **for the entire life of this project**:

```tcl
set_option -route_option 2            ;# highest routing effort
set_option -retiming 1
set_option -timing_driven 1
set_option -correct_hold_violation 1  ;# hold is fixed by INSERTING delay
```

Enabling them took clk_sys setup TNS from **-6.342 ns over 25 endpoints to
-0.059 ns over 1**, with no RTL change at all. The design had been routed at
default effort the whole time. `place_option` stays at **2** - CLAUDE.md records
that 0 builds clean, meets timing, and yields a bitstream whose DDR3 never
trains, confirmed on hardware; 3 and 4 exist and are untried.

### The three free RTL fixes that finished it

None costs a block, none changes behaviour:

1. `ms_mod_crater` / `ms_mod_turbo` **registered** - they change only when a
   game loads, and combinationally they dragged `game_id` deep into the scroll
   core.
2. `input_0..4` **registered** - the per-game mux is combinational from
   `game_id` into all four cores; these are cabinet switches read by a 2 MHz
   Z80, so a 40 MHz cycle of latency is invisible.
3. `core_reset` **registered per core** - four short local nets instead of one
   long global one; it was the critical path in the 12-game build.

### Lessons worth keeping

* **LUT RAM is not a free substitute for BSRAM.** Fine for the 256-byte sprite
  line buffers; converting the 512-byte staging RAMs cost the entire clk_sys
  domain (-536 ns), because a distributed-RAM read is a combinational walk fed
  by a family mux, closing on the opposite clock edge. One block bought, the
  design lost.
* **Mux depth matters on half-cycle paths.** `run_is_a ? : run_is_b ? : ...`
  is three dependent LUT levels; an array indexed by `run_family[1:0]` is one
  4:1 mux. Keep `FAM_*` numbered 0..3 so the family code stays usable as an
  index.
* **Check the tool options before blaming the design.** Two full days of RTL
  surgery bought less than four `set_option` lines did.

## Rolling this back

Three independent levels, coarsest last.

**1. Per-lever, no git.** Every space-saving change is a switch with a
behaviour-preserving default:

| Switch | Where | Off value | Costs |
|---|---|---|---|
| `CPU_ROM_DEPTH` | this top | `0` = full 64 KB | +4 BSRAM |
| `SCRATCH_EXTERNAL` | mcr1/mcr2/mcr3/mcr3scroll generic | `0` = per-core RAMs | +9 BSRAM |
| `SP_EXTERNAL` | mcr1/mcr2 generic | `0` = per-core sprite ROM | +16 BSRAM |
| `BG_EXTERNAL` | mcr1 generic | `0` = per-core bg planes | +4 BSRAM |
| `SND_IN_SDRAM` | this top | `0` = sound ROM in BSRAM | +8 BSRAM |
| `SPRLINE_RAMSTYLE` | all four cores | `"block_ram"` | +2 BSRAM |
| `SCROLL_CSD` | mcr3scroll generic | `0` = no FX68K (Crater only) | 0 BSRAM |

Turning one off usually means the build no longer fits — that is the point:
they exist so a suspect mechanism can be isolated, not so it can be shipped off.

**2. Per-family, no rebuild.** The families are independent at runtime. If one
core misbehaves, the other three still play; the OSD just won't load that
family's games. Nothing needs reflashing to test that.

**3. git.** Each step is its own commit:

```
465a9c2  MCR-1 added, 127/118 - over by 9   <- rollback point for the levers
8877ab9  MCR3Scroll merged, 12 games, 117/118, builds
9a1ef7d  handoff v9 - the shipping 9-game core
```

`git checkout 8877ab9 -- .` returns the whole tree to the last state that
produced a working bitstream. The shipping 9-game core in SPI flash is
untouched by any of this, so a plain power cycle is always a way back to a
known-good board.

## The one thing to be suspicious of first

The shared scratch RAM is the only change here that can corrupt a *running*
game rather than fail to build. Its safety rests on the top muxing
`we`/`addr`/`d` by the RUNNING family — a core held in reset still presents a
combinational write-enable off its static CPU decode, and an un-muxed OR of all
four would let an idle core scribble on the live game's work RAM. If games show
sporadic corruption that a family switch makes worse, set `SCRATCH_EXTERNAL(0)`
on all four cores and see whether it goes away.
