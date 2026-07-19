# FPGA Board Comparison & Custom Shield BOM

This document provides a cost and feature comparison of the various Sipeed Tang FPGA board options for building the Bally Midway MCR arcade core, followed by a Bill of Materials (BOM) estimate for the custom **Option A Shield** (Universal MCR Cabinet Interface).

---

## 1. FPGA Board & Hardware Setup Comparison

Here is a comparison of the primary hardware architectures we evaluated for running the MCR arcade core, including where the **iCEPi Zero** fits in.

| Specification / Option | Tang Primer 25K (V1 On-Chip) | Tang Primer 25K (V2 SDRAM) | iCEPi Zero (Lattice ECP5) | Tang Console 60K | Tang Console 138K |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **FPGA Chip** | GW5A-LV25 | GW5A-LV25 | Lattice ECP5U-25F | GW5A-LV60 | GW5AST-LV138 |
| **Logic Cells (LUT)** | 23,040 | 23,040 | 24,000 | 60,000 | 138,240 |
| **On-Chip Block RAM** | 126 KB (56 blocks) | 126 KB (56 blocks) | 112 KB | ~320 KB (140+ blocks) | 765 KB (340 blocks) |
| **External Memory** | None | 64Mbit SDRAM Card | **32MB SDRAM** (Onboard) | **512MB DDR3** (On SOM) | **1GB DDR3** (On SOM) |
| **Free GPIO Pins** | **26** (40-Pin) + **8** (PMOD) | **8** (PMOD 1 only) | **28** (40-Pin Header) | **92** (76 GPIO + 16 PMOD) | **92** (76 GPIO + 16 PMOD) |
| **MCR Game Support** | Partial (No Playfield Gfx) | Full MCR-1/2/3 Games | Full MCR-1/2/3 Games | Full MCR-1/2/3 Games | Full MCR-1/2/3 Games |
| **Video & Audio Path** | On-board parallel | HDMI -> VGA/Audio Dongle | GPDI Port / Parallel | Onboard Native HDMI & DAC | Onboard Native HDMI & DAC |
| **Pin Congestion** | Low | High (Pmod sharing) | Low (SDRAM is onboard) | Zero | Zero |
| **Toolchain** | Gowin EDA | Gowin EDA | **Open Source** (yosys/nextpnr) | Gowin EDA | Gowin EDA |
| **Estimated Price (Kit)**| **~$29.00** [1] | **~$39.00** (Kit + SDRAM) [2] | **$79.00** [3] | **$69.00** [4] | **$99.00** [5] |
| **Extra Modules Needed** | PMOD HDMI ($5) | PMOD HDMI ($5) + Dongle ($5) | GPDI-to-HDMI Cable ($5) | None | None |
| **Total Hardware Cost**  | **~$34.00** | **~$49.00** | **$84.00** | **$69.00** | **$99.00** |

### Recommendations:
* **Best Value / Easiest Integration: Tang Console 60K ($69)** [4]
  Because the DDR3 memory is built directly into the System-on-Module (SOM), it does not block the carrier board's pins. With **92 free GPIO pins**, native HDMI, and onboard audio DACs, you do not need shift registers or HDMI converters. It has more than enough on-chip block RAM (320KB) to run any MCR game without memory limits.
* **Cheapest Entry Point: Tang Primer 25K V1 ($34)** [1]
  Great for initial desk testing and cabinet control/audio wiring verification. However, playfield background graphics are disabled to fit the block RAM budget.

---

## 2. Custom Shield Bill of Materials (BOM) Estimate

Below is the estimated Bill of Materials to manufacture and assemble the custom **Option A Interface Shield** (Universal MCR Cabinet Interface).

### Option A.1: Parallel Shield (For Tang Primer 25K V1, or Tang Console 60K/138K)
This PCB is a passive shield that routes video, audio, and inputs in parallel. It is simple, highly reliable, and uses no active serial ICs.

> **Update (2026-07):** the shipping Console 60K design adds **two 74HC165
> shift registers** (~$0.30) for the 16 configuration DIP switches. Cabinet
> I/O stays parallel/opto-isolated; only the DIPs are serial, which keeps the
> J9 SDRAM slot free for the large MCR-3 ROM sets. See
> `docs/universal_mcr_shield_spec.md` §7.

| Item | Component Description | Designator | Qty | Unit Cost | Total Cost | Source Example |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | **Custom PCB (2-Layer)** | Board | 1 | $2.00 | $2.00 | JLCPCB / PCBWay (qty 5 minimum) |
| 2 | **opto-isolators (4-channel)** | U1, U2, U3 | 3 | $0.40 | $1.20 | TLP281-4 (SMD) |
| 3 | **LM386 Mono Audio Amp** | U4 | 1 | $0.35 | $0.35 | LM386 (DIP or SOIC) |
| 4 | **5V Step-Down Buck Regulator** | VR1 | 1 | $1.20 | $1.20 | LM2596 Module or MP1584EN |
| 5 | **R2R Resistor Arrays (10k/20k)** | RN1, RN2, RN3 | 3 | $0.20 | $0.60 | 9-pin SIP Resistor Network |
| 6 | **Discrete Resistors & Caps** | R1-R20, C1-C10 | 1 | $1.00 | $1.00 | 0805 SMD Resistors/Capacitors |
| 7 | **BC847 NPN Transistor** (Sync) | Q1, Q2 | 2 | $0.05 | $0.10 | BC847 (SOT-23) |
| 8 | **MCR Connector Headers** | J2, J3, J4, J5 | 4 | $0.50 | $2.00 | 2.54mm Pin Headers / Molex KK |
| 9 | **Female Pin Headers (to Dock)** | JP1, JP2 | 2 | $0.40 | $0.80 | 40-Pin and PMOD sockets |
| **Total**| | | | | **~$9.25** | *Excludes shipping (~$15 from China)* |

---

### Option A.2: Serial Shift-Register Shield (For Tang Primer 25K V2 + SDRAM)
If using the SDRAM card on the Tang Primer 25K, you must read the buttons serially due to pin starvation. This shield adds shift registers to read controls over 3 PMOD pins.

| Item | Component Description | Designator | Qty | Unit Cost | Total Cost | Source Example |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | **Custom PCB (2-Layer)** | Board | 1 | $2.00 | $2.00 | JLCPCB |
| 2 | **74HC165 8-bit Shift Register**| U1, U2 | 2 | $0.15 | $0.30 | 74HC165 (SOIC-16) |
| 3 | **opto-isolators (4-channel)** | U3, U4 | 2 | $0.40 | $0.80 | TLP281-4 |
| 4 | **5V Step-Down Buck Regulator** | VR1 | 1 | $1.20 | $1.20 | MP1584EN Buck Board |
| 5 | **Discrete Resistors & Caps** | R1-R20, C1-C10 | 1 | $1.00 | $1.00 | 0805 SMD |
| 6 | **MCR Connector Headers** | J2, J3, J4, J5 | 4 | $0.50 | $2.00 | 2.54mm Molex KK |
| 7 | **Female Pin Headers (to Dock)** | JP1 | 1 | $0.40 | $0.40 | 12-pin PMOD socket |
| **Total**| | | | | **~$7.70** | *Excludes shipping* |

---

## 3. Reference Pricing & Purchase Links

*   **[1] Tang Primer 25K Dock Kit:** ~$29.00 on the [Sipeed AliExpress Store](https://www.aliexpress.com/item/1005006093452411.html).
*   **[2] Tang SDRAM Expansion Module (64Mbit):** ~$10.00 on the [Sipeed AliExpress Store](https://www.aliexpress.com/item/1005006122648719.html) or Youyeetoo.
*   **[3] iCEPi Zero (Lattice ECP5):** $79.00 retail on [Elecrow Store](https://www.elecrow.com/icepi-zero-fpga-development-board.html) or [Mouser Electronics](https://www.mouser.com/ProductDetail/Crowd-Supply/CS-ICEPIZERO-01). Educational discount price is $65.00 via developer contact on the [iCEPi Zero GitHub Page](https://github.com/cyao7878/icepi-zero).
*   **[4] Tang Console 60K (SOM + Dock Bundle):** ~$69.00 on the [Sipeed AliExpress Store](https://www.aliexpress.com/item/1005007421111111.html).
*   **[5] Tang Console 138K (SOM + Dock Bundle):** ~$99.00 on the [Sipeed AliExpress Store](https://www.aliexpress.com/item/1005007421111111.html).
