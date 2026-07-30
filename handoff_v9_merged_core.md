# Handoff v9 — merged MCR-2 + MCR-3 core (2026-07-28)

Start here. Supersedes `handoff_v8_sprite_shift.md` (whose subject is RESOLVED —
see its header). `TODO.md` items 1, 2, 3 and 4a–4c carry the detail; this is the
orientation.

## Where the platform is

**`mcr23_console60k` is the product: nine games in ONE bitstream, flashed as the
power-on default.** All nine verified on hardware. Game selection is from the OSD
and persists across power cycles *and across families*.

| Family | Games (roster index) |
|---|---|
| MCR-3 (fam 2) | Tapper 0, Timber 1, Discs of Tron 2 |
| MCR-2 (fam 1) | Satan's Hollow 3, Tron 4, Wacko 5, Kozmik Kroozr 6, Two Tigers 7, Domino Man 8 |

**No 60K bitstream contains ROM data** — everything streams from the SD card
(licensing). A missing card shows an INSERT CARD screen and hot-inserting one
recovers within seconds with no power cycle.

Budget: **114/118 BSRAM**, ~20k of 60k LUT, TNS 0.000. Four blocks spare — check
the BSRAM count on *every* change.

Single-family boards (`mcr1/mcr2/mcr3_console60k`) all still build and work; the
merged board is additive. The 25K stays deliberately baked (fixed-function).

## What this session did

- **MCR-3 sprite "detached handle" SOLVED** (`2fc948e`). Address came from the
  2-deep sync registers while data was taken live, so byte j landed at byte j−1:
  the whole sprite array stored as `mem[i] = blob[i+1]`. Introduced by `500c74a`.
  Never instance-dependent — handoff v8's premise was wrong.
- **All three MCR-3 titles working**: Timber needed the gfx1 plane order (it is
  PER-CORE, not per-game); Discs of Tron needed sprite BITPLANE padding (its
  64 KB set left two of four planes empty).
- **Everything-from-SD** across all three families, plus the INSERT CARD screen.
- **OSD widened** to 20 scrolling slots (8 visible), sized for the whole series
  incl. MCR3Scroll. Pinned by `sim/osd/tb_osd.sv`.
- **The merge itself**, plus a **stored-ROM audit** instrument (below).
- **HDMI dropouts**: found a gateware lever (below).

## Open issues, in the order I would take them

### 1. Timber boot-load bug — instrument is loaded, answer NOT yet read
Timber renders correctly when chosen from the OSD but fails when loaded at BOOT
(the `use_prefs` path). **This is the immediate next action** and it is one
command; the board is sitting on a frozen Timber right now:

    cd <scratchpad> && timeout 45 python3 lg.py tim.log 40
    # then compare E5/E4/E6/E7 against:
    python3 tools/ckstore.py timber      # cpu=0261 snd=CB8C bg1=773D bg2=5B14

- **any mismatch** → names the corrupted region; it is a storage bug like the
  other three this session
- **all four match** → the ROM data is provably correct and the fault is in the
  core's *use* of it, which retires a whole class of theory

Already ruled out with evidence (do not re-litigate, see TODO item 3): the SD
card, the pack layout, any 2026-07-27 RTL change, the sprite path, and the wedge
watchdog (`kick_n=0`, `hwin=0xFF` — the CPU is alive). It is NOT a crash: the
game animates.

### 2. HDMI dropouts — a gateware fix is now in reach
Measured: 25 min on one configuration → **52% dropout**; reconfiguring WITHOUT
touching thermals → **18%**. A 3× recovery in ~30 s, far too short to cool. So
much of the degradation is recoverable by re-running DDR3 calibration. The old
"board thermal" conclusion was confounded — the overnight-cool-down evidence
also power cycled, which is itself a reconfiguration. Temperature still
contributes (18% ≫ the 0–2% of a cool board). **Next: a managed or periodic DDR3
re-calibration.** A cabinet owner cannot cool the board; gateware can recalibrate.

### 3. Folding in MCR-1, and MCR3Scroll
Measured budget (see TODO 4a — arithmetic was wrong twice, these are PnR):

| Configuration | BSRAM |
|---|---|
| MCR-2+MCR-3 (today) | 114 |
| + MCR3Scroll + FX68K | ~130 — over |
| …after MCR-2 sprites → SDRAM (−16) | ~114 |
| + MCR-1 | ~127 — over |

- **FX68K fits easily**: synthesised standalone for this exact part at **2,891
  LUT and 4 BSRAM** (microcode ROMs map to block RAM, not logic). The 68000 is
  *not* the reason to change FPGA.
- MCR3Scroll shares more than expected: its `sp_addr`/`sp_graphx32_do` is
  byte-identical to `mcr3.vhd`, and its cpu/snd/bg widths match, so only ~12
  blocks are genuinely new. **Crater Raider needs no CSD/FX68K at all** — the
  cheap first target.
- **MCR-2 sprite → SDRAM is the risky piece**: MCR-3 has 8 phases between
  latching the sprite code and drawing; MCR-2 has 1. It needs pipeline surgery,
  not a port change.
- **Escape hatch**: GW5AST-138 has **298 blocks** vs 118, and 138k LUT. All four
  families fit with ~170 spare, no surgery. `mcr2_console138k/` is a stale
  pre-fix top and CLAUDE.md warns the net→ball map is SOM-specific.

### 4. Owed cleanup
TEMPORARY diagnostics are still in the merged core (stored-ROM audit, liveness
counters in beacon E0/E1, the `if (1'b0)`-disabled v6 sweeps). Keep the audit —
retire the rest once Timber closes.

## The instrument that matters: stored-ROM audit

In `mcr23_console60k_top.sv`. After each load it sweeps all four ROM RAMs through
their **port B** (the download port, idle after loading, so the core's port A is
untouched) and checksums what actually LANDED. ~3 ms. Beacon **E5 cpu / E4 snd /
E6 bg1 / E7 bg2**; expected values from `tools/ckstore.py`.

Validated exact on Satan's Hollow (`B23C/BC50/6F34/6030`).

This exists because **three separate bugs this session had the identical shape —
delivered correctly, STORED wrongly** (sprite shift, MCR-2 bg plane 2, Timber
colours) and the older download-*stream* checksums matched through every one of
them. If a game looks wrong, read this audit before theorising.

## Traps that bit repeatedly — read this before editing

1. **Gowin use-before-declaration → silent 1-bit wire.** Cost time ~4 times in
   one session. A multi-bit signal used above its declaration becomes ONE
   floating bit with only a warning. `grep -ci "Undeclared symbol"
   impl/gwsynthesis/*.log` **must be 0** — it is a build-breaker, not a nit.
2. **Stream checksums cannot see storage bugs.** See above.
3. **Resource probes silently prune the thing you are measuring.** A constant
   select (`game_id[3]`, provably 0) deleted a whole core's video path and
   under-reported by 27 blocks; a tied-off `dl_wr` let synthesis prove a
   `LOADABLE` ROM permanently empty and delete 16 more. **Always check the
   probed module's BSRAM against its standalone figure.**
4. **A ROM whose BSRAM count SHRINKS is a disconnected ROM.** The 25K silently
   went 56→51 because bg ports were left unconnected — and the build succeeded.
5. **A power cycle boots SPI FLASH, not what was last JTAG-loaded.** Confused two
   test sessions. Flash lagged 7 commits once and produced "baked Tapper
   graphics" on a card-out test that looked like a bug in new work.
6. **One reading of a time-varying quantity is not evidence.** Dropout rate and
   animate-vs-frozen both fooled me. Use A/B/A. A 20%-vs-2% "regression" in the
   merged core evaporated on the third measurement.
7. **`dpram` modes**: `INIT_FILE` = baked default with a writable port B;
   `LOADABLE(1)` = blank but writable; **neither = port B READ-ONLY**. Dropping a
   bake without adding `LOADABLE` silently kills the download. Pinned by
   `sim/dpram/`.
8. **Connecting `q_b` at all** makes the tool infer write-through and reject with
   `PA2122`. Port B now reads only when not writing.
9. **gfx1 bg plane order is PER-CORE**: MCR-3 wants the ROM MAME loads SECOND,
   MCR-2 the FIRST. Verify new games with
   `mame -listxml <game> | grep 'region="gfx1"'`. Wrong order = right shapes,
   wrong colours, bg only.

## Bench state

- Board: merged core in SRAM **with** the stored-ROM audit; **frozen on Timber**
  (prefs select it) — the pending measurement above.
- SPI flash: merged core *without* the audit (`console60k_mcr23_merged.fs`).
  Reflash after any change you want surviving a power cycle.
- SD card: freshly written pack v2, all 12 games, byte-verified. `write_pack_v2.py`
  now verifies the WHOLE image (header-only verification hid a partial write).
- Prefs sector 2047 holds slot + family; both are honoured at boot.

## Things I got wrong, so they are not re-derived

- handoff v8's "instance-dependent" sprite fault: it was deterministic all along.
- "Timber has a stale card" → wrong; I had you rewrite the card twice for nothing.
- "Timber is crashing/frozen" → wrong; it animates. I compared stills without
  checking for motion.
- "The merged core worsens HDMI dropouts" → wrong, A/B/A disproved it.
- "MCR-3+MCR-2 fits with no SDRAM work" → wrong by 8 blocks; the probe caught it.
- "The SDRAM ROM path itself is broken" → wrong; I misattributed Timber's known
  bug. CPU-ROM-in-SDRAM genuinely fails (latency); the sound ROM is unproven.
