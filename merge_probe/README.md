# merge_probe — throwaway BSRAM probe for the merged core

Not a real board. It is MCR-3's top with an MCR-2 core instantiated alongside,
sharing the top-level CPU/sound ROM RAM, built purely to find out what a merged
bitstream actually COSTS in BSRAM. Functionally meaningless.

    tools/gw_build.sh merge_probe
    grep BSRAM merge_probe/impl/pnr/merge_probe.rpt.txt

Results 2026-07-27:

| Probe | BSRAM | |
|---|---|---|
| mcr3 + mcr2, shared CPU/sound ROM | **122 / 118** | PnR REFUSED (PA2017) |
| + bg graphics RAMs shared | **114 / 118** | fits, 4 spare |

The first number is why this project exists: the arithmetic had predicted 114
for the *un*-shared case, so the merge would have been designed on a figure
wrong by 8 blocks. Shared infrastructure is ~20 blocks, not the 12 the
synthesis per-module list implies. See TODO item 4a for the full budget.

## If you re-run it, do not repeat these mistakes

Three separate times a probe under-reported because synthesis proved part of
the second core dead and deleted it. ALWAYS sanity-check `probe_mcr2`'s BSRAM
against the standalone core's figure (26 after the bg hoist) before believing
a total.

1. **Constant family select.** The first attempt reported a comfortable 95
because the family-select was
`game_id[3]`. The OSD only ever assigns `loaded_slot[2:0]`, so synthesis proved
that bit constant 0, killed MCR-2's video path and pruned 27 of its 34 BSRAM
blocks. The probe has to keep both cores genuinely live:

   - select on something provably NON-constant (now `key_s2`, a real pin)
   - fold the second core's outputs into an actual output (here: XOR-reduced
     into the beacon's aux2) so nothing downstream can be swept

2. **Tied-off `dl_wr`.** The next attempt read 98 with `probe_mcr2` at 10.
   Tying `dl_wr` to 0 lets synthesis prove a `LOADABLE` ROM (blank, never
   written) is permanently empty, and it deleted all 16 blocks of the sprite
   graphics. `dl_wr` must be live even though it is functionally meaningless
   in the probe.


