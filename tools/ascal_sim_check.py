#!/usr/bin/env python3
"""Measure sim/ascal_out.txt the same way the capture-card frames were measured.

The hardware fault is: within the 160..1119 output window, the full 8-bar
512-px source renders into 240 px, then 272 px of black, then renders AGAIN at
672..911 - i.e. horizontal rate 4x too fast, repeating every 512 output px,
while vertical is perfect.

This prints the content column runs for one output line so the sim can be
compared directly against those numbers.  If the sim shows a single run
spanning the whole window, ascal is being used correctly and the fault is a
GowinSynthesis miscompile.  If the sim reproduces the split, it is our
configuration and it can be fixed in ascal_gw.vhd.
"""
import sys
from collections import defaultdict

path = sys.argv[1] if len(sys.argv) > 1 else "sim/ascal_out.txt"

rows = defaultdict(dict)
header = None
with open(path) as f:
    for line in f:
        line = line.strip()
        if not line:
            continue
        if line.startswith("#"):
            header = line
            continue
        parts = line.split()
        if len(parts) != 3:
            continue
        x, y, rgb = int(parts[0]), int(parts[1]), parts[2]
        rows[y][x] = rgb

if header:
    print("ascal internal geometry:", header.lstrip("# "))
print(f"output lines captured: {len(rows)}")
if not rows:
    print("NO PIXELS - simulation produced no active output")
    sys.exit(1)

# pick a line inside the colour-bar band (top sixth of the image)
ys = sorted(rows)
probe = ys[len(ys) // 12] if len(ys) > 12 else ys[0]
line = rows[probe]
xs = sorted(line)
print(f"probing output line y={probe}, {len(xs)} active pixels, "
      f"x range {xs[0]}..{xs[-1]}")

# runs of non-black
nonblack = [x for x in xs if line[x] != "000000"]
if not nonblack:
    print("line is entirely black")
    sys.exit(1)
runs = []
start = prev = nonblack[0]
for x in nonblack[1:]:
    if x != prev + 1:
        runs.append((start, prev, prev - start + 1))
        start = x
    prev = x
runs.append((start, prev, prev - start + 1))
print(f"non-black runs (start, end, width): {runs}")

total = sum(r[2] for r in runs)
print(f"total non-black width: {total}")
print()
if len(runs) == 1 and total > 800:
    print("=> SINGLE full-width image. Sim does NOT reproduce the hardware "
          "fault => GowinSynthesis miscompile, not configuration.")
else:
    print("=> Sim REPRODUCES the split/compressed image => our ascal usage or "
          "configuration is wrong, fixable in ascal_gw.vhd.")

# colour-bar widths, to read the scale directly
changes = []
prevc = None
for x in xs:
    c = line[x]
    if c != prevc:
        changes.append((x, c))
        prevc = c
print(f"\ncolour transitions on this line ({len(changes)}): "
      f"{changes[:14]}{' ...' if len(changes) > 14 else ''}")
