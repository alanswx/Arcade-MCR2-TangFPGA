# MCR shield — pre-fab review of the 2026-08-25 PCB, netlist and gerbers

Review of commit `aaab325` ("Add files via upload", 2026-08-25 15:39): the
schematics, `MCR_prototype_PCB.kicad_pcb`, the gerber/drill set generated from
it at 15:34 the same day, and the BOM csv. Previous review:
`pcb_review_2026-08-22.md`.

**Bottom line: do not order yet.** Items 1–4 below are functional faults that
would make the board not work as built; each is a small schematic change.
Items 5–9 are design gaps worth fixing on the same spin because the board is
large (267 × 199 mm, 4-layer) and a respin is expensive.

## How this was checked

KiCad 10.0.5 was installed for this. The `.net` in the repo is the one from
2026-08-22 and is stale; the schematic uploaded today has no exported netlist.
Also, **the root sheet `MCR_prototype_PCB.kicad_sch` does not reference the
eleven sub-sheet files** — it holds only D4, J0, TP5, TP6. Opened as a
project, KiCad sees a 4-part design, ERC covers nothing, and `kicad-cli sch
export netlist` returns 4 components. (The PCB footprints all carry
single-level `/uuid` paths, so the board was evidently updated from each sheet
file opened standalone.) That works for producing a board, but it means no
tool has ever run a whole-design ERC on this schematic.

So: a wrapper root that instantiates all twelve sheets was built in a scratch
copy, and from it:

- `kicad-cli sch export netlist` → 143 components, 276 nets. Saved as
  **`MCR_prototype_PCB/MCR_prototype_PCB_netlist_2026-08-25.net`**.
- That netlist was compared **pin by pin** against every pad's net in the
  `.kicad_pcb`: **212 connected nets on each side, identical connectivity,
  no differences.** So the gerbers really are what the schematic says.
- `kicad-cli sch erc` on the wrapper: one real warning (item 3).
- `kicad-cli pcb drc`: 0 unconnected items, 0 clearance/width violations
  (min track used 0.15 mm, vias 0.6/0.3 mm — ordinary fab class).
- Component pin functions were read from the symbols themselves, and the
  THS7374 and ADS7830 datasheets were pulled for the polarity/limit checks.

Everything below therefore applies equally to the schematic, the board and the
gerbers.

---

## Must fix before ordering

### 1. U1 and U2 have CLK and LOAD swapped — 16 of the 48 inputs are dead

| chip | pin 1 (`~PL`, parallel load) | pin 2 (`CP`, clock) |
|---|---|---|
| U1 (J4 IP0), U2 (J4 IP1) | **`IN_CLK`** | **`IN_LOAD_N`** |
| U3, U4, U6, U7 | `IN_LOAD_N` | `IN_CLK` |

Two of the six 74AHC165s are wired opposite to the other four. U1/U2 will
parallel-load on every clock edge and shift on the load pulse, so the J4
inputs — coins, starts, button, tilt, service, test and the whole 8-bit
D0–D7 bus — can never be read. Swap the two nets on U1 and U2. (This is in
the 2026-08-22 netlist too; the previous review missed it.)

### 2. Every SRV05-4 ESD array is wired in series with its filter cap

All 32 protected inputs have this topology (example, J4 pin 1):

```
J4.1 ─ RN8 1k ─┬─ RN1 4.7k ─ +5V
               ├─ U1.D7
               └─ C9 10n ─── U15.IO1   (SRV05 GND → GND, VCC → +5V)
```

`Net-(U15-IO1)` contains only `C9.2` and `U15.1`. The capacitor's far end
goes to the ESD diode's IO pin instead of to ground, so:

- the 10 nF filter caps float — no debounce / RF filtering at all;
- the ESD clamps see the input only through a 10 nF cap — no DC clamp.

Fix on all eight arrays (U5, U15–U19, U22, U23): capacitor pin 2 → GND, and
the SRV05 IO pin → the input node directly. This was also present on
2026-08-22.

### 3. ADS7830 REF pin is tied to +5 V while VDD is 3.3 V

U14 pin 16 (`VDD`) = +3.3 V, pin 10 (`REFin/REFout`) = +5 V. ERC flags this
(bidirectional pin driven by U24's output). The datasheet's absolute maximum
for any pin is VDD + 0.3 V, and with the internal 2.5 V reference enabled by
default the pin is being driven against a 110 Ω source. Either leave REF as
an output (100 nF to ground, use the internal 2.5 V) or drive it from +3.3 V,
not +5 V. Present on 2026-08-22 as well.

Related: the volume pot on J3/J3_DOT1 pins 1–3 is placed across **+5 V** and
GND with its wiper into CH0 — a wiper above 3.6 V exceeds the analog-input
maximum for a 3.3 V-powered ADS7830. Put the pot's top end on +3.3 V (or on
REF).

### 4. D4, the console's +5 V feed, is a 1N4148W

Pin 11 is now powered (good — that is what `shield_power_decision.md`
asked for), but through **D4 = 1N4148W, a 150 mA signal diode in SOD-123.**
The console draws several hundred mA to ~1 A. It needs a ≥2 A Schottky
(SS24/SS34, or a B340) or an ideal-diode part; a Schottky's 0.3–0.4 V drop
lands the console's USB-A host port at ~4.6 V, so an ideal diode
(LM66100 / MAX40200 class) is the better choice. The +5 V trace to pin 11
also narrows to 0.2 mm in places — make it ≥0.8 mm like the rest of the
power routing.

---

## Should fix on the same spin

### 5. No decoupling on the +3.3 V rail; almost none on +5 V

The +3.3 V net contains no capacitors at all — six 74AHC165s, the ADS7830 and
the R-78B3.3 output with nothing on them. +5 V has C41/C42 (0.1 µF) and
C43/C44 (22 µF) — two ceramics for two '595s, two THS7374s and eight ESD
arrays. Every `0.01 µF` in the BOM is an input-node filter. Add 100 nF at
each IC's supply pin and ≥10 µF at each regulator output.

Also: L1/L2 (3.3 µH) sit between the +12 V caps (C5/C7) and the regulator
inputs, with no capacitor on the regulator side of the inductor. RECOM wants
the input cap at the module pin; an inductor feeding a bare switching input is
a ringing/instability risk. Move or duplicate the 4.7 µF after L1/L2.

### 6. Video: THS7374 filter is engaged, inputs are over-range, no back-termination

- `BYPASS` (pin 9) is grounded on both U12 and U13. Per the datasheet, **low =
  9.5 MHz filter engaged, high = bypass (150 MHz).** The core's pixels are
  50 ns wide (20 MHz dot clock); a 9.5 MHz 6th-order filter will smear them.
  Tie BYPASS high for the RGB amp (U13). (DISABLE low = enabled is correct.)
- The 510/1k/2k ladder feeds the THS7374 input with no shunt. The spec's
  ladder was designed to drive the monitor's 75 Ω directly (spec §3); into a
  high-impedance input it produces 0–3.3 V, which the amp doubles — the
  linear output range at 5 V limits the input to ~2.3 V, so the top of the
  range clips. A 75 Ω shunt to ground at each input gives ~0.7 V full scale.
- The outputs go straight to the DE-15 and to J2 in parallel with no 75 Ω
  series resistors. The 6 dB gain assumes source termination; and driving
  both connectors means two 75 Ω loads with nothing isolating them. Add 75 Ω
  in series per output (one per connector if both stay).
- Sync: 3.3 V HS/VS through a 2×-gain video amp on a 5 V rail. It will work
  as a crude TTL buffer (clips at ~4.5 V, filtered edges), but the spec's
  intent was a 74HCT244/NPN stage. Acceptable if bypassed; noting it.

### 7. Audio: there is no amplifier, and the DoT speaker pins are mis-assigned

Per the archived MCR pinout table (`docs/MCR Series Pinouts.html`), J3 pins
7/9 are the **speaker −/+ terminals** of the sound board's own amp, and on
Discs of Tron J3 is 10-pin with 6/7 = speaker 1 +/− and 9/10 = speaker 2 +/−.

- The shield puts line-level, 2 kΩ-source RC-filtered PWM on those pins with
  no LM386/TPA stage (spec §3). A cabinet speaker plugged into J3 will be
  near-silent. Either add the amp or state that an external amp is required.
- On J3_DOT1, pin 6 carries `AUD_PWM_R1` and pin 7 `AUD_PWM_L1` — i.e. the +
  and − of *one* speaker get two different channels. Same for 9/10 (R2/L2).
  The schematic labels these "Front Left / Front Right / Rear Left / Rear
  Right", which does not match the cabinet: DoT has two speakers, each
  bridge-driven.
- The second pair `AUD_PWM_L2/R2` occupies **J10 pins 1 and 5** (balls R19,
  R17 = `vga_r[0]`, `vga_b[0]` in every 60K CST). Nothing in the RTL produces
  a second stereo pair, and today those pins carry video bit 0. Harmless
  electrically (RC filter only) but it needs a decision and a pin-sheet
  update before it is useful.

### 8. J5: coin meter wired to two ULN outputs, and no ground pins

- Table: J5.20 = meter **Return** (the +12 V side), J5.21 = **Meter 1**.
  Board: J5.20 ← U10.O1, J5.21 ← U10.O2 — both open-collector sinks, so the
  meter has no supply and can never click. Pin 20 should go to +12 V (fused);
  pin 21 to one ULN output. Meter 2 (J5.22, Kick/Rootbeer) and the Kick
  light (J5.23) are not provided.
- J5.9 and J5.18 are cabinet GND on every game; the board leaves both
  unconnected (J4 has its two grounds, J5 has none).
- `Start 1/2/3 Lamp` are nets on U10.O3–O5 that go to **no connector** —
  ERC reports the labels as isolated. Route them somewhere or drop them.
- `Out_Clear` (SRCLR on both '595s) still has no pull-up; `Out_En_N` got its
  10 k (R103) — good — but a floating SRCLR clears the chain before the FPGA
  configures. Add a 10 k to +3.3 V.

### 9. Mechanical

- **No mounting holes.** The only 3.2 mm drills are the two DE-15 bracket
  holes (both at y = 24.4 mm, 25 mm apart). A 267 × 199 mm 4-layer board
  with a 40-pin socket and eight MTA headers needs standoffs.
- J0 (the 2×20 socket to the console's J10) is on the **top** side at
  (125, 148). Confirm the stacking: if the shield sits under the console, the
  socket needs to face the dock's header, and pin 1 must land on J10 pin 1
  (`pcb_design.md` assumed ~135 × 95 mm under the console; this is a
  different arrangement).
- J1 pin 18 = +12 V, pins 6/7/10/20 = GND. The archived table lists J1's 13
  functions but not their 20 positions, so **I could not verify these pin
  numbers** — please check against the MCR power-supply manual before
  ordering; a wrong +12 V pin on a .156" power connector is the one mistake
  that destroys parts.

---

## Minor / for the record

- No I²C pull-ups on `ADC_SDA`/`ADC_SCL`. FPGA internal pull-ups will do for
  a bench test; 4.7 k to +3.3 V is cheap.
- Only ADS7830 CH0 is used (the volume pot). Spy Hunter needs wheel + pedal;
  CH1–CH7 are NC. The analog-switch scheme in `shield_wiring.md` is not on
  this board — fine for a prototype, but note it.
- `/1 Plyr Move Up/Down/Left/Right` on J5 1–4 are the only labelled inputs;
  the other 44 are still auto-named (`Net-(RN10-R1.2)` …). Same request as
  last time: the '165 bit order *is* the RTL input map.
- 74AHC165 inputs are pulled to +5 V while VCC is 3.3 V: **fine** — AHC
  inputs are rated to 5.5 V independent of VCC (that is why AHC, not HC).
- ULN2803 COM (pin 10) on +12 V: correct for 12 V lamps/meters.
- Track widths 0.15–1.0 mm, 0.6/0.3 vias, GND pour on In1, +5 V pour on In2:
  all ordinary; DRC is clean.
- The BOM csv is consistent with the board (48 lines, 143 parts).

## J10 / J0 as built (2026-08-25)

| J10 | ball | frozen doc | board | note |
|---|---|---|---|---|
| 1 | R19 | `VID_R0` | `AUD_PWM_L2` | see item 7 |
| 5 | R17 | `VID_B0` | `AUD_PWM_R2` | see item 7 |
| 9 | W17 | `SERVICE_N` | `Service Switch` (SW4, 1 k to +3.3 V) | ✓ as agreed 08-23 |
| 11 | — | +5 V | +5 V via D4 | see item 4 |
| 13, 38 | W22, P15 | `VID_G0`, `SPARE6` | NC | ✓ |
| 10 | V17 | `SPARE1` | NC | ✓ |
| all others | | | match the doc | ✓ (28 is `Out_Clock`; spelling only) |

## What to update in our docs once Mitch confirms

- `shield_j10_pinout.md`: pins 1/5 → second audio pair (or back to spare);
  pin 11 → "powered from shield through D4".
- `TODO.md`: RTL work — I²C master for the ADC, decision on a second audio
  pair, `OUT_CLEAR_N` driven high, video bit 0 outputs retired.
