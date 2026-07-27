#!/usr/bin/env python3
"""Expected download-stream checksums for the TEMPORARY boot-load diagnostic.

Mirrors the rotate-then-XOR accumulator in mcr3_console60k_top.sv, which
checksums each region's bytes as the loader streams them. Compare against
beacon slots E5 (cpu), E4 (snd), E6 (bg1), E7 (bg2).

    python3 tools/ck.py tapper timber
"""
import sys
sys.path.insert(0, 'tools')
from merge_roms import collect

def ck(data):
    v = 0
    for b in data:
        v = ((v << 1) | (v >> 15)) & 0xFFFF   # rotate left 1
        v ^= b
    return v

def main(games):
    for g in games:
        r = collect(g)
        if not r:
            continue
        # mcr3 payload regions, padded exactly as make_pack_v2 does
        pad = lambda b, n: bytes(b) + b"\x00" * (n - len(b))
        # byte 0 of the payload lands in the RTL's reset branch, so it is
        # cleared rather than accumulated - skip it here to match.
        regs = [("cpu(E5)", pad(r["main"], 0x10000)[1:]),
                ("snd(E4)", pad(r["snd"], 0x4000)),
                ("bg1(E6)", pad(r["gfx1_1"], 0x4000)),
                ("bg2(E7)", pad(r["gfx1_2"], 0x4000))]
        print(f"{g}: " + "  ".join(f"{n}={ck(d):04X}" for n, d in regs))

if __name__ == "__main__":
    main(sys.argv[1:] or ["tapper", "timber"])
