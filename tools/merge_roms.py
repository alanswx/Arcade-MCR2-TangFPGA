"""Extract MCR game ROMs from MAME zips.

Two consumers share the game definitions below:
  * this script  -> BRAM INIT_FILE hex tables (one game baked per bitstream)
  * make_rompack -> SD card image (many games, selected at boot)

Run from the repo root:  python3 tools/merge_roms.py <game>
"""

import os
import sys
import zipfile

# Target directories where the Gowin compiler expects the hex files
# (INIT_FILE paths resolve relative to the instantiating source file's
# directory: the per-board tops use bare names next to themselves, and
# mcr2.vhd's gfx ROMs resolve against src/rtl/).
OUT_DIRS = [
    "mcr2_primer25k/src",
    "mcr2_console60k/src",
    "mcr2_console138k/src",
    "src/rtl",
]

# Board src dirs whose tops `include the generated game_config.vh
CONFIG_DIRS = [
    "mcr2_console60k/src",
    "mcr2_console138k/src",
]

# ---------------------------------------------------------------------------
# Game definitions. ROM member names are the old-MAME set names as found in
# the merged zips; CRCs were verified against MAME 0.265 for tron.
# ---------------------------------------------------------------------------
GAME_SPECS = {
    # Satan's Hollow (MCR2): 48KB CPU, 12KB->16KB sound, 16KB bg, 32KB sprites
    "shollow": dict(
        define="GAME_SHOLLOW",
        zip_path="roms/shollow.zip",
        main_files=["sh-pro.00", "sh-pro.01", "sh-pro.02",
                    "sh-pro.03", "sh-pro.04", "sh-pro.05"],
        snd_files=["sh-snd.01", "sh-snd.02", "sh-snd.03"],
        gfx1_1_file="sh-bg.00",
        gfx1_2_file="sh-bg.01",
        gfx2_files=["sh-fg.00", "sh-fg.01", "sh-fg.02", "sh-fg.03"],
        snd_pad_to=16 * 1024,
    ),
    # Tron (MCR2, "8/9" parent set): 48KB CPU, 12KB->16KB sound, 16KB bg,
    # 32KB sprites. Sprite order per MAME gfx2: vga(e1), vgb(dc1), vgc(cb1),
    # vgd(a1 - named vga.a1 in the old sets).
    "tron": dict(
        define="GAME_TRON",
        zip_path="roms/tron.zip",
        main_files=["pro0.d2", "scpu_pgb.d3", "scpu_pgc.d4",
                    "scpu_pgd.d5", "scpu_pge.d6", "scpu_pgf.d7"],
        snd_files=["ssi_0a.a7", "ssi_0b.a8", "ssi_0c.a9"],
        gfx1_1_file="scpu_bgg.g3",
        gfx1_2_file="scpu_bgh.g4",
        gfx2_files=["vga.e1", "vgb.dc1", "vgc.cb1", "vga.a1"],
        snd_pad_to=16 * 1024,
    ),
    # Domino Man (MCR2): 32KB CPU, 16KB sound, 16KB bg, 32KB sprites.
    # The smaller CPU frees the BSRAM needed to enable the background tiles.
    "domino": dict(
        define="GAME_DOMINO",
        zip_path="roms/domino.zip",
        main_files=["dmanpg0.bin", "dmanpg1.bin", "dmanpg2.bin", "dmanpg3.bin"],
        snd_files=["dm-a7.snd", "dm-a8.snd", "dm-a9.snd", "dm-a10.snd"],
        gfx1_1_file="dmanbg0.bin",
        gfx1_2_file="dmanbg1.bin",
        gfx2_files=["dmanfg0.bin", "dmanfg1.bin", "dmanfg2.bin", "dmanfg3.bin"],
    ),
}


def write_hex(filename, data):
    for out_dir in OUT_DIRS:
        os.makedirs(out_dir, exist_ok=True)
        path = os.path.join(out_dir, filename)
        with open(path, "w") as f:
            for b in data:
                f.write(f"{b:02x}\n")
        print(f"Wrote {path} ({len(data)} bytes)")


def collect(game, quiet=False):
    """Read a game's ROM zip and return its five regions as bytes.

    Returns None if the zip is missing.
    """
    spec = GAME_SPECS[game]
    zip_path = spec["zip_path"]
    if not quiet:
        print(f"Reading ROMs from {zip_path}...")
    if not os.path.exists(zip_path):
        print(f"Error: {zip_path} not found!")
        print("      (roms/ is gitignored - copy the MAME zip there by hand)")
        return None

    with zipfile.ZipFile(zip_path, "r") as z:
        # 1. Main CPU ROM (loaded at 0x0000, contiguous)
        main_data = bytearray()
        for fn in spec["main_files"]:
            main_data.extend(z.read(fn))

        # 2. Sound ROM (SSIO Z80), optionally zero-padded to a power of two
        snd_data = bytearray()
        for fn in spec["snd_files"]:
            snd_data.extend(z.read(fn))
        if spec.get("snd_pad_to"):
            snd_data.extend(b"\x00" * (spec["snd_pad_to"] - len(snd_data)))

        # 3. Background tile graphics (gfx1): two 8KB planes
        gfx1_1_data = z.read(spec["gfx1_1_file"])
        gfx1_2_data = z.read(spec["gfx1_2_file"])

        # 4. Sprite graphics (gfx2): 32KB
        gfx2_data = bytearray()
        for fn in spec["gfx2_files"]:
            gfx2_data.extend(z.read(fn))

    if not quiet:
        print(f"  main(cpu)={len(main_data)}  snd={len(snd_data)}  "
              f"gfx1_1={len(gfx1_1_data)}  gfx1_2={len(gfx1_2_data)}  "
              f"gfx2={len(gfx2_data)}")

    return {
        "main":   bytes(main_data),
        "snd":    bytes(snd_data),
        "gfx1_1": bytes(gfx1_1_data),
        "gfx1_2": bytes(gfx1_2_data),
        "gfx2":   bytes(gfx2_data),
    }


def write_game_config(game):
    define = GAME_SPECS[game]["define"]
    for out_dir in CONFIG_DIRS:
        path = os.path.join(out_dir, "game_config.vh")
        with open(path, "w") as f:
            f.write("// Auto-generated by tools/merge_roms.py -- do not edit.\n")
            f.write(f"// Selects the per-game input/DIP mapping for: {game}\n")
            f.write(f"`define {define}\n")
        print(f"Wrote {path} ({define})")


if __name__ == "__main__":
    game = sys.argv[1] if len(sys.argv) > 1 else "domino"
    if game not in GAME_SPECS:
        print(f"Unknown game '{game}'. Choices: {', '.join(GAME_SPECS)}")
        sys.exit(1)

    print(f"=== Building ROMs for: {game} ===")
    r = collect(game)
    if r is None:
        # Do NOT write game_config.vh: leaving it pointing at a game whose
        # ROM hex files were not generated produces a build that silently
        # mixes one game's code with another's input map.
        print("ROM generation FAILED - game_config.vh left unchanged.")
        sys.exit(1)

    write_hex("rom_main.hex", r["main"])
    write_hex("rom_snd.hex", r["snd"])
    write_hex("rom_cpu.hex", r["main"] + r["snd"])
    write_hex("rom_gfx1_1.hex", r["gfx1_1"])
    write_hex("rom_gfx1_2.hex", r["gfx1_2"])
    write_hex("rom_gfx2.hex", r["gfx2"])
    print("ROM generation and copying complete!")
    write_game_config(game)
