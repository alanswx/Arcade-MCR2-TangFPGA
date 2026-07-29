// Verilator harness. Drives i_clk (40 MHz) and o_clk (74.25 MHz) on a
// picosecond timebase and dumps one settled output frame in the same
// "x y rrggbb" format tools/ascal_sim_check.py reads.
#include "Vsynth_top.h"
#include "verilated.h"
#include <cstdio>
#include <cstdint>
#include <algorithm>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vsynth_top* top = new Vsynth_top;

    const uint64_t HI = 12500;   // i_clk half period, ps (40 MHz)
    const uint64_t HO = 6734;    // o_clk half period, ps (74.25 MHz)
    // avl_clk is a SEPARATE 74.25 MHz clock in hardware (DDR3 controller
    // clk_x1, its own PLL). Same nominal rate, independent phase - model it,
    // otherwise every avl<->o crossing is hidden.
    const uint64_t HA = 6737;    // avl_clk half period, ps (deliberately skewed)
    const int FIRST_FRAME = 6;    // let the framebuffer fill
    const int NFRAMES     = 20;   // the transition defect hits ~7% of frames,
                                  // so a handful is not enough to see it
    const int DUMP_LINES  = 720;

    uint64_t t = 0, ti = HI, to = HO, ta = HA;
    top->i_clk = 0; top->o_clk = 0; top->avl_clk_in = 0; top->reset_na = 0;
    top->eval();

    // Per-line SIGNATURE rather than pixels: a 7%-of-frames defect needs many
    // frames, and 24 full pixel dumps is ~22M lines of text. A 32-bit hash per
    // output line is enough to tell WHICH source line was displayed, which is
    // exactly what the defect corrupts.
    FILE* f = fopen("ascal_v_sig.txt", "w");
    uint32_t lh = 2166136261u;
    FILE* g = fopen("ascal_v_px.txt", "w");
    int frame = 0, ox = 0, oy = 0;
    int vs_d = 0, de_d = 0, o_clk_d = 0;
    bool done = false;
    uint64_t evals = 0;

    while (!done) {
        uint64_t nt = std::min(std::min(ti, to), ta);
        t = nt;
        if (t >= 200000) top->reset_na = 1;      // release reset at 200 ns
        if (ti == t) { top->i_clk = !top->i_clk; ti += HI; }
        if (to == t) { top->o_clk = !top->o_clk; to += HO; }
        if (ta == t) { top->avl_clk_in = !top->avl_clk_in; ta += HA; }
        top->eval();
        evals++;

        // sample on o_clk rising edge
        if (top->o_clk && !o_clk_d) {
            int vs = top->o_vs, de = top->o_de;
            if (vs && !vs_d) { frame++; oy = 0; }
            if (de && !de_d) ox = 0;
            if (de) {
                if (frame >= FIRST_FRAME && frame < FIRST_FRAME + NFRAMES
                    && oy >= 118 && oy <= 126 && ox >= 160 && ox < 260)
                    fprintf(g, "%d %d %d %02x%02x%02x\n", frame, oy, ox,
                            top->o_r, top->o_g, top->o_b);
                if (ox >= 160 && ox <= 1119) {          // visible window only
                    lh ^= (uint32_t)((top->o_r << 16) | (top->o_g << 8) | top->o_b);
                    lh *= 16777619u;                     // FNV-1a
                }
                ox++;
            }
            if (!de && de_d) {
                if (frame >= FIRST_FRAME && frame < FIRST_FRAME + NFRAMES
                    && oy < DUMP_LINES)
                    fprintf(f, "%d %d %08x %d %d\n", frame, oy, lh, (int)top->dbg_o_dcpt, (int)top->dbg_und);
                lh = 2166136261u;
                oy++;
            }
            vs_d = vs; de_d = de;
            if (frame >= FIRST_FRAME + NFRAMES) {
                printf("done: himax=%u dcpt=%u evals=%llu\n",
                       top->dbg_i_himax, top->dbg_o_dcpt,
                       (unsigned long long)evals);
                done = true;
            }
        }
        o_clk_d = top->o_clk;
        if (t > 700000000000ULL) { printf("timeout\n"); break; }   // 200 ms
    }
    fclose(f); fclose(g);
    delete top;
    return 0;
}
