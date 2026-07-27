# GowinSynthesis defect report — GW5AT-60, Gowin EDA V1.9.11.03

Five independent issues found in GowinSynthesis while porting a
well-established open-source VHDL video scaler to a GW5AT-60:

| # | Issue | Severity |
|---|---|---|
| 0 | **GowinSynthesis crashes** (SIGFPE, core dumped) during "Running inference" — V1.9.12.03 only; V1.9.11.03 builds the same sources cleanly | **Critical (regression)** |
| 1 | **Silent functional miscompile** of a Bresenham accumulator — builds clean, meets timing, wrong hardware | High |
| 2 | `PA2122` — the tool infers a block-RAM shift register and gives it a `WRITE_MODE` its own placer rejects | Medium (blocks PnR, workaround exists) |
| 3 | `CK3001` — invalid DSP cascade (`CASI`) configuration | Medium (blocks PnR, no workaround found) |
| 4 | Synthesis attributes silently ignored (`ramstyle`, `syn_ramstyle`, `syn_multstyle`) | Low, but directly causes #2 and makes #1 far harder to diagnose |

Defect 1 is the important one: **the design builds with no errors and no
warnings, meets timing with margin, and produces wrong hardware behaviour.**

All are reproducible with a single freely-redistributable source file.

---

## 1. Environment

| Item | Value |
|---|---|
| Tool A | Gowin EDA **V1.9.11.03 Education**, Linux tarball — defects 1-4 |
| Tool B | Gowin EDA **V1.9.12.03 Commercial** (node-locked licence), Linux tarball — **defect 0** |
| Flow | headless `gw_sh build.tcl` (GowinSynthesis, not Synplify) |
| Device | `GW5AT-LV60PG484AC1/I0`, `-device_version B` (GW5AT-60) |
| Board | Sipeed Tang Console 60K |
| Host | Ubuntu 24.04 x86-64 |

Relevant synthesis options:

```tcl
set_device GW5AT-LV60PG484AC1/I0 -device_version B
set_option -synthesis_tool gowinsynthesis
set_option -verilog_std sysv2017
set_option -vhdl_std vhd2008
set_option -place_option 2
set_option -rw_check_on_ram 0        # also reproduces with 1
```

## 2. Device under test

`ascal.vhd` — the "Avalon Scaler" by Temlib, the video scaler used by every
MiSTer FPGA core. ~3000 lines of portable VHDL, no vendor primitives.

* Upstream: <https://github.com/MiSTer-devel/Template_MiSTer/blob/master/sys/ascal.vhd>
* Version tested: `md5 1b17376e8bf19b5c3c96c42d8d588ae6`, 3033 lines
* **Licence:** its own header states *"This code can be freely distributed and
  used for any purpose"* — so it may be attached to this report and used as a
  test case without restriction.

Line numbers below refer to that **upstream, unmodified** file.

This code is a good regression test: it is known-good silicon on Intel Cyclone V
across hundreds of designs, it is pure portable VHDL, and it exercises inferred
memories, deep register pipelines, FSMs and integer arithmetic heavily.

---

## 3. Defect 0 — GowinSynthesis crashes (SIGFPE) in V1.9.12.03

**Severity: critical. This is a regression — V1.9.11.03 builds the identical
sources cleanly.** V1.9.12.03 cannot build this design at all.

```
Running device independent optimization ...
[10%] Optimizing Phase 0 completed
[15%] Optimizing Phase 1 completed
[25%] Optimizing Phase 2 completed
Running inference ...
Floating point exception (core dumped)          <-- exit status 136
```

The crash is always at the same stage ("Running inference"), with no error
message and no log entry.

### Reproduced with

| Input | V1.9.11.03 | V1.9.12.03 |
|---|---|---|
| upstream `ascal.vhd` + minimal wrapper (`build_defect2_PA2122.tcl`) | `ERROR (PA2122)` at PnR | **SIGFPE** |
| patched `ascal.vhd`, full design (`build_defect1_miscompile.tcl`) | builds clean, 0 violations | **SIGFPE** |
| same, with `MASK=0x07` (bicubic + polyphase removed) | builds clean | **SIGFPE** |

So it is not specific to the polyphase filters, not specific to our patches,
and not specific to the full design.

### Control — the environment is sound

A trivial design (a 12-deep 8-bit register pipeline) synthesises successfully
under V1.9.12.03 in the **identical** shell environment, same device, same
options:

```
GowinSynthesis finish        rc=0
```

Both versions require `LD_PRELOAD` of the system libfreetype on Ubuntu 24.04
(otherwise `gw_sh` aborts with `undefined symbol: FT_Done_MM_Var` before
printing anything); that is the only environment adjustment, and it is applied
identically to the passing control and the crashing runs.

### Note

Defect 3 (`CK3001`) reproduces on **both** versions, at a different instance
name (`u_ascal/u_ascal/n5541_o_0_s0` under V1.9.12.03).

---

## 4. Defect 1 — silent functional miscompile of the horizontal scaler

**Severity: high.** No error, no warning, timing met, wrong hardware.

### Symptom

The scaler upscales a 512×480 source into a 960×720 output window.
**Vertical scaling is pixel-perfect. Horizontal scaling is exactly 4× too
fast**, so the source is consumed in a quarter of the output width and the
image then repeats.

Measured on the real HDMI output with a capture card, one line of an
8-colour-bar test pattern (bar width should be 960/8 = 120 px):

```
window hmin=160 hmax=1119  (960 px)
  content 160..399  (240 px, bars 30 px)   then black    then a REPEAT at 672..911
window hmin=0    hmax=1279 (1280 px)
  content 0..319   (320 px, bars 40 px)   then black    then repeats at 512, 1024
```

Content width is always `512 × window / 4`.

### The logic that miscompiles

The horizontal position advance is a Bresenham accumulator in state `sCOPY`
(upstream **line 2234**):

```vhdl
WHEN sCOPY =>
   IF o_dshi=0 THEN
      dif_v:=(o_hacc_next - 2*o_hsize + (8*OHRESH)) MOD (8*OHRESH);
      IF dif_v>=4*OHRESH THEN
         o_hacc<=o_hacc_next;
         o_hacc_next<=o_hacc_next + 2*o_ihsize;
         hcarry_v:=false;
      ELSE
         o_hacc<=dif_v;
         o_hacc_next<=(dif_v + 2*o_ihsize + (4*OHRESH)) MOD (4*OHRESH);
         hcarry_v:=true;
      END IF;
      o_dcpt_inc <= '1';
   ELSE ...
```

with (upstream lines 320, 521, 1870):

```vhdl
CONSTANT OHRESH : natural := ohres_h(OHRES);          -- 4096 for OHRES=2304
SIGNAL   o_hacc,o_hacc_next,... : natural RANGE 0 TO 4*OHRESH-1;
VARIABLE dif_v                  : natural RANGE 0 TO 8*OHRESH-1;
```

`hcarry_v` decides whether to consume a source pixel. It should be true
`2*o_ihsize / 2*o_hsize` = 1024/1920 ≈ 53 % of cycles. On hardware it asserts
roughly 4× too often.

Note the **vertical** twin of this code is structurally
identical (upstream **line 2070**) but uses hardcoded moduli:

```vhdl
dif_v :=(o_vacc_next - 2*o_vsize + 16384) MOD 16384;
IF dif_v>=8192 THEN
```

**The vertical path works correctly on the same device, in the same build.**

### Evidence that the RTL and everything around it are correct

Two independent simulations of the *same source* render the pattern
pixel-exact — 8 bars of exactly the right width spanning the full window:

1. **GHDL behavioural simulation** (`ghdl -r`), identical source, identical
   output window, ideal Avalon memory: correct.
2. **GHDL's own synthesis engine, simulated gate-level** — a genuinely
   independent inference engine doing memory inference, FSM extraction and
   register mapping:

   ```sh
   ghdl synth --std=08 --out=verilog ascal_gw > ascal_gw_synth.v
   verilator --cc --exe --build -O3 --top-module synth_top ...
   ```

   Result (640-wide window, bars should be 640/8 = 80 px):

   ```
   bars at 81-158, 161-238, 241-318, 321-398, 401-478, 481-558, 561-638
   78-80 px each, spanning the full window        -> CORRECT
   ```

So the identical logic is correct under two independent synthesis paths and
wrong only under GowinSynthesis.

### Evidence that the inputs to this logic are correct on the Gowin hardware

Debug outputs were added to observe internal state on the running device and
read out over UART. **Every input to the failing decision matches simulation
exactly**; only the result differs:

| signal (sampled at the same output raster position) | GHDL sim | Gowin hardware |
|---|---|---|
| `i_himax` (detected input width − 1) | 511 | 511 ✔ |
| `i_hsize` (input window) | 512 | 512 ✔ |
| `o_ihsize` (input width, output domain) | 512 | 512 ✔ |
| `o_hsize` (output window) | 960 | 960 ✔ |
| `o_hmax` | 1119 | 1119 ✔ |
| `i_hdown` (downscale select) | 0 | 0 ✔ |
| `o_hburst` (bursts per line) | 1 | 1 ✔ |
| `{o_copylev, o_hbcpt}` (copy queue) | 0x04 | 0x04 ✔ |
| **`o_dcpt` (destination counter)** | **241** | **124 ✘** |

The external memory path was also verified independently on hardware: a
memtest driving the identical Avalon master and the same DDR3 controller with
an address-derived payload (so a wrong *address* fails as loudly as wrong
*data*) reports **zero mismatches over thousands of full write/verify passes**.

### Ruled out by experiment (each rebuilt and re-measured on hardware)

| Changed | Result |
|---|---|
| `OHRES` 2048 vs 2304 | no change |
| `FRAC` 4 vs 8 | no change |
| `N_BURST` 256 vs 2048 (changes RAM line stride 1536→2048 B) | no change |
| Interpolator mode 0 (nearest) vs 2 (sharp bilinear) | no change |
| Input auto-detect vs hard-coded input window (`iauto=0`) | no change |
| `dif_v` expression rewritten with explicit wide `unsigned` + mask | no change |
| `o_hacc*` **signals** converted to explicit `unsigned`, MOD → wraparound | no change |
| Forcing every pipeline out of RAM (see Defect 2) | no change |
| Avalon clock phase (0° vs 90° relative to output clock) | no change (sim) |

Timing is clean in every one of those builds: **0 setup violations, 0 hold
violations**, `hclk` ~83 MHz actual against 74.25 MHz required
(82.6-83.4 MHz depending on placement).

### What we would like

An explanation or fix for why this arithmetic/FSM produces different hardware
behaviour under GowinSynthesis than under two other synthesis engines.

Gate-level simulation of the Gowin netlist would have localised this in
minutes, but `impl/gwsynthesis/*.vg` is emitted `pragma protect` **encrypted**,
so it cannot be simulated or inspected. **Please consider providing an
unencrypted post-synthesis netlist option** — that alone would have avoided
most of this investigation.

---

## 5. Defect 2 — PA2122: inferred BSRAM shift register uses an unsupported WRITE_MODE

**Severity: medium.** Hard error, blocks PnR. Workaround exists.

Synthesis completes with no error; PnR then fails:

```
ERROR (PA2122) : Not support 'o_h_poly_phase_a.t1_o_h_poly_phase_a.t1_0_0_s'(SPX9)
                 WRITE_MODE = 2'b10, please change write mode
                 WRITE_MODE = 2'b00 or 2'b01.
```

GowinSynthesis packs plain register pipelines into SPX9/SP block-RAM shift
registers and then requests a write mode those primitives reject. **The tool
generates a configuration its own placer refuses.**

Triggering code — a 5-deep pipeline of a 40-bit record, upstream line 1027:

```vhdl
SIGNAL o_h_poly_phase_a, o_h_poly_phase_a2, o_h_poly_phase_a3,
       o_h_poly_phase_a4, o_h_poly_phase_a5 : poly_phase_t;
...
o_h_poly_phase_a2<=o_h_poly_phase_a;
o_h_poly_phase_a3<=o_h_poly_phase_a2;   -- etc.
```

The same error also appears for `o_hpixq` (upstream line 543), a 7-deep queue
of 4 pixels whose taps 6 and 8 are **read simultaneously** (upstream lines 2649, 2659) — something a
single-read-port RAM cannot provide:

```
ERROR (PA2122) : Not support 'o_hpixq[2][0].b_o_hpixq[2][0].b_0_0_s'(SP)
                 WRITE_MODE = 2'b10 ...
```

Note that restructuring `o_hpixq` into seven *discrete* signals made the tool
infer **block RAM** instead of distributed RAM — i.e. it infers memory from
plain register arrays quite aggressively.

**Workaround:** `ATTRIBUTE syn_srlstyle OF <signal> : SIGNAL IS "registers";`

---

## 6. Defect 3 — CK3001: incorrect DSP CASI configuration

**Severity: medium.** Hard error, blocks PnR. No workaround found.

Feeding GowinSynthesis a **Verilog** netlist of the same design (generated by
`ghdl synth --out=verilog`, and verified correct under verilator) fails with:

```
ERROR (CK3001) : The CASI configuration of 'u_ascal/u_ascal/mult_122505_s3' is incorrect
```

The tool maps the netlist's multipliers into cascaded DSP blocks and produces
an invalid cascade configuration. `(* syn_multstyle = "logic" *)` on the
module does not change the result (see Defect 4).

---

## 7. Defect 4 — synthesis attributes silently ignored

Not a crash, but it makes the other defects far harder to work around, and
costs users a great deal of time because failures are silent.

| Attribute | Honoured by GowinSynthesis V1.9.11.03? |
|---|---|
| `ramstyle` (Quartus spelling) | **No** — silently ignored |
| `syn_ramstyle` (Synplify spelling) | **No** — silently ignored |
| `syn_multstyle` | **No** — silently ignored |
| `syn_srlstyle` | Yes |
| `syn_keep`, `syn_preserve` | Yes |

"Silently ignored" is measured, not assumed: adding `syn_ramstyle
"registers"` to the affected signals changed **neither** the SSRAM count (21)
**nor** the register count (6483), byte for byte, in the resource report.

This matters because upstream guards these exact signals with
`ramstyle "logic"` (upstream lines 519, 544, 552) *specifically* to keep them
out of RAM:

```vhdl
ATTRIBUTE ramstyle OF o_hfrac : SIGNAL IS "logic"; -- avoid blockram shift register
ATTRIBUTE ramstyle OF o_hpixq : SIGNAL IS "logic"; -- avoid blockram shift register
ATTRIBUTE ramstyle OF o_div, o_dir : SIGNAL IS "logic"; -- avoid blockram shift register
```

Every one of those guards is inert on GowinSynthesis, which is what leads
directly to Defect 2.

**Request:** either honour `ramstyle`/`syn_ramstyle`, or emit a warning when
an unrecognised synthesis attribute is encountered. GHDL, by contrast, prints
`warning: unhandled attribute "syn_srlstyle"` — that one line would have saved
hours here.

---

## 8. Reproduction

Minimal case for Defects 2 and 4 — no board required, fails at PnR:

1. Take upstream `ascal.vhd` (md5 `1b17376e8bf19b5c3c96c42d8d588ae6`).
2. Instantiate it from any top with `OHRES=2304, IHRES=1024, N_DW=128,
   N_AW=25, N_BURST=2048, FRAC=8`.
3. Build for `GW5AT-LV60PG484AC1/I0 -device_version B` with the options in §1.
4. Observe `ERROR (PA2122)`.
5. Add `syn_srlstyle "registers"` to `o_hfrac`, `o_hpixq`, `o_div`, `o_dir`
   and the `o_[hv]_poly_phase_a*` pipelines; the build then completes.

**Defect 0 (V1.9.12.03 crash)** needs only steps 1-3 above: the same minimal
case that gives PA2122 on V1.9.11.03 crashes with SIGFPE on V1.9.12.03.

Defect 1 additionally needs the scaler driven with real video (512×480 in,
720p out) to observe the wrong picture; the internal-state table in §3 can be
reproduced by exporting `o_hacc` / `o_dcpt` to spare pins or a UART.

## 9. Contact / attachments available on request

* Complete buildable project (top level, constraints, `build.tcl`)
* The GHDL-synthesised Verilog netlist that behaves correctly
* Verilator harness reproducing the correct behaviour in ~2 seconds
* Capture-card images of the incorrect hardware output
