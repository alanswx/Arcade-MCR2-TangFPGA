#!/usr/bin/env python3
"""Expected STORED-ROM checksums for the merged core's read-back audit.

    python3 tools/ckstore.py tapper                  # 15-game core (default)
    python3 tools/ckstore.py --cpu64 --snd tapper    # older 9/12-game cores

WHICH CORE YOU ARE COMPARING AGAINST MATTERS (changed 2026-07-30):
  * mcr123s_console60k (15 games) trims the shared CPU ROM to 0xE000 - the
    largest real program in the roster - so the audit sweeps 0xE000 bytes, not
    64K. It also runs the sound ROM from SDRAM, which has no port B to sweep,
    so **beacon E4 reads 0000 BY DESIGN** and carries no information.
  * mcr23_console60k / mcr23s_console60k sweep the full 64K CPU ROM and do have
    a real E4. Pass --cpu64 --snd for those.

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

def main(games, cpu_len=0xE000, want_snd=False):
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
        bgsz = 0x4000 if fam in ("mcr3", "mcr3scroll") else \
               0x1000 if fam == "mcr1" else 0x2000
        cpu = pad(r["main"], 0x10000)[:cpu_len]
        bg1 = pad(pad(r["gfx1_1"], bgsz), 0x4000)
        bg2 = pad(pad(r["gfx1_2"], bgsz), 0x4000)
        snd_txt = (f"E4 snd={ck(pad(r['snd'], 0x4000)):04X}  " if want_snd
                   else "E4 snd=0000(SDRAM)  ")
        print(f"{g:9s} ({fam})  E5 cpu={ck(cpu):04X}  {snd_txt}"
              f"E6 bg1={ck(bg1):04X}  E7 bg2={ck(bg2):04X}")

if __name__ == "__main__":
    args = sys.argv[1:]
    cpu_len = 0x10000 if "--cpu64" in args else 0xE000
    want_snd = "--snd" in args
    games = [a for a in args if not a.startswith("--")]
    main(games or ["tapper", "timber", "dotron", "shollow", "crater",
                   "spyhunt", "turbotag", "kick"], cpu_len, want_snd)
