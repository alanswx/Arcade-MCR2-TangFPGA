# future/ — parked cores (not in any build)

Vendored-and-adapted cores that are **out of scope for the current board
revision** and deliberately excluded from the build/OSD roster. They stay
here, ready, until a board revision that supports what they need.

## mcr3mono.vhd — MCR3Mono (Rampage, Sarge, Max RPM, Power Drive, Star Guards)

**Parked for a future board revision** (2026-07). The core is vendored and
platform-adapted (dprams + hcnt_out; see the git history and
`docs/mcr_core_roadmap.md` Phase E), but the MCR3Mono *board* is a different
target from the SSIO-family shield rev A:

- **Different cabinet connectors.** The mono board routes its SSIO input
  ports to different physical connectors than the SSIO board (mono:
  IP0/IP1→J2, IP2→J3, IP4→J4), so it needs its own connector set — the
  rev-A shield targets the SSIO-family connectors only.
- **3 players.** Rampage is 3-player (P1/P2/P3 sticks + buttons), beyond the
  1–2 player layout the current shield/board is scoped for.
- **Analog controls.** Max RPM uses potentiometer wheels/pedals via an
  ADC0844 — needs the (populate-optional) ADC block, which is itself a
  later shield addition.

To bring it back: move `mcr3mono.vhd` to `src/rtl/`, vendor its sound stack
(`cpu09l_128a.vhd` = Turbo Cheap Squeak's 6809, `turbo_cheap_squeak.vhd`,
`sounds_good.vhd` = FX68K, `pia6821.vhd`, FX68K — all verified Gowin-clean
in `refs/Arcade-MCR3Mono_MiSTer/`), and build the mono board per Phase E.
Once Turbo Cheap Squeak exists, `demoderb` (4-player Demolition Derby) also
becomes reachable on the existing MCR-2 core.

Not parked here: MCR3Scroll (Spy Hunter / Crater / Turbo Tag) stays in the
active roster — it uses the SSIO-family connectors, and Spy Hunter's ADC is
the same populate-optional block.
