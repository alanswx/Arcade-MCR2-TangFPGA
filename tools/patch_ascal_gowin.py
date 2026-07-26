#!/usr/bin/env python3
"""Regenerate src/ascal/ascal.vhd from upstream + the MINIMAL Gowin patch set.

Source: refs/Template_MiSTer/sys/ascal.vhd (byte-identical to Arcade-MCR3's
copy and to upstream master). Run from the repo root:

    python3 tools/patch_ascal_gowin.py

Only two kinds of change are applied, and each is here because it was proven
necessary by a build or a measurement:

 1. REQUIRED TO BUILD - `syn_srlstyle "registers"`.
    GowinSynthesis packs ascal's register pipelines into SP/SPX9 block-RAM
    shift registers and asks for WRITE_MODE=2'b10, which those primitives
    reject: PnR dies with PA2122 before placing anything. Upstream already
    guards the same signals for Quartus with `ramstyle "logic"`, but Gowin
    does not read that attribute (nor `syn_ramstyle` - verified: adding it
    changed neither SSRAM nor register counts, byte for byte).

 2. DEBUG TAPS - observability for the ongoing horizontal-scaling
    investigation. Pure observers; nothing else reads them.

DELIBERATELY NOT APPLIED (all tried, all measured, all reverted):
  * syn_keep / syn_preserve on the pipelines. These DO work where the style
    attributes are inert (SSRAM fell 21->15, ~450 registers moved out of
    RAM), but they changed NOTHING about the fault - and the set included
    o_hsv/o_vsv/o_dev/o_pev/o_end, ascal's output SYNC and DE pipelines.
    Blocking duplication/retiming on those coincided with the HDMI link
    starting to drop sync on a real monitor. Zero benefit, real risk: out.
  * Splitting o_hpixq into discrete signals - made Gowin infer BSRAM instead
    (PA2122 returned) and did not change the picture.
  * Explicit-width unsigned arithmetic in the sCOPY horizontal accumulator -
    the 15-vs-16-bit intermediate theory. Built clean, changed nothing.
  * Converting o_hacc/o_hacc_ini/o_hacc_next from `natural RANGE 0 TO
    4*OHRESH-1` to explicit `unsigned(NBH4-1 DOWNTO 0)`, so every MOD by
    4*/8*OHRESH became plain wraparound and the `>= 4*OHRESH` carry test
    became a single borrow bit. Semantically bit-identical, analysed clean
    under GHDL, built clean (0 setup/0 hold, hclk 82.1 MHz) - and o_dcpt
    stayed at 124 against the sim's 241 with the picture unchanged. So the
    miscompile is NOT in how the accumulator arithmetic is expressed.
"""
import pathlib
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
SRC = ROOT / "refs/Template_MiSTer/sys/ascal.vhd"
DST = ROOT / "src/ascal/ascal.vhd"

if not SRC.exists():
    sys.exit(f"upstream not found: {SRC} (refs/ is gitignored - re-clone it)")

s = SRC.read_text()
applied = []


def sub(old, new, why):
    global s
    if old not in s:
        sys.exit(f"PATTERN NOT FOUND ({why}):\n{old!r}")
    s = s.replace(old, new, 1)
    applied.append(why)


# --- 1. syn_srlstyle declaration -------------------------------------------
sub(
    "\tATTRIBUTE ramstyle : string;\n",
    "\tATTRIBUTE ramstyle : string;\n"
    "\t-- GOWIN PORT PATCH: GowinSynthesis does not read Quartus' `ramstyle`,\n"
    "\t-- so every \"avoid blockram shift register\" guard below is inert there\n"
    "\t-- and the pipeline is packed into SP/SPX9 block RAM with an unsupported\n"
    "\t-- WRITE_MODE (PnR error PA2122). syn_srlstyle is the spelling Gowin\n"
    "\t-- honours. Both are kept so the file stays valid for MiSTer/Quartus.\n"
    "\tATTRIBUTE syn_srlstyle : string;\n",
    "syn_srlstyle declaration",
)

# --- 2. mirror each upstream `ramstyle "logic"` guard ------------------------
for sig in ["o_hfrac", "o_hpixq", "o_div, o_dir"]:
    old = '\tATTRIBUTE ramstyle OF %s : SIGNAL IS "logic";' % sig
    sub(old, old + '\n\tATTRIBUTE syn_srlstyle OF %s : SIGNAL IS "registers";' % sig,
        f"syn_srlstyle on {sig}")

# --- 3. the polyphase pipelines (upstream does not guard these at all) -------
old_poly = "\tSIGNAL poly_wr_mode : std_logic_vector(2 DOWNTO 0);"
guards = ""
for blk in ["o_h_poly_phase_a", "o_v_poly_phase_a"]:
    guards += ('\tATTRIBUTE syn_srlstyle OF %s, %s2,\n'
               '\t                          %s3, %s4,\n'
               '\t                          %s5 : SIGNAL IS "registers";\n'
               % (blk, blk, blk, blk, blk))
sub(old_poly,
    "\t-- GOWIN PORT PATCH: 5-deep 40-bit pipelines with no intermediate taps;\n"
    "\t-- Gowin packs them into SPX9 block RAM and PA2122 kills the build.\n"
    + guards + old_poly,
    "syn_srlstyle on the polyphase pipelines")

# --- 4. debug taps ----------------------------------------------------------
sub(
    "\t\t------------------------------------\n\t\treset_na           : IN    std_logic\n\t\t);",
    "\t\t------------------------------------\n"
    "\t\t-- GOWIN DEBUG PATCH: observers for the horizontal-scaling\n"
    "\t\t-- investigation. Read out over the UART beacon; nothing else uses\n"
    "\t\t-- them. Delete together with the assignments at the end of the\n"
    "\t\t-- architecture once the fault is understood.\n"
    "\t\tdbg_o_hacc         : OUT   std_logic_vector(15 DOWNTO 0);\n"
    "\t\tdbg_o_dcpt         : OUT   std_logic_vector(11 DOWNTO 0);\n"
    "\t\tdbg_i_himax        : OUT   natural RANGE 0 TO 4095;\n"
    "\t\tdbg_i_hsize        : OUT   natural RANGE 0 TO 4095;\n"
    "\t\tdbg_o_ihsize       : OUT   natural RANGE 0 TO 4095;\n"
    "\t\tdbg_i_hdown        : OUT   std_logic;\n\n"
    "\t\t------------------------------------\n\t\treset_na           : IN    std_logic\n\t\t);",
    "debug ports",
)

sub(
    "\t----------------------------------------------------------------------------\nEND ARCHITECTURE rtl;",
    "\t----------------------------------------------------------------------------\n"
    "\t-- GOWIN DEBUG PATCH (see the entity note above).\n"
    "\tdbg_o_hacc   <= std_logic_vector(to_unsigned(o_hacc,16));\n"
    "\tdbg_o_dcpt   <= std_logic_vector(to_unsigned(o_dcptv(14),12));\n"
    "\tdbg_i_himax  <= i_himax;\n"
    "\tdbg_i_hsize  <= o_hburst;                -- bursts per input line\n"
    "\tdbg_o_ihsize <= o_copylev*64 + o_hbcpt;  -- {copy queue level, burst idx}\n"
    "\tdbg_i_hdown  <= i_hdown;\n\n"
    "\t----------------------------------------------------------------------------\nEND ARCHITECTURE rtl;",
    "debug tap assignments",
)


DST.write_text(s)
for a in applied:
    print("  applied:", a)
print(f"\nwrote {DST.relative_to(ROOT)} ({len(applied)} patches)")
