#!/usr/bin/env python3
"""Build the MCRPACK2 multi-family SD image (pack format v2).

One card serves every core family. Layout (all raw sectors, no filesystem):
  sector 2047        prefs "MCRPREF1" (NOT written by this tool - preserved)
  sector 2048        superblock: "MCRPACK2", ver, entry count, and 16-byte
                     MINI-ENTRIES read by the RTL (rom_loader.sv):
                     {family, type(0=ROM), slot, pad,
                      start_lba LE32, sector_count LE32, pad4}
  sector 2049..      rich 64-byte directory entries (tools/CRC only)
  sector 2112..      payloads, each family's download-address-map order

Per-family payload layouts (== each top's dl address map):
  mcr1 (family 0):  0x00000 CPU 32K | 0x08000 snd 16K | 0x10000 sprites 32K
                    | 0x18000 bg1 4K | 0x19000 bg2 4K            (100 KB)
  mcr2 (family 1):  0x00000 CPU 64K | 0x10000 snd 16K | 0x14000 gfx2 32K
                    | 0x1C000 bg1 8K | 0x1E000 bg2 8K            (128 KB)
  mcr3 (family 2):  0x00000 CPU 64K | 0x10000 snd 16K | 0x14000 bg1 16K
                    | 0x18000 bg2 16K | 0x1C000 sprites 128K     (240 KB)
  mcr3scroll (fam 3): as mcr3, then 0x3C000 char 4K | 0x40000 CSD 68000 32K
                    (288 KB - past 256 KB, which is why the merged top's
                    rom_loader runs a 19-bit dl_addr. The 12 KB gap at
                    0x3D000 keeps the CSD region on a clean dl_addr[18]
                    decode.)

Usage (repo root):  python3 tools/make_pack_v2.py   -> mcr_pack_v2.img
Write on the Mac:   python3 tools/write_pack_v2.py mcr_pack_v2.img /dev/rdiskN
"""
import struct, sys, zlib
sys.path.insert(0, 'tools')
from merge_roms import GAME_SPECS, collect

SECTOR, PACK_BASE, PAYLOAD_LBA = 512, 2048, 2112
FAM_ID = {"mcr1": 0, "mcr2": 1, "mcr3": 2, "mcr3scroll": 3}

def pad(b, n): return bytes(b) + b"\x00" * (n - len(b))

def blob(game, spec, r):
    fam = spec.get("family", "mcr2")
    if fam == "mcr1":
        return (pad(r["main"],0x8000) + pad(r["snd"],0x8000) +
                pad(r["gfx2"],0x8000) + pad(r["gfx1_1"],0x1000) +
                pad(r["gfx1_2"],0x1000))
    if fam == "mcr2":
        return (pad(r["main"],0x10000) + pad(r["snd"],0x4000) +
                pad(r["gfx2"],0x8000) + pad(r["gfx1_1"],0x2000) +
                pad(r["gfx1_2"],0x2000))
    if fam == "mcr3scroll":
        # Same first five regions as mcr3, then the two scroll-only ones. The
        # 0x3D000-0x3FFFF gap is deliberate: it puts the CSD ROM at 0x40000 so
        # the top decodes it as simply dl_addr[18].
        return (pad(r["main"],0x10000) + pad(r["snd"],0x4000) +
                pad(r["gfx1_1"],0x4000) + pad(r["gfx1_2"],0x4000) +
                pad(r["gfx2"],0x20000) +
                pad(r["chr"],0x1000) + b"\x00" * 0x3000 +
                pad(r["csd"],0x8000))
    # mcr3
    return (pad(r["main"],0x10000) + pad(r["snd"],0x4000) +
            pad(r["gfx1_1"],0x4000) + pad(r["gfx1_2"],0x4000) +
            pad(r["gfx2"],0x20000))

def main():
    minis, rich, payload = [], [], b""
    lba = PAYLOAD_LBA
    slots = {0: 0, 1: 0, 2: 0, 3: 0}
    # Slot numbers MUST match each family's OSD roster (osd.sv NAME0.. order),
    # NOT dict order: mcr1 OSD = kick(0), solarfox(1); mcr2 OSD = shollow(0),
    # tron(1), wacko(2), kroozr(3), twotiger(4), domino(5); mcr3 = tapper(0).
    # mcr3scroll OSD order = crater(0), spyhunt(1), turbotag(2), matching
    # mcr23s_console60k_top.sv NAME9/NAME10/NAME11.
    # NOTE the roster ORDER here is the pack slot order per family, and it
    # must match each top's OSD NAME list. The 15-game merged top
    # (mcr123s_console60k) lists mcr1 as kick(12), solarfox(13), kickman(14),
    # i.e. the same order as this list.
    ROSTER = ["kick", "solarfox", "kickman",
              "shollow", "tron", "wacko", "kroozr", "twotiger", "domino",
              "tapper", "timber", "dotron",
              "crater", "spyhunt", "turbotag"]
    for game in ROSTER:
        spec = GAME_SPECS[game]
        fam = FAM_ID[spec.get("family", "mcr2")]
        r = collect(game, quiet=True)
        if r is None:
            print(f"  skip {game} (no zip)"); continue
        b = blob(game, spec, r)
        nsec = (len(b) + SECTOR - 1) // SECTOR
        b = pad(b, nsec * SECTOR)
        slot = slots[fam]; slots[fam] += 1
        minis.append(struct.pack("<BBBBII4x", fam, 0, slot, 0, lba, nsec))
        rich.append(pad(struct.pack("<BB8sIII", fam, 0, game.encode()[:8],
                                    lba, nsec, zlib.crc32(b) & 0xFFFFFFFF), 64))
        print(f"  {game:10s} fam={fam} slot={slot} lba={lba} sectors={nsec}")
        payload += b
        lba += nsec
    assert len(minis) <= 31, "mini-entry table overflows the superblock"
    sb = pad(b"MCRPACK2" + bytes([2, len(minis)]) + b"\x00"*6 +
             b"".join(minis), SECTOR)
    dirs = pad(b"".join(rich), (PAYLOAD_LBA - PACK_BASE - 1) * SECTOR)
    img = sb + dirs + payload
    open("mcr_pack_v2.img", "wb").write(img)
    print(f"wrote mcr_pack_v2.img: {len(img)} bytes "
          f"({len(minis)} games, ends at LBA {lba})")
    print("Write at sector 2048 (Mac): "
          "python3 tools/write_pack_v2.py mcr_pack_v2.img /dev/rdiskN")

if __name__ == "__main__":
    main()
