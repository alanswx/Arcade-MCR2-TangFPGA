# shield_io simulation

Checks `src/rtl/shield_io.sv` against a behavioural model of the **as-fabbed**
shield chains (six 74AHC165s, two 74HC595s, wired as traced from
`MCR_prototype_PCB/` on 2026-10-22, see `docs/shield_bringup.md` §3). It
uses 20 random vectors on all six input bytes and the 16 output bits, and
also checks that OE stays off until the first latched word.

```sh
iverilog -g2012 -o /tmp/tb_shield sim/shield_io/tb_shield_io.sv src/rtl/shield_io.sv
vvp /tmp/tb_shield        # -> PASS shield_io: ...
```

If the board is respun, change the model's `u1..u7` wiring first, then the RTL.
