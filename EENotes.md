# EE Notes — schematic review answers (2026-07-24)

Responses to the open questions on the MCR shield schematics
(`Schematics_and_PCB/`, newest snapshot `MCR_prototype_PCB-2026-07-22_141611.zip`).
Authority docs: `docs/universal_mcr_shield_spec.md`, `docs/shield_wiring.md`,
`docs/shield_j10_pinout.md` (frozen pin sheet), `docs/mcr_game_input_matrix.md`.
A full net-by-net review of the KiCad files is still owed (next session);
these answers are from the spec side.

## 1. BAT54S clamps — the doc is right, schematic needs fixing
A clamp pair must straddle the rails: signal on the common node, top
diode cathode to **+5 V**, bottom diode anode to **GND**. With both ends
on GND you only clamp negative excursions — a positive harness transient
(+12 V solenoid/coin-counter kick is real in these cabinets) goes straight
into the 74AHC165 inputs. Fix before fab.

## 2. Doc §3B calling J2 an "input" — doc bug, agreed
J2 is **video out** per the Master Pinouts matrix
(`docs/mcr_game_input_matrix.md` / `docs/MCR_Master_Pinouts.pdf`). §3B
should reference J4/J5 (player inputs). Fix the doc, renumber the U-chips
**once**, then freeze refdes — the wiring docs cite them.

## 3. Player 1/2/3 start lamps — keep them
The SSIO drives lamps from its output ports on several MCR games; the
same 74HC595 chain serves them at zero extra cost. Routed-but-unpopulated
is free; adding traces later costs a board spin. Good call including them.

## 4. U8/U9 ('595) clear pins
Tie **/SRCLR high** (10 k to rail). Power-on glitch protection belongs on
**/OE**: pull-up so outputs stay Hi-Z until the FPGA drives /OE low after
configuration. Lamps and coin counters must not chatter during boot/config.

## 5. J3 volume-pot ADC
Don't add a dedicated ADC or new FPGA pins: the spec's analog section
(Spy Hunter / Max RPM) already defines a SPI ADC — put the volume pot on a
**spare channel of that same ADC**; the FPGA reads it over the existing SPI
chain. Pin assignments come only from `docs/shield_j10_pinout.md`; if a pin
must move, change that sheet first (it is the authority over spec §4b).

## 6. Audio output stage — drop the LM386
With the external dual-amp module present, the shield outputs **line level
only**: PWM -> RC filter -> coupling cap -> amp input. Two gain stages in
series invites noise and clipping. No LM386.

## 7. Voltage level conversions — the audit rule
- **Inputs**: must be **74AHC165** (not HC/HCT), VCC = 3.3 V. AHC inputs
  tolerate 5 V harness levels while the part runs at 3.3 V — that is the
  entire reason the spec picks AHC. Verify every input chip's family and
  rail on the schematic.
- **Outputs**: a 5 V-supplied '595 driven by 3.3 V logic is marginal
  (VIH(min) at 5 V VCC is 3.5 V for HC). Either run the '595s at 3.3 V with
  transistor drivers for lamps/counters, or use **AHCT/HCT** (TTL input
  thresholds) if they must run at 5 V.
- Systematic check next session: every FPGA-facing net 3.3 V, every
  harness-facing net 5 V-tolerant, every rail pin verified against the PDF.

## Next session, item 0
Extract `MCR_prototype_PCB-2026-07-22_141611.zip` and do the net-by-net
review against the spec and the seven answers above.
