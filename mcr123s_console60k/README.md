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

## RESULT: it fits in BSRAM, but it does NOT meet timing on the 60K

**Do not flash this board's bitstream.** Gowin emits a `.fs` whether or not
timing closes; this one does not close.

| Build | BSRAM | clk_sys setup TNS | other |
|---|---|---|---|
| v3: staging RAMs in LUT RAM | 108/118 | **-536.088 ns / 459 eps** | hclk -1.896 |
| v4: reverted, video_ram shared | 116/118 | -8.093 ns / 32 eps | hclk -0.310, sdram -1.044 |
| v5: shared-RAM muxes -> true 4:1 | **116/118** | **-6.342 ns / 25 eps** | clk1x hold -0.109 / 3 |

Logic 75%, registers 28%. So **space was never the wall — placement congestion
is.** At four cores the design is dense enough that half-cycle paths which
passed comfortably in the 12-game build (worst slack there: +0.027 ns) no
longer make it.

Where the remaining 26 failing endpoints live:

| count | path |
|---|---|
| 17 | `mcr1_core` T80 -> `sh_sprc_ram` / `sh_vram_ram` (shared scratch RAM) |
| 7 | `osd_inst/game_id` -> `scroll_core/sprlinebuf2a` |
| 3 | `fb_inst` -> `fb_inst` (DDR3 framebuffer, **hold**) |
| 1 | `sdram/addr_last2[1]` -> `SDRAM_A[3]` (vendored controller, 80 MHz) |

Two lessons worth keeping:

* **LUT RAM is not a free substitute for BSRAM.** It worked for the 256-byte
  sprite line buffers; converting the 512-byte staging RAMs cost the entire
  clk_sys domain, because a distributed-RAM read is a combinational walk fed by
  a family mux, closing on the opposite clock edge. One block bought, -536 ns
  paid.
* **Mux depth matters on half-cycle paths.** Rewriting
  `run_is_a ? : run_is_b ? : run_is_c ? :` chains as an array indexed by
  `run_family[1:0]` (one true 4:1 mux) recovered ~1.75 ns of TNS for free.

### If someone picks this up again

Untried, in order of expected value:

1. **Register `ms_mod_crater` / `ms_mod_turbo`.** They only change when a game
   loads, so a register is functionally free, and `osd_inst/game_id` is 7 of
   the 26 failing endpoints. Do this regardless — it is correct anyway.
2. **Give MCR-1 back its own `sprites_ram_cache` and `video_ram`** (split
   `SCRATCH_EXTERNAL` into per-RAM generics). That removes MCR-1 from the two
   muxes carrying all 17 of its failing endpoints, at +2 blocks — landing on
   118/118 with zero spare.
3. The `fb_inst` HOLD violations and the `sdram` path are **not caused by any
   of this work**; they are congestion pressure on already-marginal paths. Hold
   failures do not improve with a slower clock and can be intermittent on
   hardware, so treat a build that merely "looks fine" with suspicion.
4. **GW5AST-138** — 298 blocks, 138k LUT. Removes the whole class of problem
   rather than shaving at it.

The recommendation from here is (4), or ship 12 games on the 60K: that build
(`mcr23s_console60k`) closes cleanly at 117/118 with 0 violations.

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
