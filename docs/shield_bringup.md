# MCR shield: bring-up of the fabricated board (2026-10)

**Start here for anything on the physical shield.** This covers the board
that came back from the fab, what it actually is (traced from Mitch's final
files, not from our earlier plans), how to mate the console safely, and how
to check every input and output with the bitstream that supports it.

| Doc | Use it for |
|---|---|
| **this file** | the as-fabbed board, the RTL bit map, the bring-up sequence |
| `shield_j10_pinout.md` | the 40-pin J0/J10 contract (ball per pin) |
| `shield_wiring.md` | cabinet connectors and harness meaning per game |
| `pcb_review_2026-08-25.md` | the pre-fab review history (all items closed) |
| `shield_power_decision.md` | why the shield feeds the console on pin 11 |

## 1. What was fabricated

**Mitch's "September 8 Version" (`60363fa`, pushed 2026-09-10).** That
commit is the board that was built. Relative to the last reviewed upload
(`d5f0787`, 2026-08-28) it changes no connectivity:

- The `.kicad_pcb` pad nets are **identical** to `MCR_prototype_PCB.net`
  (183 nets, the same 143 parts, no net added or moved).
- Parts were swapped to LCSC stock for assembly: DIP switches →
  DSIC08LHGET, L1/L2 → FAUL1360-3R3MT, U24/U25 → **Mornsun K7805-2000R3 /
  K7803-2000R3** (same 2 A rating and pinout as the R-78B parts), SW3 →
  PTS645SM43.
- **The five M4 mounting holes were deleted.** The photos confirm the board
  has none. Mount it with care (see §6).
- `fabrication-toolkit-options.json` was added: the board was ordered
  through the KiCad JLC fabrication toolkit, which writes its own output.
  **The gerbers and drill files committed in `MCR_prototype_PCB/` are the
  2026-08-28 set and are stale.** They still contain the 4.3 mm holes. Do
  not re-order from them. Regenerate from the `.kicad_pcb` instead.
- `MCR_prototype_PCB.net` still shows the pre-swap part values. Its
  connectivity is current.

Photos, 2026-10-22 (`docs/shield_photos/`):

| File | Shows |
|---|---|
| `2026-10-22_shield_top_unpowered.jpg` | assembled top side, before the MTA headers |
| `2026-10-22_shield_powered_rails_ok.jpg` | headers fitted, **+12 V / +3.3 V / +5 V OK LEDs lit**, no console |
| `2026-10-22_console_seated_on_J0.jpg` | Tang Console (rev 32001C) seated face-up on J0 |

## 2. Before the console goes on: safety checks

The shield **powers the console** through J0 pin 11 (D4, 1N5822). If the
console sits on J0 rotated 180°, J0 pin 11 (+5 V) lands on console pin 30
and pin 12 (GND) lands on pin 29. Those are FPGA balls AB18 and AA18, so
the mistake costs an FPGA. Check this once, with **nothing powered**:

1. **Shield alone, powered from +12 V:** TP2 = 3.3 V, TP3 = 5.0 V; J0
   pin 11 to pin 12 ≈ **4.6 V** (5 V minus the Schottky drop). *(The rail
   LEDs in the photo say the first two are fine. Measure pin 11 too.)*
2. **Power off. Seat the console on J0, both unpowered.** Then beep:
   - shield **TP4 (GND) ↔ the console's USB-C shell**: must beep;
   - shield **D4 cathode (J0-11) ↔ console GND**: must **NOT** beep.
     It reads the console's 5 V rail, which is tens of ohms or more, not a
     short.
   If TP4 does not reach the console's ground, the console is rotated.
   Stop.
3. **First power-up with the console fitted:** +12 V only, **no USB-C**.
   The console's power LED should light from the shield alone. After that,
   USB-C for programming may stay plugged in alongside: D4 keeps the two
   5 V sources from fighting (`shield_power_decision.md` §4).
4. **Still unverified, measure when convenient:** the console's current
   draw from the shield (D4 drop at load), and J1's .156" +12 V/GND pin
   positions against the MCR power-supply manual before you plug in a real
   cabinet harness (`pcb_review_2026-08-25.md` item 9).

## 3. The as-built bit map (the RTL contract)

Traced pad-by-pad from the fabricated netlist, 2026-10-22. It is
implemented in `src/rtl/shield_io.sv` and simulated against a model of this
exact wiring (`sim/shield_io/tb_shield_io.sv`). Where it disagrees with
the older tables in `shield_j10_pinout.md` §3 (seven '165s, per-function
wiring), **this map is the board**.

### Input chain: six 74AHC165s, 48 bits

Chain order U1 → U2 → U3 → U4 → U6 → U7 → `IN_DATA` (U1.SER = GND). U5 is
an SRV05-4 ESD array, not a '165. Each harness line passes a 4.7 kΩ
pull-up to +5 V, a 1 kΩ series resistor and an SRV05 clamp; there are no
filter caps (Mitch removed them, see the 08-27 re-check).

| '165 | Byte | Wired from | Bit order |
|---|---|---|---|
| U1 | **IP0** | J4 pins 1–8 (coin1, coin2, start1, start2, button, tilt, service, test) | **reversed**: J4-1 → H … J4-8 → A, so IP0 = bit-reverse(U1) |
| U2 | **IP1** | J4 pins 10–13, 15–18 (D0–D7) | D0 → A … D7 → H |
| U3 | **IP2** | J5 pins 1–8 | J5-1 → A … J5-8 → H |
| U4 | **IP4** | J6 pins 1–7, 9 | J6-1 → A … J6-7 → G, J6-9 (2P fire) → H |
| U6 | **SW1** | DIP positions 1–8, closed = 0 | pos 1 → A |
| U7 | **SW2** | DIP positions 1–8, closed = 0 | pos 1 → A |

SSIO bit k of every port is the connector's k-th data line, idle = 1, so
`shield_io` hands the cores raw SSIO bytes. The per-game meaning lives in
the cores and in `docs/MCR Series Pinouts.html`.

### Output chain: two 74HC595s → ULN2803s

| Bit | '595 | ULN → connector | Driven with |
|---|---|---|---|
| 0 | U8.QA | U10.O1 → **J5-21** (coin meter 1; J5-20 is the +12 V return side) | ~100 ms pulse per coin-door coin |
| 1–6 | U8.QB–QG | U10.O2 NC, O3–O5 = "Start 1/2/3 Lamp" labels **with no connector**, O6 NC | 0 |
| 7 | U8.QH | U10.O8 NC | Journey `tape_run` (bodge point for a deck/MP3 module) |
| 8–15 | U9.QA–QH | U11 → **J5-10…17** (MD0–3, ST0/SEL0, ST1/SEL1, ARD/FL0, SEL/FL1) | the running core's SSIO `output_4` (MCR-3 / MCR3Scroll), else 0 |

`OUT_EN_N` is held high (outputs off) until the first full word has been
shifted and latched. `OUT_CLEAR_N` is driven high permanently.

**Open question on J5-10…17 polarity.** A ULN2803 *sinks* when its bit is
1, so this inverts a TTL-level line. Spy Hunter's SEL (J5-17) selects
wheel vs gas on the cabinet's control board. Confirm on a real cabinet
whether the original SSIO drove these lines active-high TTL before
trusting them, and invert `sh_out4` in the top if it did.

## 4. The bitstream

**Only `mcr123s_console60k` (the 15-game core, the power-on default)
drives the shield chains.** Older bitstreams still give video, audio,
straps and LEDs on the shield, but leave pins 9 and 25–34 high-Z and put
video bit 0 on pins 1/5 (harmless into the audio RC filters).

Built 2026-10-22 (macOS, V1.9.11.03): 0 errors, no PA1019, no undeclared
symbols, every clock TNS 0.000, clk_sys Fmax 43.1 MHz, 117/118 BSRAM, 75 %
logic. Staged as **`bitstreams/console60k_mcr123s_shield.fs`** (md5
`4517c040…`). It is not flashed and not yet run on hardware. To make it the
power-on default:

```sh
openFPGALoader -b tangconsole -f --verify bitstreams/console60k_mcr123s_shield.fs
```

(retry until the verify is clean. Drop `-f --verify` for a volatile
test load.)

What the shield build adds:

| J10 | Signal | Behaviour |
|---|---|---|
| 1 / 5 | `audio_l2` / `audio_r2` | second PWM pair, **a copy of the front L/R mix** (no core produces DoT's rear channels separately yet) |
| 9 | `service_n` | SW3. **Hold 0.5 s → game-select OSD.** Press again while it is open → exit (B) |
| 25–28, 31–34 | chain pins | 1.25 MHz scan, ~40 µs per frame of 48 in + 16 out bits |
| 19, 20, 29, 30 | ADS7830 | **not driven** (no I²C master yet; only CH0, the J3 volume pot, is wired) |
| 37 / 39 / 40 | JP1 / JP2 / JP3 | 15 kHz / composite sync / VS off, fitted = GND = on (unchanged) |

**SW2 position 1 = cabinet mode.**

- **Open (default): pad mode.** Games use the USB pad and their compiled
  DIP defaults, exactly as before. The coin door (IP0) is ANDed in, so a
  cabinet's coin, start, tilt and test switches work alongside the pad.
- **Closed: cabinet mode.** IP0, IP1, IP2 and IP4 come **verbatim from
  J4/J5/J6**, and IP3 (the game DIPs) comes from **SW1**. The pad is used
  only for the OSD. With no harness plugged in, every input reads idle.

In either mode, **the OSD can be driven from the cabinet**: Service (hold)
opens it, Start 1 moves down, Start 2 moves up, the J4-5 button loads, and
Service exits. All harness inputs are masked to idle while it is open.
SW2 positions 2–8 are unassigned.

With **no shield fitted**, `IN_DATA`'s FPGA pull-up reads all-ones: every
input idle and cabinet mode off. So the same bitstream remains correct on a
bare console.

## 5. Bring-up sequence

Do the checks in §2 first. Then, with `mcr123s_console60k` flashed:

1. **Video:** VGA monitor on the DE-15, JP1 open (31 kHz). Then a 15 kHz
   monitor on J2_RGBS_Out1 with JP1 fitted. JP4 selects the THS7374 filter:
   put it on **+5 V = bypass**, because the filter's 9.5 MHz corner smears
   20 MHz pixels. Don't load the DE-15 and J2 at once: they share one 75 Ω
   per gun, so the level halves.
2. **Status LEDs D35–D38:** calib steady, pix and 27M blinking, ddr_rst off
   = video pipeline healthy.
3. **Audio:** line level on J3 (L1/R1) and J3_DOT1 (all four channels)
   into the cabinet's external amplifier.
4. **Inputs over USB serial** (`screen /dev/tty.usbserial-* 115200`). The
   beacon rotates 16 diagnostic slots, about 0.84 s each. The shield's are
   the lines whose `q` field reads `E8`–`EB`, with the value in `x`:

   | q | x = |
   |---|---|
   | E8 | `{IP0, IP1}` |
   | E9 | `{IP2, IP4}` |
   | EA | `{SW1, SW2}` |
   | EB | bit 15 = cabinet mode, bit 14 = Service held |

   Idle reads `FFFF` everywhere. Flip SW1/SW2 one position at a time:
   position n clears bit n-1 of its byte. Then ground each J4/J5/J6 input
   to the harness GND (J4-9, J5-9/18) and check the bit drops. The bit map
   in §3 says which one to expect. A whole byte stuck at `FF` with the
   others working means a broken cascade at that device. Every byte stuck
   at `FF` means a dead IN_CLK, IN_LOAD_N or IN_DATA (TP5/TP6 carry the
   first two).
5. **OSD from the cabinet:** hold SW3 and the menu opens.
6. **Outputs:** with a meter or LED from J5-21 to +12 V, drop a coin and
   expect one ~100 ms sink pulse. J5-10…17 follow `output_4` while an MCR-3
   or MCR3Scroll game runs. See the polarity question in §3.
7. **Cabinet mode:** close SW2-1, set SW1 to the game's manual DIP
   settings, and plug the harness in.

## 6. Known board gaps (prototype, fix on a respin)

- **No mounting holes** (deleted in the Sept 8 version). The 267 × 199 mm
  board hangs off its connectors.
- Start 1/2/3 lamp nets (U10.O3–O5) reach no connector. Meter 2 (J5-22)
  and the Kick button light (J5-23) are not provided.
- Only ADS7830 CH0 (the volume pot) is wired. Spy Hunter / Max RPM pots
  need CH1–CH7 and an I²C master in RTL.
- DE-15 and J2 share one 75 Ω series resistor per gun.
- J1 power-pin positions are still unverified against the manual.
- R18 (a 75 Ω output resistor) carries a capacitor footprint in the
  schematic. It is the same 0805 land, so electrically harmless.
