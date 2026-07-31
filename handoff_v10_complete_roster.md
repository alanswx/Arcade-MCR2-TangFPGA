# Handoff v10 — the complete roster, and what is still missing (2026-07-30)

Start here. Supersedes `handoff_v9_merged_core.md`, which predates MCR-1, the
15-game merge and all hardware verification.

This document exists because "what is left?" had no single answer: `TODO.md` is
136 KB with cocktail mode at line 1819, the per-board READMEs are board-scoped,
and some gaps — Discs of Tron's **speech** most obviously — were not written
down anywhere at all.

---

## Where the platform is

**One bitstream holds every MCR game this board can run: 15 titles, four
families.** `mcr123s_console60k` is flashed as the power-on default.

| Family | OSD idx | Games |
|---|---|---|
| MCR-3 (2) | 0–2 | Tapper, Timber, Discs of Tron |
| MCR-2 (1) | 3–8 | Satan's Hollow, Tron, Wacko, Kozmik Kroozr, Two Tigers, Domino Man |
| MCR3Scroll (3) | 9–11 | Crater Raider, Spy Hunter, Turbo Tag |
| MCR-1 (0) | 12–14 | Kick, Solar Fox, Kickman |

Budget: **116/118 BSRAM, 75% logic, 0 timing violations**, clk_sys Fmax 43.0 vs
40.0 MHz required. No ROM data in the bitstream — everything streams from the
SD card (licensing).

**Verified on hardware: 7 of 15** — Wacko, Kick, Kickman, Solar Fox, Spy Hunter,
Turbo Tag, Crater Raider. That is all of MCR-1 and all of MCR3Scroll.

Every *mechanism* the merge depends on is proven:

| Mechanism | Blocks it saved | Proven by |
|---|---|---|
| Sprite ROM shared MCR-1 ↔ MCR-2 | 16 | Kick + Wacko |
| CSD 68000 ROM in SDRAM (`cpu2`) | 16 | Spy Hunter sound |
| Sound ROM in SDRAM (`cpu3`) | 8 | Kick, Kickman (SSIO-only) |
| Scratch RAM shared ×4 | 4 | all seven |
| CPU ROM trimmed to 0xE000 | 4 | all seven |
| bg pair shared, MCR-1's 4 KB planes | 4 | Kick |

All three audio configurations work: SSIO-alone, SSIO+CSD, and CSD-alone.

---

## 1. Still to VERIFY (not missing — just unplayed)

**Regression pass on the eight remaining MCR-2/MCR-3 games**: Tapper, Timber,
Discs of Tron, Satan's Hollow, Tron, Kozmik Kroozr, Two Tigers, Domino Man.
They were verified in `mcr23_console60k`, before the shared scratch RAM, the
trimmed CPU ROM and the SDRAM sound ROM existed.

Do it by **switching between families repeatedly**, not by playing each in
isolation: the shared scratch RAM is the only mechanism that can corrupt a
*running* game, and family switching is how you would provoke it.
`SCRATCH_EXTERNAL(0)` on all four cores is the isolation switch (costs 4 blocks
the build does not have, so it is a diagnostic, not a fallback).

---

## 2. MISSING FEATURES — the actual answer to "what is left?"

### 2a. Sound and speech

| Gap | Status |
|---|---|
| **Discs of Tron SPEECH** | **Absent.** DoT's Squawk & Talk board (6809 + TMS5200) was never implemented in the upstream MiSTer core, so there is nothing to port. DoT plays and sounds correct otherwise. Implementing it means writing the board from scratch. |
| **Journey tape music** | Journey is not in the roster at all — see 2b. |
| Everything else | Working. SSIO, Cheap Squeak Deluxe/FX68K, and the SSIO+CSD mix are all verified. |

### 2b. Games not in the roster

| Game | What it needs | Same board? |
|---|---|---|
| **Journey** | `wave_sound.sv` plus a DDR3 read port for its tape samples (MBs, too big for SDRAM alongside sprites). It is `mcr_91475`, not 91490, so `mcr2p5=1`. | Yes |
| **Demolition Derby** | Turbo Cheap Squeak (6809) vendored; then it drops into the existing MCR-2 core. But it is **4-player**, so it may hit the same connector limit as Rampage. | Probably not |
| **MCR3Mono** (Rampage, Sarge, Max RPM, Power Drive, Star Guards) | A **different board rev** — its IP ports route to different cabinet connectors, plus 3-player wiring and an ADC. Core is vendored and parked in `future/`. | **No** |

### 2c. Cabinet features (all gated on the shield PCB, which is not built)

| Gap | Detail |
|---|---|
| **Cocktail mode** | Unaddressed across every game (`TODO.md` "Cocktail mode"). Four separate problems: no operator control over the upright/cocktail DIP; player-2 inputs tied off; Wacko needs a core port addition for the trackball mux; and screen flip is unverified. |
| **Spy Hunter lamp panel** | `show_lamps` tied to 0. Needs the shield's second 74HC595 — zero extra header pins. |
| **Real wheel / pedal** | Spy Hunter and Turbo Tag use `steering_control.vhd` driven from the d-pad as a stand-in. A real analogue wheel needs the shield's ADC. |
| **Service menu / coin door** | Groundwork only: holding the coin key ~3 s to open a menu is designed, not built. The real cabinet group is Coin 1 + Service/Test, which arrives via the 74HC165 chain. |
| **NVRAM / high scores** | `cmos_ram.vhd` exists and the cores have `dl_nvram` ports, but the merged top ties them **off** — nothing persists but the selected game. |

### 2d. Video

**Seven of the fifteen games are ROT90 cabinets** — Satan's Hollow, Tron, Spy
Hunter, Turbo Tag and all three MCR-1 titles — so on a normal landscape monitor
they render sideways. That is *correct* for a real cabinet and wrong for
everything else, and it is the single biggest product gap.

The fix is scaler rotation: the frame is already in DDR3, so it is a read-address
transform rather than new storage (cost: address arithmetic plus a deeper
prefetch, because transposed reads destroy burst locality — read 8×8 tiles
rather than lines). No scaler here has it yet. See `docs/scaler_options.md`.

Also wanted, in rough value order: interpolation (nearest → sharp-bilinear),
scanlines, integer/pixel-perfect scaling, and aspect/overscan control.

**The scaler decision is now a real trade**: at 116/118 BSRAM there is no room
for `ascal_v`'s +10 blocks. It is 15 games on `ddr3_framebuffer`, or 12 games
with the better scaler — unless `N_DW` is narrowed to 64, which is where the +10
comes from.

### 2e. Known open bugs

| Bug | Status |
|---|---|
| **HDMI dropouts** | Long-standing. The PLL VCO fix (2026-07-28) removed the main cause; the residual is recoverable by re-running DDR3 calibration, so a managed/periodic recalibration is the candidate gateware fix. **Not re-measured on this core.** Measuring needs discipline — record time since configuration and soak for tens of minutes, because a fresh flash hides the entire fault class. |
| **Timber boot-load** | Renders correctly from the OSD but fails when loaded at BOOT (the `use_prefs` path). Instrumented but never read. Not re-checked since the merge. |

---

## 3. Polish / debt

- **Retire the bring-up diagnostics** (owed since v9): the sprite-word audit,
  the liveness counters in beacon E0/E1, the disabled `if (1'b0)` sweeps, the
  SDRAM dump. Keep the stored-ROM audit. Frees logic (75% now) and buys back
  timing margin. Do it *after* the roster is verified — they are the instrument.
- **Control and DIP tuning**: Kick's spinner sensitivity and MCR-1's `input_3`
  are placeholders; MCR3Scroll DIPs are the MRA defaults, not cross-checked
  against MAME per game.
- **Apply the new build options to the other boards.** Every board except
  `mcr123s_console60k` still builds at DEFAULT routing effort — see the build
  options section in CLAUDE.md. They may all have margin sitting unclaimed.
- **`impl/` for the two new boards is not committed** (315 MB). The repo
  convention is to commit it; this was left out deliberately.

---

## 4. What I would do next, in order

1. The eight-game regression pass (§1) — the only thing that could still be a
   real bug rather than a missing feature.
2. HDMI soak on this core (§2e) — wait a good while after any flash first.
3. Retire the diagnostics (§3), reclaiming logic and timing margin.
4. Then pick a direction: **scaler rotation** is the highest-value feature for
   anyone not building a real cabinet; the **shield PCB** is the highest-value
   for anyone who is.

---

## 5. Lessons from this session that outlive it

- **Check the toolchain before blaming the design.** `build.tcl` had only ever
  set `place_option 2`; enabling `route_option 2`, `retiming`, `timing_driven`
  and `correct_hold_violation` took clk_sys TNS from −6.342 ns over 25
  endpoints to −0.059 ns over 1 with **no RTL change**. Two days of RTL surgery
  bought less than four `set_option` lines.
- **LUT RAM is not a free substitute for BSRAM.** Fine for 256-byte line
  buffers; doing it to the 512-byte sprite staging RAMs cost the entire clk_sys
  domain (−536 ns), because a distributed-RAM read is a combinational walk fed
  by a mux, closing on the opposite clock edge.
- **Never budget one BSRAM block per array.** PnR already packs small ones:
  folding four 512-byte RAMs into one returned 2 blocks, not 4. Every estimate
  this project made was optimistic; only PnR is authoritative.
- **Mux depth matters on half-cycle paths.** `a ? : b ? : c ? :` is three
  dependent LUT levels; an array indexed by `run_family[1:0]` is one 4:1 mux.
  Keep `FAM_*` numbered 0..3 so the family code stays usable as an index.
- **Identical structure across cores is the cheapest saving there is.** The
  sprite ROM, bg pair and scratch RAMs were byte-identical in all four cores,
  and only one core runs at a time. Sharing them cost nothing and saved 28
  blocks — more than every clever trick combined.
