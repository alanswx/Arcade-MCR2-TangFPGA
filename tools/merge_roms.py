import os
import zipfile
import shutil

def merge_shollow():
    zip_path = "roms/shollow.zip"
    
    # Target directories where Gowin compiler expects files based on instantiation paths
    top_src_dir = "mcr2_primer25k/src"
    rtl_src_dir = "src/rtl"
    
    print(f"Reading ROMs from {zip_path}...")
    if not os.path.exists(zip_path):
        print(f"Error: {zip_path} not found!")
        return

    # Satan's Hollow Part Map
    main_files = ["sh-pro.00", "sh-pro.01", "sh-pro.02", "sh-pro.03", "sh-pro.04", "sh-pro.05"]
    snd_files = ["sh-snd.01", "sh-snd.02", "sh-snd.03"]
    gfx1_1_file = "sh-bg.00"
    gfx1_2_file = "sh-bg.01"
    gfx2_files = ["sh-fg.00", "sh-fg.01", "sh-fg.02", "sh-fg.03"]

    with zipfile.ZipFile(zip_path, 'r') as z:
        # 1. Main ROM: 48KB (0x0000 - 0xBFFF)
        main_data = bytearray()
        for fn in main_files:
            main_data.extend(z.read(fn))
        assert len(main_data) == 48 * 1024
        
        # 2. Sound ROM: 16KB (0xC000 - 0xFFFF)
        snd_data = bytearray()
        for fn in snd_files:
            snd_data.extend(z.read(fn))
        assert len(snd_data) == 12 * 1024
        snd_data.extend(b'\x00' * (4 * 1024))
        assert len(snd_data) == 16 * 1024

        # 3. GFX1_1 (8KB) and GFX1_2 (8KB)
        gfx1_1_data = z.read(gfx1_1_file)
        gfx1_2_data = z.read(gfx1_2_file)
        assert len(gfx1_1_data) == 8 * 1024
        assert len(gfx1_2_data) == 8 * 1024

        # 4. GFX2 (32KB)
        gfx2_data = bytearray()
        for fn in gfx2_files:
            gfx2_data.extend(z.read(fn))
        assert len(gfx2_data) == 32 * 1024

    # Helper function to write hex files to both target directories
    def write_hex(filename, data):
        for out_dir in [top_src_dir, rtl_src_dir]:
            os.makedirs(out_dir, exist_ok=True)
            path = os.path.join(out_dir, filename)
            with open(path, "w") as f:
                for b in data:
                    f.write(f"{b:02x}\n")
            print(f"Wrote {path} ({len(data)} bytes)")

    write_hex("rom_main.hex", main_data)
    write_hex("rom_snd.hex", snd_data)
    write_hex("rom_cpu.hex", main_data + snd_data)
    write_hex("rom_gfx1_1.hex", gfx1_1_data)
    write_hex("rom_gfx1_2.hex", gfx1_2_data)
    write_hex("rom_gfx2.hex", gfx2_data)
    print("ROM generation and copying complete!")

if __name__ == "__main__":
    merge_shollow()
