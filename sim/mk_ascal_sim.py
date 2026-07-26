#!/usr/bin/env python3
"""Generate sim/ascal_sim.vhd from src/ascal/ascal.vhd for GHDL.

ascal computes a few `natural` expressions unconditionally and only CONSUMES
them under a guard that makes them non-negative.  Synthesis does not care (the
value just wraps in its 4-bit vector and is never read), and Quartus does no
runtime range checking, so upstream never notices.  GHDL checks every signal
assignment against its subtype and aborts:

    ghdl:error: bound check failure at ascal.vhd:2247

Each substitution below is behaviour-preserving for every value that is
actually read - it only pins the unread underflow case to 0.  The synthesis
source stays byte-identical to what the FPGA build uses, so the simulation
still tests the real thing.

Run from sim/:  python3 mk_ascal_sim.py
"""
import re
import sys
import pathlib

SRC = pathlib.Path(__file__).resolve().parent.parent / "src/ascal/ascal.vhd"
DST = pathlib.Path(__file__).resolve().parent / "ascal_sim.vhd"

# (description, exact source text, replacement)
SUBS = [
    (
        "o_pshift <= o_off(0)-1: sSHIFT is only entered when o_off(0)>0 "
        "(line 2241), so the o_off(0)=0 result is never read.",
        "\t\t\t\t\to_pshift<=o_off(0) -1;",
        "\t\t\t\t\tIF o_off(0)>0 THEN o_pshift<=o_off(0) -1; "
        "ELSE o_pshift<=0; END IF; -- SIM GUARD",
    ),
    (
        "o_pshift <= o_pshift-1 runs in the same cycle as the "
        "IF o_pshift=0 exit test, so it underflows on the final shift.",
        "\t\t\t\t\to_pshift<=o_pshift-1;",
        "\t\t\t\t\tIF o_pshift>0 THEN o_pshift<=o_pshift-1; END IF; -- SIM GUARD",
    ),
    (
        "o_ihsizem <= o_ihsize + o_off(0) - 2 underflows before the first "
        "line has been measured (o_ihsize still 0).",
        "\t\t\t\t\t\to_ihsizem<=o_ihsize + o_off(0) - 2;",
        "\t\t\t\t\t\tIF o_ihsize + o_off(0) >= 2 THEN "
        "o_ihsizem<=o_ihsize + o_off(0) - 2; "
        "ELSE o_ihsizem<=0; END IF; -- SIM GUARD",
    ),
]

text = SRC.read_text()
applied, missing = [], []
for desc, old, new in SUBS:
    if old in text:
        text = text.replace(old, new, 1)
        applied.append(desc)
    else:
        missing.append((desc, old))

banner = (
    "-- GENERATED FILE - do not edit. Produced by sim/mk_ascal_sim.py from\n"
    "-- src/ascal/ascal.vhd. Only difference: guards on unread `natural`\n"
    "-- underflows that GHDL's runtime range checks reject. See that script.\n"
)
DST.write_text(banner + text)

for d in applied:
    print("applied:", d.split(":")[0])
if missing:
    print("\nWARNING - these substitutions did not match (ascal.vhd changed?):")
    for d, old in missing:
        print("  ", d.split(":")[0], "\n     wanted:", repr(old))
    sys.exit(1)
print(f"\nwrote {DST} ({len(applied)}/{len(SUBS)} guards)")
