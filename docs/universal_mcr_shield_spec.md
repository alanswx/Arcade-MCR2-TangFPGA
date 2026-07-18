# Universal MCR Shield — Consolidated Specification

Single source of truth for the cabinet-interface shield that lets a Tang
Console 60K/138K drop into any original Bally Midway MCR-1/2/3 cabinet as a
CPU-board replacement. Consolidates and supersedes the electrical/pinout
content spread across `handoff_v2_design.md` (§2–3, written for the Primer
25K dock) and `pcb_design.md` (floorplan/KiCad, still authoritative for
layout). Game-function reference: `docs/mcr_game_input_matrix.md`.

## 1. Design principles

1. **Expose the original MCR connectors** (J2, J3, J4, J5, Video, power,
   audio) so the cabinet harness plugs straight in — no JAMMA adaptation.
2. **No DIP switches, no jumpers.** Connector wiring is identical across all
   MCR games (see the matrix doc); every game-specific interpretation lives
   in the FPGA top. One shield serves every core.
3. **Passive/parallel shield.** Every cabinet input gets its own
   opto-isolated FPGA pin; the Console 60K/138K has the pin budget, so no
   shift registers (those were only needed for the pin-starved 25K+SDRAM,
   see handoff_v2 Option A.2).

## 2. FPGA signal budget

| Group | Signals | Direction | Interface |
|---|---:|---|---|
| J2 (P1) | 6 | in | opto, active low |
| J3 (coin/start/tilt) | 5 | in | opto, active low |
| J4 (Opt X, 8-bit dial bus) | 8 | in | opto, active low |
| J5 (Opt Y / P2) | 11 | in | opto, active low |
| Video RGB | 9 (3:3:3) | out | R2R DAC → 1 Vp-p |
| Video sync | 2–3 (HS, VS, opt. CSYNC) | out | NPN/74HCT buffer → 5V TTL |
| Audio | 1–2 (PWM) | out | RC filter → LM386 |
| **Total** | **~44** | | |

Fits the Console's 2×20 headers ("up to 2×38 IOs" per Sipeed wiki) without
touching PMOD0/PMOD1 or the USB/SD/SDRAM pins.

## 3. Electrical interface (consolidated)

- **Power:** cabinet +12 V → onboard buck (LM2596/MP1584EN, ≥1.5 A) → 5 V to
  the Console's 5 V input. Do not use the cabinet's +5 V rail (noise/brownout)
  or −5 V rail (not needed — no 4116 DRAMs).
- **Inputs:** TLP281-4 quad optos, cabinet side pulled to +5 V through
  4.7 kΩ; output transistor pulls the FPGA pin (internal pull-up, 3.3 V) to
  GND. 100% galvanic isolation of all 30 input lines (8 × TLP281-4).
- **Video RGB:** R2R ladder per gun (510 Ω / 1 kΩ / 2 kΩ for bits 2/1/0)
  into the monitor's 75 Ω load ≈ 1 Vp-p. No active buffer needed.
- **Video sync:** 3.3 V FPGA → BC847 NPN stage (or 74HCT244 powered at 5 V)
  → 5 V TTL negative-going HS/VS on Video-8/9. G07/K4600-style monitors at
  15 kHz; the core must be in `tv15Khz_mode=1` for a real MCR cabinet
  monitor.
- **Audio:** PWM → 2-stage RC low-pass (~15 kHz) → LM386 (12 V rail) → mono
  speaker terminals.

## 4. Dock connector plan (from schematic `Tang_Mega_60K_Console_32001C`, rev 1.3)

The dock's two 2×20 headers are **J9 ("SDRAM0 CONN", near PCIe)** and
**J10 ("SDRAM1 CONN", near the PMODs)** — each carries a full 38-signal
SDRAM-pinout GPIO bus. Architecture decision:

- **J9 — reserved for the Tang SDRAM module** (future frame buffer / ROM
  store; nand2mario cores use these exact pins, `cs_n = F21` on this rev).
- **J10 + PMOD0 + PMOD1 — the shield** (38 + 16 = 54 IOs for ~44 nets).
- USB-A ports remain the controller path; HDMI remains for modern displays.

### 4a. J10 header ↔ FPGA ball map (verified: sheets 4, 6, 8 of rev C PDF)

| J10 pin | Net | Ball | J10 pin | Net | Ball |
|---|---|---|---|---|---|
| 1 | D0 | R19 | 2 | D1 | P19 |
| 3 | D2 | U21 | 4 | D3 | T21 |
| 5 | D4 | R17 | 6 | D5 | P16 |
| 7 | D6 | T18 | 8 | D7 | R18 |
| 9 | D15 | W17 | 10 | D14 | V17 |
| 11 | **+5V** | — | 12 | **GND** | — |
| 13 | D13 | W22 | 14 | D12 | W21 |
| 15 | D11 | P17 | 16 | D10 | N17 |
| 17 | D9 | N14 | 18 | D8 | N13 |
| 19 | A12 | V20 | 20 | CLK | U20 |
| 21 | A9 | Y22 | 22 | A11 | Y21 |
| 23 | A7 | AB22 | 24 | A8 | AB21 |
| 25 | A5 | AA21 | 26 | A6 | AA20 |
| 27 | WE | AB20 | 28 | A4 | AA19 |
| 29 | EXIO0 (=DM0 via 0Ω) | AA18 | 30 | EXIO1 (=DM1 via 0Ω) | AB18 |
| 31 | CAS | Y19 | 32 | RAS | Y18 |
| 33 | CS | T20 | 34 | BA0 | N15 |
| 35 | BA1 | U18 | 36 | A10 | U17 |
| 37 | A0 | R16 | 38 | A1 | P15 |
| 39 | A2 | R14 | 40 | A3 | P14 |

Caveats: **V17 = CSI_B, AB20 = CSO_B/DOUT, AA19 = RDWR_B** are config
dual-purpose pins — synthesis needs the matching `-use_sspi_as_gpio`-family
options (the 25K build.tcl shows the pattern). U20/V20 are GCLK-capable
(bonus, not required). All J10 banks (6/7/8) are 3.3 V.

### 4b. Cabinet pin → J10/PMOD assignment

Inputs (all opto-isolated, active low, internal pull-ups):

| Cabinet pin | Function | J10 pin | Ball |
|---|---|---|---|
| J4-1..7,9 | Opt X D0–D7 (dial bus) | 1,2,3,4,5,6,7,8 | R19,P19,U21,T21,R17,P16,T18,R18 |
| J5-1..6 | Opt Y D0–D5 | 18,17,16,15,14,13 | N13,N14,N17,P17,W21,W22 |
| J5-15 | Opt Y D6 / P2 Up | 10 | V17 |
| J5-16 | Opt Y D7 / P2 Down | 9 | W17 |
| J5-17 | P2 Left | 36 | U17 |
| J5-18 | P2 Right | 22 | Y21 |
| J5-19 | P2 Button 1 | 19 | V20 |
| J2-1..6 | P1 Up,Down,Left,Right,B1,B2 | 37,38,39,40,28,25 | R16,P15,R14,P14,AA19,AA21 |
| J3-1..5 | Coin1,Coin2,Start1,Start2,Tilt | 26,23,24,21,34 | AA20,AB22,AB21,Y22,N15 |
| reserved (outputs: coin meters / lamps / J6) | — | 20,27,31,32,33,35,29,30 | U20,AB20,Y19,Y18,T20,U18,AA18,AB18 |

Video/audio on the PMODs (shield covers both sockets):

| Signal | PMOD | Ball |
|---|---|---|
| VID_R[2:0] (R2R) | PMOD0 | V18, V19, G21 |
| VID_G[2:0] (R2R) | PMOD0 | G22, F18, E18 |
| VID_B[2:1] (R2R) | PMOD0 | C22, B22 |
| VID_B[0] (R2R) | PMOD1 | W19 |
| VID_HS / VS / CSYNC (5V TTL buf) | PMOD1 | W20, F19, F20 |
| AUD_PWM_L / R | PMOD1 | E22, D22 |
| spare | PMOD1 | E21, D21 |

**Note:** the current `mcr2_console60k.cst` desk-test assignments (buttons
on PMOD1, provisional cab video) intentionally differ; re-pin to this table
when shield rev A is finalized — cabinet inputs then arrive via J10 optos
and the USB pad, so PMOD desk buttons retire.

+12 V from the cabinet enters the shield at a screw terminal → buck → 5 V.

## 5. RTL requirements per game core

- `tv15Khz_mode = 1` for cabinet use (native 15 kHz RGBS); HDMI path stays
  active concurrently for bring-up.
- Input mapping from nets above into `input_0..input_4` per game, bit
  positions verified against MAME (`mcr.cpp`) — see examples in
  `mcr_game_input_matrix.md`.
- Spinner/trackball (J4/J5 8-bit buses) feed the core's `spinner.sv` /
  analog paths — only needed for dial games (Tron, Kick, Kozmik, Wacko,
  DoT, Spy Hunter).

## 6. Open items

1. **5 V delivery route** — shield buck → console. Preferred: into the
   dock's USB-C power input (goes through the dock's OR-ing/OVP, sheet 3).
   J10 pin 11 exposes a +5 V rail, but whether back-feeding it powers the
   SOM cleanly (it sits behind the OR-ing/OVP/bead chain) is unverified —
   do not use it as an input until traced.
2. **Board revision** — ✅ checked: J10's header pinout is net-for-net
   identical in rev A (32001A, 1.22) and rev C (32001C, 1.3); only the
   footprint differs (TH vs SMD 2×20). Ball map in §4a is from rev C's SOM
   sheets; if a board is identified as rev A, spot-check sheets 4/6 (the
   only known dock-level reroute is SDRAM0_CS: F19 on the old NEO dock →
   F21 now — J9 side, doesn't affect the shield).
3. **J6 / SSIO IP4** and **lamp/coin-meter outputs** — not in the matrix
   PDF; 8 J10 pins are reserved for them. Survey MAME + cabinet manuals
   before finalizing rev A (outputs need driver transistors, not optos).
4. **Board outline/mounting** — `pcb_design.md` + `tools/generate_pcb.py`
   own the physical layout; sync them to §4b (they currently assume generic
   2×20 headers, and J9 must be left clear for the SDRAM module).
5. **138K variant** — same dock; header nets are dock-level, but the
   net→ball map on sheets 4–6 is SOM-specific. Re-extract from the 138K
   SOM schematic before targeting it.
