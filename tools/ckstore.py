#!/usr/bin/env python3
"""Expected STORED-ROM checksums for the merged core's read-back audit.

The audit in mcr23_console60k_top.sv sweeps each ROM RAM through its idle
port B after a load and accumulates a rotate-then-XOR checksum IN ADDRESS
ORDER. That is deliberately different from the old stream checksums, which
measured what the loader delivered and were blind to three separate
"delivered correctly, stored wrongly" bugs.

    python3 tools/ckstore.py tapper timber shollow

Beacon slots: E5 cpu, E4 snd, E6 bg1, E7 bg2.
"""
import sys
sys.path.insert(0, 'tools')
from merge_roms import GAME_SPECS, collect

def ck(data):
    v = 0
    for b in data:
        v = ((v << 1) | (v >> 15)) & 0xFFFF
        v ^= b
    return v

def main(games):
    for g in games:
        spec = GAME_SPECS.get(g)
        if not spec:
            print(f"{g}: unknown"); continue
        r = collect(g, quiet=True)
        if not r:
            continue
        fam = spec.get("family", "mcr2")
        pad = lambda b, n: bytes(b) + b"\x00" * (n - len(b))
        # The RAMs are MCR-3-sized; MCR-2's bg planes are 8K in a 16K RAM, so
        # the upper half reads back as the zeros it was left as.
        bgsz = 0x4000 if fam == "mcr3" else 0x2000
        cpu = pad(r["main"], 0x10000)
        snd = pad(r["snd"], 0x4000)
        bg1 = pad(pad(r["gfx1_1"], bgsz), 0x4000)
        bg2 = pad(pad(r["gfx1_2"], bgsz), 0x4000)
        print(f"{g:9s} ({fam})  E5 cpu={ck(cpu):04X}  E4 snd={ck(snd):04X}  "
              f"E6 bg1={ck(bg1):04X}  E7 bg2={ck(bg2):04X}")

if __name__ == "__main__":
    main(sys.argv[1:] or ["tapper", "timber", "dotron", "shollow"])
