# FX68K — cycle-accurate 68000, vendored 2026-07-30

Copied verbatim from `refs/Arcade-MCR3Scroll_MiSTer/rtl/FX68K/` (Jorge Cwik /
ijor, BSD-style licence in `fx68k.txt` upstream). Needed by
`src/rtl/cheap_squeak_deluxe.vhd`, the Cheap Squeak Deluxe music board inside
`mcr3scroll.vhd` (Spy Hunter / Turbo Tag). MCR3Mono's Sounds Good board reuses
it, so this is a one-time cost for two families.

Files: `fx68k.sv`, `fx68kAlu.sv`, `uaddrPla.sv`, plus the `fx68k.vhd` package
that declares the COMPONENT so VHDL can instantiate the SystemVerilog module.

**`microrom.mem` / `nanorom.mem` must stay next to `fx68k.sv`** — its
`$readmemb` calls name them with no path, and Gowin resolves `$readmemb`
relative to the instantiating source file's directory (same rule as
`INIT_FILE`; see CLAUDE.md).

The only `altera` strings in these sources are `// altera message_off`
comment pragmas — there are no vendor primitives, which is why this ports
without modification.

Measured standalone on GW5AT-LV60PG484: **2,891 LUT, 4 BSRAM** (the microcode
ROMs infer block RAM rather than logic).
