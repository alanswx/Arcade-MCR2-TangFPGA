"""Write mcr_rompack.img to an SD card, with guard rails (macOS).

The pack is raw sectors - no filesystem - starting at sector 2048 (1 MiB
into the card), where src/rtl/rom_loader.sv reads it. This script exists
because the alternative is hand-typed `dd of=/dev/rdiskN`, and one wrong
digit there erases a disk. It will:

  * only consider EXTERNAL, PHYSICAL disks (never the internal drive)
  * read the card's partition table and REFUSE if any partition overlaps
    the pack's sectors (2048 .. 2048+len/512). A card formatted the usual
    SD-Association way (first partition at sector 8192) keeps its
    filesystem; one partitioned at sector 2048 would be corrupted, so it
    is rejected - reformat it or use a spare card.
  * unmount, write, then read the header back and verify "MCRPACK1".

Usage (needs root for the raw device):

    python3 tools/make_rompack.py              # build the image first
    sudo python3 tools/write_rompack.py        # list candidate cards
    sudo python3 tools/write_rompack.py disk4  # write to /dev/disk4

The card obviously has to be in a reader on the computer - the console's
own SD slot is read-only gateware and cannot program cards.
"""

import os
import plistlib
import struct
import subprocess
import sys

SECTOR = 512
PACK_BASE = 2048        # must match rom_loader.sv / make_rompack.py
IMAGE = "mcr_rompack.img"


def run(*cmd, capture=True):
    return subprocess.run(cmd, check=True,
                          stdout=subprocess.PIPE if capture else None).stdout


def external_disks():
    """[(devname, size_bytes, protocol, [volume names])] for candidate disks.

    Candidates are physical disks that are external OR removable - the
    Mac's built-in SDXC reader reports its cards as "internal" (it sits on
    PCIe), so filtering on external alone would miss the most common case.
    The boot SSD (internal, non-removable) can never appear here.
    """
    pl = plistlib.loads(run("diskutil", "list", "-plist", "physical"))
    disks = []
    for d in pl.get("AllDisksAndPartitions", []):
        dev = d["DeviceIdentifier"]
        info = plistlib.loads(run("diskutil", "info", "-plist", dev))
        if info.get("Internal", False) and not info.get("RemovableMedia",
                                                        False):
            continue
        vols = [p.get("VolumeName") for p in d.get("Partitions", [])
                if p.get("VolumeName")]
        disks.append((dev, d.get("Size", 0),
                      info.get("BusProtocol", "?"), vols))
    return disks


def partitions_overlapping(dev, first, last):
    """Partition entries of /dev/dev that overlap sectors [first, last]."""
    with open(f"/dev/r{dev}", "rb") as f:
        mbr = f.read(SECTOR)
        if len(mbr) < SECTOR or mbr[510:512] != b"\x55\xaa":
            return []          # no partition table - blank card, all good
        entries = []
        for i in range(4):
            e = mbr[446 + 16 * i: 446 + 16 * (i + 1)]
            ptype = e[4]
            lba, num = struct.unpack("<II", e[8:16])
            if ptype and num:
                entries.append((ptype, lba, num))
        if any(t == 0xEE for t, _, _ in entries):     # GPT behind protective MBR
            f.seek(SECTOR)
            hdr = f.read(SECTOR)
            table_lba, = struct.unpack("<Q", hdr[72:80])
            n_ent, ent_sz = struct.unpack("<II", hdr[80:88])
            f.seek(table_lba * SECTOR)
            table = f.read(n_ent * ent_sz)
            entries = []
            for i in range(n_ent):
                e = table[i * ent_sz:(i + 1) * ent_sz]
                if e[:16] != b"\x00" * 16:
                    s, e_ = struct.unpack("<QQ", e[32:48])
                    entries.append((0, s, e_ - s + 1))
    return [(lba, lba + num - 1) for _, lba, num in entries
            if lba <= last and lba + num - 1 >= first]


def main(argv):
    here = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    image = os.path.join(here, IMAGE)
    if not os.path.exists(image):
        sys.exit(f"{IMAGE} not found - run: python3 tools/make_rompack.py")
    size = os.path.getsize(image)
    first, last = PACK_BASE, PACK_BASE + (size + SECTOR - 1) // SECTOR - 1

    disks = external_disks()
    if len(argv) < 2:
        if not disks:
            sys.exit("No external disk found - insert the SD card in a "
                     "reader (the console's slot can't program cards).")
        print(f"{IMAGE}: {size} bytes -> sectors {first}..{last}\n")
        print("Candidate disks (pick one, then rerun with its name):")
        for dev, sz, proto, vols in disks:
            names = f"  [{', '.join(vols)}]" if vols else "  [no volumes]"
            print(f"  {dev:8s} {sz / 1e9:6.1f} GB  {proto:16s}{names}")
        print(f"\n  sudo python3 tools/write_rompack.py <diskN>")
        return

    dev = argv[1].removeprefix("/dev/").removeprefix("r")
    if dev not in [d for d, _, _, _ in disks]:
        sys.exit(f"{dev} is not an external/removable physical disk "
                 f"(saw: {', '.join(d for d, _, _, _ in disks) or 'none'}). "
                 "Refusing.")
    if os.geteuid() != 0:
        sys.exit("Raw device access needs root: rerun with sudo.")

    overlap = partitions_overlapping(dev, first, last)
    if overlap:
        rngs = ", ".join(f"{a}..{b}" for a, b in overlap)
        sys.exit(f"REFUSING: {dev} has a partition at sectors {rngs}, "
                 f"which the pack ({first}..{last}) would corrupt.\n"
                 "Use a spare card, or reformat this one (a standard "
                 "SD-Association format starts the partition at sector "
                 "8192, clear of the pack).")

    subprocess.run(["diskutil", "unmountDisk", f"/dev/{dev}"], check=True)
    with open(image, "rb") as src, open(f"/dev/r{dev}", "r+b") as dst:
        dst.seek(PACK_BASE * SECTOR)
        dst.write(src.read())
        dst.flush()
        os.fsync(dst.fileno())
        # verify the header made it
        dst.seek(PACK_BASE * SECTOR)
        if dst.read(8) != b"MCRPACK1":
            sys.exit("Verify FAILED - header does not read back. Bad card?")
    print(f"OK: wrote {size} bytes to {dev} at sector {PACK_BASE}, "
          "header verified (MCRPACK1).")
    subprocess.run(["diskutil", "eject", f"/dev/{dev}"], check=False)
    print("Card ejected - move it to the console and open the OSD "
          "(Select+Start).")


if __name__ == "__main__":
    if sys.platform != "darwin":
        sys.exit("macOS only. On Linux/Windows use the dd/Win32DiskImager "
                 "recipe that make_rompack.py prints.")
    main(sys.argv)
