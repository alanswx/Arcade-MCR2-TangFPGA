# Our own scaler — feature spec

The fallback if the ascal Verilog port (`docs/ascal_port_notes.md`) dead-ends,
and worth doing regardless: these four features are what we actually want from
ascal, none of them need ascal, and all four sidestep the four GowinSynthesis
defects that file triggers.

**We already have two working scalers on this silicon**, both proven with the
`video_test60k/` A/B rig:

| | BRAM (`src/video/bram_scaler.sv`) | DDR3 (`src/ddr3fb/ddr3_framebuffer.v`) |
|---|---|---|
| Logic | 1788 (3%) | ~4500 (8%) |
| BSRAM | 90/118 | ~9 |
| hclk Fmax | **106.6 MHz** | 82-83 MHz |
| Scaling | correct | correct |
| Audio, 15 s | **0 lost cycles** | 1 lost cycle |
| Tearing | yes (single-buffered) | yes (single-buffered) |

Both scale correctly — which ascal never managed here. What they lack is
below, in priority order.

---

## 1. Triple buffering — highest value, do first

**Problem.** Both are single-buffered: the reader scans the same memory the
writer is filling, so a 60.09 vs 60.00 Hz source/output mismatch produces a
slowly drifting **tear line**. Confirmed visually on both builds.

**Design** (ascal's, `buf_offset(buf, RAMBASE, RAMSIZE)`):

```
BUF_STRIDE = FB_SIZE * 2                 // address units per frame
wr_base    = wr_buf * BUF_STRIDE         // 0/1/2 -> a cheap 3:1 mux
rd_base    = rd_buf * BUF_STRIDE
```

Three registers, all in the `clk_x1` domain (no new CDC — `fb_vsync` is
already crossed there as `b_vsync_toggle_rr`, and the shadow raster `scy/scx`
is native to it):

```
wr_buf   currently being written
rd_buf   currently being scanned out
latest   most recently COMPLETED buffer
```

Rules:
* on source vsync: `latest <= wr_buf;  wr_buf <= 3 - wr_buf - rd_buf;`
  (the remaining index of {0,1,2} — writer never picks the one being read)
* on output frame start (`scx==0 && scy==0`): `rd_buf <= latest;`

Then add `wr_base` to `wr_addr`, and initialise `prefetch_addr_line` to
`rd_base` instead of 0.

**Cost.** ~50 lines. Memory 3 x 492 KB = 1.5 MB of 512 MB. Address width grows
by 2 bits (`FB_SIZE*2*3` = 21 bits, well inside the 28-bit `app_addr`).
**Result: tearing eliminated entirely.**

Gate behind `parameter TRIPLE_BUFFER = 0` so the production MCR cores keep
current behaviour until it is proven on the `video_test60k` rig.

---

## 2. Burst reads into a ping-pong line buffer

**Problem.** `ddr3_framebuffer` reads **4 pixels per DDR3 command** into a
32-entry buffer, prefetching ~44 pixels ahead. That is a lot of small
transactions, it is intolerant of refresh and latency spikes, and on underrun
the output silently substitutes grey `0x202020` — an invisible, unlogged
glitch. This is the most likely cause of the residual artifacts.

**Design** (ascal's `o_dpram`, sized `BLEN*2`): fetch a whole burst — up to
`N_BURST` bytes — into a double-buffered line cache. Scan out of one half
while the other fills. One large transaction per line instead of ~128 small
ones.

**Why it helps.** DDR3 is far more efficient on long bursts within an open
row, and a full-line cache absorbs refresh stalls that a 32-entry buffer
cannot. Removes the underrun path rather than papering over it.

**Cost.** ~100 lines plus a BSRAM line buffer (512 px x 12 bpp = 6 Kbit, well
under one block). **Add an underrun counter to the UART beacon** — it should
read zero, and if it does not we will know instead of guessing.

---

## 3. Input auto-detection

**Problem.** `fb_width`/`fb_height` must be told to the framebuffer, so
15 kHz vs 31 kHz needs a strap and a new core needs a recompile.

**Design.** Measure it the way ascal does — and note **ascal's detection logic
demonstrably works on Gowin**: it reported 511/479 correctly throughout the
investigation, so this part is safe to copy.

```
hcnt resets on i_de rising edge, increments per pixel enable
i_himax <= hcnt on i_de falling edge
i_vimax <= vcnt on i_vs edge
width = i_himax + 1;  height = i_vimax + 1
```

Latch at vsync so geometry only changes between frames.

**Cost.** ~30 lines. One bitstream then handles any source resolution.

---

## 4. Parameterised output timing

**Problem.** `ddr3_framebuffer` is hardwired to 720p (`FRAME_W=1650`,
`FRAME_H=750` appear as literals).

**Design.** Promote the raster totals to parameters
(`htotal/hsstart/hsend/hdisp` + `v*`), as ascal does, so 1080p or a 15 kHz
output mode becomes a constant change. The `hdmi` module already takes
`VIDEO_ID_CODE`; the PLL chain would need matching TMDS rates.

**Cost.** ~20 lines of parameterisation, plus PLL work per new mode.

---

## Not worth reimplementing

**Polyphase / bicubic interpolation.** This is the one thing ascal offers that
we cannot cheaply match — and it is exactly where the DSPs go and where
`CK3001` triggers. Sharp-bilinear (which we have) is the accepted sweet spot
for arcade content anyway. Revisit only if a working ascal appears.

---

## Suggested order

1. Triple buffering on `video_test60k/ddr3_top.sv` — measure the tear before
   and after with the capture card.
2. Underrun counter in the beacon (one line, tells us if #2 is even needed).
3. Burst reads, if the counter says underruns are real.
4. Auto-detect, then parameterised timing.
5. Promote to `mcr2_console60k` / `mcr3_console60k` once proven on the rig.

**Also worth considering:** at 240p a BRAM framebuffer is only ~45 blocks, so
**double-buffering entirely in BRAM (~90 blocks) gives zero tearing with no
DDR3 at all** — and the BRAM path already has ~24 MHz more timing margin and
measurably cleaner audio. Storing a 6-bit palette index instead of RGB (MCR's
palette is 64 x 9, exactly nestang's trick) brings 480p into range too.
