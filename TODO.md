# TODO / open issues

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
       bitstream, 114/118 BSRAM, flashed as the power-on default. Confirmed
       rendering: Tapper, Timber, DoT, Satan's Hollow, Wacko, Two Tigers.
       NOT yet eyeballed: Tron, Kozmik Kroozr, Domino Man (the first two
       have analogue controls whose wiring was ported wholesale).
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
   PROBE GOTCHA worth remembering: the first probe reported a comfortable 95
   because the family-select signal was `game_id[3]`, which synthesis proved
   constant 0 (the OSD only assigns loaded_slot[2:0]) - it killed MCR-2's
   video path and pruned 27 of its 34 blocks. Any future probe must select on
   something provably non-constant (a physical input).

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
- **MCR3Scroll core (Spy Hunter/Crater/Turbo Tag) — Phase D, core ready,
  board gated on SDRAM.** `src/rtl/mcr3scroll.vhd` vendored + adapted
  (dprams + hcnt_out). The Cheap Squeak Deluxe / FX68K / pia6821 /
  steering_control sound stack is verified Gowin-clean and listed for
  vendoring at board-build time. Crater Raider first (SSIO-only, no FX68K);
  Spy Hunter adds CSD + steering + lamps. Design in the roadmap.
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
