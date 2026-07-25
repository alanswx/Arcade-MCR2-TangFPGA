# Handoff v7 — the MCR jukebox: MCR-3 working, pack v2, roadmap underway

**Date: 2026-07-25. Supersedes v5/v6 (whose sprite-bug conclusions were
disproved) and updates v4 (platform).** The authoritative work queue is the
ROADMAP at the top of `TODO.md`; this handoff is the narrative state.

## What works, verified on hardware

- **MCR-3 / Tapper on the Tang Console 60K**: full attract + gameplay,
  sprites from the Tang SDRAM module, colors verified against reference
  screenshots (MobyGames) over HDMI capture. In SPI flash as the power-on
  default; archived as
  `bitstreams/console60k_mcr3_tapper_sprites_working.fs`.
- **Cold boot < 10 s** via the HALT wedge-watchdog (the Z80 crashes on
  some cold boots for a still-unidentified power-event-scoped reason
  during its first seconds; the watchdog detects the halted CPU and
  retries the full reset+reload path until the game runs — typically one
  retry).
- **MCR-2 60K** unchanged-working (six games, OSD switching, prefs).

## The two discoveries that unblocked everything

1. **SDRAM pin-clock phase (THE sprite fix).** The Tang SDRAM module
   (Winbond W9825G6KH) is fine. `sdram_gw` forwarded SDRAM_CLK at 0
   degrees; the chip then samples commands at the exact instant they
   change, and that margin drifts with temperature/activity — data
   "decayed" to FF within ~30-100 s of idle no matter what refresh
   scheme ran. Every nand2mario design drives this module's clock pin
   from a ~225-degree-shifted PLL output. Adopting that (one PLLA output,
   `gowin_pll_core80` CLKOUT3 -> `sdram_gw.clk_fwd`) fixed retention
   completely (0 errors at 8+ minutes idle). Retention harnesses to
   re-verify any change: `mcr2_console60k/diag/build_retention.tcl`
   (nand2mario reference controller) and `build_gwret.tcl` (ours).
2. **Tapper bg colors**: the bg ROM planes were swapped in
   `tools/merge_roms.py`. Rule since: **MAME's per-game gfx1 load order
   is the law** (Timber's is opposite Tapper's).

## Pack format v2 (implemented; hardware test pending)

One SD card for every family. `rom_loader.sv` auto-detects
`MCRPACK1`/`MCRPACK2` at sector 2048 — v1 cards keep working (verified).
v2: 16-byte mini-entries in the superblock
`{family, type, slot, start_lba, sector_count}`, 18-bit `dl_addr`,
per-family payload layouts (see `tools/make_pack_v2.py` header), MCR-3
full-from-SD (CPU/snd/bg/sprites all routed). Build the image anywhere;
**write the card on the Mac**:
`python3 tools/make_pack_v2.py && python3 tools/write_pack_v2.py mcr_pack_v2.img /dev/rdiskN`

## Games

| Core | Games | State |
|---|---|---|
| MCR-2 | Shollow, Tron, Wacko, Kroozr, Two Tigers, Domino | hardware-working |
| MCR-3 (91490) | Tapper | hardware-working |
| MCR-3 (91490) | Timber, Discs of Tron | wired end-to-end (MAME-sourced specs/inputs; DoT dial via spinner.sv); first boot awaits the v2 card |
| MCR-1 | Kick, Kickman, Solar Fox | builds; never hardware-tested |
| — deferred | Journey (91475 + wave audio), MCR3Mono (board rev), Scroll games (new core) | see TODO |

## Awaiting the user's bench session

1. Write the v2 card (Mac) → test Timber, DoT, v2 loading, and the
   cabinet chord (hold the coin key ~3 s → OSD).
2. HDMI dropouts (~1 blink/12 s): audio data islands are the major cause
   (proven by a DVI-mode test on a monitor); the correct fix changes the
   sample rate AND the ACR N/CTS parameters together — the 32 kHz
   divider-only attempt killed sync and is reverted (commits
   2bee7ea/2424e0c). Thermal residual second.
3. Core switching decision: GW5A multiboot (RECONFIG_N pin + 
   `-multiboot_spi_flash_address` chain; 16 MB flash = 6 slots) vs
   TangCore-style BL616-JTAG loading. TODO item 4 has the full analysis.

## Process rules that were paid for in days (also in CLAUDE.md)

- JTAG SRAM loads fail silently ~1/3 of the time: **verify every load**
  with a per-build beacon marker before trusting any result.
- Flash writes lie: always `openFPGALoader -f --verify`, retry (first
  attempt usually fails just past byte 0x30000).
- The BL616 UART wedges on reconfig; only a USB-C replug clears it — and
  the replug is also a POWER CYCLE (USB-C powers the board).
- Gowin use-before-declaration = silent floating net, even on clocks.
- Measurement: windowed rates only; full-width counters only; beware the
  serial buffer's stale-flush poisoning t=0 samples.
