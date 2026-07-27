# OSD roster / scrolling tests

The menu grew from a fixed 6-row list to a 20-slot scrolling one. A hardware
round-trip is a ~20 minute build, so the row->roster mapping, the scroll
follow and the marker glyphs are pinned here instead.

    cd sim/osd
    for n in 3 6 12 17; do
      iverilog -g2012 -Ptb_osd.NG=$n -o tb_o$n tb_osd.sv ../../src/rtl/osd.sv
      ./tb_o$n
    done

`osd_font.hex` is symlinked from `src/rtl/` because `$readmemh` resolves
relative to the working directory here (Gowin resolves it relative to the
instantiating source file instead).

The testbench drives a real 634x525 MCR raster and scrapes the 24x14
character grid straight out of the render pipeline, so a failure prints the
actual menu as ASCII.

Covered:
- NG=3 / NG=6 - what MCR-1, MCR-3 and MCR-2 ship today: no ghost rows from
  the unused NAME defaults, and no scroll hints when the list fits.
- NG=12 - the merged MCR-1/2/3 roster: rows map to the right entries, the
  list scrolls to follow the cursor, `>` `*` `^` `V` land correctly, and the
  cursor wraps both ways with the scroll reset to match.
- NG=17 - the whole series we are building (MCR-1 3 + MCR-2 7 + MCR-3 4 +
  MCR3Scroll 3): scrolls to the last entry, `^` shown, `V` correctly gone.

The bug this caught before it reached hardware: `row_game` was computed with
`p1_row[2:0]`, so rows 8/9/10 wrapped to 0/1/2 and silently repeated the
first three entries at the bottom of the list.
