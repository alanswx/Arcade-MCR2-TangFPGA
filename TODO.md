# TODO / open issues

> **For the consolidated view — current state, what is verified, and what is
> still MISSING (speech, Journey, cocktail mode, NVRAM, lamps, scaler
> rotation) — read `handoff_v10_complete_roster.md` first.** This file is the
> detail behind it, and it is long: cocktail mode is ~1800 lines down.

Single list of known gaps. Detail lives in the linked docs; this is the
index so nothing hides in a §6 somewhere. Roughly ordered by "blocks the
next real milestone" within each section.


## ROADMAP — the MCR jukebox (agreed 2026-07-24, in priority order)

1. **HDMI dropout fix.** MAJOR FIX LANDED 2026-07-25, measured via the
   capture card: the framebuffer's sample clock ran at 48 kHz while
   AUDIO_OUT_RATE declared 32 kHz to the HDMI stack's ACR - a 50% rate
   lie. Making both 32 kHz took content frames from 14% to 41-69%
   (3-5x). The earlier "32k hung the monitor" trial was almost certainly
   a corrupt un-verified flash, not the rate change. A fractional-exact
   divider was tried and made things WORSE (clk_audio is a real clock
   downstream; edge jitter >> ppm offset) - reverted, do not repeat.
   RESIDUAL RESOLVED TO BOARD THERMAL 2026-07-26: udev rule added for the
   capture card (99-mcr-capture.rules, 534d:2109 -> plugdev) enabling
   unprivileged USB reset; a fresh card reset does NOT recover the rate
   (86% -> 71%), but an overnight cool-down took the identical build from
   28% to 86% content. The drift is the BOARD warming - suspects: TMDS
   analog margin, or the DDR3 wr-FIFO holds (+0.001 ns). Ground truth
   still wanted: the user's monitor impression on the consistent-32k
   build (warm vs cold). Cosmetic: /etc/udev/rules.d/99-mcr-capture.rules
   has a stray indented EOF line from the heredoc - harmless, cleanable
   with: sudo cp 99-mcr-capture.rules /etc/udev/rules.d/ (clean copy in
   the repo root).
   **NEW LEAD 2026-07-27/28 — a RECONFIG recovers it, which cooling cannot
   explain.** Measured repeatedly across one long session on the same board:
   | when | dropout | context |
   |---|---|---|
   | cold, post-reconfig | 1% | |
   | after hours on ONE config | 57% | |
   | post-reconfig | 1% | no cooling |
   | after sitting on one config | 20% | |
   | post-reconfig (mcr3) | 2% | minutes later |
   | post-reconfig (merged) | 0% | minutes later |
   EVERY low reading follows a reconfiguration; every high one follows a long
   run on a single configuration. A reconfig does not cool the board, but it
   DOES re-run DDR3 calibration and re-lock the PLLs - so the degradation
   looks like calibration DRIFT that re-calibration fixes, rather than an
   analog TMDS margin that only cooling fixes.
   This also puts a confound in the existing "board thermal" conclusion: the
   overnight-cool-down test that took 28% -> 86% content also POWER CYCLED
   the board, which is itself a reconfiguration. Cooling and recalibration
   were never separated.
   **SOAK RESULT 2026-07-28 — recalibration IS a large lever, measured:**
   after 25 min on one configuration the board sat at **52% dropout**;
   reconfiguring WITHOUT touching thermals took it straight to **18%** - a
   3x recovery in the ~30 s a reconfig takes, over which the board cannot
   meaningfully cool. So the degradation is substantially recoverable in
   GATEWARE. It is not the whole story (18% is still far from the 0-2% seen
   on a cool board, so temperature matters too), but "wait for it to cool"
   is not the only fix, and it is not one a cabinet owner can apply.
   NEXT: a managed/periodic DDR3 re-calibration, or at minimum re-calibrate
   on a trigger. Caveat on the measurement: the reconfig also loaded a
   slightly newer bitstream (same design plus a post-load audit sweep), which
   cannot plausibly account for a 3x change but is worth repeating cleanly.
   ALSO RULED OUT: the merged core is NOT worse than the single-family build.
   An A/B/A (merged 20%, mcr3 2%, merged 0%) shows the spread is time
   variation, not the extra 54% of logic - do not chase clock-gating for this.

   Original notes: Mechanism cornered: audio data islands, 48 kHz
   divider actually emits 48,027 Hz vs ACR constants claiming 48,000 →
   sinks periodically resync. The 32 kHz quick-try killed sync because ONLY
   the divider changed — a correct fix sets rate + ACR N/CTS consistently
   through the hdl-util hdmi instantiation (N=4096 for 32 k / 6144 for 48 k),
   or copies whatever current nestang does here (refs/nestang vendorable).
   Evidence + revert details: commits 2bee7ea/2424e0c, and the two-cause
   entry below (thermal residual is secondary).

2. **All cores load ROMs from the SD card ("everything-from-SD").** NOW A
   LICENSING REQUIREMENT, not just an optimisation: no copyrighted ROM data
   may ship inside a distributed bitstream, so the INIT_FILE bakes have to
   go and the card becomes mandatory.
   **STATUS 2026-07-27 — the mechanism is already built and wired.** Every
   ROM in all three families has a dl write decode driving `dpram` port B:
   MCR-2 `mcr2.vhd` (bg1/bg2/sprite gfx) + top (cpu/snd), same for
   `mcr1.vhd`, and MCR-3 (bg via core dl, sprites via SDRAM). And `dpram`
   in INIT_FILE mode is a TRUE dual-port RAM — the file is only the
   power-on default and port B writes land normally. (CLAUDE.md's "port B
   is inert in the dpram ROM mode", and the same line in mcr2.vhd:768, are
   STALE — they describe an older dpram. Fixed 2026-07-27.)
   **DONE for all three 60K boards 2026-07-27** — no 60K bitstream contains
   ROM data any more:
   - `dpram` gained a `LOADABLE` mode ("writable dual-port, NO init file").
     Needed because the generate picks `ram_mode` when INIT_FILE is empty
     and there port B is READ-ONLY — dropping a bake without it silently
     kills that ROM's download path. All three modes pinned in `sim/dpram/`.
   - mcr3_console60k un-baked and **hardware-verified**: Tapper and Timber
     both render correctly with a completely ROM-free bitstream.
   - mcr1_console60k and mcr2_console60k un-baked, and **BOTH VERIFIED ON
     HARDWARE 2026-07-27** loading entirely from the card with no ROM data
     in the bitstream: MCR-2 booted Wacko (58 distinct frames/90, 1 black)
     and MCR-1 booted Kickman — its first ever hardware run — with colours
     compared against MAME (skyline, pink text, mauve buildings, brown
     ladders, red/yellow balloons all match). MCR-1's picture is rotated on
     a normal monitor, which is CORRECT for its ROT90 cabinet. BSRAM
     unchanged (77/118 and 94/118), TNS 0.000.
     Not yet exercised: MCR-1 Kick and Solar Fox; MCR-2's other five.
   - Bake control is a per-board GENERIC on mcr1.vhd/mcr2.vhd
     (`GFX1_1_INIT`/`GFX1_2_INIT`/`GFX2_INIT`/`GFX_LOADABLE`), defaults
     baking, so mcr2_primer25k and mcr2_console138k are untouched. The 25K
     stays baked on purpose — fixed-function single-game board.
   **"INSERT CARD" screen — DONE and HARDWARE-VERIFIED 2026-07-27.** Booted
   with the card physically out: the message appears (no game, as intended -
   there is no baked fallback any more). Inserting the card while it ran was
   picked up within seconds and booted straight into the saved game with NO
   power cycle, which is the behaviour that matters for a cabinet (no reset
   button). Implementation notes in src/rtl/osd.sv - the core must NOT be
   held in reset while the screen is up (mcr1/2/3.vhd hold hcnt/vcnt at zero
   under reset and the OSD draws in the core raster domain, so resetting
   blanks the message), retries are self-paced off loader_error, and leaving
   the screen pulses core reset so the Z80 restarts cleanly on real ROMs.
   Still owed:
   - `merge_roms` still emits `rom_*.hex` for the 25K/138K, and
     `game_config.vh` is still needed on the 60K for `GAME_DEFAULT` (the
     slot used when the prefs sector has no valid entry).
   Feeds directly into item 4's merge — the shareable ROM RAM is what makes
   one bitstream hold all three cores.

3. **Add MCR titles until the series is complete.** PROGRESS 2026-07-27:
   **NINE GAMES SHIP IN ONE BITSTREAM** (mcr23_console60k, the flashed
   power-on default): all six MCR-2 titles plus all three MCR-3 titles, each
   verified on hardware, switchable from the OSD with the choice persisted
   across power cycles and across families.
   **ALL THREE MCR-3 TITLES NOW WORK ON HARDWARE** - Tapper, Timber and
   Discs of Tron. Timber plays perfectly when chosen from the OSD (only the
   boot-load caveat below is outstanding). Discs of Tron renders correctly
   after the sprite bitplane fix; its screen is mirrored, which is CORRECT
   (the real cabinet uses a mirror). Remaining for DoT: the aim DIAL is not
   wired (aim uses the dedicated IP2 buttons).
   Earlier notes:
   Timber and Discs of Tron added end-to-end (specs from MAME 0.265 source,
   input maps, OSD slots 1/2, pack entries).
   **TIMBER — TWO FAULTS. Colours FIXED; a BOOT-LOAD CRASH is still open.**
   (1) *Wrong bg colours* — FIXED and hardware-verified 2026-07-27. Root
   cause was the gfx1 PLANE ORDER in merge_roms (see the per-core rule
   below). Confirmed against MAME: the TREES LEFT / TIME LEFT boxes are now
   black with an orange border and orange text, bushes green, cabin red.
   (2) *Boot-load renders corrupt bg tiles; OSD load is fine* — OPEN, and
   the ONLY thing outstanding for Timber. Chosen from the menu it plays
   perfectly (owner-confirmed), so this is a boot-path defect, not a
   "Timber does not work" one.
   **Two earlier write-ups of this were WRONG and are corrected here:**
   it is NOT a stale SD card (the pack image was decoded and compared
   byte-for-byte against the ROMs - every region MATCHes, and two rewrites
   changed nothing), and it is NOT a crash/freeze (the game animates: ~39
   distinct non-black frames per 100 captured; an earlier "3 distinct
   frames" reading caught a dropout-heavy window, not a frozen core).
   MEASURED on a FAILING boot load, all with the TEMPORARY instruments now
   in the top:
   - download-stream checksums ALL CORRECT: cpu 8279, snd CB8C, bg1 773D,
     bg2 5B14 - exactly what tools/ck.py predicts from the ROMs. So the
     loader DELIVERS every byte of every region correctly.
   - sprite audit bit-exact ({0E74,1786,17FD,0FE1}) on every boot.
   - CPU is ALIVE: hwin = 0xFF (the code's own "running" signature) and
     kick_n = 0, so the wedge watchdog never fires. Boot sequence normal
     (rr_rises 2, rst_evts 2, boot_kicked 1).
   - Not any 2026-07-27 RTL change: a bitstream built before all of it
     behaves identically. Not Tapper: it boot-loads fine, repeatedly.
   So the bytes are delivered correctly and the CPU runs, yet bg tiles are
   wrong - which means the suspect is what actually LANDS IN the bg dprams,
   not what was sent. That is the exact shape of the sprite bug fixed this
   morning (stream correct, storage corrupted by an address/data pipeline
   mismatch), so it is the obvious place to look.
   NEXT STEP: a read-back audit of the two bg dprams after load, mirroring
   the sprite audit that has worked so well - connect their port-B q_b,
   sweep and checksum, compare against tools/ck.py. That distinguishes
   "stored wrong" from "stored right but rendered wrong" in one boot.
   Still unexplained and worth keeping in mind: why an OSD-commanded reload
   of the same slot produces a correct picture when the boot path does not.
   CAUTION: the board reaches ~57% black frames (thermal HDMI dropout, TODO
   item 1) after hours of running - capture-based measurements get
   unreliable, so prefer beacon counters over screenshots when it is warm.
   **DISCS OF TRON — WORKS. Sprite bitplane padding FIXED and
   HARDWARE-VERIFIED 2026-07-27.** Screen is mirrored, which is CORRECT (the
   real cabinet uses a mirror). Confirmed on the board after a card rewrite:
   sprite audit bucket2 reads 09F7 (the bitplane-padded prediction; the
   broken layout read 126A), and all four download checksums match
   tools/ck.py exactly - cpu 621C, snd 2FE4, bg1 2DF3, bg2 02AF - with
   kick_n=0 / hwin=0xFF showing a healthy CPU.
   Original symptom: ran, but sprites striped / missing interior pixels. Cause: the MCR-3 sprite engine fetches each 32-bit word
   as {Q3[i],Q2[i],Q1[i],Q0[i]} from the FOUR 32 KB QUARTERS of the 128 KB
   region, so every bitplane owns a fixed 32 KB slot. merge_roms simply
   concatenated the gfx2 files and padded at the END, which is only correct
   for a full 128 KB set (tapper/timber: 8 x 16 KB, each pair exactly fills
   a quarter). DoT has 8 x 8 KB = 64 KB, so it landed as Q0=files0-3,
   Q1=files4-7, Q2=ZEROS, Q3=ZEROS - sprites drawn with 2 of 4 bitplanes,
   i.e. missing pixels. Fix: assemble gfx2 BY PLANE, padding each pair to
   its 32 KB slot. tapper/timber are byte-identical afterwards (verified);
   only DoT changes. Gated to family==mcr3: MCR-1/MCR-2 sprites are a FLAT
   32 KB region (one aWidth=15 dpram read 8 bits at a time), and padding
   their planes overflowed the region and shifted every later game in the
   pack - caught before commit. New DoT sprite-audit tuple:
   {0x046E, 0x099B, 0x09F7, 0x04F0}.
   DoT's aim DIAL still not wired (uses the dedicated IP2 buttons). DoT's aim DIAL not wired yet (aim uses its
   dedicated IP2 buttons; spinner.sv WIRED 2026-07-24 - aim buttons rotate the dial; swap minus/plus if inverted on hardware).
   Remaining: Next: Timber, Discs of
   Tron (MCR-3, same core as Tapper); then the MCR3Scroll games (Spy Hunter,
   Crater Raider, Journey) per docs/mcr_core_roadmap.md; MCR3Mono stays
   parked for a board rev (future/README.md). Also: MCR-1 (Kick/Solar Fox)
   is built but never hardware-verified — verify while at it. Remember the
   Tapper lesson: bg ROM plane order bg0->gfx1_1 for EVERY new game.

4. **Core switching (multi-FAMILY). DECISION 2026-07-27: MERGE MCR-1/2/3
   into ONE bitstream; multiboot is deferred to MCR3Scroll/MCR3Mono.**
   Driver: ROMs must stream from the user's SD card for licensing anyway
   (no copyrighted ROM data may ship inside a bitstream), and that is the
   same work that makes a merged core fit. Merged, core switching becomes
   the instant SD reload that game switching already is — no reconfig, no
   flash slot map, no wire. See items 4a/4b below for the budget and the
   multiboot findings (kept: Scroll/Mono will need them).

   **4a. Merge budget — MEASURED, not estimated (2026-07-27).** A throwaway
   two-core probe build (`merge_probe/`, MCR-3's top with an MCR-2 core
   alongside sharing the CPU/sound ROM RAM) was built through PnR to get real
   numbers, because the arithmetic was WRONG. Predicted 114, actual **122 —
   PnR refused it: "ERROR (PA2017) The number(122) of BSRAM exceeds the
   resource limit(118)"**. The gap: shared infrastructure is ~20 blocks, not
   the 12 the synthesis per-module list suggests (PnR packing, plus the SD
   reader / dump / audit RAMs that never show as named modules).
   Logic is a non-issue throughout: the 2-core probe is 18.8k of 60k LUT.
   Real per-board totals and the model they give:
   | Build | BSRAM | = infra + ROMs + core |
   |---|---|---|
   | mcr3 alone | 88 | 20 + 40 + 28 |
   | mcr2 alone | 94 | 20 + 40 + 34 |
   | mcr1 alone | 77 | 20 + 24 + 33 (32K CPU ROM) |
   | **mcr3+mcr2 probe** | **122** | 20 + 40 + 28 + 34 — **OVER by 4** |
   Where that leaves each option:
   | Plan | BSRAM | |
   |---|---|---|
   | 2-way (mcr3+mcr2), bg gfx RAMs shared | **114** | **MEASURED, fits** |
   | 2-way (mcr3+mcr2), MCR-2 sprites -> SDRAM | 106 | fits, but needs sprite surgery |
   | 3-way as-is | 155 | way over |
   | 3-way, BOTH sprite sets -> SDRAM | 123 | still over |
   | 3-way, + bg gfx shared (28 -> 16) | **111** | fits, 7 spare |
   **So the sprite->SDRAM move is required even for a TWO-family merge** -
   the earlier claim that mcr3+mcr2 "fits today with no SDRAM work" was based
   on the bad arithmetic and is retracted. The 3-way additionally needs the bg
   gfx RAMs shared, which means hoisting them out of the vendored cores.
   REVISED ORDER (2026-07-27, after looking at the sprite pipelines):
   (1) DONE - hoist the bg gfx RAMs out of mcr2.vhd/mcr3.vhd and share them.
       Re-probed at **114/118, PnR accepts it**. Chosen over the sprite
       ->SDRAM move because MCR-2 has NO latency slack for SDRAM: MCR-3 has
       8 phases between latching the sprite code and drawing the first pixel
       (which is what absorbs the round trip), MCR-2 has 1. Moving its
       sprites would mean restructuring the sprite pipeline - the same
       surgery that produced the detached-sprite bug.
   (2) DONE - mcr23_console60k merges MCR-2 + MCR-3, 9 games in one
       bitstream, 114/118 BSRAM, flashed as the power-on default.
       **ALL NINE GAMES VERIFIED ON HARDWARE**: Tapper, Timber, Discs of
       Tron, Satan's Hollow, Tron, Wacko, Kozmik Kroozr, Two Tigers,
       Domino Man - including the analogue-control ones (Tron's aim
       spinner, Kroozr's dial + synthesised stick), whose wiring was ported
       wholesale from the standalone MCR-2 top.
       Three bugs found and fixed during bring-up, all worth remembering:
       - MCR-2's bg PLANE 2 landed 8 KB high in the shared 16 KB RAM: its
         region starts at 0x1E000 and the write address sliced [13:0]
         (=0x2000). MCR-3's bg2 is at 0x18000 where that is 0, so it only
         showed on MCR-2 games - as "slightly wrong palette".
       - a SAVE recorded the wrong family: rom_loader's `family` feeds both
         the entry search and prefs byte 9, but the save runs after the menu
         closes, so it wrote boot_family instead of the chosen game's.
       - `ldr_family` was defined in terms of `run_family`, which latches on
         the same edge - so it latched its own stale value and the wrong
         CORE ran while the right DATA was loaded.
       The first is the important one: the download-stream checksums matched
       throughout, because they measure what the loader DELIVERS, not where
       it LANDS. Same blindness that hid the sprite bug. A storage-side
       read-back audit is still the missing instrument.
   (3) MCR-1: hoist its bg too, and take on the sprite->SDRAM surgery with a
       known-good merged reference to compare against.
   (4) Fold MCR-1 in (111/118 with both sprite sets in SDRAM).
   **4a-bis. MCR3Scroll FOLDED IN AND MEASURED (2026-07-30) - board
   `mcr23s_console60k/`, 12 games across three families.** Not a throwaway
   probe this time: a real merge, with the roster, input maps, ROM specs and
   pack layout done (`merge_roms` family `mcr3scroll`, `make_pack_v2` family 3,
   15 games in `mcr_pack_v2.img`). Scaler kept as `ddr3_framebuffer` - the
   cheap one - because BSRAM is the resource in question; `ascal_v` would add
   10 blocks.
   PnR numbers, `ddr3_framebuffer`, CSD ROM already in SDRAM:
   | Configuration | BSRAM | verdict |
   |---|---|---|
   | mcr2+mcr3 (today, shipping) | 114 | fits |
   | + MCR3Scroll, CSD/FX68K IN | **127** | over by 9 |
   | + MCR3Scroll, CSD/FX68K OUT (`SCROLL_CSD=0`, Crater Raider only) | **127** | over by 9 |
   | ...then the two levers below | **fits, PnR places it** | **12 games, one bitstream** |
   Logic is a non-issue: 33.5k of 59.9k (56%), registers 25%.
   **The Cheap Squeak Deluxe / FX68K stack costs ZERO BSRAM blocks** - the two
   builds above differ only in whether it is compiled and land on the same 127.
   Its microcode ROMs (`uRam`/`nRam`) and the 68000 register file
   (`regs68H`/`regs68L`) map to ROM16/SSRAM, not block RAM. So the handoff's
   "+ MCR3Scroll + FX68K ~130" was close on the total but wrong about the
   cause: the 68000 is free, the cost is MCR3Scroll's own video/sprite RAMs.
   What made it fit in the first place, and cost nothing:
   - bg gfx pair HOISTED out of `mcr3scroll.vhd` and shared, as `mcr3.vhd`'s
     was on 2026-07-27 (note it is UNCROSSED there, unlike mcr3.vhd)
   - the 128 KB sprite region in SDRAM shared with MCR-3, write swizzle and
     all: `mcr3scroll.vhd`'s sprite fetch is byte-identical to `mcr3.vhd`'s, so
     `merge_roms` assembles its gfx2 by plane into four 32 KB slots and the
     existing port2 path is reused unchanged
   - the 32 KB CSD 68000 ROM in SDRAM on the idle **port1/cpu2** group (banks
     0,1), which is what upstream MiSTer does too. In BSRAM it would be 16
     blocks. The 68000's DTACK handshake absorbs the latency - unlike the main
     Z80, which is why 4c's CPU-ROM-in-SDRAM failed. UNVERIFIED on hardware.
   Closing the 9-block gap - both levers applied, PnR-measured:
   | Step | BSRAM | |
   |---|---|---|
   | 3-family, as first built | 127 | over by 9 |
   | + sprite line buffers -> LUT RAM | **125** | over by 7 |
   | + sound ROM -> SDRAM | **PnR ACCEPTS - it PLACES** | fits |
   1. **Sprite line buffers -> LUT RAM: -2 blocks, not the 10 hoped for.**
      Ten 256x8 buffers across the three cores (2 mcr2, 4 mcr3, 4 mcr3scroll)
      each burn a whole 18 Kb block for 2 Kb of storage. `gen_ram.sv` gained a
      `RAMSTYLE` parameter and the cores a `SPRLINE_RAMSTYLE` generic (default
      "block_ram", so every existing board is untouched). Gowin DID honour it -
      SSRAM went 98 -> 418 RAM16, synthesis BSRAM 118 -> 116 - but PnR only
      gave back 2 blocks, so it evidently packs most of those small arrays into
      shared blocks already. Cheap (+1.9k logic) and worth keeping, but do not
      budget 1 block per small RAM: **PnR packing, not the array count, decides.**
   2. **Sound ROM 16 KB -> SDRAM: this is what made it fit.** Written through
      port1 at word 0x4000 (above the CSD ROM), read on the idle `cpu3` port,
      byte lane = `snd_addr[0]`. The sound Z80 runs at 2 MHz
      (`mcr_sound_board` divides clk_sys by 20), so its address is stable
      ~500 ns per fetch against sdram_gw's ~7 clk_sys worst case - about 3x the
      main Z80's margin, which is why 4c's CPU-ROM attempt failed and this is
      expected to work. `SND_IN_SDRAM` in the top switches it back.
      **NOT hardware-verified** - 4c left it "not disproven, not verified", and
      that is still true. Side effect: the stored-ROM audit's `snd` leg (beacon
      E4) has no port B to sweep and reads 0 by design.
   **4a-ter. MCR-1 FOLDED IN AND MEASURED (2026-07-30) - `mcr123s_console60k`,
   15 games, four families. 127/118 - OVER BY 9.**
   MCR-1 costs **+10 blocks** (117 -> 127) and that is AFTER the big win:
   - **The 32 KB sprite ROM is now SHARED between MCR-1 and MCR-2.** Their
     `sprite_graphics` instances are structurally identical (dpram 8 x 32K,
     port A read on clock_vidn at `sp_code_line_mux`), and only one core is
     ever out of reset, so one RAM serves both - hoisted to the top exactly
     like the bg pair. **16 blocks, zero timing risk, no SDRAM migration.**
     This retires lever 4 below for MCR-1's half of the problem.
     Behind `SP_EXTERNAL` (mcr1+mcr2) and `BG_EXTERNAL` (mcr1) generics,
     default 0, so mcr2_primer25k / mcr2_console138k / mcr2_console60k /
     mcr1_console60k are untouched.
     TRAP: MCR-2 writes its sprite ROM through `{~dl_addr[14], dl_addr[13:0]}`
     - bit 14 INVERTED - while MCR-1 writes a plain address. That twist used
     to live inside mcr2.vhd; the top now reproduces it per loading family.
   - CPU ROM (32 KB program), sound ROM (in SDRAM) and the bg pair (4 KB
     planes at the bottom of the shared 16 KB) all shared as well.
   So the remaining +10 is MCR-1's own SCRATCH RAM: wram 2K, video_ram 1K,
   sprite_ram 512, cache 512. Logic went 60% -> 74%, registers 25% -> 28%.
   **Levers for the last 9 blocks, cheapest first:**
   1. **CPU ROM 64 KB -> 56 KB: -4, low risk.** MEASURED: the largest real
      program in the roster is 57344 bytes = 0xE000 exactly (tapper, timber,
      dotron, crater, spyhunt; turbotag's 0x10000 is 56 KB of ROM plus 8 KB of
      MRA zero padding). Every core's `cpu_rom_addr` stays below 0xE000 in
      normal operation - mcr3scroll's xor-twist maxes at 0xDFFF, and
      mcr2/mcr3 pass cpu_addr straight through but the Z80 map above 0xDFFF
      is RAM/IO, never ROM. Needs a depth parameter on `dpram` plus
      `main_pad_to=0xE000` for the scroll family.
   2. **Share the per-core SCRATCH RAMs: -9 or so, invasive.** All four cores
      have `wram` (2K), `sprite_ram` (512) and `sprites_ram_cache` (512) of
      identical shape, and only one core runs at a time - the same argument
      that just worked for the sprite ROM. Twelve more port moves across four
      vendored cores, and these have CPU WRITE ports, so it is more than the
      read-only hoists done so far.
   3. **GW5AST-138 (298 blocks): ends the whole problem**, plus 138k LUT with
      logic already at 74%. `mcr2_console138k/` is a stale pre-fix top and
      CLAUDE.md warns the net->ball map is SOM-specific.
   **BOTH LEVERS APPLIED 2026-07-30** (user-approved, "I have validated the
   cores well enough"):
   - `dpram` gained a `DEPTH` parameter and the shared CPU ROM is now 0xE000
     rather than 64 KB. The download write is gated on the same bound, because
     Turbo Tag's payload carries 8 KB of zero padding above 0xDFFF that would
     otherwise write past the end of the array. The stored-ROM audit's CPU
     sweep is bounded to match, so `tools/ckstore.py` must checksum only the
     first 0xE000 bytes to compare against beacon E5.
   - `wram` (2 KB) + `sprite_ram` (512) + `sprites_ram_cache` (512) hoisted out
     of ALL FOUR cores behind `SCRATCH_EXTERNAL` (default 0). They are
     byte-identical in every core, so one set replaces four.
     **The top muxes we/addr/d by the RUNNING family, and that is load-bearing:
     a core held in reset still presents a combinational write-enable off its
     static CPU decode, so an un-muxed OR would let an idle core corrupt the
     live game's work RAM.** This is the only change in the whole merge that
     can break a RUNNING game rather than fail to build - suspect it first if
     games show sporadic corruption.
   MEASURED, and the estimates were optimistic AGAIN - PnR, not arithmetic:
   | Step | BSRAM | |
   |---|---|---|
   | MCR-1 added, sprite ROM already shared | 127 | over by 9 |
   | + CPU ROM 64K -> 56K (predicted -4) | | |
   | + scratch RAM shared x4 (predicted -9) | 119 | over by 1 |
   | + the two shared 512x8 staging RAMs -> LUT RAM | **PnR ACCEPTS** | **15 games fit** |
   Both together gave **-8, not the -13 predicted**. Same lesson as the sprite
   line buffers: PnR already packs small arrays, so hoisting four 512-byte RAMs
   into one does NOT return four blocks. **Never budget a block per array.**
   **AND IT CLOSES TIMING - 15 GAMES, ONE BITSTREAM, ON THE 60K.**
   BSRAM 116/118, Logic 75%, **0 setup and 0 hold violations, TNS 0.000 on
   every clock**, clk_sys Fmax 43.008 vs 40.000 MHz required (+7.5%),
   clk_sdram 95.3 vs 80.0. **No larger FPGA needed.** Never run on hardware.
   Timing did NOT close by RTL work - it closed by BUILD OPTIONS:
   | Step | clk_sys setup TNS |
   |---|---|
   | shared scratch RAM, muxes as 4:1 chains | -6.342 ns / 25 eps |
   | **+ route_option 2, retiming, timing_driven, correct_hold_violation** | **-0.059 / 1** |
   | + registered mod_crater/turbo, inputs, per-core reset | **0.000 / 0** |
   `build.tcl` had only ever set `place_option 2`; the design was routed at
   DEFAULT effort for the life of the project. See the new build-options
   section in CLAUDE.md - **check those before doing RTL surgery for timing.**
   The three RTL fixes that finished it cost nothing: `ms_mod_crater`/
   `ms_mod_turbo`, `input_0..4` and a per-core `core_reset` copy, all
   registered (each only matters at game-load or switch-sample rates).
   Two lessons that cost a build each:
   - **LUT RAM is NOT a free substitute for BSRAM.** It worked for the 256-byte
     sprite line buffers; doing it to the 512-byte sprite STAGING RAMs sent
     clk_sys TNS to **-536 ns over 459 endpoints**, because a distributed-RAM
     read is a combinational walk through the LUT array fed by a 4-way family
     mux, closing on the OPPOSITE clock edge. One block bought, the whole
     clk_sys domain paid.
   - **Mux DEPTH matters on half-cycle paths.** Rewriting
     `run_is_a ? : run_is_b ? : run_is_c ? :` chains as an array indexed by
     `run_family[1:0]` - one true 4:1 mux instead of three dependent LUT
     levels - recovered ~1.75 ns of TNS for free. Keep FAM_* numbered 0..3 so
     the family code stays usable as the index.
   Every lever is a switch with a behaviour-preserving default; the table and
   the git rollback points are in `mcr123s_console60k/README.md`.

   Levers NOT needed yet, kept for MCR-1:
   3. CPU ROM 64 KB -> 56 KB (-4). Every MCR-2/3/Scroll program ROM ends at
      0xDFFF; above that the Z80 map is RAM/IO. Needs a depth parameter on
      `dpram` and a check that no core mirrors ROM above 0xE000.
   4. MCR-2 sprites 32 KB -> SDRAM (-16). The known-hard one: MCR-2 has 1
      phase of slack between latching the sprite code and drawing, MCR-3 has
      8. Pipeline surgery, not a port change.
   5. GW5AST-138 (298 blocks) - no surgery at all.
   Also fixed in the new top, still open in `mcr23_console60k`: an
   unconditional `input_4 = 8'hFF;` AFTER the input-mux `endcase` overrides
   every per-game IP4 the case sets - Wacko's aim stick, Kozmik Kroozr's
   synthesised Y axis and Two Tigers' player-2 dial all read 0xFF.
   `mcr2_console60k` does not have the line; it came in with the merge.
   Gowin trap found here: **FX68K cannot be bound the upstream way.**
   `use work.fx68k.all` + a COMPONENT in a package also named `fx68k` gives
   EX4806 ("primary unit of binding component is not an entity" - it resolves
   to the package), and mixed-language port matching is CASE SENSITIVE, so
   `extReset`/`enPhi1`/`iEdb` all fail with EX4968. Fix:
   `src/rtl/FX68K/fx68k_lc.sv`, a lower-case-port wrapper reached by direct
   entity instantiation.

   PROBE GOTCHA worth remembering: the first probe reported a comfortable 95
   because the family-select signal was `game_id[3]`, which synthesis proved
   constant 0 (the OSD only assigns loaded_slot[2:0]) - it killed MCR-2's
   video path and pruned 27 of its 34 blocks. Any future probe must select on
   something provably non-constant (a physical input).

   **4c. CPU/sound ROM in SDRAM — TRIED 2026-07-27, PARTIAL RESULT.**
   The two biggest BSRAM consumers are the shared 64 KB CPU ROM (32 blocks)
   and 16 KB sound ROM (8). `sdram_gw` already has three CPU READ ports
   (cpu1/cpu2/cpu3) on banks 0,1 - a different bank group from the sprite
   port on banks 2,3, so no contention - and every top had them tied to
   zero. Upstream MiSTer's Arcade-MCR3 runs CPU+sound from SDRAM this way.
   Wiring it up took 114 -> **74 blocks**, i.e. 44 spare, which would fit
   MCR3Scroll (~16 incl. FX68K) and MCR-1 (~13) with room over.
   RESULT:
   - **CPU ROM in SDRAM FAILS.** Colour bars, no game - the Z80 is running
     on stale data. Matches the timing sum: the controller needs ~7 clk_sys
     worst case (up to a 7-cycle clk_sdram round to launch plus 7 to commit,
     and clk_sdram is 2x clk_sys), and the main Z80 has cpu_ena every 8
     clk_sys, ~16 across a T1->T3 read. Too little margin, and the port1
     group round-robins between port1/cpu1/cpu2/cpu3 so a port can wait
     extra rounds.
   - **Sound ROM in SDRAM: VERIFIED ON HARDWARE 2026-07-30.** Kick and
     Kickman are SSIO-ONLY (no Cheap Squeak Deluxe) and both have sound in
     the merged 15-game core, so the shared 16 KB sound ROM read from SDRAM
     on the `cpu3` port works. Its Z80 runs at 2 MHz (mcr_sound_board divides
     clk_sys by 20), ~3x the main CPU's margin, which is why this succeeds
     where the CPU-ROM move failed. **Worth 8 blocks, and those 8 blocks are
     what made the 15-game merge fit.** `SND_IN_SDRAM` stays 1.
     (The earlier inconclusive attempt compared against TIMBER, which has its
     own boot-load bug - that comparison proved nothing either way.)
   Experiment reverted; it lives in git history (both moves were behind
   independent `CPU_ROM_IN_SDRAM` / `SND_ROM_IN_SDRAM` switches so either
   can be re-enabled). If the CPU ROM is ever wanted in SDRAM it needs real
   latency hiding - a prefetch or a small cache - not just wiring.
   NOTE: this experiment also confirmed **Timber's boot-load corruption is
   still present in the MERGED core** - the merge did not fix it.

   **4b. Multiboot mechanics — DECODED and partly VERIFIED on this
   toolchain (keep for Scroll/Mono).** The 2026-07-24 investigation's notes
   were never actually committed (1b25a33 staged only RTL), so they are
   recorded here properly:
   - `//MultiBootMode: Single` in the .fs header is the SPI **bus width**
     (Single/Fast/Dual/Quad), NOT a "multiboot off" flag. The old worry
     about it was a red herring.
   - The jump pointer is `set_option -multiboot_spi_flash_address <hex>`
     (plus `-multiboot_address_width 24`). **VERIFIED 2026-07-27**: 300000
     vs 600000 produce DIFFERENT bitstream bodies, so the address really is
     encoded. Pass the value WITHOUT a `0x` prefix — `0x300000` yields a
     cosmetic `//MultiBootSPIAddr: 0x0x300000` (same bits, ugly header).
     `-mspi_jump` / `-mspijump_spi_flash_address` are the sibling options.
   - GW5A (Arora V) has **no fabric GOCONFIG/HOTBOOT primitive**; reload is
     triggered by the dedicated **RECONFIG_N** pin.
   - **RECONFIG_N routing — ANSWERED 2026-07-27** (was the open hardware
     question): dock schematic sheet 19/17 (`FPGA_CFG`, rev A and rev C) —
     `RECONFIG_N` is SOM connector J0 pin 61 = SOM ball **N12**
     (`BANK3_N12_IOR9B`), pulled up on the SOM, and grounded by **SW2**
     (`RECFG_KEY`, a 6x6 mm tact switch on the dock) through C9 10 nF with
     D1 for ESD. So the net exists and a spare GPIO can be jumpered to it;
     the FPGA cannot drive it directly because it is a dedicated config pin.
   - Cost that killed it for this product: each hop is a FULL
     reconfiguration — 2.51 MB at the default 2.5 MHz single-lane SPI is
     ~8 s, and the device always starts at flash address 0, so a ring walk
     happens on EVERY cold boot, not just when switching (a cabinet set to
     the 3rd core pays ~24 s per power-on). `-multiboot_mode Quad` might cut
     that ~4x (untested). `-loading_rate` rejected every value tried
     (100/50/30/20/10.0/5.0) on GW5AT-60 — accepted set unknown.
   - Flash budget: 16 MB (JEDEC 0B 40 18), 2.51 MB per .bin -> five 3 MB
     slots. Design in docs/sd_card_layout_v2.md ("cores in flash, ROMs on
     SD" — option 1).

5. **Persist the chosen core across power cycles.** GROUNDWORK IN
   2026-07-24: prefs sector byte 9 now records the running FAMILY on every
   save, and the loader reads it back (pref_core) - wired and building,
   unused until item 4 provides the jump mechanism. Remaining: Extend the existing
   MCRPREF sector (2047 — today it stores the last game slot within a
   family) with a CORE/family id. Every core checks the pref early at boot:
   if it isn't the saved core, multiboot-jump to the right flash slot; else
   boot normally into the saved game. Cabinet comes up exactly where the
   owner left it.

6. **Cabinet-button core/game switching, consistent across ALL games.**
   GROUNDWORK IN 2026-07-24: hold the physical coin key (AB13) ~3 s to open
   the OSD - implemented identically in all three family tops + osd.sv
   (btn_menu_hold). On the shield this signal moves to the 74HC165 Service
   line (no credit side-effect). Untested on hardware. Remaining:
   USB Select+Start stays, but a real cabinet needs the ORIGINAL controls to
   open the menu. The chord must use inputs that exist on EVERY MCR harness
   regardless of game — per docs/mcr_game_input_matrix.md the safe universal
   set is the coin-door group (Coin 1 + Service/Test switches), NOT player
   panel buttons (those vary per game). Proposal: long-hold Service (or
   Service+Coin1) -> OSD opens; navigation via a fixed pair present
   everywhere (P1 Start / Coin buttons). Wire through the shield's 74HC165
   chain (docs/shield_j10_pinout.md); must behave identically in all six+
   input maps so muscle memory transfers between games.

---

## Scaler plan — docs first, port second (2026-07-28)

Two documents now capture everything, so neither path restarts from zero:
  * `docs/ascal_port_notes.md` - all ascal knowledge: architecture, our
    integration, the exact fault, the ten eliminated hypotheses, the confirmed
    sim-vs-hardware divergences, the four GowinSynthesis defects, and a staged
    Verilog port plan with a TRIPWIRE (port to nearest-neighbour only and test
    on hardware BEFORE writing any interpolator).
  * `docs/scaler_features.md` - the fallback/parallel track: triple buffering,
    burst reads into a ping-pong line buffer, input auto-detect, and
    parameterised output timing, specified against our own working scalers.

`src/video/ascal_v.sv` - hand Verilog port, nearest-neighbour. Interface
matches ascal_gw.vhd so it drops into ascal_test60k and sim/vsynth unchanged.
Key simplification: 16 bpp so 8 pixels fit a 128-bit word exactly and a line
is a whole number of words - which removes ascal's o_off/o_pshift/sSHIFT
burst-offset machinery entirely, and that machinery is where its SECOND,
carry-independent `o_hacpt` increment lives. Triple buffering built in AND
ENABLED (`.triple_buf(1'b1)`).

**TRIPWIRE PASSED 2026-07-28 — it renders a correct picture on hardware,
which ascal itself never did.** Capture-card measured: active window
x=160..1119 (960 px), 8 colour bars of 118-122 px (expect 120), six equal
vertical bands of ~120 lines, all six pattern bands correct. Build is clean:
~4.3k registers, 28/118 BSRAM, no undeclared symbols, no setup/hold
violations, only the accepted `gowin_pll_hdmi` PA1019.
Full bring-up log (six bugs, in the order they bit) in
`docs/ascal_port_notes.md` §6. Two of them are worth repeating here because
they are methodology, not RTL:
  * a weak checker passed a broken design for several iterations - an
    under-run line buffer returns STALE data, and on a repetitive test
    pattern stale data still measures as plausible colour bars.
    `tools/scaler_check.py` now validates a whole frame.
  * the DDR3 sim model was too kind (fixed 12-cycle latency), so the reader
    always won a race it loses on silicon. Stalls added, `STALL` parameter -
    **and even so neither model configuration reproduced the fault.** The old
    design still passes under stalls; cranking the stall to 250 starves the
    WRITE path and the frame just goes black. What settled it was an on-chip
    tap read over UART, exactly as with ascal itself. Simulation guided the
    fix; it did not prove it.

### Is ascal_v ready to replace `ddr3_framebuffer`? Not yet (assessed 2026-07-28)

The trade is NOT "ascal instead of triple buffering" - ascal_v has ALREADY
done the triple buffering, and `ddr3_framebuffer` has no buffering concept at
all (grep finds no buffer/base-address logic; it is single-buffered). So
`scaler_features.md` §1 would be ~50 lines of work thrown away if ascal_v
clears its gate. **HOLD the ddr3_framebuffer triple-buffering work as the
fallback; do not start it.**

Against promoting ascal_v today: hours old, has rendered exactly one test
pattern, never run a game core, audio entirely unproven, three open defects.
`ddr3_framebuffer` is what the merged 9-game core runs on, verified across
the whole roster. For it long-term: triple buffering, input auto-detect,
parameterised output timing, and full-line burst reads instead of the
4-pixel prefetch that §2 already fingers as the likely artifact source.

**Open symptom: HDMI looks more stable than the old path but SHIMMERS, with
a vertical wobble/jump every so many frames.** Ranked suspects:
  1. **Unsynchronised multi-bit CDC on the geometry.** `o_iw`/`o_ih` are
     latched from `i_hdmax`/`i_vdmax` (input clock domain) by one `o_clk`
     edge at `ocx==0 && ocy==0`, no handshake. `line_words` is derived from
     `o_iw`, so a glitched sample corrupts the stride for that frame. How
     often depends on the beat between the clocks - "every so many frames".
     NOTE the probability argument cuts against this: if i_hdmax only
     updates once per source frame, the coincidence window is ~1e-6/frame,
     i.e. hours, not seconds. **Verify what actually drives i_hdmax before
     believing this.**
  2. **60.09 Hz source vs 60.00 Hz output** - a ~0.09 Hz beat repeats or
     drops a frame every ~11 s. Triple buffering removes the TEAR but cannot
     remove this judder; only genlocking output to source can.
  3. **Nearest-neighbour at 1.5x** - 480->720 maps lines 1,2,1,2..., so any
     motion crawls. Inherent; this is what bilinear/polyphase exists to fix
     and it is the part NOT ported.

### Promotion gate - do in order

  * **A1. DONE 2026-07-28 - both CDC suspects ELIMINATED by measurement.**
    Three sticky saturating counters added to `ascal_v` (`dbg_cdc`) and read
    over UART for 95 s (~5700 frames), build marker D:
    | counter | reading | meaning |
    |---|---|---|
    | `cdc_fly` | **0** | buffer index never sampled mid-change |
    | `cdc_bad` | **0** | never an invalid index (>2) |
    | `cdc_geo` | **2**, not growing | exactly the power-on transient |
    Suspect 1 was doubly wrong. First, `i_hdmax`/`i_vdmax` are written the
    SAME value every vsync (511/479) with a stable source, so those registers
    never transition and the crossing is inert - `cdc_geo`'s 2 counts are just
    `o_iw` initialising 512 -> 1 -> 512 at power-on.
    Second, the replacement theory - incoherent multi-bit sampling of
    `latest` (which rotates 0->1->2, and 1->2 flips BOTH bits, so a 2FF sync
    stops metastability per bit but not incoherence across bits) - is real but
    far too RARE. The beat phase advances ~2475 cycles per frame while the
    hazard window is ONE cycle out of 1.65M, so it steps over the hazard
    almost every time: expect ~1 hit per 8 minutes, not one per few seconds.
    **Still worth fixing for robustness** (cross a single-bit toggle and
    capture the stable data on the synced edge); the same flaw exists in the
    OTHER direction on `rd_buf` -> `rdbuf_a2`, where an incoherent sample
    makes `free_buf` wrong and the writer could pick the buffer being read.
    But it is NOT the wobble. Retitled as A2b below.
  * **A2. Wobble suspects, revised after A1.** Leading candidate is now
    **frame-start write alignment**: `wr_ptr` resets at `a_frame_start`, and
    any words still in the write FIFO from the previous frame then land at the
    TOP of the new buffer, shifting the whole image by a sub-line offset that
    varies frame to frame - which would read as exactly "shimmer plus a
    vertical wobble every so many frames". The counting argument says leftover
    should be 0 (30720 words/frame, bursts of 8, 64 words/line), so this needs
    MEASURING not assuming: add a per-frame written-word counter and flag any
    frame != 30720. Then re-test suspects 2 (60.09 vs 60.00 beat) and 3
    (nearest-neighbour 1.5x line crawl), which remain live and are inherent
    rather than bugs.
  * **A2 UPDATE 2026-07-28 - shimmer QUANTIFIED, two theories killed.**
    90 raw (yuyv, not mjpeg) frames captured off the card and compared:
    | measurement | result |
    |---|---|
    | band-boundary y over 90 frames | **121 / 122 / 123** - moves 1-2 px |
    | left-border x over 90 frames | **160 in every good frame** - stable |
    | consecutive pixel-identical pairs | 6/89 (~8% of pixels change) |
    | highest-variance rows | 252, 297 (h-stripe band), 495-531 (checker) |
    The shimmer is **purely VERTICAL**. Horizontal never moves, and the bands
    that flicker are exactly the vertical-shift-sensitive ones (h-stripes,
    checkerboard) while the VERTICAL-stripe band is steady. A sub-line offset
    would smear horizontally too; a whole-line offset moves only vertically.
    This KILLS suspects 2 and 3 as the cause: nearest-neighbour mapping is
    deterministic per frame (the vertical Bresenham resets at ocy==VTOTAL-1),
    and repeating/dropping a frame of a STATIC pattern changes nothing.
    **The write-alignment fix (deferred buffer switch + short end-of-frame
    burst, `frame_pend`/`drain_cnt`) made NO measurable difference** - the
    distribution is unchanged. Kept anyway (it is correct, lint/sim clean, and
    removes a real residue path) but it is NOT the cause.
    **NEW LEADING THEORY: three buffers <-> three discrete vertical positions.**
    Each triple-buffer slot appears to hold the image at a slightly different
    vertical offset, so the picture jumps as `rd_buf` rotates 0->1->2.
    **Experiment RUN (marker F, `.triple_buf(1'b0)`) - PARTIALLY confirms:**
    | config | band-edge positions | spread |
    |---|---|---|
    | triple (E) | 121x60, 122x20, **123x3** | 2 px |
    | single (F) | 121x64, 122x19 | **1 px** |
    The THIRD position disappears with one buffer, so the triple-buffer slots
    ARE misaligned relative to each other - a real bug, worth fixing (suspect
    the per-buffer base address or a per-buffer write-start offset). But the
    dominant 121/122 jitter SURVIVES single-buffering, so that part is not
    buffer-related. Note single-buffering also introduces tearing, so the two
    configs are not perfectly comparable.
    **CONTROL RUN 2026-07-28 - the instrument is FINE and the fault is OURS:**
    | build | band-edge | spread | med changed px/pair |
    |---|---|---|---|
    | ascal_v triple (E) | 121x60, 122x20, 123x3 | 2 px | 72298 |
    | ascal_v single (F) | 121x64, 122x19 | 1 px | 53233 |
    | **ddr3_framebuffer (DD)** | **120x83** | **0 px** | **22091** |
    The capture card resolves vertical position EXACTLY on the known-good
    path, so the 7/90 detection failures are a benign capture artifact and
    the jitter is real. ascal_v also churns 2.4-3.3x more pixels per pair.

    **IT IS NOT A SHIFT.** Diffing a y=121 frame against a y=122 frame:
    shifting by +-1 row makes them match WORSE (15.0% / 17.7% differing) than
    shift 0 (9.3%), and only **70 of 720 rows differ**, scattered as isolated
    single/double rows clustered in the high-detail bands. The picture does
    not move - **individual output LINES are sporadically wrong.**

    **`dbg_underrun` was TRUTHFUL; dismissing it as "a lying instrument" was
    wrong.** It reads F (saturated, >=15/frame) because lines really do
    starve. Making the swap unconditional (to break the A2 deadlock) turned a
    late prefetch from a hang into a wrong line.

    **ROOT CAUSE FOUND: the one-line lookahead was worth ZERO cycles.** The
    lookahead advance and the prefetch issue are in two separate always
    blocks that BOTH fire at `ocx == 0`. With non-blocking assignment the
    prefetch read the PRE-update `sy_a` - the line needed by the line being
    displayed right now, not the next one. So the intended full-line lead
    collapsed back to the 160 px pillarbox: the exact race A2 was supposed to
    have fixed, reintroduced by scheduling rather than by addressing.
    FIX APPLIED: expose the next value as a wire (`sy_a_nxt`, with `vstep_a`
    /`in_vwin`) so both blocks see the same view, and prefetch on that.
    Lints clean, sim still passes (79 good bar rows, 0 bad), builds clean.
    **VERIFIED ON HARDWARE (marker 7) - THE LOOKAHEAD FIX DID NOT WORK.**
    It corrected the band edge to 120 (matching the control, so it did fix the
    A3 off-by-one as a side effect) but the corruption is unchanged: 59
    differing rows/pair vs 55 before, and underruns still read F.

    **BEST METRIC FOUND - adjacent-row duplication in the 1px h-stripe band.**
    Clean 480->720 nearest-neighbour must give ~0.333; excess duplication is
    lines repeating because their prefetch never landed:
    | build | duplicate rate |
    |---|---|
    | ddr3_framebuffer control | **0.385** (near-ideal) |
    | ascal_v before (E) | 0.551 |
    | ascal_v after lookahead fix (7) | 0.586 |
    ~17% of lines are EXTRA duplicates. **Starvation is real and quantified.**
    Use this metric, not band-edge position - the "vertical wobble" reading was
    an artifact of a starved line landing on the band boundary. The picture
    never moves: diffing two frames, shift 0 matches best (9.3%) and +-1 row
    matches WORSE (15.0%/17.7%).

    **The bridge is NOT the bottleneck.** `ascal_avl_ddr3.sv` issues read
    commands back-to-back (`rd_go = state==ST_READ && app_rdy`, one per
    cycle), so 64 words should land in ~80 cycles of the 1650 available.
    So the deadline is met on paper yet missed in practice - the next step is
    to MEASURE the actual fetch latency on chip (a cycle counter from rq_tog
    to rd_done, max-latched onto the beacon) rather than reason about it.

    **ROOT CAUSE FOUND AND FIXED IN SIM 2026-07-28 - it was the FETCH GATE.**

    First, the test bench was testing the wrong design: `sim/vsynth/av_top.v`
    ran a **640x480** output with `vmax=479`, i.e. **1:1 vertical scaling**,
    while hardware is 720p with `vmax=719`, i.e. **1.5x**. The line-repeat
    path, the 1650-cycle line timing and the 960-wide window were NEVER
    simulated. That is why the sim passed a design that starved on hardware.
    Fixed: av_top now uses HTOTAL=1650/VTOTAL=750/HDISP=1280/VDISP=720,
    hmin=160 hmax=1119 vmax=719, and DUMP_LINES=720 (DUMP_FRAME lowered to 8
    - a 720p frame is 1.24M cycles, 3x the old raster, and 24 frames times
    out). **With that geometry the sim REPRODUCES the fault**: h-stripe
    duplication 0.544 vs hardware 0.586. Iterate here, not on the board.

    **Best diagnostic: run-length histogram of identical adjacent rows** in
    the 1px h-stripe band. At 1.5x every run must be 1 or 2. Observed:
    `[(1,16), (2,26), (4,10), (7,1)]` - runs of **4**, and no 3s. A 4 is two
    2-runs merged: one source line is skipped entirely and its predecessor
    covers both slots. Only 53 of 76 expected source lines appeared.

    **The bug:**
    ```
    if (!swap_req || !rd_busy) begin      // swap_req is the PRE-update value
    ```
    Right after a swap `swap_req` is still 1, so `!swap_req` is 0 and the gate
    collapses to `!rd_busy`. Whenever the previous fetch's completion toggle
    had not cleared, the NEXT line's fetch was never issued - so that source
    line was skipped. ~19% of line transitions. Removing the gate gives
    **duprate 0.333 exactly, runs = only 1s and 2s (39 ones, 38 twos)** -
    better than the ddr3_framebuffer control's 0.385 - with colour bars at
    exactly 120 px and all six bands correct.

    **CONFIRMED ON HARDWARE 2026-07-28 (marker 9) - ascal_v now MATCHES the
    control exactly.**
    | build | dup rate | run lengths | differing rows/pair |
    |---|---|---|---|
    | ddr3_framebuffer control | 0.385 | 1s and 2s only | 0/720 |
    | ascal_v before | 0.551 | 1s, 2s, **804 fours, 23 sevens** | 55/720 |
    | **ascal_v fixed** | **0.385** | **1s and 2s only** | **1/720** |
    Run-length distribution is now identical to the control (3237 ones, 3154
    twos, zero 4s). Beacon confirms the mechanism: **481 fetches/frame**
    (expect 480, was ~390) and **96-cycle worst fetch latency** against the
    1650-cycle line budget - 6% utilisation, so latency was never the issue
    and an unguarded fetch issue is safe by a wide margin.
    (The 0.385-vs-0.333 gap between hardware and sim is the capture path -
    the control reads 0.385 too, so 0.385 is what a perfect result looks
    like through this card.)

    **RESIDUAL AFTER THE GATE FIX (marker 9) - two SEPARATE faults, do not
    conflate them again (I did, for hours):**

    **(i) PLATFORM SYNC LOSS - NOT the scaler.** Black-frame rate is
    IDENTICAL across all three builds: ddr3_framebuffer control **7/90 (8%)**,
    ascal_v before **7/90**, ascal_v after **7/90**. The known-good
    framebuffer drops sync at exactly the same rate, so this lives in the
    HDMI/TMDS path downstream of both scalers. **This is what makes the DDR3
    path unusable, and fixing ascal_v cannot fix it.** It is roadmap item 1
    and deserves its own attack - it matters more than the residual below.

    **(ii) ascal_v line-selection jitter at content transitions.** Excluding
    black frames:
    | build | clean pairs | med wrong rows | band-edge |
    |---|---|---|---|
    | ddr3 control | **82/82** | 0 | 120 always |
    | ascal_v triple | 35/82 | 1 (p90 4) | 120x80, 122x3 |
    | ascal_v single | 25/82 | 2 (p90 5) | 120x81, 122x2 |
    **Single buffering is WORSE, so per-buffer misalignment is NOT the cause**
    - the earlier "3 buffers <-> 3 positions" theory is dead. Keep triple.
    Only **37 distinct rows** ever fail; 21 are within 3 of a band boundary
    (120/240/360/480/600) and account for 92/142 hits, the rest cluster at the
    top border (rows 2-6). Each fails in ~7% of frames. A wrong line is only
    VISIBLE where adjacent source lines differ, so this is an occasional
    off-by-one in WHICH line is displayed at a transition - the h-stripe band
    run-lengths are otherwise perfect (1s and 2s only).
    Beacon is steady through all of it: **x01E1 = 481 fetches/frame**,
    **q0C-0D = 96-104 cycle worst latency** vs a 1650-cycle budget, no spikes.
    So every fetch IS issued and memory IS fast - this is not starvation.
    **Lead suspect: the first output line of each frame.** At `ocy==0` the
    code forces `nsy = 12'hFFF` and fetches `sy_a_nxt` (the line for ocy==1),
    so output line 0 displays whatever was already in the buffer and source
    line 0 is never fetched for it. That is an off-by-one at frame top, and
    it fits the row 2-6 cluster. NEXT: dump 3+ consecutive frames from the
    720p sim (it reproduces now) and check whether the band edge jitters
    there - debug with full internal visibility rather than on the board.

    **SIM NOW REPRODUCES THE RESIDUAL DEFECT - debug here, not on the board.**
    Two changes made it usable: `mcr_testpattern` got a `FREEZE_BAR`
    parameter (default 0, hardware unaffected) because a per-line signature
    comparison is useless when an animated overlay touches every line every
    frame; and the harness now dumps a **per-line FNV-1a hash** for 20 frames
    plus `dbg_sy` (source line displayed) instead of pixels - 24 full frames
    of pixels is ~22M lines of text. Also: the old 200 ms sim-time cap only
    allowed ~12 frames (raised to 700 ms), and ASAN is not needed (the old
    constructor segfault does not occur in this harness) - `-O2` is ~5x faster.

    Findings, all from simulation with a STATIC source:
    * Most frames are **bit-identical**; 12 of 20 frames carry 1-6 wrong
      lines. Deterministic, so a glitch frame can be re-dumped at will.
    * **`dbg_sy` is CORRECT on every glitching line** (`sy == ideal`
      everywhere; the only deviation is row 0, which is the deliberate
      `nsy=12'hFFF` frame-start force). **So the addressing/Bresenham is
      RIGHT and the DATA is stale** - do not go looking at sy again.
    * The stale content is an EARLIER SOURCE LINE, not the previous frame:
      at rows 120/121/123/124 the pixels are all-white (colour-bar band,
      ~line 79) where the vertical-stripe pattern belongs. With a static
      source, previous-frame staleness would be invisible - so this is
      line-level, not frame-level.
    * **Buffer parity is the pattern.** Rows 120,121 (line 80) and 123,124
      (line 82) are stale; row 122 (line 81) is fine. Lines 80 and 82 both
      live in ping-pong half Y, line 81 in half X. **The fetches targeting Y
      did not land; X was always correct.** Same shape at every other
      cluster (360/361/363/364, 240/241/242/245, 3/4/6/7).
    * Note `avl_clk == o_clk` in the sim harness, so this is NOT a CDC race -
      it is deterministic logic.

    **A4 SETTLED: `dbg_underrun` is measuring nothing - DELETE IT.** Measured
    78-410 underruns per frame against ~480 fetches, with ZERO correlation to
    glitches (frame 7: und=410, 0 wrong lines; frame 18: und=78, 1 wrong
    line). The toggle-based `rd_busy` is not a valid completion signal.
    Replace with a word-count completion (count `avl_readdatavalid` against
    `rq_len_l`) before relying on any guard that uses it.

    **ROUND 2 - four integrity checks ALL PASS, so the fault is PHASE, not data:**
    * **Write path clean.** ddr3_model now asserts that with a STATIC source a
      location is never rewritten with a different value: 600k+ writes,
      **0 mismatches**. DDR3 holds correct data at correct addresses.
    * **No short fetches.** Every fetch delivers exactly `rq_len` (64) words
      into its half - counter `short_cnt` = 0 across 20 frames.
    * **No fill/display collisions.** A fill never targets the half currently
      displayed - counter `collide_cnt` = 0.
    * **All fetches issued** (481/frame) and worst latency 96 cycles of 1650.

    **THE ACTUAL MECHANISM: the fetch/display schedule is NOT frame-invariant.**
    Traced with `+define+ASCALV_TRACE` (guarded, off by default):
    ```
    frame A:  issue ocy=116 sy_nxt=77 ... swap ocy=117 sy_have=77
    frame B:  issue ocy=115 sy_nxt=77 ... swap ocy=116 sy_have=77
    ```
    Same source line, but frame B runs the whole schedule ONE OUTPUT LINE
    ahead of frame A. Addresses are right in both (4928 / 136000 / 70464 =
    line 77 at buffer bases 0 / 65536 / 131072, so triple buffering rotates
    correctly). What drifts is the PHASE of the ping-pong relative to the
    raster - which is why a given line is stale in one frame and fine in the
    next, and why glitches cluster by buffer parity.

    **FRAME-START THEORY REFUTED BY EXPERIMENT 2026-07-28.** A deterministic
    frame start WAS implemented (at `ocy==VTOTAL-1`: set `rd_buf<=nrd`,
    `disp_buf<=1`, fetch source line 0 into half 0, `swap_req<=1`,
    `sy_have<=12'hFFF`; the old `ocy==0` forced-`nsy` refetch removed). Proved
    to execute (25 times, once per frame, rd_buf rotating 0->2->1). **The
    glitches are byte-identical: same 12 frames, same rows.** So frame-start
    phase is NOT the cause. The change is KEPT anyway - it is correct, it puts
    source line 0 on output line 0 (it previously landed on line 1), and it
    makes the line-0 fetch use the NEW rd_buf instead of the pre-update one.
    Note `sy` deviations from ideal are now **0** including row 0.

    **Where that leaves it - every per-fetch invariant holds, yet data is
    stale.** Verified simultaneously: DDR3 content correct, address correct,
    fetch issued, exactly 64 words delivered, target half never the displayed
    one, sy == ideal. If all of those are true the displayed half MUST hold
    the right line - so one of the checks is not measuring what it claims, or
    the staleness enters between the fill and the read. Next things to try,
    cheapest first: (a) log the actual 64 words of a fetch for a known glitch
    line and compare against DDR3 contents at that address - this
    distinguishes "wrong data fetched" from "right data, wrong half read";
    (b) check the `linebuf` read pipeline across the swap (`lb_word`/`px_sel`
    are registered, so the half select is sampled a cycle before use);
    (c) widen the ping-pong to 4 slots so a late or misrouted fill cannot
    alias onto the half about to be displayed.

    **Bridge protocol hazard CHECKED and refuted.** `avl_waitrequest` in
    `ascal_avl_ddr3.sv` is `!(wr_go || (rd_go && beat==0))`, i.e. it goes LOW
    on WRITE beats - so a master sitting in its read state could read that as
    "read accepted", drop the request, and leave the half stale. Instrumented
    the bridge (`+define+ASCALV_TRACE`): **read-while-writing = 0**. It cannot
    happen here because ascal_v only enters `A_RD` from `A_IDLE`, and it would
    have been stalled in `A_WR` if the bridge were mid-write. Reads started
    tracks the expected ~481/frame. **Still worth hardening** - the waitrequest
    encoding is a latent trap for any future master that pipelines.

    (superseded) Suspected cause - frame-start state is never reset. At `ocy==0` the
    code forces `nsy = 12'hFFF`, but a fetch for line 0 has usually ALREADY
    been issued at `ocy==VTOTAL-1` (sy_a_nxt=0 vs the last line's sy) and
    swapped in. The forced value makes line 0 fetch a SECOND time,
    redundantly, and that extra fetch flips the ping-pong parity. Whether it
    happens depends on carry-over state - `swap_req`, `disp_buf`, `sy_have`,
    `sy_fill` are NOT reset at frame start - so the phase can differ frame to
    frame. **FIX DIRECTION: reset the whole line-buffer state machine
    deterministically at frame start** (or stop forcing `nsy` and let the
    normal comparison run), so every frame begins from an identical phase.

    (superseded) NEXT: count fetches ISSUED vs read COMPLETIONS in sim, per ping-pong
    half, and assert that a half is fully written before it is displayed.
    Also fix (separately, currently invisible with a static source because
    the buffers hold identical content): at `ocy==0` the fetch uses
    `base_of(rd_buf)` with the PRE-update `rd_buf`, so the first fetch of
    each frame reads the previous frame's buffer.

    **STILL OPEN (A4): `rd_busy` is unreliable.** The gate only misfired
    because the completion toggle was still set 1650 cycles after issue. With
    the gate gone this no longer affects the picture, but `dbg_underrun`
    remains meaningless until it is fixed, and issuing a fetch is now
    UNGUARDED - safe at one fetch per 1650-cycle line against ~80-cycle
    reads, but it should be given a correct guard rather than none.

    (superseded) Structural fix if latency turns out to be jittery: the control has no
    per-line deadline at all - `ddr3_framebuffer` streams with a 32-entry
    prefetch buffer and PREFETCH_DELAY=44. ascal_v's per-line burst gives it a
    hard deadline every line. Deepening to 4 line-buffer slots and prefetching
    2 lines ahead would double the budget and absorb jitter.

    **Wrong theories this session, recorded so they are not retried:**
    geometry CDC (values are constant); triple-buffer index CDC (real but ~1
    hit per 8 min, far too rare); frame-start write alignment (fix made no
    measurable difference); the capture card (control proves it resolves
    position exactly, spread 0px). Also: `dbg_underrun` was TRUTHFUL - calling
    it a lying instrument was wrong, and cost time.

    (superseded) INSTRUMENT SUSPICION: exactly 7 of 90 frames fail detection
    in all captures (before the write fix, after it, and single-buffered) -
    a constant that survives unrelated RTL changes belongs to the measuring
    apparatus, not the design. **NEXT: run the identical 90-frame measurement
    against a `video_test60k/ddr3_top` build as a CONTROL.** If the known-good
    production framebuffer shows the same 121/122 split and the same 7/90,
    the capture card cannot resolve 1 px of vertical position and this whole
    line of measurement needs a different instrument (e.g. photograph the
    monitor, or compare a long-exposure capture). Only if the control is
    CLEAN is the residual jitter real and ours.
  * A2b. Fix both multi-bit CDCs (toggle + stable data), robustness.
  * **A5 SCOPED: MiSTer's audio system is NOT transplantable.** `sys_top.v`
    drives HDMI_TX_D[23:0]+HS/VS/DE/CLK and HDMI_I2S into an **external
    ADV7513 transmitter**; `sys/i2s.v` is a ~40-line serialiser and there is
    NO data-island, ACR, CTS or audio-sample-packet logic anywhere in
    `sys/` - the ADV7513 does all of it in silicon. We generate TMDS
    ourselves via OSER10, so hdl-util/hdmi (already vendored, already
    carrying audio for all nine shipping games) is the only real option.
    Remaining work is the raster-ownership swap: `hdmi.sv` is the timing
    MASTER (cx/cy are outputs), while `ascal_v` generates its own raster, so
    ascal_v needs external-raster inputs driven from cx/cy. Use the INTEGER
    `AUDIO_CLK_DELAY = 74250*1000/AUDIO_RATE/2` divider from
    ddr3_framebuffer - a fractional-exact one made dropouts WORSE (roadmap
    item 1) and a declared-vs-actual mismatch was the original 50% rate lie.
  * A3. Fix the `vmax` off-by-one - the bottom white border is missing
    (top/left/right render). Static, not a wobble source.
  * A4. Fix or remove `dbg_underrun`: it reads F (>=15/frame) while the
    picture is correct, so it is lying. A lying instrument is worse than
    none. Suspect the read-completion toggle, not real starvation.
  * A5. **Add the 1 kHz sine + `tools/audio_dropout_check.py` to the ascal
    rig** (it has HDMI audio clock plumbing but no tone and no measurement).
    Gate: match BRAM's 0 lost cycles in 15 s, or at least DDR3's 1.
  * A6. Run a REAL core (MCR-2 Domino) through it, not a test pattern.
  * A7. Soak-test a FLASHED build - also settles the production-reboot
    question below.
  * Only if promoted: bilinear / sharp-bilinear (suspect 3's real fix, and
    where CK3001 and the DSPs live - this is the risky part of the port).

**Production-reboot question (asked 2026-07-28).** Needing frequent reboots
during this session is most likely a DEVELOPMENT artifact: each
`openFPGALoader` SRAM load restarts five PLLs and the DDR3 controller
mid-flight, dozens of times per session, whereas production configures once
from SPI flash and stays up. The chip is cool to the touch (not thermal) and
the FT2232 re-enumerated mid-session, pointing at USB/reset. **This is a
hypothesis, not a result** - A7 is what would actually settle it. Note it
also lines up with the "a RECONFIG recovers it" lead in roadmap item 1.

## STATUS 2026-07-29 — read this first

### ascal_v IN THE MCR-3 CORE — IT FITS (2026-07-29)
`src/video/ascal_fb.sv` is a **drop-in replacement for `ddr3_framebuffer`**
built on ascal_v: same port list plus two extra inputs (`i_ce`, `i_de`),
because ascal_v needs the pixel tick and the active-video LEVEL separately -
`fb_we` is their AND and drops between pixels, which would look like one line
per pixel to the input capture. Swapping a core is a module-name change plus
two wires (`pixel_tick`, `cap_active` already exist in the MCR tops).

**Builds clean in `mcr3_console60k`** - no errors, PA1019 absent, no
undeclared symbols:
| resource | ddr3_framebuffer | ascal_fb | delta |
|---|---|---|---|
| Logic | 13338 | 13590 | +252 |
| Registers | 8613 | 8688 | +75 |
| CLS | 9893 | 10096 | +203 |
| **BSRAM** | **88/118** | **98/118 (84%)** | **+10** |
| DSP | 1 | 2 | +1 |
**20 BSRAM blocks to spare.** (The merged 9-game core at 114/118 would NOT
fit - 124 needed. Halving `MAX_WIDTH` reclaims nothing: Gowin allocates BSRAM
by WIDTH, and both the line buffer and write FIFO are 128 bits. Narrowing
`N_DW` to 64 is the lever if those blocks are ever needed.)

**RUNNING — TAPPER RENDERS CORRECTLY THROUGH ascal_v (2026-07-29).** Clean
colours, sprites and text, no visible glitches. This is the first time ascal_v
has scaled REAL GAME CONTENT rather than the test pattern.

**Root cause of the calibration failure: ascal_v was not held in reset until
DDR3 finished training.** `ddr3_framebuffer` holds its own state machines in
reset via `ddr_rst`; my wrapper reset ascal_v on `rst_n` alone, so it started
issuing Avalon reads and writes DURING the training sequence and calibration
never completed. Fix:
```
.reset_n(rst_n & init_calib_complete & ~ddr_rst)
```
Measured: **6/6 loads calibrate**, matching the control's 8/8 (before the fix
it was 0/many). **Any future master on this DDR3 controller must stay quiet
until `init_calib_complete`** - the app interface is not tolerant of traffic
during training, and the symptom is silent (builds clean, times clean, video
path perfect, memory simply dead).

**Debugging note worth keeping:** the control and the ascal build share the
same top and therefore the SAME beacon format, so a silent SRAM load failure
is indistinguishable from a real result. Four "c0" readings that looked like
the control failing were actually leftover ascal bitstreams. **When A/B-ing
two builds of the same core, give them distinguishable beacon markers.**

(historical) NOT YET RUNNING: DDR3 does not calibrate (beacon stuck at `c0`, black
screen). The core itself runs - beacon counters advance and the format is
the mcr3 one (`d0D LBA`), so this is bring-up of the wrapper, not the scaler.
Already checked and matched against BOTH references
(`ddr3_framebuffer.v` and `ascalv_top.sv`): DDR3 controller `rst_n` tied to
`1'b1` (feeding the core reset in was wrong and was fixed), `pll_ddr3.reset`,
`pll_mDRP_intf.rst_n(1'b1)`, `syn_keep` on `clk_x1` ONLY (adding it to `hclk`
breaks the merge with the top's `fb_hclk` that the SDC constrains, giving
TA2003/TA2004).
**The VIDEO PATH IS PROVEN GOOD** - user reports HDMI SYNC with **grey
borders and a black window**. Grey is ascal_v's own pillarbox fill (`0x20`),
so its raster, the HDMI stack and the TMDS output are all working; black in
the window is the line buffer returning zeros because DDR3 never calibrates.
**Only the DDR3 link is broken.**

**Ruled out by experiment (do not repeat):**
  * `place_option` - already 2 in mcr3's build.tcl (CLAUDE.md's documented
    "builds clean, DDR3 never trains" cause).
  * DDR3 controller port wiring - diffed against `ddr3_framebuffer.v`
    lines 185-220, equivalent.
  * Controller `rst_n` - was wrongly fed the core reset; now `1'b1` like both
    references. Real bug, fixed, but not the cause.
  * `ddr3_framebuffer.v` left compiled alongside `ascal_fb` (it instantiates
    its own pll_ddr3/gowin_pll_hdmi/DDR3 IP) - removed from `build.tcl`.
    Correct hygiene, not the cause.
  * PLL exhaustion - PLLA reports 5/8.
  * `rw_check_on_ram` (mcr3 uses 1, the working ascal rig uses 0) - tried 0,
    no change; reverted.

**Still to try:** the ascal rig and this core differ mainly in DENSITY
(13.6k logic / 98 BSRAM vs 4.7k / 28), and the Gowin DDR3 IP is known to be
placement-sensitive. Suspect physical placement pressure rather than RTL -
try constraining/floorplanning the DDR3 IP, or build a cut-down mcr3 (one
game, no USB/SDRAM) to see whether calibration returns as density drops.
Also worth diffing `clk50_pll`/`clk27` net properties (global vs local
routing) between the two designs, since `clk_g` feeds calibration.

### SCALER BACKLOG (after the line-glitch fix)
**Cleanups (small, do first):**
  * **DELETE `dbg_underrun`** - it measured 78-410 hits/frame with zero
    correlation to real glitches; a lying instrument is worse than none.
  * Remove the `ASCALV_TRACE` scaffolding and the leftover debug counters
    (`cdc_*`, `short_cnt`, `collide_cnt`, fetch/latency) - they are compiled
    into the current numbers and cost logic.
  * Audio tone reads **982.6 Hz** instead of 1000 (-1.7%). The audio clock is
    right (32004 Hz), so suspect truncation in `sine_gen`'s phase increment.
    Cosmetic for a tone, but a systematic pitch error would carry into games.
**Validation not yet done:**
  * **Run a REAL game core through `ascal_v`** - it has only ever scaled the
    test pattern.
  * Soak-test a FLASHED (not SRAM) build; also settles the production-reboot
    question.
**Features:** see `docs/scaler_options.md` "Modes worth adding" - rotation for
ROT90 cabinets is the highest-value one for this project, then interpolation,
scanlines, integer scaling, aspect/overscan, 240p verification.

### *** ascal_v LINE GLITCH FIXED *** (marker 5)
Root cause was **two bugs in the Avalon handshake, not in the scaler logic**:

1. **`rd_pending` was a ONE-CYCLE PULSE treated as a LEVEL.**
   ```
   always @(posedge avl_clk) begin
       rq_s1 <= rq_tog; rq_s2 <= rq_s1;   // 2FF sync advances rq_s2 EVERY cycle
       ...
       A_RD: rq_s2 <= rq_s1;              // "consume"
   wire rd_pending = (rq_s1 != rq_s2);    // therefore true for ONE cycle only
   ```
   The synchroniser itself advances `rq_s2`, so a request was visible for a
   single cycle. **Any read issued while the FSM was not sitting in A_IDLE was
   silently dropped** - the line never arrived and the raster showed stale
   data. Fixed with a proper request LATCH (`rd_req`), set on the toggle edge
   and cleared on acceptance, with SET taking priority over CLEAR.
2. **`avl_waitrequest` was not transaction-specific.** It was
   `!(wr_go || (rd_go && beat==0))`, so it went low on WRITE beats too; a
   master sitting in its read state could mistake a write acceptance for its
   own read and consume a request the bridge never saw. Now
   `avl_read ? !(rd_go && beat==0) : avl_write ? !wr_go : 1'b1`.

**Measured on hardware, exclusive capture device:**
| metric | before (E) | after (5) |
|---|---|---|
| clean frame pairs | 94/292 | **342/342** |
| wrong rows per pair | median 2, p90 6 | **0** |
| band edge over 120 frames | 120/121/122 | **120 every frame** |
| h-stripe duplicate rate | 0.333 | 0.333 (ideal) |
Colour bars: 8, correct colours, 118-120 px. Picture verified LIVE (0
identical consecutive pairs - always check this, a frozen image also scores
0 wrong rows). **ascal_v now matches the shipping framebuffer's stability
while scaling better than it (0.333 vs 0.385).**

Both fixes are in `src/ascal/ascal_avl_ddr3.sv` and `src/video/ascal_v.sv`.
The 4-slot ring is NOT needed for this and was set aside (WIP at
`scratchpad/ascal_v.ring_wip`); the ping-pong is correct once requests stop
being dropped. Note the ring exposed the bug precisely because it issues reads
back-to-back - a good stress pattern to keep in mind.

### MERGED 9-GAME CORE REBUILT WITH THE PLL FIX — user-verified good
Rebuilt `mcr23_console60k` (PA1019 absent, no negative slack, no undeclared
symbols, 10684 registers / 18%, 114/118 BSRAM as documented) and SRAM-loaded it.
**User played Timber with HDMI audio and reported NO dropouts - "1000% better".**
That is the acceptance signal; take it over any number below.

**METHOD WARNING - `blackdetect` IS INVALID ON GAME CONTENT.** The soak
reported 22 intervals / 5.21% black, but games legitimately go dark (attract
transitions, level changes, dark scenes) and every OSD game switch reloads ROMs
and intentionally drops the raster. The test pattern was a valid subject
precisely because it never goes black. **For game cores, use the user's eyes or
a content-independent signal (e.g. TMDS lock, or a frozen-frame detector), not
black-frame counting.**

One transient seen mid-session: video went black while the core stayed alive
(beacon counters advancing, `c1 r0`), and a reconfiguration brought it back.
Unexplained, seen once, and not reproduced after the clean reload - watch for
it rather than treat it as closed.

### OPEN: picture not centred, on BOTH VGA and HDMI (reported 2026-07-29)
Affects analog VGA as well as HDMI. VGA is driven straight from the core's
raster and never passes through the framebuffer, so **this is in the CORE's
active-window placement, not the scaler**. `ddr3_framebuffer` centres a
`disp_width=960` window at x=160 of 1280 automatically, so the HDMI side is
symmetric by construction. Look at the per-game hstart/vstart / active-window
constants in the core, not at the video path. Cosmetic, separate from the
scaler work.

**Landed and verified:**
  * **HDMI sync loss FIXED across every core** - `gowin_pll_hdmi27.v` VCO was
    1485 MHz, outside the 700-1400 MHz spec, recorded for months as an
    "accepted PA1019 warning". Now `MDIV_SEL=41, MDIV_FRAC_SEL=2,
    ODIV0_SEL=3` (VCO 1113.75 MHz, same 371.25 MHz out). PA1019 is gone from
    the log; soak-verified **30 min / 0.000% black**, confirmed on the monitor.
    The PLL is SHARED - `mcr2_console60k`, `video_test60k`, `merge_probe` and
    the shipping game cores all get this fix. **Re-testing the merged 9-game
    core is the highest-value open item.**
  * **`dvi_tx_ext` -> hdl-util `hdmi`** in `ascal_test60k`: raw DVI measured
    21.7% black, HDMI 0.00%. Brought **working audio** (1 kHz tone, 0
    dropouts) to that rig for the first time.
  * **`ascal_v` scales pixel-exactly** - h-stripe duplicate rate 0.333
    (ideal; the shipping framebuffer is 0.385), colour bars at exactly 120 px,
    all six pattern bands correct. From "ascal cannot be compiled on this
    toolchain" to this in one session.
  * **The simulation is now trustworthy** - deterministic (explicit `ram[]`
    init) and representative (two independent 74.25 MHz clocks). This is the
    single most useful artifact for whoever continues.

**Open:** ~2 wrong rows per frame in `ascal_v` (details below), the 4-slot
ring that should fix it (31-line producer wedge), and the interpolators that
were never ported.

**New doc:** `docs/scaler_options.md` - decision guide comparing all four
scaler paths with measured numbers, plus the measurement discipline. Start
there if you are new to this area.

## ascal_v — forward plan (agreed 2026-07-28)

Four things are outstanding beyond the last rendering defect. Ordered by what
blocks use of the core, not by how interesting they are.

### 1. Sync loss — HIGHEST PRIORITY
**CORRECTION 2026-07-28: the "7/90 black frames on every build" figure was
WRONG and must not be quoted.** Those 7 frames are at indices **0-6 of every
capture** - the capture card's lock-up time at the start of a recording, not
dropouts. A 90-frame grab is only ~1.5 s, far too short to catch a fault the
user sees "every so often". Any future dropout measurement must (a) discard
the first ~10 frames and (b) run for MINUTES. Use
`ffmpeg -vf blackdetect=d=0.02:pix_th=0.08 -f null -`, which reports black
intervals directly, rather than grabbing frames and thresholding.
**MEASURED PROPERLY 2026-07-28 (5 min each, same method, back to back):**
| build | black intervals in 300 s | black time |
|---|---|---|
| ascal_v (marker 9) | **26** | **6.5%** |
| **ddr3_framebuffer control** | **0** | **0.0%** |
**The sync loss is ascal_v's output path, NOT the platform.** The earlier
"identical on every build, therefore downstream of both scalers" conclusion
was wrong - it came from the capture lock-up artifact above.
Corroborating: the user's analog **VGA output never drops**, and VGA is driven
straight from the source raster, bypassing scaler, DDR3 and TMDS. So the core
and its timing are fine. The FPGA also keeps running throughout (643 beacon
lines logged across the control run).

**PRIME SUSPECT: the rig emits raw DVI, not HDMI.**
| | control | ascal rig |
|---|---|---|
| output stage | hdl-util `hdmi`, `DVI_MODE(0)` | `dvi_tx_ext` |
| signalling | HDMI: AVI InfoFrames + data islands | raw DVI, no infoframes |
| 5-min sync | 0% black | 6.5% black |
Many HDMI sinks re-lock periodically without AVI InfoFrames inside a timeout,
which matches the symptom (irregular 0.4-2.4 s blackouts on BOTH the monitor
and the capture card).
**So roadmap items 1 and 2 are ONE job:** swapping `dvi_tx_ext` -> hdl-util
`hdmi` should fix the sync loss AND deliver audio, with a module already
proven on this silicon across nine shipping games. Do that next.
**HDMI SWAP DONE AND MEASURED (marker C).** `dvi_tx_ext` replaced with
hdl-util `hdmi` (VIDEO_ID_CODE 4, DVI_OUTPUT 0, AUDIO_RATE 32000) + the 1 kHz
`sine_gen` tone + the INTEGER `AUDIO_CLK_DELAY` divider. `ascal_v` gained
`ext_rast`/`ext_cx`/`ext_cy` so the hdmi module is the timing MASTER and the
scaler follows its cx/cy (hmin/hmax shifted 2 px to absorb the scaler's
2-cycle pixel pipeline). Build clean: 4968 registers (was 4284), 28/118 BSRAM,
no undeclared symbols. **Audio now exists in this rig for the first time.**
Result, one consistent parser over all three 5-minute logs:
| build | intervals | black time |
|---|---|---|
| ascal_v + raw DVI | 31 | **21.7%** |
| ascal_v + hdl-util HDMI | 32 | **7.8%** |
| ddr3_framebuffer control | **0** | **0.0%** |
**A real ~3x improvement, but NOT a fix.** (Note: an earlier hand parse of the
DVI log gave 6.5%; that parse was faulty - always use the same extractor for
both sides of a comparison.)

**SYNC LOSS IS FIXED 2026-07-28 - and the residual was MY MEASUREMENT.**
Exclusive-device 3-minute blackdetect on the HDMI build: **0 intervals,
0.00% black.** The user independently confirmed on the monitor that it no
longer cuts out. The earlier "7.8% residual" was self-inflicted: a SECOND
ffmpeg was grabbing a frame from `/dev/video4` 25 s into that run, and two
processes contending for one v4l2 device produce exactly that signature.
**Measurement discipline for this rig, learned twice now:**
  * nothing else may touch `/dev/video4` during a dropout measurement -
    `pgrep -f ffmpeg` first, and never grab a preview frame mid-run;
  * discard events starting at t<0.5 s (capture card lock-up);
  * use ONE parser for both sides of any comparison.
So: `dvi_tx_ext` -> hdl-util `hdmi` took ascal_v from 21.7% black to **0.00%**,
matching the ddr3_framebuffer control. Raw DVI without AVI InfoFrames was the
whole cause.

**AUDIO NOW EXISTS in the rig, and the first measurement found a real bug.**
Captured off the MiraBox (`arecord -D hw:3,0`, MS2109): tone present but at
**7852 Hz instead of 1000**, with 628k waveform glitches. Cause: `sine_gen`'s
`sample_en` is a ONE-CYCLE ENABLE but was fed `clk_audio`, which is a real
50%-duty CLOCK for the hdmi module - so the phase accumulator advanced ~1160
times per sample period. Fixed by deriving a single-cycle tick from
`clk_audio`'s rising edge. **Keep the two signals distinct: hdmi needs the
clock, sine_gen needs the pulse.**

**2026-07-28 LATE — THE REAL FAULT IS TIME-DEPENDENT AND LOOKS LIKE DDR3.**
Sequence observed with the user watching: the ddr3_framebuffer CONTROL build
(marker DD - the framebuffer all nine shipping games use) looked **perfect
immediately after flashing**, then began **flashing/dropping a few minutes
later on the same configuration**. That is exactly the "degrades on one
config, a RECONFIG recovers it" pattern in roadmap item 1.
**This invalidates the freshness of every dropout number measured so far** -
including "control = 0.00% black over 5 min", which was taken right after a
flash, i.e. precisely when the fault is absent. **Any future dropout
measurement must record TIME SINCE CONFIGURATION and run long enough to cross
the degradation point.**

Correlation that points at the cause:
| path | uses DDR3? | behaviour |
|---|---|---|
| analog VGA (straight off the source raster) | **no** | **never drops** |
| ascal_v -> HDMI | yes | degrades |
| ddr3_framebuffer -> HDMI | yes | degrades |
Everything that touches DDR3 degrades and recovers on reconfig; the one path
that bypasses it is flawless. A reconfig re-runs DDR3 calibration, which is
the obvious thing that would heal on reload and drift while sitting. The
beacon still reports `c1 r0` (calib complete, no reset) while degraded, so the
controller does NOT know it has a problem - do not trust that flag alone.
**Also note a monitor-compatibility layer on top of this:** one HDMI monitor
would not lock at all while a second monitor and the capture card were both
perfect on the same bitstream. Keep that separate from the DDR3 drift.

**PRIME SUSPECT FOUND: the HDMI PLL VCO IS OUT OF SPEC.**
Captured the board WHILE DEGRADED (40 s, control build): 51 black frames and
44 frozen frames - but the colour bars in a surviving frame are **perfect**
(8 bars, 118-120 px, exactly correct RGB). **So DDR3 data is fine; the LINK
drops.** That redirects suspicion from memory to clocking.
`src/ddr3fb/gowin_pll_hdmi27.v` runs `MDIV_SEL=55, ODIV0_SEL=4` from 27 MHz:
**VCO = 1485 MHz, outside the GW5A PLLA spec range of 700-1400 MHz.** This is
the PA1019 warning `CLAUDE.md` records as the single ACCEPTED exception
("NESTang's standard config, confirmed working"). **That acceptance now looks
wrong** - an out-of-spec VCO is exactly what works cold and goes marginal with
time/temperature.
It explains every observation: analog VGA never drops (different PLL,
`gowin_pll_mcr2`); both scalers degrade identically (both share this chain);
recovers on reconfig (PLL relocks cold); degrades while sitting; and the
picture content is intact whenever there IS a picture.
**FIXED AND SOAK-VERIFIED 2026-07-28.** `MDIV_SEL=41, MDIV_FRAC_SEL=2,
ODIV0_SEL=3` applied to `src/ddr3fb/gowin_pll_hdmi27.v`. **PA1019 is now
ABSENT from the build log**, and a 30-minute soak with NO reconfiguration
gave **0 black intervals / 0.000% black**, independently confirmed on the
monitor. The old PLL degraded within a few minutes of every configuration.
Build otherwise unchanged (4969 registers, 28/118 BSRAM).
`CLAUDE.md` updated: the "accepted PA1019 exception" is deleted and PA1019 is
a build-breaker again with no exceptions. The PLL is shared, so this should
fix HDMI dropout on `mcr2_console60k`, `video_test60k`, `merge_probe` and the
shipping game cores too - **worth re-testing the merged 9-game core next.**

(historical) FIX - same 371.25 MHz with an in-spec VCO:
| MDIV | ODIV0 | VCO | out | |
|---|---|---|---|---|
| 55 + 0/8 | 4 | **1485.00** | 371.25 | out of spec (current) |
| **41 + 2/8** | **3** | **1113.75** | 371.25 | **in spec - use this** |
| 27 + 4/8 | 2 | 742.50 | 371.25 | in spec (fallback) |
Set `MDIV_SEL=41, MDIV_FRAC_SEL=2, ODIV0_SEL=3`. **Verify PA1019 disappears
from the build log** (that warning becomes a real pass/fail signal again), then
soak-test for >30 min WITHOUT reconfiguring. If it holds, update `CLAUDE.md` -
the "accepted PA1019 exception" section is then actively harmful advice, and
the same PLL is used by the shipping game cores, so this would fix them too.

**IF THE PLL FIX DOES NOT HOLD:** `src/ascal/avl_ddr3_memtest.sv` already exists and
drives the same bridge with an address-derived payload (a wrong ADDRESS fails
as loudly as wrong DATA); it previously ran zero mismatches over thousands of
passes. **Run it for tens of minutes without reconfiguring** and watch for
errors appearing over time. If they do, this is DDR3 calibration drift and the
fix belongs in the controller (periodic recalibration / read-leveling), not in
any scaler. If it stays clean while HDMI still degrades, the drift is in the
HDMI/TMDS clocking instead.

**AUDIO MEASURED GOOD after the tick fix** (build marker E), captured off the
MiraBox MS2109 at 48 kHz for 20 s:
| metric | before tick fix | after |
|---|---|---|
| tone | 7852 Hz | **982.6 Hz** (expect 1000) |
| waveform glitches | 628160 (31408/s) | **87** (4.35/s) |
| real dropouts | - | **0** |
The one "dropout" the checker reports sits at **t=0.003 s** and is the
`arecord` lock-up at capture start - the exact analogue of the video capture
artifact. After t=1 s the stream is continuous (the 4.2% "silence" is just the
sine's zero crossings). **So: HDMI video holds sync 100%, and audio runs clean
with no dropouts.** Both A5 gates met.

**Minor open item:** the tone reads 982.6 Hz rather than 1000 (-1.7%). The
audio clock itself is right (`AUDIO_CLK_DELAY`=1160 -> 32004 Hz, +0.013%), so
this is most likely truncation in `sine_gen`'s phase increment, or the capture
card's 32->48 kHz resampling. Cosmetic for a test tone; worth checking before
real game audio goes through, since a systematic pitch error would carry. **This is what makes the platform
unusable** - it is why the DDR3 path was rejected, and no amount of scaler
work touches it. Ties directly into roadmap item 1 (HDMI dropout) and the
"a RECONFIG recovers it" lead. Attack this before polishing the scaler.

### 2. HDMI instead of DVI + AUDIO (one job, not two)
`ascal_test60k` uses `dvi_tx_ext`, which is **DVI-only - there is no audio
path at all** (see the note at the top of `ascalv_top.sv`). Both items are the
same piece of work: bring in hdl-util `hdmi.sv`.
  * **MiSTer's audio is NOT transplantable** - `sys_top.v` drives an external
    **ADV7513** over parallel RGB + I2S, and `sys/i2s.v` is a ~40-line
    serialiser. There is NO data-island/ACR/CTS/audio-packet logic anywhere in
    MiSTer's `sys/` because the ADV7513 does it in silicon. We generate TMDS
    ourselves via OSER10, so hdl-util (already vendored, already carrying
    audio for all nine shipping games) is the only real option.
  * **The work is raster ownership.** `hdmi.sv` is the timing MASTER (`cx`/`cy`
    are outputs); `ascal_v` generates its own raster. Give ascal_v external
    raster inputs driven from `cx`/`cy` - both are 720p/1650x750 on the same
    74.25 MHz clock, so everything downstream is unchanged (costs a 2-pixel
    horizontal offset from the pixel pipeline, correctable).
  * **Use the INTEGER divider** `AUDIO_CLK_DELAY = 74250*1000/AUDIO_RATE/2`
    copied from `ddr3_framebuffer.v`. A fractional-exact divider made dropouts
    WORSE (roadmap item 1) and a declared-vs-actual rate mismatch was the
    original 50% rate lie. Then add the 1 kHz sine +
    `tools/audio_dropout_check.py`; gate on BRAM's 0 lost cycles in 15 s.

### 3. Interpolation — the feature we deliberately removed
The port is **nearest-neighbour only**. At 1.5x that maps 480->720 as
1,2,1,2..., so anything in motion crawls - this is inherent, not a bug, and it
is a real part of the "shimmer". ascal's answer is bilinear / sharp-bilinear /
bicubic / polyphase (`mode[2:0]`, with `MASK` deciding which are BUILT).
Restore cheapest-first: **nearest -> bilinear -> sharp-bilinear**, leaving
bicubic/polyphase last. **Risk to plan for:** that is where all the DSPs go and
the likely `CK3001` trigger (see the four GowinSynthesis defects above), and it
is the reason the port was scoped to nearest in the first place. Sharp-bilinear
is the accepted sweet spot for arcade content, so stopping there is a
legitimate end state.

### 4. Cleanups carried by the current code
  * **DELETE `dbg_underrun`** - measured 78-410 hits/frame with ZERO
    correlation to real glitches. The toggle-based `rd_busy` is not a valid
    completion signal; replace with a word count if a guard is ever needed.
  * Remove the `+define+ASCALV_TRACE` scaffolding once the last defect is
    closed (it is `ifdef`-guarded, so it costs nothing meanwhile).
  * `sim/vsynth/obj_dir/` build artifacts are tracked in git - add a
    `.gitignore` entry.
  * `mcr_testpattern` gained a `FREEZE_BAR` parameter (default 0, hardware
    unaffected); keep it, the multi-frame signature comparison needs it.

## Video dropout A/B rig — `video_test60k/` (2026-07-28)

Matched pair, same test pattern + same 1 kHz sine + same hdl-util HDMI stack,
differing ONLY in framebuffer architecture. Build with
`gw_sh build_bram.tcl` / `gw_sh build_ddr3.tcl` from `video_test60k/`.

  * `bram_top.sv` - nestang architecture ported from nes2hdmi.sv:
    dual-port BRAM, writer frame-stateless, 1-cycle read, ONE output clock
    domain. New `src/video/bram_scaler.sv`.
  * `ddr3_top.sv` - the same test through gbatang `ddr3_framebuffer`.

RESULTS (capture card video + `arecord` from the MS2109, analysed with
`tools/audio_dropout_check.py`):

| | BRAM | DDR3 |
|---|---|---|
| Logic | 1788 (3%) | ~4500 (8%) |
| BSRAM | 90/118 | ~9 |
| hclk Fmax | **106.6 MHz** | 82-83 MHz |
| picture | correct | correct |
| audio, 15 s | **0 lost cycles** | **1 lost cycle** |

Both scale CORRECTLY (unlike ascal). The BRAM build has ~24 MHz more hclk
margin and measurably cleaner audio - one lost cycle in 15 s on DDR3 matches
the "slight clicks" heard on hardware. BRAM cost is 90/118 BSRAM at
512x480x6 (RGB222); a palette index would cut that as it does for nestang.
Both show a slowly drifting TEAR LINE - expected and benign: single-buffered
and free-running, exactly like nestang, so a 60.09 vs 60.00 Hz mismatch
tears rather than dropping frames.

NOT reproduced: "raining white pixels" at the left edge seen on a real
monitor does not appear through the capture card (MJPEG likely smooths
single-pixel noise). Frame-to-frame instability measures the same on both.

NOTE the test rig is reportedly much cleaner than the PRODUCTION core, which
shares this same DDR3 framebuffer. That points at something the rig does not
have - the core's own audio path, SDRAM contention, OSD, or ROM loader -
rather than at the framebuffer itself. Worth bisecting there next.

## ascal (MiSTer scaler) evaluation — `ascal_test60k/`

**Status 2026-07-25: PROVEN ON HARDWARE.** A standalone bring-up rig
(MCR-timed test pattern -> ascal -> DDR3 -> DVI 720p, plus the same pattern
straight out the J10 VGA pins at 15/31 kHz) builds clean and displays.
Beacon confirms ascal auto-detects 512x480 and generates its own 720p
raster. Timing: 0 setup / 0 hold violations, all clocks pass.

Costs measured on GW5AT-LV60 (PnR, whole rig incl. DDR3 IP + DVI):
6359 logic (11%), 56/118 BSRAM (48%), 37/118 DSP. ascal alone at synthesis:
3274 logic / 23 BSRAM / 51 DSP with all five interpolators; 2263 logic /
25 DSP with bicubic+polyphase disabled (MASK=0x07) — BSRAM is unchanged
either way, it is the OHRES-sized output line buffers.

Open items:
1. **Horizontal scale is 4x too small; image repeats every 512 output px.**
   Vertical is perfect (480 -> 720). Captured and measured via the MiraBox
   card, two window settings:
     window 960  -> content 240 px    window 1280 -> content 320 px
   Both equal 512 * window / **2048**, i.e. ascal scales as though the input
   line were 2048 px wide, not 512. 2048 is ascal's DEFAULT `IHRES`.
   RULED OUT by measurement, do not re-investigate:
     - the Avalon->DDR3 bridge. Beacon counters `dB4 LB4` = 46080 write AND
       46080 read 16-byte words per frame, exactly 512*480*3/16. Data volume
       and addressing are provably correct in both directions.
     - input detection: ascal's own `i_hdmax`/`i_vdmax` report 511/479.
     - output raster: ascal's `o_vs` frame counter advances.
   ALSO RULED OUT, by debug taps added to ascal.vhd and read over the
   beacon (`GOWIN DEBUG PATCH`, still in the tree) — every geometry value
   ascal actually uses is CORRECT:
     i_hsize = 512   o_ihsize = 512   o_hsize = 960   o_hmax = 1119
     i_hdown = 0     i_himax = 511    i_vdmax = 479
   (`d20 L10` then `d3C L22` on the beacon.) So it is NOT the input
   auto-detect, NOT the i_clk->o_clk `<ASYNC>` crossing of o_ihsize, and
   NOT the output window.
   AND ruled out by experiment — the picture is byte-identical across:
     OHRES 2048 vs 2304 (MiSTer default) ... no change
     FRAC  4 vs 8 (MiSTer ships 8) ........ no change
     N_BURST 256 vs 2048 (MiSTer ships 2048) no change
   That last one is the strange part: N_BURST changes the RAM line stride
   (1536 -> 2048 bytes), which cannot leave the image untouched if the
   reader is using it. Config is now MiSTer's shipped set (OHRES default,
   FRAC=8, N_BURST=2048, N_DW=128) and the fault survives all of it.

   Precise symptom, measured off the capture card: within the correct
   160..1119 window the full 8-bar source renders into 240 px, then 272 px
   of black, then renders AGAIN at 672..911. Period 512 output px (equal to
   the SOURCE width, and invariant under every generic above); horizontal
   rate exactly 4x too fast. Vertical is perfect.

   **GHDL SIMULATION RESULT (2026-07-25) — ascal AND our configuration are
   CORRECT.** `sim/tb_ascal.vhd` drives ascal_gw with the identical source
   (512x480 bars, MCR timing) and identical output window (720p, hmin=160,
   hmax=1119), but replaces the Avalon side with an IDEAL zero-wait memory.
   Result, via `tools/ascal_sim_check.py`:
       non-black runs: [(160, 1119, 960)]     <- ONE full-width image
       colour bars at 160,281,401,521,641...  <- 120 px each = 64 * 1.875
   i.e. pixel-exact correct scaling, auto-detect included (i_himax=511).
   Sharp-bilinear edge blending is visible in the transition pixels, so the
   interpolator works too. Reference output kept as sim/ascal_out_ideal.txt.

   => The fault is NOT ascal, NOT the generics, NOT auto-detect, NOT the
   output window. The ONLY thing differing between that passing sim and the
   failing hardware is `ascal_avl_ddr3.sv` + the real Gowin DDR3 controller.
   The earlier "bridge ruled out" note above is SUPERSEDED: matching word
   COUNTS per frame proved only that the right VOLUME moved, not that the
   right addresses or ordering did.

   **BRIDGE ALSO CLEARED — in simulation AND on hardware.**
   `sim/tb_ascal_bridge.vhd` puts a VHDL transcription of ascal_avl_ddr3
   plus a Gowin-style DDR3 app model into the same harness. Renders
   pixel-perfect at BOTH 12-cycle latency with light backpressure AND
   40-cycle latency with 50% backpressure. So the bridge logic is right and
   read latency/backpressure are not the gap.
   Then on REAL hardware: `src/ascal/avl_ddr3_memtest.sv` +
   `ascal_test60k/build_memtest.tcl` (top `ddr3_avltest_top.sv`) drive the
   SAME bridge and SAME controller with an address-derived payload — so a
   wrong ADDRESS fails as loudly as wrong DATA, which is what matching word
   counts could never have caught. Beacon: **`d08 L..`** — 8 mismatches at
   startup, then ZERO for 20+ s across thousands of full write/verify
   passes, while the pass counter free-runs. The Avalon/DDR3 path is sound.

   **CONCLUSION: GowinSynthesis miscompiles ascal.** Everything else is
   eliminated by measurement: ascal + config correct (3 sims), bridge
   correct (2 sims + hardware memtest), DDR3 path correct (hardware
   memtest), geometry correct (debug taps). Consistent with this file
   already having two PROVEN GowinSynthesis RAM-inference failures.
   Note GowinSynthesis IGNORES both `syn_srlstyle` and `syn_ramstyle`
   (verified: adding them changes neither SSRAM 21 nor register count 6483,
   byte for byte), so upstream's three `ramstyle "logic"` guards - which
   exist precisely to keep the horizontal pipeline out of RAM - are
   SILENTLY INERT on this toolchain. ascal builds 21 distributed LUT-RAM
   primitives (RAM16S4/RAM16SDP4) regardless; `o_hpixq` is a 7-deep queue
   whose taps are all read at once, which a single-read-port LUT RAM cannot
   provide. That remains the best-fitting mechanism (horizontal broken,
   vertical fine - o_vpixq is only 4x24 bits and stays in registers) but is
   NOT yet proven, since forcing the attribute had no effect.

   **STEP 1 DONE 2026-07-25 — RAM INFERENCE IS *NOT* THE CAUSE.** Disproven,
   do not retry. What was done and what it showed:
     * `o_hpixq` split from `arr_pixq(2 TO 8)` into 7 discrete signals.
       GowinSynthesis then inferred *BSRAM* instead (PA2122 returned) and the
       register count FELL 6483->6003 - it infers memory from the 4-element
       `arr_pix` arrays too, not just the shift chain.
     * **`syn_keep` + `syn_preserve` DO work** where the style attributes do
       not. They are a different lever: they forbid the net being optimised
       away/merged at all. Applying them moved the signals into real
       flip-flops - register count 6483 -> 6651 (o_hpixq) -> 6743
       (o_hfrac/o_div/o_dir), PA2122 gone, 0 setup / 0 hold violations.
     * With ALL FOUR guarded signals provably in registers, the hardware
       picture is byte-identical: bars still 30 px, content still 160..399
       and 672..911. So the fault is elsewhere.
   Note SSRAM stayed at 21 (RAM16S4 x10, RAM16SDP4 x10) throughout, so those
   LUT-RAMs belong to something else in ascal, not these four signals.
   The patches are KEPT: they implement upstream's documented intent (the
   `ramstyle "logic"` guards exist precisely to keep these out of RAM, and
   Gowin ignores them), they cost ~260 registers, and timing is unaffected.

   Reusable finding for ANY MiSTer core ported to Gowin: GowinSynthesis
   1.9.11.03 silently ignores `ramstyle`, `syn_ramstyle` AND `syn_srlstyle`,
   but honours `syn_keep` / `syn_preserve`. Use those to control inference.

   **STEP 2 DONE — INTERNAL STATE PROVABLY DIVERGES.** `dbg_o_hacc` and
   `dbg_o_dcpt` taps added to ascal.vhd, sampled at output (line 100, pixel
   300) by IDENTICAL logic in `ascal_test60k_top.sv` and
   `sim/tb_ascal_bridge.vhd`:
       signal    GHDL (renders correctly)   hardware (broken)
       o_hacc    1472                       ~1728-1791 (jittery)
       o_dcpt    241                        124  (stable)
   Same RTL, same data delivered to it, different internal state - the
   destination counter advances at roughly HALF rate on hardware. This is
   the horizontal copy/advance pipeline, not the memory path.

   **SRL/LUT-RAM inference is NOT the mechanism either — disproven.**
   syn_keep/syn_preserve were extended to every shift-register pipeline in
   the output path: o_copyv, o_dcptv, o_dcptv_clr/inc (12-deep 1-bit chains
   that gate the destination counter increment, and which upstream does NOT
   guard because Quartus never RAMs them), o_hsv/o_vsv/o_dev/o_pev/o_end.
   This DID take effect - SSRAM fell 21 -> 15 (RAM16SDP1 gone entirely,
   RAM16S4 10->7, RAM16SDP4 10->8), registers rose 6743 -> 6930, 0 setup /
   0 hold violations - and the picture and the probe values did NOT change
   at all. Cumulatively ~450 registers were moved out of RAM across all the
   guards with zero behavioural effect.

   **MORE ELIMINATED 2026-07-25 (all built clean, all changed NOTHING):**
     * Clock phase. `sim/tb_ascal_phase.vhd` reruns with avl_clk offset 90
       deg from o_clk (hardware has two independent 74.25 MHz PLLs; the
       original testbench made them phase-identical, masking every `<ASYNC>`
       crossing). Still renders perfectly, and o_dcpt stays 241-242
       regardless of phase - so the hardware's 124 is a real divergence, not
       a testbench artefact.
     * Explicit-width arithmetic in the sCOPY horizontal accumulator. The
       theory was good: `(o_hacc_next - 2*o_hsize + 8*OHRESH) MOD 8*OHRESH`
       peaks at 49151 (16 bits) but lands in `dif_v`, declared 15 bits,
       whereas the VERTICAL twin uses hardcoded 16384/8192 and peaks at
       32767 which FITS - neatly explaining horizontal-broken/vertical-fine.
       Rewritten with wide explicit unsigned + mask (MOD by a power of two).
       Picture and probe values bit-identical. Disproven.
     * Burst bookkeeping. `o_hburst` = 1 on BOTH sim and hardware (correct
       for N_BURST=2048: a 1536-byte line fits one 2048-byte burst).
       NOTE the o_copylev comparison is INCONCLUSIVE as instrumented - the
       hardware beacon samples it continuously while the sim prints one
       instant at the probe point. To settle it, latch o_copylev at the
       probe point on hardware the way o_dcpt already is.

   `src/ascal/ascal.vhd` is now REGENERATED by `tools/patch_ascal_gowin.py`
   from the upstream copy in refs/, carrying only the minimal patch set
   (syn_srlstyle, without which PnR fails PA2122; plus debug taps) - 44
   diverged lines, down from 176. That script also records every patch that
   was tried and rejected, so nothing gets re-applied by accident.

   **FAULT FULLY LOCALISED 2026-07-25.** With the probe latched at the SAME
   raster point in both sim and hardware (line 100, pixel 300):
       o_hburst           sim 1     hw 1     MATCH
       {o_copylev,hbcpt}  sim 04    hw 04    MATCH
       o_dcpt             sim 241   hw 124   DIVERGE
   So burst fetching and the copy queue are identical - the copy FSM is NOT
   starved (an earlier "starved queue" reading was an artefact of comparing a
   continuous hardware sample against a single sim instant; it is now latched).
   In sCOPY, o_dcpt_inc fires EVERY cycle once o_dshi hits 0, while the SOURCE
   advances only on hcarry_v (Bresenham; carry rate should be 2*o_ihsize /
   2*o_hsize = 1024/1920 = 53% for 512->960). Source consumed 4x too fast =>
   hcarry_v asserting far too often => line ends early => o_dcpt only reaches
   124. The fault is the `dif_v >= 4*OHRESH` carry decision and nothing else.
   ALSO: the fault is MODE-INDEPENDENT - forcing nearest (mode 0), which
   bypasses every interpolator but shares this advance logic, reproduces it
   byte-identically. So the interpolator data path is innocent too.

   **UNSIGNED REWRITE (2026-07-25) — ALSO DISPROVEN.** o_hacc/o_hacc_ini/
   o_hacc_next converted from `natural RANGE 0 TO 4*OHRESH-1` to explicit
   `unsigned(NBH4-1 DOWNTO 0)`, so every MOD by 4*/8*OHRESH became plain
   wraparound and the `>= 4*OHRESH` carry test became one borrow bit.
   Bit-identical by construction, analysed clean under GHDL, built clean
   (0 setup / 0 hold, hclk 82.1 MHz). Hardware: o_dcpt still 124 vs the
   sim's 241, picture byte-identical. REVERTED - the miscompile is not in
   how the accumulator arithmetic is EXPRESSED, at either the expression or
   the signal-type level.

   **HARD-BAKED INPUT GEOMETRY (2026-07-25) — ALSO NO CHANGE.** iauto=0 with
   himin/himax=0/511, vimin/vimax=0/479 pins the input window and removes the
   whole auto-detect path (and its i_clk->o_clk <ASYNC> crossings). Picture
   byte-identical. Reverted to iauto=1. The `iauto`/`himin`/`himax`/`vimin`/
   `vimax` ports remain exposed on ascal_gw for cores that need overscan
   cropped.

   **PROOF IT IS GOWINSYNTHESIS (2026-07-25).** GHDL has its own synthesis
   engine, so ascal was run through THAT and the result simulated - the
   gate-level check Gowin's `pragma protect` encrypted .vg denies us:
       ghdl synth --std=08 --out=verilog ascal_gw  -> 1 MB Verilog netlist
   Simulated with verilator against the REAL mcr_testpattern.sv and REAL
   ascal_avl_ddr3.sv (sim/vsynth/), 640x480 output window:
       bars at 81-158,161-238,241-318,321-398,401-478,481-558,561-638
       ~78-80 px each (expected 640/8 = 80), spanning the full window
   PERFECT. So ascal's coding style survives a second, independent
   inference engine (memory inference, FSM extraction, register mapping)
   and the fault is SPECIFIC TO GOWINSYNTHESIS. This is the evidence to
   send Gowin.

   Attempting to USE that netlist as a workaround - feeding Gowin the
   GHDL-generated Verilog instead of the VHDL, which bypasses its VHDL
   front-end entirely (ascal_test60k/build_ghdlnl.tcl +
   src/ascal_ghdlnl_top.sv + src/ascal/ascal_gw_synth.v) - hits a THIRD
   GowinSynthesis defect: `ERROR (CK3001) : The CASI configuration of
   'u_ascal/u_ascal/mult_122505_s3' is incorrect`, i.e. it mis-maps the
   netlist's multipliers into cascaded DSP blocks. `syn_multstyle="logic"`
   is ignored, like every other style attribute. Not pursued further.

   TOOLING NOTE: verilator runs this netlist in ~2 SECONDS where iverilog
   took over an hour without finishing, and GHDL behavioural takes ~30 min.
   Use verilator for any future ascal work. Harness in sim/vsynth/.
   Watch the frame rate: a 640x480 output raster free-runs at ~177 Hz while
   the source is 60 Hz, so dump a LATE output frame (24+) or the
   framebuffer has not been filled yet and everything reads black.

   **BUG REPORT WRITTEN:** `docs/gowin_bug_report.md` - self-contained, for
   submission to Gowin once the licence comes through. Covers all four
   findings (silent horizontal miscompile, PA2122, CK3001, ignored
   attributes) with upstream line numbers, measured evidence tables and a
   minimal no-board repro for PA2122.

   **COMMERCIAL V1.9.12.03 TESTED 2026-07-27 — DOES NOT FIX IT, IT IS WORSE.**
   Installed side-by-side at `~/gowin_1.9.12.03` (free 1.9.11.03 in `~/IDE`
   untouched); node-locked licence at `~/gowin_1.9.12.03/gowin.lic` with
   `IDE/bin/gwlicense.ini` pointed at it. Build with
   `tools/gw_build_1912.sh <board> [tcl]`.
     * VHDL ascal -> **GowinSynthesis CRASHES**: `Running inference ...` then
       `Floating point exception (core dumped)`, exit 136. No error message.
       Reproduces with upstream ascal + minimal wrapper, with our patched
       ascal in the full design, and with MASK=0x07 (bicubic + polyphase
       removed) - so it is not the polyphase memories and not our patches.
     * A trivial 12-deep pipeline design synthesises fine under 1.9.12.03 in
       the IDENTICAL environment (rc=0), so the toolchain/env is sound.
     * The same sources still build CLEAN on 1.9.11.03 (0 errors, 0 setup /
       0 hold) - verified after the 1.9.12.03 runs. Clean regression.
     * GHDL Verilog netlist path: `CK3001` on 1.9.12.03 too (different
       instance name), so that workaround is still blocked.
   Net: 1.9.12.03 cannot build this design at all. Stay on 1.9.11.03.
   The crash is now Defect 0 in `docs/gowin_bug_report.md` - a hard crash is
   usually easier to get fixed than a subtle miscompile, so it may be the
   most useful lever with Gowin support.

   **LICENCE CAVEAT:** the licence is node-locked to `06:BB:FA:F8:40:51`,
   which on this machine is the **docker bridge** `br-8f7dfefb2229`, not the
   physical NIC (`enp4s0`, d8:5e:d3:81:75:af). Docker bridge MACs are
   regenerated when the network is recreated, so the licence can silently
   stop working. Consider re-requesting it against enp4s0.

   **BRESENHAM REFORMULATION (2026-07-28) — ALSO NO CHANGE.** ascal's carry
   decision emulates a SIGNED compare inside an unsigned `natural` via
   `(acc_next - 2*o_hsize + 8*OHRESH) MOD 8*OHRESH >= 4*OHRESH`. Decoded that
   is plain Bresenham, so it was replaced with the direct form
   `IF o_hacc_next >= 2*o_hsize THEN ... - 2*o_hsize` - no MOD, no sign trick,
   the exact formulation in src/video/bram_scaler.sv which Gowin compiles
   CORRECTLY on this device. Verified semantically identical via
   ghdl synth + verilator (bars at 81-158,161-238,... unchanged). Built clean
   (0 errors, 0 setup/0 hold). Hardware: byte-identical wrong output.

   **KEY OBSERVATION.** The carry arithmetic has now been rewritten FOUR ways
   - original modular form, explicit-width unsigned expression, unsigned
   signals with wraparound, and plain compare - and hardware output is
   byte-identical every time. If the arithmetic itself were being miscompiled,
   changing its form should change the failure somehow. That it does not
   suggests the carry is computed CORRECTLY and something downstream is wrong.
   BEST REMAINING PROBE (untested): `o_ihsizem <= o_ihsize + o_off(0) - 2`,
   which sets when a line ENDS (`o_last <= o_hacpt >= o_ihsizem`). A line
   ending at ~1/4 of the source is precisely our symptom, and o_ihsizem has
   never been observed on hardware. It is also one of the three signals the
   GHDL sim guard patches, so sim and hardware differ there by construction.

   **WHERE THIS STOPS.** Every targeted hypothesis is exhausted. The fault
   is a GowinSynthesis miscompile of ascal's horizontal Bresenham advance;
   it survives every rephrasing of that logic, is mode-independent, and
   cannot be chased further from RTL because the .vg netlist ships
   `pragma protect` encrypted, blocking gate-level simulation.
   REMAINING OPTIONS (need something outside this toolchain/IDE):
     a. Try a different Gowin IDE version. Only V1.9.11.03 Education is
        installed here; the bug may not exist in another release.
     b. Synplify Pro instead of GowinSynthesis - not in the Education
        edition, needs a licensed IDE.
     c. Report to Gowin. The repro is small and specific: ascal's sCOPY
        carry decision, correct in GHDL, wrong in hardware, with all inputs
        to it proven identical by on-chip taps.

   NEXT STEPS, in order of expected value:
   1. **Clock-phase hypothesis (DONE - disproven, see above).** The testbench drives o_clk
      and avl_clk from the same generator, so they are phase-IDENTICAL - and
      that masks every `<ASYNC>` crossing inside ascal. On hardware they are
      hclk (HDMI PLL) and clk_x1 (DDR3 controller PLL): both 74.25 MHz off
      the same 27 MHz, but SEPARATE PLLs, so arbitrary fixed phase.
      `sim/tb_ascal_phase.vhd` reruns the identical test with avl_clk offset
      90 degrees. If the fault reproduces, this is a genuine CDC problem the
      first three sims could never have caught, and the fix is structural:
      run ascal's o_clk from clk_x1 and cross into the TMDS serialiser's
      hclk domain through an explicit FIFO (what gbatang does), rather than
      handing ascal two independent same-frequency clocks.
   2. If phase is not it, tap further up the horizontal chain (o_copy state,
      o_dshi, o_off) to find where 241 becomes 124.
   2. Synplify Pro honours syn_ramstyle natively and would sidestep
      GowinSynthesis entirely — but it is NOT in this Education-edition IDE
      install (`~/IDE/bin` has GowinSynthesis only). Needs a licensed IDE.
   3. Report upstream/Gowin. Minimal repro is small: a 7-deep array of
      records with all taps read, plus `ramstyle "logic"`.

   Also found by GHDL, worth reporting upstream: ascal has three `natural`
   underflows that no synthesis tool range-checks — ascal.vhd:2247
   (`o_pshift <= o_off(0)-1`), :2274 (`o_pshift <= o_pshift-1`) and :2250
   (`o_ihsizem <= o_ihsize + o_off(0) - 2`). All are benign in hardware
   (the values are only read under guards that make them non-negative), but
   they abort GHDL. `sim/mk_ascal_sim.py` regenerates sim/ascal_sim.vhd with
   exactly those three guards so the SYNTHESIS source stays untouched.
2. **No HDMI audio.** The rig uses `src/dvi_tx/dvi_tx_ext.sv` (DVI only)
   because ascal owns the output timing and hdl-util's `hdmi` module wants
   to own it. Audio needs ascal -> line FIFO -> `hdmi.sv`.
3. **Polyphase needs coefficients.** `poly_*` ports are exposed but tied
   off; modes 0-3 work without them. Loading a MiSTer filter file needs a
   small ROM + loader (256 entries: [H][V][H2][V2] x 16 phases x 4 taps,
   10-bit signed).
4. **Integrating into mcr2_console60k** replaces `ddr3_framebuffer`. BSRAM
   is the binding constraint there (currently 94/118) — see the ROM->SDRAM
   item, which is the lever if it does not fit.
5. `ascal.vhd` carries ONE local patch (`syn_srlstyle`, marked "GOWIN PORT
   PATCH") — GowinSynthesis ignores Quartus' `ramstyle` guards and packs
   ascal's pipelines into SP/SPX9 block RAM with an unsupported write mode
   (PA2122). Re-apply on any upstream refresh.

---

## Discs of Tron Environmental — CABINET BACKLIGHT OUTPUT (Tang) (2026-08-04)

**Scope decision: the Tang drives the REAL cabinet's backlight. It does NOT
render a backdrop image.** The backdrop artwork is a MiSTer-only feature (a
monitor on a desk has no cabinet behind it); a Tang board is assumed to be
sitting in an actual Environmental cabinet, which already has the backlit
scenery. All the Tang owes it is the signal.

**The signals already exist in the core.** `output_4` is wired out of
`mcr3.vhd` and connected in `mcr3_console60k_top.sv` (done 2026-08-01 for the
Squawk & Talk port). From MAME `mcr.cpp:565` `dotron_op4_w`:

| OP4 bit | Cabinet net | Meaning |
|---|---|---|
| 6 | J1-4 (FL0) | backlight ENABLE - drives the lamp directly |
| 7 | J1-3 (FL1) | flasher STROBE enable |

On the real machine a flasher control board holds a 555 astable
(R1=R2=56k, C=1uF -> **8.5714 Hz**, 77.616 ms high / 38.808 ms low), gated by
J1-3 and clocked through a D flip-flop on AC sync; J1-4 drives the fixture
directly, and the two outputs are **wire-OR'd**.

**Therefore emit BOTH bits as two separate signals and let the cabinet's own
flasher board do the timing.** Do not synthesise 8.57 Hz in RTL unless the
target is a bare lamp/SSR with no flasher board, in which case one combined
signal is what is wanted. Two signals is the cabinet-accurate interface and
degrades gracefully - they can always be wire-OR'd externally.

**Where it goes electrically.** `docs/shield_j10_pinout.md` §4 already designs
the output path: a 2x 74HC595 chain (16 bits) on 4 pins, with a ULN2803 for
12 V loads and `OUT_EN_N` pulled up so lamps stay off until the RTL drives it
low. The backlight is one more bit in that chain. Until the shield exists, a
spare J10 GPIO will do for bench work - see `docs/bench_wiring.md` for what
that header currently drives.

**Only the Environmental set moves these bits.** MAME installs
`dotron_op4_w` from `init_dotrone` ONLY; the upright `dotron` never writes OP4
at all. So the output sitting static on the upright is CORRECT, not a bug to
chase. Verified on the MiSTer prototype: OP4 traffic on the upright is limited
to the lamp-sequencer nibble, and bits 6/7 never move.

**Not started.** No pin assigned, no RTL written. The core-side prerequisite
(bringing `output_4` out) is already done.

## Cocktail mode — unaddressed across every game

**Everything currently assumes an upright cabinet.** This is not one switch;
it touches four separate things, and each game does it differently:

1. **Cabinet DIP is hardcoded upright.** `input_3` is a constant per game in
   `mcr2_console60k_top.sv` (Domino `0x3E` — note `0xFF` would select
   *cocktail*; Tron `0x80`). Nothing lets an operator choose. SW2-3 in the
   shield spec is reserved for this but unimplemented.
2. **Player-2 inputs are tied off.** Cocktail play needs the second player's
   controls, which live in different ports per game and are currently
   constants: Tron's cocktail joystick (IP2 upper nibble), Satan's Hollow
   (IP1 upper nibble), Two Tigers' P2 dial (IP4, tied to 0), Wacko's
   `IP1.ALT`/`IP2.ALT` trackball.
3. **Wacko's trackball mux is not implemented.** SSIO output port 4 bit 0
   selects P1 vs cocktail-P2 trackball. `mcr_sound_board.vhd` *does* expose
   `output_4`, but `mcr2.vhd` never brings it out to the entity — so this
   needs a (small) core port addition before cocktail Wacko can work. Upright
   play is unaffected, which is why it works today.
4. **Screen flip is unverified.** Cocktail cabinets rotate the image 180° for
   player 2. Need to establish whether the core implements flip at all, how
   it is triggered, and how it interacts with the DDR3 framebuffer capture
   (which samples the core's raster directly).

Also needed for real two-player use: a **second USB pad** on port 2
(usb2_dp M15 / usb2_dn M16 — pins verified, unused).

### How the cabinet setting actually reaches the core (two layers)

`input_3` **is** the original board's DIP bank (the switches at B3), read by
the SSIO as input port 3 — an internal core signal, not a pin. Our shield
replaces that board, so the FPGA has to supply those bits:

    SW2-3 (switch on the shield)
      -> 74HC165 chain -> 3 FPGA pins     (switch reaches the FPGA)
      -> per-game bit placement
      -> input_3 bit N -> core SSIO       (FPGA reaches the core)

So the cocktail switch both runs through the 165 *and* lands in `input_3`;
they are different layers. Neither costs additional pins.

**The bit position is different per game** (verified against MAME):

| Game | Cabinet bit in IP3 |
|---|---|
| Tron, Satan's Hollow | bit 1 (0x02) |
| Domino Man, Wacko, Kozmik Kroozr | bit 6 (0x40) |
| Two Tigers (conversion set) | none — IP3 unused entirely |

**`input_3` is not purely DIP switches.** Tron puts the *cocktail player's
fire button* on IP3 bit 7 (`PORT_BIT(0x80, ..., IPT_BUTTON1) PORT_COCKTAIL`),
so that port mixes config switches with a live cabinet input. Open question:
the master pinout matrix lists Tron as having **no J5**, so where a cocktail
Tron's P2 fire button arrives on the harness is undocumented — needs a
cocktail cabinet manual or real hardware. (J5-19 "P2 Button 1" is pinned and
is the obvious candidate, but that is a guess.)

**Other pin impact:** cocktail P2 controls for Tron/Domino arrive on SSIO
IP2 = J5 1-8, and IP4 / J6 is covered too — every harness input rides the
shield's 74HC165 chain (`docs/shield_j10_pinout.md`), so no per-line pin
budget exists anymore. See the Shield PCB section.

---

## Hardware bring-up (untested on the board)

- ~~SD ROM loader has never run on hardware~~ **RESOLVED 2026-07-21**: pack
  written to the card with `tools/write_rompack.py` (lands in the gap
  before the card's partition, filesystem untouched) and games load from
  the OSD on hardware. The reject-foreign-card path was proven earlier
  (beacon `L09`).
- ~~HDMI black screen~~ **RESOLVED 2026-07-20** after a long hunt. HDMI now
  works: 720p from the DDR3 framebuffer, game + border verified on hardware.
  Root causes, in the order found (each invisible to the error log):
  1. video reset gated on ROM loading (fixed: video resets from power-on only)
  2. IDE `Place_Option 0` vs build.tcl's 2 (DDR3 never trained on IDE builds)
  3. **gbatang's cross-PLL serializer clocking** — pixel clock from the DDR3
     controller, serial clock from a second PLL; OSER10 phase left to routing
     luck. Restructured to NESTang's single chain (27→PLL→371.25→CLKDIV/5)
     with a shadow-raster + async-FIFO bridge into the scanout domain.
  4. **Verilog use-before-declaration** — Gowin makes an implicit 1-bit wire
     with only a warning; the encoder's rgb input was one floating bit and
     the pixel FIFO was swept. Post-build check #4 in CLAUDE.md now guards
     this ("Undeclared symbol" grep must be empty).
  Diagnostic assets that earned their keep, kept in the repo: the UART
  beacon, `diag/hdmi_selftest` (dvi_tx 640x480), `diag/fb_selftest`
  (framebuffer alone), `diag/nes_video_selftest` (NESTang clocking, the
  decisive one). Verified only in simulation
  against a card model (`make -C sim`). The card image is built but not yet
  burned. Beacon `L` low nibble = {sd_ready, sd_err, done, error}; high nibble low 2 bits = USB device type (3 = gamepad).
- **Left-edge pixel overlap.** Root cause is the core's ~13-pixel RGB-vs-hcnt
  pipeline lag. HDMI compensates in the capture window; the analog path did
  not compensate at all until 2026-07 (the previous line's tail leaked into
  the first ~13 visible pixels). Both paths now share the live-tunable
  `cap_delay` — Select + D-pad Right/Left, value in the beacon as `d<hex>`.
  **Still to do: confirm on hardware and hardcode the winning value as
  `CAP_DELAY_DEFAULT`.** One step is <2 screen pixels on HDMI, so it takes
  10–15 taps to see there; it should be far more obvious on analog.
- **Analog framing on a desk LCD is imperfect and expected.** The core emits
  634 pixels/line at 20 MHz; an LCD locks to it (31.55 kHz ≈ VGA's 31.47 kHz)
  but then samples ~800 pixels at 25.175 MHz across our line, stretching
  ~1.26× and mis-positioning active video. Use the monitor's Auto Adjust.
  A real 15 kHz arcade monitor has no sampling window and does not care, so
  this does not affect cabinet use — and fixing it for LCDs would mean
  putting a line buffer/scaler back into the analog path, which is exactly
  what keeps that path shimmer-free. Not worth it.
- **PmodVGA in the PMOD sockets is unproven.** Four strap combinations on
  J10-39/40 resolve row/socket orientation; also note the module is *not*
  passive — its SN74ALVC245 buffers need **3.3 V on VCC** (never 5 V).
  The J10 jumper route (or a DE-15 breakout + 9 resistors) avoids the
  ambiguity entirely.
- ~~Green channel lost at 15 kHz on a 15 kHz-capable LCD~~ **RESOLVED
  2026-07**: the display had mis-detected the sync format. 15 kHz now
  defaults to **separate H and V sync** (also what a real MCR cabinet wants,
  Video pins 8/9); composite sync remains available on the J10-39 strap.
  Two lessons worth keeping: a mis-detected sync format can look exactly
  like a dead colour channel, and **displays latch their format detection**
  — switching format on a live signal may not re-trigger it, which made an
  earlier four-way test look like a total failure when one combination
  actually worked.
- **New games' controls are derived, not played.** Trackball/analogue-stick
  sensitivity on a d-pad is guesswork — Kroozr's stick ramp rate especially.
  Tron's aim direction may need reversing (MAME marks the dial PORT_REVERSE).
- **Two Tigers has +0.08 ns setup slack** — met, but the tightest of the six.
  Suspect timing first if that game alone misbehaves.

---

## Multi-game / product

- **SD card format v2 — DEFERRED, plan written**: see
  `docs/sd_card_layout_v2.md`. **Do not touch the on-card format,
  `rom_loader.sv`, or the `make_*_pack.py` tools until MCR-3 Tapper renders
  sprites from the card as it is** — the current card is the only known-good
  input to that debug. The motivating bug is live today: `make_rompack.py`
  and `make_sprite_pack.py` both hardcode `PACK_BASE = 2048`, so one card
  cannot hold both the MCR-2 game pack and the MCR-3 sprite pack; whichever
  was written last wins, and an MCR-2 build then reads a garbage slot and
  shows **Satan's Hollow** (`osd.sv:162`, slot 0). If coexistence is needed
  before v2 lands, the cheap fix is to give the MCR-3 top a different
  `PACK_BASE` — it is already a module parameter, so no format change is
  required.

- **OSD game-select menu is IMPLEMENTED (60K)** — `src/rtl/osd.sv`, drawn in
  the core raster domain so it shows on HDMI + VGA 31 kHz + 15 kHz alike.
  Select+Start opens; Up/Down, A = load slot from SD pack, B = exit. All six
  input maps are now compiled in and muxed at runtime by `game_id`;
  `game_config.vh` only picks the baked-in boot game. **Working on
  hardware 2026-07-21** (menu, SD reload, game switching; navigation
  debounce fixed by frame-rate button sampling). Remaining OSD work:
  - **ROT90 direction unverified**: menu on Tron/Shollow is drawn rotated
    for a cabinet monitor; if it reads mirrored/upside-down, swap the
    mapping noted in `osd.sv` (u/v remap line).
  - **"LOADING..." is never visible**: the core raster stops while the core
    is reset during a reload, so the screen freezes (HDMI) / drops sync
    (VGA) for ~1 s instead. Fix would be keeping the video counters running
    through reset in `mcr2.vhd` (touchy — it's shared with the 25K).
  - **Opening the menu inserts a coin** (Select doubles as Coin1 before the
    Start half of the combo lands). Harmless; goes away when the shield's
    dedicated service button opens the menu instead.
  - **Stale CMOS RAM across switches**: each game boots on the previous
    game's CMOS contents; MCR games checksum it and factory-reset, so this
    should self-heal — verify per game, else clear cmos_ram on reload.
  - ~~No prefs persistence~~ **DONE 2026-07-21**: selections are written
    to SD sector 2047 (CMD24) and win over the baked default at power-on;
    sim-verified round trip (`make -C sim`). Untested on hardware.
  - **Two Tigers' Dogfight Start moved to D-pad Up** (was Select+Start,
    which is now the menu combo).
- **No multiboot selector** for switching MCR family cores (2.5 MB per core,
  so all three fit well under 8 MB of flash).
- **Fallback behaviour is minimal.** Loader failure falls back to the baked
  ROMs and the OSD shows "LOAD FAILED"; the shield spec still wants a status
  LED so a field failure is diagnosable without a display.

## Shield PCB

- **Cabinet-side wiring is documented**: `docs/shield_wiring.md` (connector
  footprints, 74AHC165/74HC595 chain diagrams, sync buffer/DAC, BOM). The
  analog/ADC question is settled: **only Spy Hunter and Max RPM need an
  ADC** (potentiometer steering/pedals; every other control is digital or
  an optical encoder the FPGA decodes). Plan is a populate-optional SPI ADC
  (ADS7830/MCP3208) with a per-channel MODE jumper routing Opt X/Opt Y to
  the '165 (digital) or the ADC (analog), set per cabinet. FPGA reads the
  ADC over spare J10 pins.


- **5 V delivery route unverified** — J10 pin 11 exposes +5 V but sits behind
  the dock's OR-ing/OVP chain; do not back-feed it until traced. USB-C is the
  known-good path.
- **Header pinout is FROZEN (2026-07-21): `docs/shield_j10_pinout.md`.**
  Everything on J10 only — video/audio/straps/LEDs on the pins today's
  bitstreams already drive, ALL cabinet inputs + both DIP banks on a
  7×74AHC165 chain (3 pins; 3.3 V parts, 5 V-tolerant inputs), outputs on a 74HC595+ULN2803 chain (4 pins),
  service button direct. This resolved the old J6/IP4 gap (chain device
  U5) and the lamp/coin-meter question ('595 chain, extensible free).
  Remaining on it:
  - **Expander-chain RTL does not exist yet** — a small module scanning
    the '165s into the input mux (ORed with the USB pad), driving the
    '595s, and a SERVICE_N → OSD-open hook. J10 pins 25-34 are reserved
    and high-Z until then; the shield works for video/audio/straps/LEDs
    with current bitstreams on day one.
  - J6's *cabinet-side* connector wiring wants a manual cross-check
    before crimping harnesses (the matrix PDF has no J6 sheet).
- **`tools/generate_pcb.py` is not synced** to `shield_j10_pinout.md`, and
  still assumes generic 2×20 headers; J9 must stay clear for the SDRAM
  module.
- **138K variant**: header nets are dock-level but the net→ball map is
  SOM-specific; re-extract before targeting it.

## Cores / ports

- **MCR-3 Tapper sprites — FIXED 2026-07-24 (commit 3dbe824): the SDRAM
  pin clock needed a 225-degree phase shift.** Full attract mode verified
  on screen (bartender/patrons/mugs) via HDMI capture; array-health sweep
  reads allff=47 vs 51 for a perfect image. sdram_gw is pure-upstream
  again; the fix is one PLL output (gowin_pll_core80 CLKOUT3 @225deg ->
  clk_fwd). Flash holds the working build; also archived as
  bitstreams/console60k_mcr3_tapper_sprites_working.fs.
  Cleanup still owed: retire the diagnostic beacon slots/sweep/watchdog
  instrumentation to a maintainable minimum (keep the HALT watchdog and a
  slow array-health sweep), then resume the v5 plan (Phase 2:
  everything-from-SD; Phase 3: backport MCR-1/2 - NOTE those cores use the
  same module via other paths in future work: apply the 225-deg discipline
  anywhere the Tang SDRAM module is used).
  STANDING LESSONS (cost days): (1) JTAG SRAM loads fail silently ~1/3 of
  the time - confirm every load with a per-build beacon marker; (2) flash
  writes lie without -f --verify; (3) Gowin use-before-declaration makes
  floating 1-bit nets - even on clocks (the "90deg changed nothing"
  phantom); (4) windowed rates only, full-width counters only.

- **HDMI dropouts — TWO causes (measured 2026-07-24 on a real monitor).**
  (1) Audio/ACR data islands, the major one: a DVI_MODE(1) build (no data
  islands, silent) made cutouts MUCH rarer. Audit the audio integration vs
  NESTang's (sample rate into the framebuffer, ACR CTS/N values).
  (2) A time-correlated residual: dropouts resume "a while in" (thermal
  drift); prime suspects the DDR3 wr-FIFO hold margins (+0.001 ns at
  nominal, negative on some placement rolls) or TMDS analog margin.
  Also noted: no picture during early boot (DDR3 calib + watchdog reload
  latency) — believed benign, unconfirmed. The MCR-3 top's `DVI_MODE` was
  put back to 0 on 2026-07-27 (full HDMI + audio, matching the mcr1/mcr2
  tops) when the sprite-shift fix was flashed; the silent-DVI experiment is
  finished — the real audio fix was making the sample rate and the ACR
  constants agree at 32 kHz, and the residual is board thermal.

- **Sprite "slight offset" report (2026-07-25) — FIXED 2026-07-27.** Root
  cause: in the MCR-3 top's dl→SDRAM port2 sprite write, the address and
  byte lane came from the 2-deep sync registers (`dl_sp_off_s2`) while the
  data was taken live off `dl_data`. `dl_wr`'s edge is detected on the
  clk_sdram cycle where `_s2` still holds the previous byte, so byte j's
  data landed at byte j−1's address and the whole 128 KB sprite array was
  stored as `mem[i] = blob[i+1]` — precisely the observed
  glass..gap..detached-handle shape. Introduced by 500c74a (pack v2);
  builds at/before 3dbe824 took address and data both live and are clean.
  Fix: `dl_data_s1/s2`, so all three fields sit at the same pipeline
  depth. Confirmed three ways — the audit's `i%4` bucket tuple read the
  ROM prediction rotated left by one, bit-exact, on 13/13 loads; the
  artifact was visible on a fresh load with no warm-up or power cycle;
  and `mcr3_console60k/diag/dlsync_tb.v` (iverilog) reproduces the shift
  and shows the fix clean. NOT instance-dependent — the earlier
  "instance dependence" came from instruments that were blind to it (the
  synthetic pattern was keyed on the destination index, so it always read
  back aligned). See the RESOLVED header of `handoff_v8_sprite_shift.md`.
  The audit sweep is kept as the per-boot canary, now reporting all four
  buckets in E0..E3 (Tapper expects `{0x1266,0x1B00,0x1AD1,0x13E4}`).
  Historical detail below.

- **(historical) Sprite "slight offset" investigation trail.** Facts
  established blind:
  (1) `src/rtl/mcr3.vhd` diffed against upstream MiSTer — IDENTICAL except
  the documented patches (INIT_FILE dprams, vcntout/cpu_halt_n exports),
  so sprite/bg COMPOSITION (which happens inside the core) cannot differ
  from MiSTer's. (2) Top-level sprite wiring matches MiSTer's
  Arcade-MCR3.sv structurally. (3) The one real divergence was OUR
  diagnostic-era `sp_addr_r` register: +1 clk_sdram of sprite fetch
  latency that MiSTer does not have -> plausible horizontal shift.
  REMOVED (sp_addr now feeds the controller directly, MiSTer-exact) and
  in flash as of f7b5d39. Zoomed frame comparison vs the MobyGames
  reference hinted the mug sprite sinking ~4px into the bar top in the
  OLD build, but the frames are different game moments - inconclusive.
  UPDATE 2026-07-26 — the artifact is now precisely characterized from
  live captures (scratchpad live_199 + zooms): **the last-drawn 8px
  word-slot of a sprite is displaced ~8px RIGHT with a transparent gap
  where it belongs** (empty mug: glass..gap..detached handle; patrons: a
  detached right sliver). Established: (1) the pack blob decodes
  perfectly offline — all 256 codes render right, handles attached
  (scratchpad sheet.png), so card data is good; (2) MAME ground truth
  confirms handle attaches directly to the glass; (3) a GHDL testbench
  (scratchpad/spsim/sp_tb.vhd) running the mcr3.vhd sprite machine
  VERBATIM against a cycle-exact model of sdram_gw's sp port renders
  all four words contiguous for ALL 7 possible 80MHz-round alignments —
  the RTL logic cannot produce the artifact, and the engine cannot even
  write past its 32px window. So the fault is a hardware-only behavior
  (fetch/data path at 225-deg, or something synthesis-specific).
  IN FLIGHT: a diagnostic build that (a) replaces sprite codes 22/23
  (mugs) with a synthetic pattern at SD-load time — fetch word w renders
  as 8px of color w+1, so one capture of the attract mug shows exactly
  which word landed at which slot; (b) adds a post-load port2 audit
  sweep counting nonzero sprite words by i%4 in beacon slots E0-E3
  (write-side loss vs fetch-side). Both marked TEMPORARY in
  mcr3_console60k_top.sv; REVERT after diagnosis.

- **See `docs/mcr_core_roadmap.md`** for the phased plan. All ROMs in `roms/`.
- **MCR3Mono (Rampage/Sarge/Max RPM/Power Drive/Star Guards) — PARKED for
  a future board rev.** Core is vendored + ready but moved to
  `future/mcr3mono.vhd`, out of the active build/OSD roster: the mono board
  needs different cabinet connectors (IP ports routed to different
  connectors), 3-player wiring (Rampage), and the ADC (Max RPM) — a
  different board target from the SSIO-family shield rev A. Un-park steps +
  rationale in `future/README.md`; design in the roadmap (Phase E). Bonus
  still stands: once Turbo Cheap Squeak is vendored, demoderb (4-player
  Demolition Derby) drops into the existing MCR-2 core.
- **MCR3Scroll core (Spy Hunter/Crater/Turbo Tag) — Phase D. MERGED INTO
  `mcr23s_console60k` 2026-07-30, BSRAM-BLOCKED, nothing on hardware yet.**
  The whole sound stack is vendored and BUILDS: `cheap_squeak_deluxe.vhd`,
  `pia6821.vhd`, `steering_control.vhd` and FX68K (via the `fx68k_lc.sv`
  lower-case wrapper — upstream's package+COMPONENT route does not bind on
  GowinSynthesis, see `mcr23s_console60k/README.md`). ROM specs and the pack
  layout are done: `merge_roms` family `mcr3scroll` for all three games,
  `make_pack_v2` family 3, `mcr_pack_v2.img` now carries 15 games.
  **The 3-family merge FITS**, after moving the sound ROM to SDRAM; it was
  127/118 before that. Detail and measurements in item 4a-bis above. The FX68K costs zero blocks;
  MCR3Scroll's own video/sprite RAMs are the cost.
  Open before it can run: the fit, then bg plane order (a guess — swap
  `gfx1_1_files`/`gfx1_2_files` if tiles show right shapes/wrong colours),
  per-game DIPs, Spy Hunter's lamp panel, and a real wheel/pedal on the
  shield ADC (`steering_control` on the d-pad is the stand-in).
- **MCR-3 core (Tapper/Timber/Journey/DoT) — Phase C, core ready, board
  gated on SDRAM.** `src/rtl/mcr3.vhd` vendored + platform-adapted (builds
  once wired). Board integration is fully designed in
  `docs/mcr_core_roadmap.md` (memory split: CPU/sound/bg baked BRAM,
  sprites->SDRAM, Journey tape->DDR3; the exact MiSTer sprite interleave;
  40/100 MHz CDC; SD->SDRAM sprite loader). Do the board build AFTER the
  Phase B memtest passes on hardware - Tapper/Timber first (plain SSIO
  sound). Journey needs a DDR3 wave port; DoT ships without speech.
- ~~SDRAM memtest — Phase B~~ **DONE / VERIFIED ON HARDWARE 2026-07-22.** Standalone
  test of the Tang SDRAM module (J9) using the exact controller MCR-3 will
  use (`src/rtl/sdram_gw.sv`, Gowin-adapted from MiSTer MCR-3). Flash
  `bitstreams/console60k_sdram_memtest.fs` with the module plugged in:
  J10 LED debug_o[0]=PASS, [1]=DONE, [2]=FAIL, [3]=heartbeat; UART beacon
  shows progress then c1/c0. FSM Verilator-validated. If reads fail, first
  suspect the SDRAM_CLK phase (swap D0/D1 on the ODDR in sdram_gw.sv).
  This gates all MCR-3/Scroll/Mono cores.
- **MCR-1 (Kick/Kickman/Solar Fox) — Phase A builds, not yet on hardware.**
  `src/rtl/mcr1.vhd` + `mcr1_console60k/`; bitstreams
  `bitstreams/console60k_mcr1_{kick,solarfox}.fs` (BSRAM 77/118, setup
  +0.585 ns, checks clean). To verify on hardware:
  `openFPGALoader -b tangconsole -f bitstreams/console60k_mcr1_kick.fs`.
  Open items: hardware bring-up (video/sound/controls); Kick spinner
  sensitivity + DIP defaults (input_3 = 0xFF placeholder) need tuning; OSD
  text rotation direction on the rotated MCR-1 monitors is a guess.
  ~~SD pack switching needs pack-format-v2~~ **RESOLVED 2026-07-24: pack
  v2 is implemented and the MCR-1 top is wired for it (FAMILY=0); its
  games are in mcr_pack_v2.img** - still needs the same hardware test as
  everything else MCR-1. One maintenance debt: the MCR-1 top is a copy of the MCR-2 top -
  a future refactor to a unified family-ifdef top would remove the
  duplicated video/USB/SD/OSD infrastructure (deferred to protect the
  working MCR-2 build during its own hardware validation).
- **Tang Primer 25K project is stale**: still the line-buffer video path and
  a Satan's Hollow input map. Fine as-is, but it no longer matches the 60K.
- **Tang Console 138K project is stale**: pre-framebuffer architecture.
