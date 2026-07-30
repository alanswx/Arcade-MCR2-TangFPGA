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
