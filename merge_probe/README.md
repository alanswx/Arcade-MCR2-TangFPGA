# merge_probe — throwaway BSRAM probe for the merged core

Not a real board. It is MCR-3's top with an MCR-2 core instantiated alongside,
sharing the top-level CPU/sound ROM RAM, built purely to find out what a merged
bitstream actually COSTS in BSRAM. Functionally meaningless.

    tools/gw_build.sh merge_probe
    grep BSRAM merge_probe/impl/pnr/merge_probe.rpt.txt

Result 2026-07-27: **122 / 118 — PnR refused it** (PA2017). The arithmetic had
predicted 114, so the merge design would have been built on a number that was
wrong by 8 blocks. Shared infrastructure is ~20 blocks, not the 12 the
synthesis per-module list implies. See TODO item 4a for the full budget.

## If you re-run it, do not repeat this mistake

The first attempt reported a comfortable 95 because the family-select was
`game_id[3]`. The OSD only ever assigns `loaded_slot[2:0]`, so synthesis proved
that bit constant 0, killed MCR-2's video path and pruned 27 of its 34 BSRAM
blocks. The probe has to keep both cores genuinely live:

- select on something provably NON-constant (it now uses `key_s2`, a real pin)
- fold the second core's outputs into an actual output (here: XOR-reduced into
  the beacon's aux2) so nothing downstream can be swept

Always sanity-check `probe_mcr2`'s BSRAM in
`impl/gwsynthesis/merge_probe_syn_rsc.xml` against the standalone core's
figure (34) before trusting a total.
