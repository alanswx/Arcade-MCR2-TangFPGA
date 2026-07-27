# dpram mode tests

`dpram` has three modes and the wrong one fails SILENTLY (port B writes are
discarded, no error anywhere), so they are pinned by simulation:

    iverilog -g2012 -o dp_tb  dp_tb.sv  ../../src/rtl/dpram.sv && ./dp_tb
    iverilog -g2012 -o dp_tb2 dp_tb2.sv ../../src/rtl/dpram.sv && ./dp_tb2   # needs init4.hex in cwd

- `dp_tb.sv`  — LOADABLE=1 accepts port-B writes; plain (no INIT_FILE, no
  LOADABLE) correctly leaves port B read-only.
- `dp_tb2.sv` — INIT_FILE preloads AND a later port-B write overrides it.
  This is the one that disproves the old "port B is inert in ROM mode" claim.
