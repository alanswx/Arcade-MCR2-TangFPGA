# Shield ↔ Tang Console 60K: the J10 40-pin header (rev A freeze)

**This is the authoritative pin sheet for the shield PCB.** It supersedes
the draft net plan in `universal_mcr_shield_spec.md` §4b (which spread
video onto the PMOD sockets); the shield now connects to **J10 only** —
video, audio and all controls on one 40-pin header, both PMOD sockets left
free. Electrical details (optos, DAC values, buck) stay in the spec §3.

Ground rules:

- **Every J10 signal is 3.3 V LVCMOS (banks 6/7/8). Nothing is 5 V
  tolerant.** Cabinet-side 5 V never touches a header pin: inputs go
  through optos into the shift registers, sync/video leave through
  buffers/ladders.
- Pins marked **live** are driven by the bitstreams shipping today —
  video/audio works on the board the day it is soldered, with no gateware
  change. Pins marked **reserved** are allocated here and safe to route
  now; the expander RTL that drives them is a small, planned change
  (`TODO.md`). Until then they are high-Z from the FPGA.
- J10 is the 2×20, 2.54 mm header **nearest the PMOD sockets** (the other
  2×20, J9, is the SDRAM slot — the shield must leave it unobstructed).
  Odd/even pins face each other; anchor orientation electrically at
  **pin 11 = +5 V / pin 12 = GND**. Header is net-for-net identical on
  dock rev A (32001A) and rev C (32001C); ball map from the rev C SOM
  sheets (spec §4a/§6.2).

## 1. The 40 pins

| Pin | Ball | Net | Dir (FPGA) | Status | Function |
|---:|---|---|---|---|---|
| 1 | R19 | `VID_R0` | out | live | red bit 0 (= copy of bit 3; DAC may ignore) |
| 2 | P19 | `VID_R1` | out | live | red bit 1 → 2 kΩ |
| 3 | U21 | `VID_R2` | out | live | red bit 2 → 1 kΩ |
| 4 | T21 | `VID_R3` | out | live | red bit 3 (MSB) → 510 Ω |
| 5 | R17 | `VID_B0` | out | live | blue bit 0 (copy of bit 3) |
| 6 | P16 | `VID_B1` | out | live | blue bit 1 → 2 kΩ |
| 7 | T18 | `VID_B2` | out | live | blue bit 2 → 1 kΩ |
| 8 | R18 | `VID_B3` | out | live | blue bit 3 (MSB) → 510 Ω |
| 9 | W17 | `SPARE0` | — | spare | |
| 10 | V17 | `SPARE1` | — | spare | CSI_B config pin — needs the `-use_sspi_as_gpio` build option (already set) |
| 11 | — | **+5 V** | — | power | rail **out of** the dock; light loads only; do NOT back-feed (spec §6.1) |
| 12 | — | **GND** | — | power | star ground for the shield |
| 13 | W22 | `VID_G0` | out | live | green bit 0 (copy of bit 3) |
| 14 | W21 | `VID_G1` | out | live | green bit 1 → 2 kΩ |
| 15 | P17 | `VID_G2` | out | live | green bit 2 → 1 kΩ |
| 16 | N17 | `VID_G3` | out | live | green bit 3 (MSB) → 510 Ω |
| 17 | N14 | `VID_HS` | out | live | HSync, negative; carries **CSYNC** when strap pin 39 = GND |
| 18 | N13 | `VID_VS` | out | live | VSync, negative |
| 19 | V20 | `SPARE2` | — | spare | GCLK-capable |
| 20 | U20 | `SPARE3` | — | spare | GCLK-capable |
| 21 | Y22 | `LED_CALIB` | out | live | status LED: DDR3 trained (steady on = good) |
| 22 | Y21 | `LED_PIX` | out | live | status LED: pixel-clock heartbeat ~1 Hz |
| 23 | AB22 | `LED_27M` | out | live | status LED: 27 MHz heartbeat ~0.8 Hz |
| 24 | AB21 | `LED_DDR_RST` | out | live | status LED: DDR reset (steady OFF = good) |
| 25 | AA21 | `IN_CLK` | out | reserved | 74HC165 chain shift clock (≤2 MHz) |
| 26 | AA20 | `IN_LOAD_N` | out | reserved | 74HC165 SH/LD̄ — low pulse snapshots all inputs atomically |
| 27 | AB20 | `IN_DATA` | in | reserved | serial data from U7.QH (CSO_B config pin — option already set) |
| 28 | AA19 | `OUT_CLK` | out | reserved | 74HC595 chain shift clock (RDWR_B config pin — option already set) |
| 29 | AA18 | `SPARE4` | — | spare | EXIO0: 0 Ω-linked to DM0 net on the dock — verify before use |
| 30 | AB18 | `SPARE5` | — | spare | EXIO1: 0 Ω-linked to DM1 — same caveat |
| 31 | Y19 | `OUT_DATA` | out | reserved | serial data to U8.SER |
| 32 | Y18 | `OUT_LATCH` | out | reserved | 74HC595 RCLK — output register update |
| 33 | T20 | `SERVICE_N` | in | reserved | cabinet service button, direct (opens the OSD); shield pull-up to 3V3 |
| 34 | N15 | `OUT_EN_N` | out | reserved | 74HC595 OE̅. **Shield MUST pull up to 3V3** so meters/lamps stay off until the RTL drives it low |
| 35 | U18 | `AUD_PWM_L` | out | live | PWM audio left → RC filter → amp (spec §3) |
| 36 | U17 | `AUD_PWM_R` | out | live | PWM audio right (mono cabinets: use L only) |
| 37 | R16 | `MODE15_N` | in | live | **strap: GND = native 15 kHz** (cabinet), open = 31 kHz. Internal pull-up; solder-jumper on shield, closed by default |
| 38 | P15 | `SPARE6` | — | spare | |
| 39 | R14 | `SYNC_CSYNC_N` | in | live | strap: GND = composite sync on `VID_HS`; open = separate H/V (**default — real MCR monitors take separate H/V on Video-8/9**) |
| 40 | P14 | `SYNC_VSOFF_N` | in | live | strap: GND = hold VS inactive (single-sync RGBS); open = normal |

Sanity check for layout review: 20 live signals + 3 straps + 8 reserved +
7 spare + 2 power = 40 exactly; every ball above matches spec §4a's
schematic-verified table, and every **live** pin matches what the current
bitstreams already drive (`bench_wiring.md`).

## 2. Input chain — every switch in the cabinet on 3 pins

Seven 74HC165s (3.3 V supply — the shield regulates its own 3V3; J10 has
no 3V3 pin), daisy-chained `U1.QH → U2.SER … U6.QH → U7.SER`, with
`IN_DATA` reading `U7.QH`. Cabinet lines arrive through the optos (spec
§3), then 4.7 kΩ pull-ups to 3V3 into the '165 parallel inputs: idle
high, active low — the same polarity the SSIO saw.

`IN_LOAD_N` snapshots **all 56 bits in the same instant**, which is what
makes the 8-bit parallel spinner/trackball buses safe to serialize — no
tearing, by construction. A full scan at 2 MHz takes ~30 µs; the games
poll their inputs once per frame (16.7 ms), so the chain is ~500× faster
than anything the software can observe.

| Device | Input A…H (in order) | Covers |
|---|---|---|
| U1 | J2-1 P1 Up, J2-2 P1 Down, J2-3 P1 Left, J2-4 P1 Right, J2-5 P1 Btn1, J2-6 P1 Btn2, J3-1 Coin1, J3-2 Coin2 | player 1 + coins |
| U2 | J3-3 Start1, J3-4 Start2, J3-5 Tilt, J5-17 P2 Left, J5-18 P2 Right, J5-19 P2 Btn1, spare, spare | system + P2 switches |
| U3 | J4-1..7,9 = Opt X D0…D7 | dial/spinner/trackball-X bus (Tron, Kick, Kroozr, Wacko, DoT, Spy Hunter) |
| U4 | J5-1..6 = Opt Y D0…D5, J5-15 D6/P2 Up, J5-16 D7/P2 Down | trackball-Y / P2 stick |
| U5 | J6-1..8 = IP4 D0…D7 | aux port: Wacko cocktail aim, Two Tigers P2 dial, **Kroozr stick Y (needed even upright)**, DoT aux |
| U6 | SW1 positions 1…8 | game option DIPs = the core's IP3, verbatim (spec §7a) |
| U7 | SW2 positions 1…8 | system DIPs: menu enable, video mode, … (spec §7a) |

Serial arrival order (for the RTL, not the PCB): after a `IN_LOAD_N`
pulse, bits arrive **U7 first, input H first** — i.e. U7.H, U7.G, … U7.A,
U6.H, … down to U1.A last.

Wiring notes that matter to the layout:
- **Tron cocktail rule** (spec §7a): the J5-19 cocktail-fire line is ALSO
  ORed with SW1-8 in the FPGA — no extra wiring; just route each to its
  own chain bit as tabled.
- DIP switches connect position→GND with the same 4.7 kΩ pull-ups (closed
  switch reads 0); no optos needed for the two DIP banks.
- Unused inputs (U2 spares): tie high through the pull-up, do not float.

## 3. Output chain — meters and lamps on 4 pins

One 74HC595 (U8) to start; more daisy-chain onto `U8.QH'` later at zero
pin cost (Spy Hunter's lamp panel, MCR-3 era). Outputs feed a ULN2803
(cabinet 12 V loads, flyback diodes included in the ULN):

| U8 bit | QA…QH | Load |
|---|---|---|
| 0 | QA | Coin meter 1 |
| 1 | QB | Coin meter 2 |
| 2 | QC | Start 1 lamp |
| 3 | QD | Start 2 lamp |
| 4–7 | QE…QH | spare lamps (game-specific) |

`OUT_EN_N` (pin 34) **must have a pull-up on the shield**: it holds every
output off from power-on until the gateware takes control — no coin-meter
clicks or lamp flashes during the ~1 s of FPGA configuration.

## 4. Video, audio, straps (live today)

- **DAC:** 3-bit R2R per gun — MSB 510 Ω, 1 kΩ, 2 kΩ (bench-proven values,
  `bench_wiring.md`) summed into the monitor's 75 Ω ≈ 1 Vp-p. Bit 0 of
  each gun is just an MSB copy for 4-bit Pmods — leave it unconnected or
  pad for a future 4th resistor.
- **Sync:** `VID_HS`/`VID_VS` are 3.3 V, negative-going. Buffer to 5 V TTL
  for the cabinet (BC847 stage or 74HCT244 at 5 V, spec §3). Real MCR
  monitors want **separate H and V** (Video conn pins 8/9) — leave the
  pin-39/40 straps open; they exist for OSSC/RetroTink-style RGBS gear.
- **15 kHz:** close the pin-37 solder jumper for a cabinet build. Open =
  31 kHz for bench VGA monitors. HDMI works in both modes regardless.
- **Audio:** PWM out; RC low-pass (~15 kHz corner) → LM386 on the 12 V
  rail → speaker (spec §3). Mono cabinets use `AUD_PWM_L`.
- **Status LEDs (pins 21–24):** route to 4 small LEDs via 1 kΩ. They are
  the case-closed diagnostics: calib steady + pix/27M blinking + ddr_rst
  off = video pipeline healthy.

## 5. Does it cover every game? (the proof)

| Game | Needs beyond P1+coins+SW1 | Where it lands |
|---|---|---|
| Tron | aim dial (8-bit), cocktail P2 stick + fire | U3; U4 (J5-15/16) + U2 (J5-17/18) + J5-19‖SW1-8 rule |
| Domino Man | 4-way stick only | U1 |
| Satan's Hollow | P2 controls (cocktail) | U2/U4 |
| Wacko | trackball X+Y, aim stick, cocktail trackball | U3 + U4; aim on U5 (J6) |
| Kozmik Kroozr | dial + analogue stick X/Y | U3; stick X on U4, **stick Y on U5 (J6)** |
| Two Tigers | two dials + 4 buttons | U3 (P1 dial), U5 (P2 dial), U1/U2 buttons |
| MCR-1 Kick / Solar Fox (roadmap) | spinner | U3 |
| MCR-3 Tapper/Timber/Journey (roadmap) | P2 full stick, more buttons | U2/U4/U5 spares |
| MCR-3 DoT / Spy Hunter (roadmap) | aim/steering buses, lamps | U3/U4/U5; lamps on '595 chain (extend, zero pins) |

Every SSIO input port is reachable: IP0/IP1/IP2/IP4 from U1–U5, IP3 from
U6 (+the Tron OR rule), and the USB pads stay active in parallel for
bench/home use. Nothing about a new game can outgrow the header — worst
case adds a '165 or '595 to a chain.

## 6. Bring-up order for the board

1. Populate video DAC + sync buffer + audio + straps + LEDs only. Flash
   any current `bitstreams/console60k_*.fs` → full game on the cabinet
   monitor (15 kHz strap closed), sound, LEDs. No new gateware needed.
2. Populate optos + '165/'595 chains once the expander RTL lands
   (tracked in TODO.md; pins are frozen here, so no board spin).
3. USB pad and HDMI work throughout as the reference path.

## 7. Change control

- This table is the contract: `mcr2_console60k.cst`, the expander RTL, and
  `tools/generate_pcb.py` must follow it. If a pin must move, change THIS
  file first, in the same commit.
- Current CST already matches every **live** pin (they are today's bench
  assignments, deliberately). The **reserved** pins appear in the CST only
  when the expander RTL lands.
