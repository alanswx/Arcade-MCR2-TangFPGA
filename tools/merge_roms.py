"""Extract MCR game ROMs from MAME zips.

Two consumers share the game definitions below:
  * this script  -> BRAM INIT_FILE hex tables (one game baked per bitstream)
  * make_rompack -> SD card image (many games, selected at boot)

Run from the repo root:  python3 tools/merge_roms.py <game>
"""

import os
import sys
import zipfile

# Target directories where the Gowin compiler expects the hex files, keyed by
# game family. INIT_FILE paths resolve relative to the instantiating source
# file's directory: the per-board tops use bare names next to themselves, and
# the core .vhd's gfx ROMs resolve against src/rtl/. src/rtl is shared, so its
# gfx hex reflects the LAST merge_roms run - regenerate before each build (as
# rebuild_all.sh does). Splitting by family keeps an MCR-1 build from
# clobbering the MCR-2 boards' game_config.vh and vice versa.
HEX_DIRS = {
    "mcr1": ["mcr1_console60k/src", "src/rtl"],
    "mcr2": ["mcr2_primer25k/src", "mcr2_console60k/src",
             "mcr2_console138k/src", "src/rtl"],
    "mcr3": ["mcr3_console60k/src", "src/rtl"],
    # MCR3Scroll has no baked board: it only ever exists inside the merged
    # 60K bitstream, which carries no ROM data at all (licensing). So there is
    # nowhere to write hex to, and writing to src/rtl would clobber whichever
    # baked family the 25K last used.
    "mcr3scroll": [],
}

# Board src dirs whose tops `include the generated game_config.vh, by family
CONFIG_DIRS = {
    "mcr1": ["mcr1_console60k/src"],
    "mcr2": ["mcr2_console60k/src", "mcr2_console138k/src"],
    "mcr3": ["mcr3_console60k/src"],
    "mcr3scroll": [],      # merged board only - no GAME_DEFAULT to write
}

# ---------------------------------------------------------------------------
# Game definitions. ROM member names are the old-MAME set names as found in
# the merged zips; CRCs were verified against MAME 0.265 for tron.
# ---------------------------------------------------------------------------
# The MCR-3 sprite region is a fixed 128 KB split into four 32 KB bitplane
# slots by the fetch engine; see the plane assembly in collect().
SPRITE_REGION = 0x20000

GAME_SPECS = {
    # --- MCR-1 (90009 video board; core src/rtl/mcr1.vhd) ------------------
    # Different download/ROM map from MCR-2: CPU is 4KB ROMs padded to 32KB,
    # sound 16KB, sprites 32KB (8KB x4), bg two 4KB planes. The per-region
    # hex output is family-agnostic, so collect() is unchanged; `family`
    # drives the SD pack layout (tools/make_rompack.py) and picks the MCR-1
    # top's input map via the define.
    #
    # Kick / Kickman: unicycle balloon-kicker. Spinner (kicker angle) on IP1
    # low nibble, kick button on IP0 bit 4. Kickman = the same board with the
    # US-region "-ur" CPU ROMs; identical inputs.
    "kick": dict(
        family="mcr1",
        define="GAME_KICK",
        zip_path="roms/kick.zip",
        main_files=["1200a-v2.b3", "1300b-v2.b4", "1400c-v2.b5",
                    "1500d-v2.d4", "1600e-v2.d5", "1700f-v2.d6"],
        snd_files=["4200-a.a7", "4300-b.a8", "4400-c.a9", "4500-d.a10"],
        gfx1_1_file="1800g-v2.g4",
        gfx1_2_file="1900h-v2.g5",
        gfx2_files=["2600a-v2.1e", "2700b-v2.1d", "2800c-v2.1b", "2900d-v2.1a"],
        snd_pad_to=16 * 1024,
    ),
    "kickman": dict(
        family="mcr1",
        define="GAME_KICK",     # identical input map to Kick
        zip_path="roms/kickman.zip",
        main_files=["1200-a-ur.b3", "1300-b-ur.b4", "1400-c-ur.b5",
                    "1500-d-ur.d4", "1600-e-ur.d5", "1700-f-ur.d6"],
        snd_files=["4200-a.a7", "4300-b.a8", "4400-c.a9", "4500-d.a10"],
        gfx1_1_file="1800g-v2.g4",
        gfx1_2_file="1900h-v2.g5",
        gfx2_files=["2600a-v2.1e", "2700b-v2.1d", "2800c-v2.1b", "2900d-v2.1a"],
        snd_pad_to=16 * 1024,
    ),
    # Solar Fox: 4-way stick (mirrored across IP1), two fire buttons. 28KB
    # CPU (7x4KB), 12KB->16KB sound, 32KB sprites, two 4KB bg planes.
    "solarfox": dict(
        family="mcr1",
        define="GAME_SOLARFOX",
        zip_path="roms/solarfox.zip",
        main_files=["sfcpu.3b", "sfcpu.4b", "sfcpu.5b", "sfcpu.4d",
                    "sfcpu.5d", "sfcpu.6d", "sfcpu.7d"],
        snd_files=["sfsnd.7a", "sfsnd.8a", "sfsnd.9a"],
        gfx1_1_file="sfcpu.4g",
        gfx1_2_file="sfcpu.5g",
        gfx2_files=["sfvid.1a", "sfvid.1b", "sfvid.1d", "sfvid.1e"],
        snd_pad_to=16 * 1024,
    ),

    # --- MCR-3 (91490 video board; core src/rtl/mcr3.vhd) -----------------
    # Tapper (main set): 56KB CPU (4 ROMs, last is 8KB), 16KB sound (4x4KB),
    # 32KB bg (2x16KB planes), 128KB sprites (8x16KB -> SDRAM, not baked).
    # bg plane order follows the MRA: bg_1(6f) -> gfx1_1, bg_0(5f) -> gfx1_2.
    # Discs of Tron, upright set (mcr_91490, ROT0). Old-MAME file names in
    # our zip, mapped positionally to MAME 0.265's dotron set (.1c=pg0,
    # .2c=pg1, .3c=pg2, .4c=pg3). bg planes load loc-bg2.6f FIRST (per
    # MAME), sprites in MAME order g,h,e,f,c,d,a,b (64K, padded). Sound
    # 4x4K -> 16K. The aim DIAL (IP1) is not wired yet - aim uses the
    # dedicated IP2 aim up/down buttons; spinner.sv integration is a TODO.
    "dotron": dict(
        family="mcr3",
        define="GAME_DOTRON",
        zip_path="roms/dotron.zip",
        main_files=["loc-pg0.1c", "loc-pg1.2c", "loc-pg2.3c", "loc-pg1.4c"],
        snd_files=["sound0.a7", "sound1.a8", "sound2.a9", "sound3.a10"],
        snd_pad_to=16 * 1024,
        # Same plane-order fix as timber (2026-07-27): MAME loads loc-bg2.6f
        # at offset 0 and loc-bg1.5f at 0x2000, so the SECOND one goes in
        # gfx1_1. See the timber comment below for why getting this backwards
        # gives right shapes / wrong bg colours. NOT hardware-verified yet.
        gfx1_1_file="loc-bg1.5f",   # MAME 0x2000 (loaded second)
        gfx1_2_file="loc-bg2.6f",   # MAME 0x0000 (loaded first)
        gfx2_files=["loc-g.cp4", "loc-h.cp3", "loc-e.cp6", "loc-f.cp5",
                    "loc-c.cp8", "loc-d.cp7", "loc-a.cp0", "loc-b.cp9"],
    ),
    # Timber (1984, mcr_91490 = the Tapper board, ROT0).
    # gfx1 PLANE ORDER - fixed 2026-07-27, verified against `mame -listxml`.
    # The previous comment here claimed MAME loads timber's gfx1 "REVERSED vs
    # tapper". That was WRONG: MAME loads the '1' ROM at offset 0 and the '0'
    # ROM at 0x4000 for BOTH games (tapper: bg_1 then bg_0; timber: timbg1
    # then timbg0). The plane order is NOT per-game - it is PER-CORE, because
    # mcr2.vhd and mcr3.vhd wire their two bg dprams differently (see the
    # "crossed wiring" note in mcr3_console60k_top.sv, commit 50b075e):
    #   MCR-3 (mcr3.vhd):  gfx1_1 = ROM MAME loads SECOND (higher offset)
    #   MCR-2 (mcr2.vhd):  gfx1_1 = ROM MAME loads FIRST  (offset 0)
    # Both are hardware-verified - tapper for MCR-3, and domino/shollow/tron/
    # wacko/kroozr for MCR-2 (all of which are offset-0-first and correct).
    # So timber must be timbg0 then timbg1, same as tapper. Having it
    # backwards swapped the two bg BITPLANES; because both planes share
    # bg_code_line and only supply the low 2 bits of bg_palette_addr, that
    # shows up as correct SHAPES with wrong COLOURS on bg tiles only -
    # sprites, sky and ground all look right. Exactly the reported symptom.
    # Sprites in MAME's pair-swapped order (fg1,fg0,fg3,fg2,...), 128 KB.
    # Sound 3x4K padded to 16K.
    "timber": dict(
        family="mcr3",
        define="GAME_TIMBER",
        zip_path="roms/timber.zip",
        main_files=["timpg0.bin", "timpg1.bin", "timpg2.bin", "timpg3.bin"],
        snd_files=["tima7.bin", "tima8.bin", "tima9.bin"],
        snd_pad_to=16 * 1024,
        gfx1_1_file="timbg0.bin",   # MAME 0x4000 (loaded second)
        gfx1_2_file="timbg1.bin",   # MAME 0x0000 (loaded first)
        gfx2_files=["timfg1.bin", "timfg0.bin", "timfg3.bin", "timfg2.bin",
                    "timfg5.bin", "timfg4.bin", "timfg7.bin", "timfg6.bin"],
    ),
    "tapper": dict(
        family="mcr3",
        define="GAME_TAPPER",
        zip_path="roms/tapper.zip",
        main_files=["tapper_c.p.u._pg_0_1c_1-27-84.1c",
                    "tapper_c.p.u._pg_1_2c_1-27-84.2c",
                    "tapper_c.p.u._pg_2_3c_1-27-84.3c",
                    "tapper_c.p.u._pg_3_4c_1-27-84.4c"],
        snd_files=["tapper_sound_snd_0_a7_12-7-83.a7",
                   "tapper_sound_snd_1_a8_12-7-83.a8",
                   "tapper_sound_snd_2_a9_12-7-83.a9",
                   "tapper_sound_snd_3_a10_12-7-83.a10"],
        # bg_0 -> gfx1_1, bg_1 -> gfx1_2, same as every other game. These were
        # reversed, which swapped bg pixel indices 1<->2: blue walls rendered
        # orange, gray floor maroon, red title banner orange (sprites - same
        # palette RAM - were fine, which is what localized it). 2026-07-24.
        gfx1_1_file="tapper_c.p.u._bg_0_5f_12-7-83.5f",
        gfx1_2_file="tapper_c.p.u._bg_1_6f_12-7-83.6f",
        gfx2_files=["tapper_video_fg_1_a7_12-7-83.a7",  # MRA sprite order
                    "tapper_video_fg_0_a8_12-7-83.a8",
                    "tapper_video_fg_3_a5_12-7-83.a5",
                    "tapper_video_fg_2_a6_12-7-83.a6",
                    "tapper_video_fg_5_a3_12-7-83.a3",
                    "tapper_video_fg_4_a4_12-7-83.a4",
                    "tapper_video_fg_7_a1_12-7-83.a1",
                    "tapper_video_fg_6_a2_12-7-83.a2"],
        snd_pad_to=16 * 1024,
    ),

    # --- MCR3Scroll (core src/rtl/mcr3scroll.vhd) --------------------------
    # Two regions no other family has: a 4 KB CHAR/ALPHA plane (`chr`, loaded
    # into the core's own dpram at dl 0x8000) and the 32 KB 16-bit Cheap Squeak
    # Deluxe 68000 ROM (`csd`, which goes to SDRAM - 16 BSRAM blocks is more
    # than the merged build has). bg planes are 16 KB = TWO 8 KB files each.
    #
    # Sprites: assembled BY PLANE into four 32 KB slots, exactly like MCR-3, so
    # the merged top's existing sprite write-swizzle is reused unchanged. That
    # works because upstream MCR3Scroll does the same interleave in its MRA
    # (`<interleave output="32">`, maps 0001/0010/0100/1000, two files per lane)
    # while Arcade-MCR3.sv does it in gateware - the SDRAM contents match either
    # way. File ORDER within each pair follows the MRA, which is the same
    # pair-swapped pattern as tapper (fg1,fg0,fg3,fg2,...).
    #
    # gfx1 plane order: mcr3scroll.vhd's bg dprams are UNCROSSED (bg_graphics_1,
    # the dl "00" range, feeds bg_graphx1_do), unlike mcr3.vhd - so gfx1_1 is
    # the pair MAME/the MRA loads FIRST. NOT hardware-verified: if bg tiles come
    # out with right shapes and wrong colours, swap these two (that is the exact
    # symptom, and it cost a day on Timber - see CLAUDE.md).
    #
    # DIP bytes: MRA `switches default="FF 00"` for all three, i.e. input_3 =
    # 0xFF. Not cross-checked against MAME per game yet.

    # Crater Raider - SSIO sound only, no CSD, LANDSCAPE cabinet.
    "crater": dict(
        family="mcr3scroll",
        define="GAME_CRATER",
        zip_path="roms/crater.zip",
        main_files=["crcpu.6d", "crcpu.7d", "crcpu.8d", "crcpu.9d",
                    "crcpu.10d"],
        main_pad_to=0xE000, main_pad_byte=0xFF,   # MRA: <part repeat=0x4000>FF
        snd_files=["crsnd4.a7", "crsnd1.a8", "crsnd2.a9", "crsnd3.a10"],
        snd_pad_to=16 * 1024,
        gfx1_1_files=["crcpu.3a", "crcpu.4a"],
        gfx1_2_files=["crcpu.5a", "crcpu.6a"],
        chr_files=["crcpu.10g"],
        csd_files=[],                              # no Cheap Squeak Deluxe
        gfx2_files=["crvid.a4", "crvid.a3", "crvid.a6", "crvid.a5",
                    "crvid.a8", "crvid.a7", "crvid.a10", "crvid.a9"],
    ),
    # Spy Hunter - SSIO + Cheap Squeak Deluxe, wheel/pedal on IP2.
    "spyhunt": dict(
        family="mcr3scroll",
        define="GAME_SPYHUNT",
        zip_path="roms/spyhunt.zip",
        main_files=["spy-hunter_cpu_pg0_2-9-84.6d",
                    "spy-hunter_cpu_pg1_2-9-84.7d",
                    "spy-hunter_cpu_pg2_2-9-84.8d",
                    "spy-hunter_cpu_pg3_2-9-84.9d",
                    "spy-hunter_cpu_pg4_2-9-84.10d",
                    "spy-hunter_cpu_pg5_2-9-84.11d"],   # 5x8K + 16K = 56K
        snd_files=["spy-hunter_snd_0_sd_11-18-83.a7",
                   "spy-hunter_snd_1_sd_11-18-83.a8"],  # only 8K of SSIO ROM
        snd_pad_to=16 * 1024,
        gfx1_1_files=["spy-hunter_cpu_bg0_11-18-83.3a",
                      "spy-hunter_cpu_bg1_11-18-83.4a"],
        gfx1_2_files=["spy-hunter_cpu_bg2_11-18-83.5a",
                      "spy-hunter_cpu_bg3_11-18-83.6a"],
        chr_files=["spy-hunter_cpu_alpha-n_11-18-83"],
        csd_files=["spy-hunter_cs_deluxe_u17_b_11-18-83.u17",
                   "spy-hunter_cs_deluxe_u18_d_11-18-83.u18",   # low bytes
                   "spy-hunter_cs_deluxe_u7_a_11-18-83.u7",
                   "spy-hunter_cs_deluxe_u8_c_11-18-83.u8"],    # high bytes
        gfx2_files=["spy-hunter_video_1fg_11-18-83.a7",
                    "spy-hunter_video_0fg_11-18-83.a8",
                    "spy-hunter_video_3fg_11-18-83.a5",
                    "spy-hunter_video_2fg_11-18-83.a6",
                    "spy-hunter_video_5fg_11-18-83.a3",
                    "spy-hunter_video_4fg_11-18-83.a4",
                    "spy-hunter_video_7fg_11-18-83.a1",
                    "spy-hunter_video_6fg_11-18-83.a2"],
    ),
    # Turbo Tag (prototype) - CSD sound ONLY (mod_turbo disables the SSIO
    # board), so snd_files is empty. The MRA repeats ttprog5 to fill 56K and
    # patches one CPU byte.
    "turbotag": dict(
        family="mcr3scroll",
        define="GAME_TURBOTAG",
        zip_path="roms/turbotag.zip",
        main_files=["ttprog0.bin", "ttprog1.bin", "ttprog2.bin",
                    "ttprog3.bin", "ttprog4.bin", "ttprog5.bin",
                    "ttprog5.bin"],                # MRA repeats the last 8K
        main_pad_to=0x10000, main_pad_byte=0x00,
        main_patches=[(0x0B2C, 0x18)],             # MRA <patch offset=0x0B2C>
        snd_files=[],                              # no SSIO sound board
        snd_pad_to=16 * 1024,
        gfx1_1_files=["ttbg0.bin", "ttbg1.bin"],
        gfx1_2_files=["ttbg2.bin", "ttbg3.bin"],
        chr_files=["ttan.bin"],
        csd_files=["ttu17.bin", "ttu18.bin",       # low bytes
                   "ttu7.bin",  "ttu8.bin"],       # high bytes
        gfx2_files=["ttfg1.bin", "ttfg0.bin", "ttfg3.bin", "ttfg2.bin",
                    "ttfg5.bin", "ttfg4.bin", "ttfg7.bin", "ttfg6.bin"],
    ),

    # --- MCR-2 (90010 video board; core src/rtl/mcr2.vhd) -----------------
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
    # Wacko (MCR2): 32KB CPU, 12->16KB sound, 16KB bg, 32KB sprites.
    # Trackball game; the SSIO input mux only selects the cocktail player's
    # trackball, so upright play needs no mux support.
    "wacko": dict(
        define="GAME_WACKO",
        zip_path="roms/wacko.zip",
        main_files=["wackocpu.2d", "wackocpu.3d", "wackocpu.4d", "wackocpu.5d"],
        snd_files=["wackosnd.7a", "wackosnd.8a", "wackosnd.9a"],
        gfx1_1_file="wackocpu.3g",
        gfx1_2_file="wackocpu.4g",
        gfx2_files=["wackovid.1e", "wackovid.1d", "wackovid.1b", "wackovid.1a"],
        snd_pad_to=16 * 1024,
    ),
    # Kozmik Kroozr (MCR2): 40KB CPU, 12->16KB sound, 16KB bg, 32KB sprites.
    # Spinner (rotating cockpit) plus an analogue stick.
    "kroozr": dict(
        define="GAME_KROOZR",
        zip_path="roms/kroozr.zip",
        main_files=["kozmkcpu.2d", "kozmkcpu.3d", "kozmkcpu.4d",
                    "kozmkcpu.5d", "kozmkcpu.6d"],
        snd_files=["kozmksnd.7a", "kozmksnd.8a", "kozmksnd.9a"],
        gfx1_1_file="kozmkcpu.3g",
        gfx1_2_file="kozmkcpu.4g",
        gfx2_files=["kozmkvid.1e", "kozmkvid.1d", "kozmkvid.1b", "kozmkvid.1a"],
        snd_pad_to=16 * 1024,
    ),
    # Two Tigers (MCR2, Tron-conversion set): 32KB CPU, 12->16KB sound,
    # 16KB bg, 32KB sprites. The *dedicated* set (twotiger) additionally
    # needs a video-RAM address remap at 0xE800 that this core does not
    # implement, so the conversion set is the one we support.
    "twotiger": dict(
        define="GAME_TWOTIGER",
        zip_path="roms/twotigerc.zip",
        main_files=["2tgrpg0.bin", "2tgrpg1.bin", "2tgrpg2.bin", "2tgrpg3.bin"],
        snd_files=["2tgra7.bin", "2tgra8.bin", "2tgra9.bin"],
        gfx1_1_file="2tgrbg0.bin",
        gfx1_2_file="2tgrbg1.bin",
        gfx2_files=["2tgrfg0.bin", "2tgrfg1.bin", "2tgrfg2.bin", "2tgrfg3.bin"],
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


def write_hex(filename, data, family):
    for out_dir in HEX_DIRS[family]:
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

    def cat(z, names):
        out = bytearray()
        for fn in names:
            out.extend(z.read(fn))
        return out

    with zipfile.ZipFile(zip_path, "r") as z:
        # 1. Main CPU ROM (loaded at 0x0000, contiguous).
        # main_pad_to / main_pad_byte reproduce an MRA `<part repeat=...>` fill.
        # Crater Raider's is 0xFF, not 0x00 - the MRA is the authority, and an
        # 0xFF fill reads as RST 38h rather than NOP if the Z80 ever gets there.
        main_data = cat(z, spec["main_files"])
        if spec.get("main_pad_to"):
            fill = bytes([spec.get("main_pad_byte", 0x00)])
            main_data.extend(fill * (spec["main_pad_to"] - len(main_data)))
        # MRA <patch> bytes (Turbo Tag's prototype ROM needs one).
        for off, val in spec.get("main_patches", []):
            main_data[off] = val

        # 2. Sound ROM (SSIO Z80), optionally zero-padded to a power of two.
        # Turbo Tag has NO SSIO board (mcr_sound_board is disabled by
        # mod_turbo); all its audio comes from the Cheap Squeak Deluxe, so
        # snd_files is empty and the region is just padding.
        snd_data = cat(z, spec.get("snd_files", []))
        if spec.get("snd_pad_to"):
            snd_data.extend(b"\x00" * (spec["snd_pad_to"] - len(snd_data)))

        # 3. Background tile graphics (gfx1): two planes. MCR-1/2 use one 4/8 KB
        # file per plane; MCR3Scroll's planes are 16 KB = TWO 8 KB files each,
        # so the plural keys take a list.
        gfx1_1_data = bytes(cat(z, spec["gfx1_1_files"])) \
            if spec.get("gfx1_1_files") else z.read(spec["gfx1_1_file"])
        gfx1_2_data = bytes(cat(z, spec["gfx1_2_files"])) \
            if spec.get("gfx1_2_files") else z.read(spec["gfx1_2_file"])

        # 3b. MCR3Scroll only: the 4 KB char/alpha plane (Spy Hunter's status
        # line) and the 32 KB 16-bit Cheap Squeak Deluxe 68000 ROM. The CSD
        # halves are ROM_LOAD16_BYTE: the first 16 KB is the LOW byte of each
        # word, the second the HIGH byte (the merged top's port1 write applies
        # exactly that lane split).
        chr_data = bytes(cat(z, spec.get("chr_files", [])))
        csd_data = bytes(cat(z, spec.get("csd_files", [])))

        # 4. Sprite graphics (gfx2), assembled BY BITPLANE.
        # The MCR-3 sprite engine fetches one 32-bit word as
        #   {Q3[i], Q2[i], Q1[i], Q0[i]}
        # where Qp is the p'th QUARTER of the 128 KB region - i.e. each plane
        # owns a fixed 32 KB slot, regardless of how much ROM the game
        # actually has. Plain concatenation only happens to be right when the
        # set is a full 128 KB (tapper, timber: 8 x 16 KB, so each pair of
        # files exactly fills a quarter).
        # Discs of Tron has 8 x 8 KB = 64 KB. Concatenated and padded at the
        # END, its four planes land as Q0=files0-3, Q1=files4-7, Q2=ZEROS,
        # Q3=ZEROS - so sprites render with only 2 of their 4 bitplanes, which
        # on screen is missing interior pixels / a striped look. Verified
        # against `mame -listxml`: MAME loads DoT's 8 files contiguously at
        # 8 KB spacing, so the plane grouping is pairs either way; what
        # matters is padding EACH plane to its 32 KB slot.
        # Pairs -> planes, each padded to a quarter. Full-size sets are
        # byte-identical to the old behaviour (no padding needed).
        # MCR-3 ONLY. MCR-1/MCR-2 sprites are a FLAT 32 KB region read 8 bits
        # at a time (mcr1/mcr2.vhd's sprite_graphics is one aWidth=15 dpram),
        # not four 32 KB bitplane slots - padding their planes would overflow
        # the region and shift every later game in the pack.
        files = spec["gfx2_files"]
        gfx2_data = bytearray()
        if spec.get("family", "mcr2") in ("mcr3", "mcr3scroll"):
            per_plane = SPRITE_REGION // 4          # 32 KB
            for i in range(0, len(files), 2):
                plane = bytearray()
                for fn in files[i:i + 2]:
                    plane.extend(z.read(fn))
                if len(plane) > per_plane:
                    raise SystemExit(
                        f"{game}: sprite plane is {len(plane)} bytes, over "
                        f"the {per_plane}-byte slot - check gfx2_files")
                plane.extend(b"\x00" * (per_plane - len(plane)))
                gfx2_data.extend(plane)
        else:
            for fn in files:
                gfx2_data.extend(z.read(fn))

    if not quiet:
        extra = ""
        if chr_data or csd_data:
            extra = f"  chr={len(chr_data)}  csd={len(csd_data)}"
        print(f"  main(cpu)={len(main_data)}  snd={len(snd_data)}  "
              f"gfx1_1={len(gfx1_1_data)}  gfx1_2={len(gfx1_2_data)}  "
              f"gfx2={len(gfx2_data)}{extra}")

    return {
        "main":   bytes(main_data),
        "snd":    bytes(snd_data),
        "gfx1_1": bytes(gfx1_1_data),
        "gfx1_2": bytes(gfx1_2_data),
        "gfx2":   bytes(gfx2_data),
        "chr":    chr_data,      # MCR3Scroll char/alpha plane (else b"")
        "csd":    csd_data,      # MCR3Scroll CSD 68000 ROM     (else b"")
    }


def write_game_config(game):
    spec = GAME_SPECS[game]
    define = spec["define"]
    family = spec.get("family", "mcr2")
    for out_dir in CONFIG_DIRS[family]:
        os.makedirs(out_dir, exist_ok=True)
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

    family = GAME_SPECS[game].get("family", "mcr2")
    write_hex("rom_main.hex", r["main"], family)
    write_hex("rom_snd.hex", r["snd"], family)
    write_hex("rom_cpu.hex", r["main"] + r["snd"], family)
    write_hex("rom_gfx1_1.hex", r["gfx1_1"], family)
    write_hex("rom_gfx1_2.hex", r["gfx1_2"], family)
    write_hex("rom_gfx2.hex", r["gfx2"], family)
    print("ROM generation and copying complete!")
    write_game_config(game)
