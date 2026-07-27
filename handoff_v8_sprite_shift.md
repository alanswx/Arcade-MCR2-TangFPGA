# Handoff v8 — MCR-3 Tapper sprite "detached handle" investigation (2026-07-27)

Start after `handoff_v7_jukebox.md`. This documents the user-reported
"sprites are cut off — look at the beer glass" bug (2026-07-25), what has
been PROVEN, the instruments now in the tree/bitstream, and exactly what
remains. An experiment was still running on the bench when this handoff
was written — see "In flight" at the bottom.

## The symptom, precisely characterized

On the artifact session (flash build of 2026-07-25, bad6bd5-era), sprites
render with their **last-drawn 8px word-slot displaced one slot (8px) to
the right, with a transparent gap where it belongs**:

- sliding empty mug: [glass 16px][8px gap][detached handle 8px]
- patrons: body intact + a detached 8px sliver one slot right of the body
- capture evidence: scratchpad `live_199.png`, zooms `zz_mug199.png`,
  `zz_patron199.png` (scratchpad = the session temp dir; re-derive from
  any capture of an affected boot if lost)

The observable is EXACTLY equivalent to the sprite array reading as
`mem[i] = blob[i+1]` (one 32-bit-word global shift): for the empty-mug
tile (code 23, handle in ROM word 0, drawn UNflipped) a +1 shift renders
[w1 glass][w2 glass][w3 = empty = GAP][next-line w0 = handle]. Same math
reproduces the patron sliver. This artifact is SESSION/INSTANCE-dependent:
every load taken on 2026-07-26/27 is clean (see below).

## What is PROVEN (do not re-litigate)

1. **Card data is perfect.** The pack blob (make_pack_v2 sprite region,
   MAME file order fg_1,fg_0,fg_3,fg_2,fg_5,fg_4,fg_7,fg_6) decodes
   offline into all 256 sprite codes pixel-perfect, handles attached.
   Word i = {Q3[i],Q2[i],Q1[i],Q0[i]} (Q = 32KB quarters), bytes consumed
   low-first, hi-nibble-first. Mug codes: 22 (full, handle RIGHT = word 3),
   23 (empty, handle LEFT = word 0, cols 8-31 of word 3 empty).
2. **MAME ground truth** (headless, `scratchpad/mame_rt`, fabricated
   midssio.zip from the RTL PROM): handle attaches directly to the glass;
   demo mugs at the tap are a DIFFERENT (handle-less) code — don't be
   fooled by them.
3. **The RTL cannot make this shape.** `mcr3_console60k/diag/sp_tb.vhd`
   (GHDL; README beside it) runs the mcr3.vhd sprite machine VERBATIM
   against a cycle-exact model of sdram_gw's sp port (7-cycle rounds
   @80MHz, launch at RAS1 t=4, commit at READ1b). All 7 possible
   round-vs-engine alignments, flipped and unflipped: four contiguous
   words, always. The engine also physically cannot write outside its
   32px window (sp_on_line spans phases 10..42 only). GHDL gotcha: regs
   must be zero-initialized in sim ('U'+1 poisons counters; silicon
   powers up 0).
4. **mcr3.vhd is upstream-identical** (diffed; only INIT_FILE dprams +
   vcntout/cpu_halt_n exports). **sdram_gw.sv read path is
   upstream-identical** (diffed; changes are refresh diag, port2_we fix,
   Gowin tristate/ODDR, and sp_q committing whole at READ1b — commit time
   of the full word unchanged). Top-level wiring matches MiSTer
   Arcade-MCR3.sv (sp_addr direct, sp_q direct, 40/80 same-PLL, SDC
   declares them synchronous, timing met).
5. **Write path verified on hardware, 6+6 fresh loads**: a post-load
   port2 audit sweep (TEMPORARY, in the current top) reads back all 32K
   sprite words. Nonzero-word counts bucketed by i%4 match the blob
   prediction {0x1289,0x1B0A,0x1AD8,0x1409} (E0/E1/-/E3 beacon slots;
   measured 0x128A on E0, ±1 word = noise). Pattern-compare (E4) = 0x0000
   on every load.
6. **Fetch/render path verified per-pixel on hardware** via a TEMPORARY
   dl substitution: sprite codes 22/23 load a synthetic pattern (word w =
   (w+1)*2 opaque px then transparent). Captured sliding mugs in 5/6
   reload rounds show runs of 4/8/12/16 screen px (native 2/4/6/8) with
   shrinking gaps, correctly anchored = correct word->slot mapping,
   correct flip handling, no displacement.

Bottom line: **the failure is real but instance-dependent** — some
power-on/reconfig instances (or the specific 2026-07-25 flash build's
placement, or warm-board conditions) systematically read the array +1
word; the current builds over ~12 reconfig+load cycles never do.

## Instruments currently in the tree (all marked TEMPORARY, commit 64e7dda)

In `mcr3_console60k/src/mcr3_console60k_top.sv`:
- **Pattern substitution** (dl sprite write path): codes 22/23 replaced at
  load time. REVERT for any user-facing build (mugs render as red/blue
  bars!). Grep "TEMPORARY DIAGNOSTIC (2026-07-26)".
- **Audit FSM** (`aud_*`): after each load, sweeps all sprite words via
  the idle port2 (req/ack, race-free same-domain), counts nonzero by i%4
  and pattern mismatches on codes 22/23. Beacon x/q after the sweep:
  rotating E0/E1 = buckets 0/1, E4 = mismatches (0=clean, ~0xC0=shifted,
  FFFF=no sweep yet), E3 = bucket 3. Before the sweep: spw_count.
  NOTE: if the pattern substitution is reverted, E4-compare is
  meaningless — but the BUCKET counts alone still detect a ±1 shift
  (they rotate: shifted array reads ≈ {1B0A,1AD8,1409,1289}). Keeping
  the audit (cheap, one sweep post-load) is recommended as the per-boot
  canary; kill the E4 compare with the pattern.
- The v6-era diagnostics (chk sweep, scrub, pattern writer) are still
  present but disabled with `if (1'b0)` — the owed cleanup pass now has
  one more item.

On the bench: board SRAM currently holds the pattern+audit build
(impl/pnr/mcr3_console60k.fs of commit 64e7dda, built 06:02 2026-07-27).
SPI flash still holds the 2026-07-25 user-facing build (bad6bd5-era) —
i.e. **flash still has the artifact-capable build; power cycling boots
it.**

## Old-build cycling — RESULT (completed after the first draft)

3 SRAM load cycles of `bitstreams/console60k_mcr3_tapper_sprites_working.fs`
(the 3dbe824-era archive, which still contains the old sp_addr_r register),
120s HDMI captures each (scratchpad `oldround1..3/`): the demo's sliding
full mug (code 22) renders PERFECTLY in all three loads — handle attached
(zooms `zz_old1mug.png`, `zz_old23mugs.png`; the attract is deterministic,
frame f_083 of each round is the same game moment).

So the day's tally is **~15 fresh JTAG reconfig+load cycles across three
different bitstreams (current pattern/audit builds ×12, old archive ×3) —
zero reproductions**. The 2026-07-25 artifact session remains the only
observation. Untested reproduction paths, in order of value:
- **Power-cycle boot from SPI flash** (bad6bd5-era build — the exact
  artifact bitstream; a plain power cycle boots it). Needs hands at the
  bench (USB-C replug); capture the attract mug afterward.
- **Warm board**: the artifact session followed hours of uptime (the HDMI
  dropouts already prove thermal drift on this board). If a cold flash
  boot is clean, repeat after an hour of running.
- OSD-commanded reloads (the user had been switching games via the menu
  that session) — trigger a few via the cabinet chord/controller and
  re-check; the OSD reload path skips the prefs read but shares the
  loader FSM, so a difference would be surprising but is untested.

## Leading suspects for the instance dependence (open)

- **Fetch-side address sampling**: sdram_gw's RAS1 slot samples
  `{sp_addr,1'b0}` combinationally across the clk_sys→clk_sdram crossing
  (declared synchronous, timing met at nominal). The engine's prefetch
  (+1 addressing) means a capture that slips one fetch-slot late reads
  exactly word+1 — the observed artifact. Mixed-bit capture on a warm
  board (the HDMI dropouts already prove board thermal drift) or a
  placement-marginal path in that one build would be invisible to STA at
  nominal and produce a STABLE per-instance shift.
- Hardening option (cheap, sim-validated margin exists): sample sp_addr
  into clk_sdram and only launch when two consecutive samples agree
  (stability filter, +2 cycles latency — sim shows all alignments still
  meet the latch deadline with ≥2 cycles spare even +1 round late). Do
  NOT reintroduce a bare sp_addr_r register in clk_sys — that was removed
  deliberately (f7b5d39) as a MiSTer divergence.

## Recommended next steps (in order)

1. Finish the oldround1..3 analysis (frames already on disk or still
   arriving; same detector scripts as round1..6 — see scratchpad
   `reload_cycle.sh` and the mug-signature python in the session log).
2. Reproduce on demand: power-cycle → flash (artifact-capable) build →
   capture attract → check the mug. If it reproduces: reload the SAME
   build repeatedly to measure rate; if it never does, the 07-25 session's
   corruption was environmental (warm board) — park with the thermal
   HDMI investigation and rely on the audit canary.
3. Either way: revert the pattern substitution, keep the audit buckets,
   rebuild, reflash (`-f --verify`, retry until clean), regenerate
   `bitstreams/`, and ask the user to eyeball the mug.
4. If reproduction is ever caught live with the audit on board: E4/bucket
   rotation tells write vs fetch in one UART line, closing the case.

## Standing bench facts (unchanged from v7, repeated because they bite)

- JTAG SRAM loads fail silently ~1/3 → per-build beacon marker (here: the
  rotating E-tags / E4 value) before trusting results.
- Flash writes need `-f --verify`, retried until clean.
- UART: lg.py in scratchpad (auto-picks highest ttyUSB, survives
  re-enumeration); beacon 115200; JTAG reconfig may wedge the BL616 UART —
  only a USB-C replug (= power cycle!) clears it.
- MiraBox capture card = /dev/video4-5 (Brio webcam owns video0-3);
  1280x720, HDMI dropouts show as black frames (board-thermal, worse warm).
- MAME ground truth env: scratchpad/mame_rt (tapper.zip + fabricated
  midssio.zip); `-video none -sound none -nothrottle -str N` for
  deterministic attract snapshots; -aviwrite for video.
- Gowin builds: `tools/gw_build.sh mcr3_console60k`; post-build checks per
  CLAUDE.md (PA1019 exception, Undeclared-symbol grep, slack).

## Key artifacts (session scratchpad, worth re-deriving if lost)

- `sheet.png`, `codes0_47.png`, `zz_rom_mugs.png` — offline blob decodes
- `live_199.png` + zooms — the artifact, characterized
- `zz_pat_031.png`/`zz_pat_300.png` (v1 bands), `zz_p2_049_448_576.png`
  (v2 run-lengths — the money shot: 2/4/6/8 correctly anchored)
- `round1..6/`, `oldround1..3/` — reload-cycle captures + uart logs
- `mameframes/`, `mf2/` — MAME attract frame libraries
