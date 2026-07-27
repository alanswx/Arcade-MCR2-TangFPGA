# sp_tb.vhd — MCR-3 sprite machine GHDL testbench (2026-07-26)

Standalone sim of the mcr3.vhd sprite engine (copied verbatim) against a
cycle-exact model of sdram_gw's sp port (7-cycle rounds @80MHz, launch at
RAS1=t4, commit at READ1b). Built to chase the "detached mug handle"
artifact.

Run:
  ghdl -a --std=93c -fsynopsys -fexplicit sp_tb.vhd
  ghdl -e --std=93c -fsynopsys -fexplicit sp_tb
  ghdl -r --std=93c -fsynopsys -fexplicit sp_tb -gT0=<0..6> [-gHFLIP_ATTR=16]

Result (all 7 alignments T0, flipped and not): the render is four contiguous
8px words — the RTL cannot produce the displaced-last-word artifact, and the
engine cannot write outside its 32px window. GHDL gotcha fixed here:
registers must be zero-initialized in declarations ('U'+1='X' poisons the
phase counter forever; silicon powers up at 0).
