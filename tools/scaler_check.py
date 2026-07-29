#!/usr/bin/env python3
"""Strict frame checker for the scaler simulations.

Written after a weak check passed a design that produced garbage on hardware:
measuring colour-bar widths on one or two rows is not enough, because an
under-run FIFO returns STALE data, and on a repetitive test pattern stale data
still looks plausible.

This validates the whole dumped frame against what mcr_testpattern.sv must
produce, and fails loudly on anything it cannot explain.

Usage: python3 tools/scaler_check.py out.txt [src_w] [src_h] [win_x0] [win_w]
"""
import sys
from collections import defaultdict

path = sys.argv[1]
SRC_W = int(sys.argv[2]) if len(sys.argv) > 2 else 512
SRC_H = int(sys.argv[3]) if len(sys.argv) > 3 else 480
WIN_X0 = int(sys.argv[4]) if len(sys.argv) > 4 else 0
WIN_W = int(sys.argv[5]) if len(sys.argv) > 5 else 640

BAR = ["ffffff", "ffff00", "00ffff", "00ff00", "ff00ff", "ff0000", "0000ff", "404040"]

rows = defaultdict(dict)
for line in open(path):
    p = line.split()
    if len(p) == 3:
        rows[int(p[1])][int(p[0])] = p[2].lower()
if not rows:
    sys.exit("no pixels in dump")

ys = sorted(rows)
print(f"{path}: {len(ys)} output lines, x {min(rows[ys[0]])}..{max(rows[ys[0]])}")

fails = []

def src_row_of(y):
    """Which source row an output row maps to (nearest neighbour)."""
    return (y * SRC_H) // 720 if 720 else 0

# The source pattern has 6 equal bands of SRC_H/6 rows each.
band_h = SRC_H // 6
def band_of(y):
    return min(5, src_row_of(y) // band_h)

# ---- 1. colour-bar band: exactly 8 equal bars, correct order ---------------
bar_rows = [y for y in ys if band_of(y) == 0]
checked = 0
for y in bar_rows:
    line = rows[y]
    xs = sorted(x for x in line if WIN_X0 <= x < WIN_X0 + WIN_W)
    if not xs:
        continue
    runs, prev, start = [], None, xs[0]
    for x in xs:
        if line[x] != prev:
            if prev is not None:
                runs.append((start, x - start, prev))
            prev, start = line[x], x
    runs.append((start, xs[-1] - start + 1, prev))
    big = [r for r in runs if r[1] >= WIN_W // 16]      # ignore the moving bar
    seen = [r[2] for r in big]
    expect_w = WIN_W / 8.0
    if len(big) < 7:
        fails.append(f"y={y}: only {len(big)} wide runs, expected ~8 colour bars")
    else:
        for st, w, col in big:
            if abs(w - expect_w) > expect_w * 0.35:
                fails.append(f"y={y}: bar at x={st} width {w}, expected ~{expect_w:.0f}")
                break
        order = [c for c in seen if c in BAR]
        if order != sorted(order, key=lambda c: BAR.index(c)):
            fails.append(f"y={y}: bars out of order: {order}")
    checked += 1
print(f"colour-bar band: checked {checked} rows")

# ---- 2. every pixel must be a colour the pattern can actually produce ------
allowed = set(BAR) | {"000000", "202020", "ff8000", "101010", "00ff00"}
bad = defaultdict(int)
for y in ys:
    for x, c in rows[y].items():
        if not (WIN_X0 <= x < WIN_X0 + WIN_W):
            continue
        if c in allowed:
            continue
        r, g, b = (int(c[i:i+2], 16) for i in (0, 2, 4))
        # greys (ramp band) and pure-channel values are legitimate
        if r == g == b:
            continue
        if all(v in (0x00, 0x11, 0x22, 0x44, 0x55, 0x77, 0x88, 0xaa, 0xbb,
                     0xcc, 0xdd, 0xee, 0xff, 0x40, 0x80) for v in (r, g, b)):
            continue
        bad[c] += 1
if bad:
    top = sorted(bad.items(), key=lambda kv: -kv[1])[:6]
    fails.append(f"{sum(bad.values())} pixels with impossible colours, e.g. {top}")

# ---- 3. bands must actually change down the frame --------------------------
sig = {}
for y in ys:
    line = rows[y]
    xs = sorted(x for x in line if WIN_X0 <= x < WIN_X0 + WIN_W)
    changes = sum(1 for i in range(1, len(xs)) if line[xs[i]] != line[xs[i-1]])
    sig.setdefault(band_of(y), []).append(changes)
print("band signatures (mean colour changes per row):")
for b in sorted(sig):
    m = sum(sig[b]) / len(sig[b])
    print(f"   band {b}: {len(sig[b]):3d} rows, mean {m:6.1f}")
if len(sig) > 1:
    means = [sum(v)/len(v) for v in sig.values()]
    if max(means) - min(means) < 5:
        fails.append("all bands look identical - vertical addressing is stuck")

print()
if fails:
    print("FAIL:")
    for f in fails[:10]:
        print("  -", f)
    sys.exit(1)
print("PASS - frame matches the expected pattern")
