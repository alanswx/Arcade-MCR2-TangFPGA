# Simulation evidence

Both of these render the test pattern **correctly**, from the same VHDL that
misbehaves on Gowin hardware.

## 1. Behavioural (GHDL)

```sh
python3 mk_ascal_sim.py          # guards 3 `natural` underflows GHDL rejects
ghdl -a --std=08 ascal_sim.vhd ../src/ascal_gw.vhd tb_ascal.vhd
ghdl -r --std=08 tb_ascal --stop-time=90ms
python3 ascal_sim_check.py ascal_out.txt
```

Expected: one full-width image, `[(160, 1119, 960)]`, colour bars 120 px each.

## 2. GHDL's own synthesis engine, simulated gate-level (verilator)

This is the check Gowin's encrypted `.vg` netlist makes impossible.

```sh
ghdl synth --std=08 --out=verilog ascal_gw > ascal_gw_synth.v
verilator --cc --exe --build -O3 -Wno-fatal --top-module synth_top \
    -o vsynth_sim vsynth_top.v vsynth_ddr3_model.v ascal_gw_synth.v \
    ../src/mcr_testpattern.sv ../src/ascal_avl_ddr3.sv vsynth_main.cpp
./obj_dir/vsynth_sim
```

Runs in ~2 seconds. Expected, for a 640-wide window (bars should be 80 px):

```
bars at 81-158, 161-238, 241-318, 321-398, 401-478, 481-558, 561-638
```

Note the output raster free-runs faster than the 60 Hz source here, so the
harness dumps a late frame; dumping an early one shows black because the
framebuffer has not been filled yet.
