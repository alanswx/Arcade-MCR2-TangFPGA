#!/usr/bin/env python3
"""
Phase-1 (sprites-first) SD pack builder for MCR-3 / Tapper.

The MCR-3 sprite ROM (128 KB) is too big for BSRAM, so it lives in the Tang
SDRAM module and must be streamed in from the SD card at boot. This builds a
minimal MCRPACK1 image whose single 128 KB slot IS the raw sprite blob (the 8
sprite planes concatenated in MRA order). rom_loader streams that slot as
dl_addr 0..0x1FFFF, and the mcr3 top swizzles it into SDRAM (MiSTer's
Arcade-MCR3 sprite write map). CPU/sound/bg stay baked in BSRAM this phase.

Phase 2 folds this into make_rompack.py once CPU/sound/bg also load from SD.

Pack layout (raw sectors, no filesystem; matches rom_loader.sv / make_rompack):
    sector 2048 (PACK_BASE)      header: "MCRPACK1" + slot_count(=1)
    sector 2049.. (PACK_BASE+1)  slot 0 payload = 128 KB sprite blob

Usage:
    python3 tools/make_sprite_pack.py            # -> tapper_sprite_pack.img
    # then dd to the card (see the printed instructions)
"""
import sys, os, zipfile

SECTOR       = 512
PACK_BASE    = 2048
SLOT_SECTORS = 256
SLOT_BYTES   = SLOT_SECTORS * SECTOR          # 128 KiB
MAGIC        = b"MCRPACK1"

# Tapper sprite planes, in MRA concatenation order (fg_1,fg_0,fg_3,fg_2,
# fg_5,fg_4,fg_7,fg_6) - identical to merge_roms.py's gfx2_files and the
# Arcade-MCR3 Tapper .mra. Each plane is 16 KB; 8 * 16 KB = 128 KB.
TAPPER_ZIP   = "roms/tapper.zip"
TAPPER_SPRITES = [
    "tapper_video_fg_1_a7_12-7-83.a7",
    "tapper_video_fg_0_a8_12-7-83.a8",
    "tapper_video_fg_3_a5_12-7-83.a5",
    "tapper_video_fg_2_a6_12-7-83.a6",
    "tapper_video_fg_5_a3_12-7-83.a3",
    "tapper_video_fg_4_a4_12-7-83.a4",
    "tapper_video_fg_7_a1_12-7-83.a1",
    "tapper_video_fg_6_a2_12-7-83.a2",
]

OUT_PATH = "tapper_sprite_pack.img"


def main(argv):
    if not os.path.exists(TAPPER_ZIP):
        sys.exit(f"error: {TAPPER_ZIP} not found (copy the MAME zip in by hand)")

    blob = bytearray()
    with zipfile.ZipFile(TAPPER_ZIP) as z:
        names = set(z.namelist())
        for fn in TAPPER_SPRITES:
            if fn not in names:
                sys.exit(f"error: {fn} missing from {TAPPER_ZIP}")
            blob += z.read(fn)

    if len(blob) != SLOT_BYTES:
        sys.exit(f"error: sprite blob is {len(blob)} bytes, expected {SLOT_BYTES} "
                 f"(128 KB) - check the plane list/sizes")

    # header sector
    hdr = bytearray(SECTOR)
    hdr[0:8] = MAGIC
    hdr[8]   = 1                                # one slot
    name = b"TAPPER"
    hdr[16:16+len(name)] = name                # slot 0 name (informational)

    with open(OUT_PATH, "wb") as f:
        f.write(hdr)
        f.write(blob)

    print(f"wrote {OUT_PATH}: {SECTOR + len(blob)} bytes "
          f"(1 header sector + {len(blob)//1024} KB sprite slot)")
    print()
    print("Write it to the card at sector 2048 (1 MiB in). Find the disk with")
    print("`diskutil list`, UNMOUNT it (do NOT erase), then:")
    print(f"  macOS: diskutil unmountDisk /dev/diskN")
    print(f"         sudo dd if={OUT_PATH} of=/dev/rdiskN bs=512 seek={PACK_BASE}")
    print(f"  Linux: sudo dd if={OUT_PATH} of=/dev/sdX bs=512 seek={PACK_BASE} conv=fsync")


if __name__ == "__main__":
    main(sys.argv[1:])
