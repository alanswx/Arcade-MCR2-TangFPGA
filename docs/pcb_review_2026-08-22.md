# MCR shield — netlist review, 2026-08-22

Review of `MCR_prototype_PCB_netflist.net` (commit `2dded8a`) and the schematic
rework in `e2432fb`, checked against `docs/shield_j10_pinout.md`, which is the
project's frozen pin sheet for the 40-pin header to the Tang.

Method: the netlist was parsed and every J0 pin compared with the doc. Full
table at the end. Nothing here is a complaint — most of the deviations look
like improvements — but each one either needs a doc update or changes what the
FPGA has to do, so they need agreeing rather than absorbing silently.

Nothing in this review has been changed in the repo. The doc still says what it
said before.

---

## 0. Answers added 2026-08-23

Two follow-ups from Alan, both resolved below: **pin 33 is accepted as built**
(service moves to pin 9), and **powering the console from the shield** is
traced through the dock schematic.

### 0a. Pin 33 stays as you built it — service moves to pin 9

`docs/shield_j10_pinout.md` has been updated:

| J10 pin | FPGA ball | now | was |
|---|---|---|---|
| 33 | T20 | `OUT_CLEAR_N` — output, '595 SRCLR | `SERVICE_N` |
| **9** | **W17** | **`SERVICE_N` — input, pull-up to 3V3** | `SPARE0` |

Pin 9 is a plain spare with no config-pin caveat (unlike pin 10, which is
CSI_B). **This needs one wire added on the board**: cabinet service button to
J0 pin 9, with a pull-up to 3V3, exactly as pin 33 had.

Two notes:

- I looked for a zero-pin option first, since the service button is just
  another contact closure: **all 48 parallel inputs on the six '165s are
  already used**, so there is no free slot in the scan chain. A dedicated pin
  it is. (A seventh '165 would also work and cost no FPGA pins, if you would
  rather keep pin 9 spare.)
- `OUT_CLEAR_N` is an **FPGA output** and must be driven high in normal
  operation. If it is left floating the output chain clears. Worth a pull-up
  on the shield so lamps and meters stay in a known state before the FPGA is
  configured, in the same spirit as `OUT_EN_N` on pin 34.

### 0b. Powering the console from the shield

Traced through `Tang_Mega_60K_Console_32001C__Schematics.pdf` sheet 3
(SYS POWER) and sheet 8 (EX CONN). This closes open item #1 in
`universal_mcr_shield_spec.md` §6, which had it as unverified.

**The rail exists and it does reach the SOM.** J10 **pin 11 = +5 V**,
**pin 12 = GND** (J9 pin 11/12 are the same rail). On sheet 3 that +5 V sits
downstream of `VBUS_OUT` through ferrite FB4, and the SOM is fed from the same
`VBUS_OUT` through ferrite FB5. So 5 V injected at pin 11 reaches the SOM by
FB4 → `VBUS_OUT` → FB5. Both ferrites are UPZ2012U221-3R0TF, rated 3 A, so the
path itself is not the limit.

**But I do not recommend feeding pin 11, for one specific reason.** The dock
OR-rings its three supplies (debug USB, soft USB, battery) through ideal-diode
FETs into U13, and pin 11 is *downstream* of all of it. Inject there and:

- it back-drives U13's output and bypasses the OVP entirely, and
- more importantly, **if anyone plugs in a USB-C cable while the shield is
  powering pin 11, the two supplies are in parallel with no OR-ing between
  them.** That is a real failure mode in a cabinet, where USB-C will get
  plugged in for programming.

**Preferred route: feed our 5 V into the dock's USB-C power input instead.**
That goes through the OR-ing FET as designed, so a second supply plugged in
later is arbitrated rather than fought. Sheet 3 shows two such inputs
(`5V_USB` from the debug port and `5V_USB_S` from the soft port), either of
which is the intended way in. This is also what spec §6 already called the
preferred route, and the trace now backs it up.

So: **USB-C, not pin 11** — but the shield can absolutely be the source, no
separate wall wart needed.

**Current budget — please check before ordering.** The shield's 5 V comes from
U24, an R-78B5.0-**2.0** (2 A). That has to carry the console *and* the
shield's own logic, lamps excepted. I have not measured what a 60K console
draws with DDR3, HDMI and USB active. If it is 1.5 A the margin is thin. Worth
a measurement, or a 3 A part.

**A bonus from sheet 8, which resolves a question in section 3 below:** J10
pins 29/30 are `SDRAM1_EXID0/1`, 0 Ω-linked to `SDRAM1_DM0/DM1` via R29/R31 —
and the optional pulls to +3V3 and GND (R30/R32) are **marked DNP**. So those
pins are plain FPGA I/O with nothing fighting them, and the ADC address lines
are safe. The caveat in our pin sheet can be retired.

---

## 1. Pin 33 — resolved, see 0a above

|  | |
|---|---|
| **Frozen doc** | `SERVICE_N` — **input**. Cabinet service button, shield pull-up to 3V3, opens the OSD. |
| **Netlist** | `Out_Clear` — **output**. Drives `SRCLR` on both '595s (U8.10, U9.10). |

Two separate consequences:

**a. The direction is reversed on a pin the FPGA may currently read.** The RTL
has to drive pin 33 as an output now. If anything still treats it as the
service input, that is contention on a real pin.

**b. The cabinet service button has no home.** I searched every net for
SERV / TEST / DIAG / AUX and there is nothing — it has been dropped rather than
relocated.

Worth asking before we accept it: does `SRCLR` need a pin at all? It can be
tied high, because the RTL can clear the chain by shifting eight zeros and
latching. Spending one of forty FPGA pins on it *and* losing the service button
is a steep price if that is the only reason. If there is a reason I am missing,
say so and I will update the doc instead.

Either way the button needs somewhere to go — a '165 input would do, and there
is room.

## 2. Looks right, needs the doc updated to match

**Pin 11, +5 V from the dock — now unconnected.** The shield self-powers
instead: +12 V in on J1.18, through ferrites L1/L2, into R-78B5.0 (U24) and
R-78B3.3 (U25). This is better than what the doc describes and it matches the
warning already in spec §6.1 about not back-feeding the dock rail. Confirm it
is deliberate and I will rewrite the doc's pin 11 entry.

**Pins 1, 5, 13 — `VID_R0`/`B0`/`G0` unconnected.** Three bits per channel
instead of four. Correct: the core's video path is natively 3:3:3, so the
fourth bit never carried real information — the doc described it as "a copy of
bit 3", which was always a fiction. The ladder that is there (510 Ω / 1 kΩ /
2 kΩ on bits 3/2/1) matches the doc exactly. The RTL currently replicates the
MSB to four bits and would simply drive three unused pins; harmless, and I will
retire the bit-0 line from the doc.

## 3. Accepted, but it creates FPGA work that does not exist yet

**Pins 19, 20, 29, 30 — `SPARE2/3/4/5` are now the ADS7830 ADC**
(`ADC_SDA`, `ADC_SCL`, `ADC_A1`, `ADC_A0`). Good use of the spares, and it is
what Spy Hunter's wheel and pedal need.

Two things follow:

- **There is no I2C master in the RTL.** This is new work, not a wiring change.
  Not a problem, but it should be on the list rather than discovered later.
- **The doc's warning on pins 29/30 is now load-bearing.** It says: *"EXIO0/1:
  0 Ω-linked to DM0/DM1 net on the dock — verify before use."* They are now in
  use, so that has to actually be verified against the dock schematic before
  the board is ordered. If those links are populated, driving A0/A1 may fight
  the dock.

Minor: A0/A1 on an ADS7830 are normally strapped, not driven. Driving them from
the FPGA is fine and buys address flexibility — just confirm it is intended and
not a placeholder.

## 4. Request — label the input nets

The J4/J5/J6 parallel inputs come through as auto-generated names
(`Net-(RN6-R1)`, `Net-(RN6-R2)`, …). Electrically fine, but it means neither
the schematic nor the netlist records **which cabinet function each input is**,
so they cannot be checked against `docs/mcr_game_input_matrix.md` — the
MAME-verified per-game bit map we use to wire games up.

Since the '165 chain's bit order becomes the RTL's input mapping, this is the
one place where an unlabelled net turns into a silent wrong-button bug. Could
these get names?

Same question for `ST0`, `ST1` and `ARD` on the '595 chain — they are not in
any of our docs and I could not work out what they drive. And there are
**three** start lamps, where MCR normally has two; if the third is deliberate,
what is it for?

## 5. Useful finding — there is room for the Discs of Tron backlight

U10 has **three spare Darlington channels**: U8's QF/QG/QH drive ULN2803
outputs 13/12/11, all unconnected.

That is exactly what the Discs of Tron (Environmental) cabinet backlight needs.
The game drives it from SSIO OP4 — bit 6 is the lamp enable (J1-4) and bit 7
enables the 8.5714 Hz flasher (J1-3), wire-OR'd on the cabinet's flasher board.
Both are already decoded in the core, so this needs no board rework beyond
routing two of those spare outputs to a connector. See the "Discs of Tron
Environmental — cabinet backlight output" section of `TODO.md`.

If a connector destination can be found for two of the three, that feature is
essentially free.

---

## Appendix — full J10/J0 comparison

Generated by parsing the netlist, not transcribed by hand. Rows marked CHECK
are discussed above.

| J10 pin | FPGA ball | Frozen doc | Netlist (J0) | |
|---|---|---|---|---|
| 1 | R19 | `VID_R0` | `(not connected)` **←** | CHECK |
| 2 | P19 | `VID_R1` | `VID_R1` |  |
| 3 | U21 | `VID_R2` | `VID_R2` |  |
| 4 | T21 | `VID_R3` | `VID_R3` |  |
| 5 | R17 | `VID_B0` | `(not connected)` **←** | CHECK |
| 6 | P16 | `VID_B1` | `VID_B1` |  |
| 7 | T18 | `VID_B2` | `VID_B2` |  |
| 8 | R18 | `VID_B3` | `VID_B3` |  |
| 9 | W17 | `SPARE0` | `(not connected)` |  |
| 10 | V17 | `SPARE1` | `(not connected)` |  |
| 11 | — | `+5 V` | `(not connected)` **←** | CHECK |
| 12 | — | `GND` | `GND` |  |
| 13 | W22 | `VID_G0` | `(not connected)` **←** | CHECK |
| 14 | W21 | `VID_G1` | `VID_G1` |  |
| 15 | P17 | `VID_G2` | `VID_G2` |  |
| 16 | N17 | `VID_G3` | `VID_G3` |  |
| 17 | N14 | `VID_HS` | `VID_HS` |  |
| 18 | N13 | `VID_VS` | `VID_VS` |  |
| 19 | V20 | `SPARE2` | `ADC_SDA` **←** | CHECK |
| 20 | U20 | `SPARE3` | `ADC_SCL` **←** | CHECK |
| 21 | Y22 | `LED_CALIB` | `LED_CALIB` |  |
| 22 | Y21 | `LED_PIX` | `LED_PIX` |  |
| 23 | AB22 | `LED_27M` | `LED_27M` |  |
| 24 | AB21 | `LED_DDR_RST` | `LED_DDR_RST` |  |
| 25 | AA21 | `IN_CLK` | `IN_CLK` |  |
| 26 | AA20 | `IN_LOAD_N` | `IN_LOAD_N` |  |
| 27 | AB20 | `IN_DATA` | `IN_DATA` |  |
| 28 | AA19 | `OUT_CLK` | `Out_Clock` **←** | CHECK |
| 29 | AA18 | `SPARE4` | `ADC_A1` **←** | CHECK |
| 30 | AB18 | `SPARE5` | `ADC_A0` **←** | CHECK |
| 31 | Y19 | `OUT_DATA` | `Out_Data` |  |
| 32 | Y18 | `OUT_LATCH` | `Out_Latch` |  |
| 33 | T20 | `SERVICE_N` | `Out_Clear` **←** | CHECK |
| 34 | N15 | `OUT_EN_N` | `Out_En_N` |  |
| 35 | U18 | `AUD_PWM_L` | `AUD_PWM_L` |  |
| 36 | U17 | `AUD_PWM_R` | `AUD_PWM_R` |  |
| 37 | R16 | `MODE15_N` | `MODE_15N` |  |
| 38 | P15 | `SPARE6` | `(not connected)` |  |
| 39 | R14 | `SYNC_CSYNC_N` | `SYNC_CSYNC_N` |  |
| 40 | P14 | `SYNC_VSOFF_N` | `SYNC_VSOFF_N` |  |

Note pin 28 differs only in spelling (`OUT_CLK` in the doc, `Out_Clock` in the
schematic) — same signal, no action needed beyond picking one spelling.

## What matched without comment

Video ladder and sync (2/3/4, 6/7/8, 14/15/16, 17, 18), the four status LEDs
(21-24), the '165 input chain (25/26/27), the '595 output chain
(28/31/32/34), audio PWM (35/36), all three straps (37, 39, 40) and GND (12).
Architecture as designed: 6× 74AHC165 in, 2× 74HC595 → 2× ULN2803 out, plus the
THS7374 video path, ESD arrays and the RECOM regulators.
