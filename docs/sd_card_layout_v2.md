# SD card layout v2 — IMPLEMENTED (2026-07-24)

> **STATUS: IMPLEMENTED 2026-07-24** (loader auto-detects v1/v2 by magic;
> v1 cards keep working - verified on hardware). As-built format differs
> from the original plan in one way: the RTL reads a compact 16-byte
> MINI-ENTRY table inside the superblock sector itself
> `{family, type, slot, pad, start_lba LE32, sector_count LE32, pad4}`
> (max 31 entries), while the rich 64-byte entries with CRC live in the
> following sectors for tools only. Tools: `tools/make_pack_v2.py` builds
> `mcr_pack_v2.img` (all families, slots matching each OSD roster);
> `tools/write_pack_v2.py` writes it at sector 2048 **on the Mac**.
> Payload layouts per family are documented in make_pack_v2.py's header.
> Remaining v2 work: CRC verification in the loader, per-region entries if
> a game ever breaks the fixed family layouts, core-id in MCRPREF (roadmap
> item 5).

## Why this doc exists

`tools/make_rompack.py` (MCR-2, six games) and `tools/make_sprite_pack.py`
(MCR-3 Tapper sprites) **both hardcode `PACK_BASE = 2048`**. They write
different payloads to the same sectors, so one card cannot serve both
families — writing either one silently destroys the other.

Observed consequence: with the Tapper sprite pack on the card, booting an
MCR-2 build makes the OSD read a garbage slot, land on `loaded_slot = 0`,
and display **Satan's Hollow** regardless of what was baked in
(`src/rtl/osd.sv:162`, `game_id <= loaded_slot[2:0]`; slot 0 is
`NAME0 = "SATANS HOLLOW"`).

## Current format (v1) — what is on the card today

Raw sectors, no filesystem. Authority: `src/rtl/rom_loader.sv` (the RTL
parameters are the real contract; the Python tools mirror them).

| Sector | Contents |
|---|---|
| `PACK_BASE-1` = 2047 | prefs: `"MCRPREF1"` + last-selected slot |
| `PACK_BASE` = 2048 | header: `"MCRPACK1"` + slot count |
| `PACK_BASE+1 + n*256` | slot *n* payload, fixed 256 sectors (128 KiB) |

```
rom_loader.sv:  parameter [31:0] PACK_BASE    = 32'd2048
                parameter int    SLOT_SECTORS = 256
                sector <= PACK_BASE + 32'd1 + (cur_slot * SLOT_SECTORS);
```

Limits that force v2:

1. **Fixed 128 KiB slots.** A slot cannot describe a game whose ROM set has
   a different shape. That is precisely why MCR-3 needed a *separate* pack
   whose single slot "is" the raw sprite blob rather than a normal game
   entry — and why the two packs collide.
2. **One namespace, no family field.** Nothing on the card says whether a
   slot is MCR-1/2/3, so a card is implicitly bound to one family.
3. **No room for cores**, only ROM payloads.
4. **No integrity check.** A half-written card reads as valid.

### Minimal workaround (preferred if we need coexistence BEFORE v2)

`PACK_BASE` and `SLOT_SECTORS` are already **module parameters**, not
constants baked into the loader logic. Giving the MCR-3 top a different
`PACK_BASE` (say 16384) and matching `make_sprite_pack.py` to it makes both
packs coexist with **no format change, no v2 work, and no reflash of the
MCR-2 side**. Do this instead of v2 if the only goal is "one card, both
families".

## Proposed v2 layout

```
LBA 0            MBR; optional FAT32 partition starting at 8192
                 (host-visible drag-drop area; the FPGA never reads it)
LBA 2047         "MCRPREF1"  prefs: last game, cap_delay, video mode
LBA 2048         "MCRPACK2"  superblock: version, entry_count, dir LBA
LBA 2049..       directory entries (64 B each -> 8 per sector)
LBA 4096..       ROM payload region
LBA 0x40000..    CORE payload region (only if cores live on SD; see below)
```

Keeping the superblock at 2048 means a v2 card is *detectable* by existing
code paths (magic differs from `MCRPACK1`), so a v1 loader can refuse it
cleanly rather than misread it.

### Directory entry (64 bytes)

| Field | Size | Notes |
|---|---|---|
| `type` | 1 | `ROM` \| `CORE` |
| `family` | 1 | mcr1 / mcr2 / mcr3 / … |
| `game_id` | 8 | ASCII, e.g. `tapper__` |
| `start_lba` | 4 | absolute sector |
| `sector_count` | 4 | payload length |
| `region_table` | 40 | up to 5 × {region_id, offset, length} |
| `crc32` | 4 | over the payload |
| `flags` | 2 | reserved |

**The region table is the whole point.** Instead of "slot *n* is 128 KiB
starting here", an entry says "main is at +0 for 32 KiB, snd at +0x8000 for
16 KiB, gfx1 at …". That expresses every game's ROM shape, including the
MCR-3 sprite blob, in one uniform structure — collapsing `make_rompack.py`
and `make_sprite_pack.py` back into a single tool.

### Sizing

Not a constraint. All ~15 games' ROMs are comfortably under 16 MB;
bitstreams are 2.48 MB each as `.bin` (19–20 MB as ASCII `.fs`, so store
`.bin`). Any modern card is oversized for this.

## Cores: one per FAMILY, not one per game

Worth stating explicitly because it changes the scale of the problem: all
six MCR-2 games already share **one** bitstream and switch at runtime via
`game_id` (`src/rtl/osd.sv` owns it; `game_config.vh` only picks what is
baked in for a card-less boot). Same for MCR-1 and MCR-3. So the end state
needs roughly **3–4 cores**, not ~15.

The FPGA cannot self-reconfigure from SD. Two options:

1. **Cores in SPI flash, ROMs on SD — recommended.** Gowin multiboot jumps
   between flash addresses; switching is fast, and the card format stays
   simple (ROMs + prefs only, no CORE region). `build.tcl` already sets
   `-multi_boot 1`.
2. **Cores on SD.** Needs a loader core that copies the chosen bitstream
   into flash and then triggers reconfiguration — flash wear, seconds per
   switch, and a golden-image recovery story.

**Verify before committing to (1):** the Console 60K's SPI flash size (at
2.48 MB per `.bin`, a 16 MB part gives ~6 slots) and the multiboot address
configuration. If flash turns out too small, fall back to (2) and the
`LBA 0x40000..` CORE region above becomes live.

## Open questions

- Flash size and multiboot address map on the Tang Console 60K.
- Does the OSD game list become data read from the card (so adding a game
  needs no rebuild), or stay compiled-in parameters as today?
- Prefs: keep at 2047, or fold into the v2 superblock? Keeping it separate
  preserves the "prefs survive a pack rewrite" property.
- Whether the FAT32 partition is worth it (nice for users dropping ROM zips
  on the card; costs a filesystem parser or a host-side tool).

## Definition of done

1. One card serves MCR-1, MCR-2 and MCR-3 simultaneously.
2. `make_rompack.py` and `make_sprite_pack.py` are one tool.
3. A truncated/half-written card is *detected* (CRC), not misread.
4. Adding a game does not require touching `rom_loader.sv`.

## Related

- `src/rtl/rom_loader.sv` — the on-card contract (parameters are authority)
- `tools/make_rompack.py`, `tools/make_sprite_pack.py`, `tools/write_rompack.py`
- `src/rtl/osd.sv` — game list, `game_id`, `loaded_slot`
- `handoff_v7_jukebox.md` — platform state; the MCR-3 sprite work that
  once blocked this format is DONE (the fault was the SDRAM pin-clock
  phase, not refresh — v5/v6's conclusions are retracted)
