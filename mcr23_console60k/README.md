# mcr23_console60k — merged MCR-2 + MCR-3 core

One bitstream, nine games, chosen from a single OSD roster. Proves the merged
architecture ahead of folding MCR-1 in (TODO item 4).

    tools/gw_build.sh mcr23_console60k

Roster index -> (family, slot). The OSD works in a flat index; the SD pack is
addressed by (family, slot), and `idx_family()` / `idx_slot()` /
`fam_slot_to_idx()` in the top translate both ways. Nothing else needs to know
the roster spans two families.

| idx | game | family | slot |
|---|---|---|---|
| 0-2 | Tapper, Timber, Discs of Tron | 2 (MCR-3) | 0-2 |
| 3-8 | Satan's Hollow, Tron, Wacko, Kozmik Kroozr, Two Tigers, Domino Man | 1 (MCR-2) | 0-5 |

## What is shared, and why that is legal

Only one core runs at a time - the inactive one is held in reset - so these are
shared rather than duplicated:

- CPU ROM RAM (32 blocks) and sound ROM RAM (8)
- the bg graphics pair (8+8), hoisted out of both cores for exactly this
- video, audio, hcnt/vcnt, muxed by `run_family`

MCR-3's sprites come from SDRAM; MCR-2 keeps its own 32 KB sprite RAM, so there
is nothing to mux there.

## Two things that differ per family

1. **dl region decode.** The payload layouts diverge after the sound ROM:
   MCR-3 has bg1/bg2 at 0x14000/0x18000 (16K each) and sprites at 0x1C000;
   MCR-2 has gfx2 at 0x14000 (32K) and bg1/bg2 at 0x1C000/0x1E000 (8K each).
   The decode is gated on `ldr_is_mcr2` - the family being LOADED, which is not
   the one running, because the download happens before `run_family` updates.
2. **Boot family.** `rom_loader` reads the prefs sector first, so `pref_core`
   is settled before the pack-entry search needs `family`. A saved family this
   bitstream does not contain (e.g. MCR-1) falls back to MCR-3.

## Budget

114 / 118 BSRAM, ~19.9k of 60k LUT, TNS 0.000. Four blocks spare - check the
count on every change.
