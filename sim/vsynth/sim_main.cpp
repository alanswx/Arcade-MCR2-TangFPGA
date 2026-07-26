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
    const int DUMP_FRAME = 24, DUMP_LINES = 24;   // output raster is ~177 Hz here;
                                                 // wait for several 60 Hz source frames

    uint64_t t = 0, ti = HI, to = HO;
    top->i_clk = 0; top->o_clk = 0; top->reset_na = 0;
    top->eval();

    FILE* f = fopen("ascal_synth480_out.txt", "w");
    int frame = 0, ox = 0, oy = 0;
    int vs_d = 0, de_d = 0, o_clk_d = 0;
    bool done = false;
    uint64_t evals = 0;

    while (!done) {
        uint64_t nt = std::min(ti, to);
        t = nt;
        if (t >= 200000) top->reset_na = 1;      // release reset at 200 ns
        if (ti == t) { top->i_clk = !top->i_clk; ti += HI; }
        if (to == t) { top->o_clk = !top->o_clk; to += HO; }
        top->eval();
        evals++;

        // sample on o_clk rising edge
        if (top->o_clk && !o_clk_d) {
            int vs = top->o_vs, de = top->o_de;
            if (vs && !vs_d) { frame++; oy = 0; }
            if (de && !de_d) ox = 0;
            if (de) {
                if (frame == DUMP_FRAME && oy < DUMP_LINES)
                    fprintf(f, "%d %d %02x%02x%02x\n", ox, oy,
                            top->o_r, top->o_g, top->o_b);
                ox++;
            }
            if (!de && de_d) oy++;
            vs_d = vs; de_d = de;
            if (frame > DUMP_FRAME) {
                printf("done: himax=%u dcpt=%u evals=%llu\n",
                       top->dbg_i_himax, top->dbg_o_dcpt,
                       (unsigned long long)evals);
                done = true;
            }
        }
        o_clk_d = top->o_clk;
        if (t > 200000000000ULL) { printf("timeout\n"); break; }   // 200 ms
    }
    fclose(f);
    delete top;
    return 0;
}
