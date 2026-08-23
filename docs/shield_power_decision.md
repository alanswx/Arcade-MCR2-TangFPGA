# Powering the Tang Console 60K from the MCR shield

**Question:** can the shield power the console through a header pin, or do we
have to use a USB-C port — and does USB-C need a PD/negotiation chip?

**Answer:** feed **J10 pin 11 (+5 V)** and **pin 12 (GND)**, with a series
ideal-diode or Schottky on the shield. No USB connector, no PD chip, no CC
resistors. USB-C would also work and needs no PD chip either, but it is the
worse choice for this board.

This note exists so the reasoning can be **checked before boards are ordered**.
Everything below cites the sheet it came from. Section 5 lists what I did not
verify — please read that one first if you are short of time, because that is
where the risk actually lives.

---

## 1. What I looked at

All references are to `docs/Tang_Mega_60K_Console_32001C__Schematics.pdf`
(rev C / V32001C, 17 sheets, dated 2025-04-24) unless stated.

| Sheet | Title | What I took from it |
|---|---|---|
| **3/17** | SYS POWER | the OR-ing chain, U13, VBUS_OUT, ferrites FB4/FB5, where +5 V and VBUS_SOM come from |
| **6/17** | SOM_BTB2 | confirms `VBUS_SOM` lands on the SOM connector J2 **pin 93** |
| **7/17** | PERIPHERALS | USB-C receptacle J17: VBUS path, fuse FU1, CC1/CC2 termination |
| **8/17** | EX CONN | J10 pinout: **pin 11 = +5 V, pin 12 = GND** (J9 is the same rail) |

I also read `MCR_prototype_PCB_netflist.net` for the shield side (U24
R-78B5.0-2.0, U25 R-78B3.3-2.0, +12 V entering on J1.18 through ferrites
L1/L2).

I did **not** open rev A (32001A). The shield spec §6 item 2 records that
J10's header pinout is net-for-net identical between rev A and rev C, but I
have not personally re-checked that for the power pins.

## 2. The path, traced

From sheet 3, the dock builds its rails like this:

```
 debug USB 5 V ─┐ (Q6  AP3101A + Q5A/Q5B ideal-diode pair)
 soft  USB 5 V ─┼─► U13 LP5300B6F ─► VBUS_OUT ─┬─ FB5 ─► VBUS_SOM ─► SOM (J2.93)
 battery 4.2 V ─┘ (Q3  Si2101A   + Q19A/Q19B)  └─ FB4 ─► +5 V ─► J10.11, J9.11
                                                        └─► U2 LP3219AB5F ─► +3V3
```

Two things follow, and they are the whole basis of the recommendation:

1. **+5 V on J10 pin 11 and the SOM's supply are the same node**, separated
   only by two ferrites (FB4 and FB5, both `UPZ2012U221-3R0TF`). So 5 V
   injected at pin 11 reaches the SOM by FB4 → VBUS_OUT → FB5. There is no
   fuse, switch or diode in that path.
2. **Pin 11 sits downstream of the OR-ing.** Anything injected there bypasses
   U13 and the ideal-diode FETs entirely.

## 3. Why a pin beats the USB-C port here

From sheet 7, the soft USB-C receptacle J17:

```
VBUS (A4/B9) ── "Power Input Only" ──► FU1 0805L125/6NR ──► 5V_USB_S
CC1  (A5) ──► R45 5.1K 1% ──► GND
CC2  (B5) ──► R47 5.1K 1% ──► GND
```

**On the PD question: no chip is needed, by either route.** The port is a plain
sink — 5.1 kohm Rd on both CC lines, no PD controller anywhere on the sheet. It
never negotiates; it takes whatever is on VBUS. Plain regulated 5 V is enough.
(If we *did* use USB-C we should still fit Rp pull-ups on CC1/CC2 —
56k/22k/10k to 5 V for default/1.5 A/3 A — for correctness rather than
function, and we must **not** fit 5.1 kohm pull-downs, which is the sink role.)

**The reason to prefer the pin is FU1.** An 0805L125 is a **1.25 A hold** PTC,
and it is in series with VBUS on that port. Compare the two routes:

| | J10 pin 11 | USB-C soft port |
|---|---|---|
| Series protection in path | none (two ferrites) | **1.25 A PTC** |
| Path current rating | ~3 A, if the ferrite reading is right | 1.25 A hold |
| Extra hardware on shield | 1 diode | USB-C plug, cable, 2 resistors |
| Programming port | stays free | occupied by the power feed |
| Bypasses dock OR-ing/OVP | **yes** — see below | no |

## 4. The one real objection to pin 11, and the fix

Injecting at pin 11 means **our supply is in parallel with anything plugged
into a USB-C port, with no arbitration between them** — and USB-C *will* get
plugged in for programming. That is a genuine hazard, not a theoretical one,
and it is the reason I initially recommended against pin 11.

**Fix: put an ideal-diode controller (or a Schottky) in series with the
shield's 5 V feed to pin 11.** Then whichever supply is higher wins cleanly
instead of the two fighting. An ideal diode is preferable to a Schottky
because it avoids the 0.3–0.4 V drop, which matters on a 5 V rail feeding a
buck converter, but either removes the hazard.

With that part fitted, the objection is answered and pin 11 is simply the
better route.

**Wiring, in full:**

```
shield +5 V ──► ideal diode / Schottky ──► J10 pin 11
shield GND  ─────────────────────────────► J10 pin 12
```

Nothing else. No USB connector, no CC resistors, no PD chip.

## 5. What I did NOT verify — please check these

This is the important section. Each of these could invalidate part of the
above, and none of them is expensive to check.

1. **The ferrite current rating.** I read `UPZ2012U221-3R0TF` as 220 ohm at
   100 MHz, **3.0 A**. I did not pull the datasheet. If the "3R0" field means
   something else, the headroom argument weakens. **Please confirm from the
   part datasheet.** Both FB4 and FB5 are in our path.
2. **Actual console current draw.** I have never measured it. My claim that
   the console fits inside 1.25 A is an *inference* — it normally runs from
   that fused USB-C port, so it must — not a measurement. If the console is
   usually powered from the **debug** port instead, and that port has a larger
   fuse, the inference collapses. Worth 10 minutes with a USB power meter.
3. **The debug USB port's sheet.** I did not locate it, so I do not know its
   fuse rating or whether it differs from the soft port. It is a third option
   I could not evaluate.
4. **U13 (LP5300B6F) reverse behaviour.** Injecting at pin 11 back-drives its
   output. The OR-ing FETs upstream should block current reaching the USB
   connectors and the battery charger, but I did not check U13's datasheet for
   reverse-conduction or whether it objects to being back-fed. **This is the
   one I would most want a second opinion on**, because it is the only place
   where "it works on the bench" and "it is safe long-term" might differ.
5. **Rev A.** Checked rev C only (see §1).
6. **Our own 5 V budget.** U24 is an R-78B5.0-**2.0** — 2 A — and it must
   carry the console *and* the shield's logic. Probably fine, not generous. If
   the BOM is not frozen, a 3 A part costs little.
7. **Power sequencing.** With +12 V present the shield powers the console as
   soon as it is connected. Worth deciding whether anything should come up
   before the FPGA configures — in particular `OUT_EN_N` (pin 34) and
   `OUT_CLEAR_N` (pin 33) both want pull-ups so lamps and coin meters stay off
   until the RTL drives them.

## 6. How to check my work quickly

1. Open sheet 8, find J10, confirm **pin 11 = +5 V, pin 12 = GND**.
2. Open sheet 3, follow **+5 V** left through **FB4** to **VBUS_OUT**, then
   right through **FB5** to **VBUS_SOM**. That is the whole claim in §2.
3. Open sheet 6, confirm **VBUS_SOM** is on **J2 pin 93** — i.e. it really is
   what feeds the SOM.
4. Open sheet 7, confirm **FU1** is in series with USB-C VBUS and that CC1/CC2
   go only to 5.1 kohm resistors — no PD chip.
5. Look up FU1 (`0805L125`) and the ferrites (`UPZ2012U221-3R0TF`).

If steps 1–4 read the way I have described them, the recommendation follows.
If step 5 disagrees with my numbers, tell me and I will redo the comparison.

## 7. A note on how this changed

I first recommended **against** pin 11 and in favour of USB-C, on the OR-ing
argument alone. That was before I had traced sheet 7 and found FU1. Two things
changed my mind: the 1.25 A PTC on the USB route, and realising the OR-ing
objection is answerable with a single series diode on our side. I am recording
the reversal rather than quietly presenting the second answer, because if the
first reasoning was persuasive it is worth knowing exactly which fact undid it.
