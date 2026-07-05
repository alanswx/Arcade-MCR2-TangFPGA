# Midway MCR2 Arcade Core for Sipeed Tang Primer 25K

This repository contains the standalone, hardcoded port of Bally Midway's MCR2 arcade core (supporting games like *Satan's Hollow*, *Tron*, etc.) for the **Sipeed Tang Primer 25K (Gowin GW5A-LV25MG)** development board.

Version 1 hardcodes **Satan's Hollow** directly into the internal block RAM (BSRAM) of the FPGA, allowing it to boot instantly upon power-up without needing external SDRAM or MicroSD configuration.

---

## 1. Project Features
* **Standalone Execution:** Runs entirely on the GW5A-25's internal Block RAM (BSRAM) and Distributed RAM (SSRAM/LUTs).
* **Concurrent Video Output:** Generates upscaled DVI/HDMI (480p @ 60Hz) for desk debugging and raw 15kHz digital RGBS + CSync for mounting inside an original arcade cabinet.
* **PWM Stereo Audio:** Delta-Sigma DACs modulate 16-bit sound samples to 1-bit high-frequency PWM outputs.

---

## 2. Compilation Instructions

1. Launch the **Gowin IDE** on your PC.
2. Select **Open Project** and select `mcr2_primer25k.gprj`.
3. Verify that all source files under `src/` are listed and enabled.
4. Click **Run All** in the IDE tool bar. This executes Synthesis, Mapping, and Place & Route to output `mcr2_primer25k.fs` under the `impl/pnr/` directory.
5. Alternatively, via command line using the Gowin EDA shell (`gw_sh`):
   ```bash
   # Set library path (macOS only)
   export DYLD_LIBRARY_PATH=/Applications/GowinIDE.app/Contents/Resources/Gowin_EDA/IDE/lib
   # Run compile script
   /Applications/GowinIDE.app/Contents/Resources/Gowin_EDA/IDE/bin/gw_sh build.tcl
   ```
6. Open **Gowin Programmer**, connect the board's JTAG, scan, and program the `.fs` bitstream file to the FPGA.

---

## 3. Hardware Wiring Guide

All cabinet interfaces are mapped to the **PMOD 1** header and the **40-pin SDRAM connector** on the Tang Primer 25K Dock baseboard. 

### A. PMOD 1 Header: Cabinet Controls (Buttons/Joystick)
Wired inputs have internal **Pull-Ups enabled** on the FPGA. Wire arcade button switches to bridge these pins directly to the board's **Ground (GND)** when pressed:

| PMOD 1 Pin | FPGA Pin | Signal Name | Cabinet Button Function |
| :--- | :--- | :--- | :--- |
| **Pin 1** | A11 | `btn_shield` | P1 Shield Button / Button 2 |
| **Pin 2** | E11 | `btn_fire` | P1 Fire Button / Button 1 |
| **Pin 3** | K11 | `btn_right` | P1 Joystick Right |
| **Pin 4** | L5 | `btn_left` | P1 Joystick Left |
| **Pin 7** | A10 | `btn_tilt` | Cabinet Tilt Switch |
| **Pin 8** | E10 | `btn_service`| Cabinet Service Switch |
| **Pin 9** | L11 | `btn_coin` | Coin 1 Switch |
| **Pin 10**| K5 | `btn_start` | P1 Start Button |
| **GND** | GND | Ground | Connect to the common chain of all buttons |
| **VCC** | 3.3V | VCC | (Do not connect for button switches) |

---

### B. 40-Pin Header: Cabinet Video (RGBS) & Audio
Raw 15kHz digital video outputs, syncs, and PWM audio are routed to the 40-pin header (which is unused since SDRAM is disabled):

| 40-Pin Header Pin | FPGA Pin | Signal Name | Function |
| :--- | :--- | :--- | :--- |
| **Pin 15** | K2 | `cab_r[0]` | Red Digital LSB (Bit 0) |
| **Pin 16** | K1 | `cab_r[1]` | Red Digital Middle (Bit 1) |
| **Pin 17** | L1 | `cab_r[2]` | Red Digital MSB (Bit 2) |
| **Pin 18** | L2 | `cab_g[0]` | Green Digital LSB (Bit 0) |
| **Pin 19** | K4 | `cab_g[1]` | Green Digital Middle (Bit 1) |
| **Pin 20** | J4 | `cab_g[2]` | Green Digital MSB (Bit 2) |
| **Pin 21** | G1 | `cab_b[0]` | Blue Digital LSB (Bit 0) |
| **Pin 22** | G2 | `cab_b[1]` | Blue Digital Middle (Bit 1) |
| **Pin 23** | E1 | `cab_b[2]` | Blue Digital MSB (Bit 2) |
| **Pin 24** | A1 | `cab_hs` | Horizontal Sync |
| **Pin 25** | F2 | `cab_vs` | Vertical Sync |
| **Pin 26** | F1 | `cab_csync` | Composite Sync (CSync) |
| **Pin 28** | B2 | `audio_l` | Left Audio PWM Output |
| **Pin 29** | C2 | `audio_r` | Right Audio PWM Output |
| **GND** | GND | Ground | Common Ground |

---

## 4. Connecting to an Analog Arcade Monitor

Arcade CRT monitors (like Wells Gardner or Electrohome) expect **analog RGB** signals ($0\text{V} - 0.7\text{V}$) terminated into $75\ \Omega$ load, and composite sync.

### Resistor Ladder DAC (R2R) Diagram
Build three identical weighted-resistor networks (one for Red, one for Green, one for Blue) to scale the digital 3-bit outputs to analog levels:

```text
                 Resistors
FPGA Pin (MSB)   [Bit 2] ---[ 1k Ohm ]---+
FPGA Pin         [Bit 1] ---[ 2k Ohm ]---+----> Analog Color Output (to CRT)
FPGA Pin (LSB)   [Bit 0] ---[ 4k Ohm ]---+
```

*For absolute accuracy, use $1.0\text{k}\ \Omega$, $2.0\text{k}\ \Omega$, and $3.9\text{k}\ \Omega$ (or $4.02\text{k}\ \Omega$) metal film resistors.*

### Composite Sync (CSync) Wiring
Arcade monitors expect a composite sync signal. The core produces digital `cab_csync` (3.3V).
* Route the `cab_csync` pin (Pin 26) through a **$100\ \Omega$ to $330\ \Omega$ resistor** directly to the composite sync pin of your chassis. This limits the current and matches standard TTL sync inputs.

---

## 5. Connecting Audio
The `audio_l` and `audio_r` signals are 1-bit high-frequency PWM outputs. 
* To feed an audio amplifier, connect the pin through a simple low-pass RC filter to extract the analog waveform:

```text
FPGA Audio Pin -----[ 270 Ohm ]---+-----> Analog Out (to Amp)
                                  |
                                 === 100nF Capacitor
                                  |
                                 GND
```
