//-----------------------------------------------------------------------------
// ascal_v - DDR3-backed video scaler in Verilog, ascal architecture
//-----------------------------------------------------------------------------
// A hand port of the parts of Temlib's ascal.vhd that we actually need, written
// as idiomatic Verilog so GowinSynthesis infers it normally. See
// docs/ascal_port_notes.md for why: ascal itself is miscompiled on this device
// (horizontal advance renders the source into a quarter of the window, then
// repeats), and ten hypotheses were eliminated without finding it.
//
// TRIPWIRE (from the port plan): this is NEAREST-NEIGHBOUR only. Test it on
// hardware BEFORE writing any interpolator. If nearest renders correctly the
// port is viable; if it shows the same 4x/512-period signature, stop and use
// docs/scaler_features.md instead.
//
// Deliberate simplifications vs ascal, all of which remove machinery that was
// pure overhead for us:
//   * 16 bits per pixel (RGB444 padded), so exactly 8 pixels per 128-bit word
//     and a line stride that is a whole number of words. ascal packs 24bpp,
//     which is why it needs o_off/o_pshift/sSHIFT burst-offset juggling at all
//     - and that machinery is where its two independent o_hacpt increments
//     live. Removing it removes a whole class of bug.
//   * no interlace, no palette, no framebuffer mode, no image header,
//     no downscaling.
//   * triple buffering built in from the start (ascal's mode[3]).
//
// Interface deliberately matches ascal_gw.vhd so it drops into the existing
// ascal_test60k rig and the verilator harness in sim/vsynth/ unchanged.
//-----------------------------------------------------------------------------
`default_nettype none

module ascal_v #(
    parameter N_DW      = 128,        // Avalon data width
    parameter N_AW      = 25,         // Avalon word address width (16B words)
    parameter MAX_WIDTH = 1024,       // max source width (line buffer sizing)
    parameter RAMBASE   = 25'd0,      // word address of buffer 0
    parameter BUF_WORDS = 25'd65536,  // words per frame buffer (1 MB)
    // output raster, 720p60 by default
    parameter HTOTAL = 1650, parameter HSSTART = 1390,
    parameter HSEND  = 1430, parameter HDISP   = 1280,
    parameter VTOTAL = 750,  parameter VSSTART = 725,
    parameter VSEND  = 730,  parameter VDISP   = 720
)(
    //---------------------------------------------- input video (i_clk domain)
    input  wire        i_clk,
    input  wire        i_ce,
    input  wire [7:0]  i_r,
    input  wire [7:0]  i_g,
    input  wire [7:0]  i_b,
    input  wire        i_vs,          // ACTIVE HIGH
    input  wire        i_de,

    //--------------------------------------------- output video (o_clk domain)
    input  wire        o_clk,
    output reg  [7:0]  o_r,
    output reg  [7:0]  o_g,
    output reg  [7:0]  o_b,
    output reg         o_hs,          // ACTIVE HIGH
    output reg         o_vs,          // ACTIVE HIGH
    output reg         o_de,

    //------------------------------------------------------------- control
    input  wire        run,
    input  wire        triple_buf,    // 1 = triple buffering (no tearing)
    // External raster. hdl-util `hdmi` is a timing MASTER (its cx/cy are
    // outputs and it expects rgb for the current coordinate), so when it
    // drives the output stage the scaler must FOLLOW it rather than run its
    // own counters. Both rasters are 1650x750 on the same 74.25 MHz clock,
    // so everything downstream is unchanged.
    input  wire        ext_rast,      // 1 = take ocx/ocy from ext_cx/ext_cy
    input  wire [11:0] ext_cx,
    input  wire [11:0] ext_cy,
    input  wire [11:0] hmin,
    input  wire [11:0] hmax,
    input  wire [11:0] vmin,
    input  wire [11:0] vmax,
    output reg  [11:0] i_hdmax,       // detected source width - 1
    output reg  [11:0] i_vdmax,       // detected source height - 1

    //--------------------------------------------------- Avalon-MM master
    input  wire        avl_clk,
    input  wire        avl_waitrequest,
    input  wire [N_DW-1:0] avl_readdata,
    input  wire        avl_readdatavalid,
    output wire [7:0]  avl_burstcount,
    output wire [N_DW-1:0] avl_writedata,
    output wire [N_AW-1:0] avl_address,
    output wire        avl_write,
    output wire        avl_read,
    output wire [N_DW/8-1:0] avl_byteenable,
    output wire [15:0] dbg_underrun,
    // A1 instrumentation: three sticky saturating counters, {geo, bad, fly}.
    //   geo = frames where the latched geometry CHANGED (expect 0 - i_hdmax
    //         is written the same value every vsync, so it never transitions)
    //   bad = frames where the synchronised buffer index was INVALID (>2)
    //   fly = frames where the index was still IN FLIGHT at the capture edge
    //         (latest_o1 != latest_o2), i.e. sampled mid-change. A 2FF sync
    //         stops metastability per bit but NOT incoherence across bits,
    //         and latest rotates 0->1->2 where 1->2 flips both bits at once.
    output wire [11:0] dbg_cdc,
    // Fetch instrumentation. dbg_fetch = line fetches ISSUED in the last
    // complete frame (must be 480: one per source line). dbg_lat = worst
    // request->completion latency in o_clk cycles for that frame (budget is
    // HTOTAL = 1650). Together these split the space: too few fetches means
    // the ISSUE logic is wrong; latency over budget means MEMORY is late.
    output wire [11:0] dbg_sy,     // source line currently displayed
    output wire [11:0] dbg_fetch,
    output wire [15:0] dbg_lat,

    input  wire        reset_n
);

    localparam PPW    = N_DW/16;              // pixels per word = 8
    localparam BURSTW = 8;                    // words per burst = 128 bytes
    localparam WORDS_PER_LINE = MAX_WIDTH/PPW;  // whole words - no burst offset

    //=========================================================================
    // INPUT SIDE (i_clk) - capture, auto-detect geometry, pack into words
    //=========================================================================
    reg [11:0] i_hcnt = 0, i_vcnt = 0;
    reg        i_de_d = 0, i_vs_d = 0;
    reg [11:0] i_himax = 0, i_vimax = 0;

    // 16-bit store: RGB444 in the low 12 bits
    wire [15:0] i_pix = {4'd0, i_r[7:4], i_g[7:4], i_b[7:4]};

    reg [N_DW-1:0] i_shift = 0;               // pixel packer
    reg [$clog2(PPW)-1:0] i_pcnt = 0;         // pixels accumulated (0..PPW-1)
    reg            i_word_valid = 0;          // one pulse per full word
    reg [N_DW-1:0] i_word = 0;

    always @(posedge i_clk) begin
        i_word_valid <= 1'b0;
        if (!reset_n) begin
            i_hcnt <= 0; i_vcnt <= 0; i_pcnt <= 0;
            i_himax <= 0; i_vimax <= 0;
        end else if (i_ce) begin
            i_de_d <= i_de;
            i_vs_d <= i_vs;

            // ---- geometry auto-detect (ascal's method; proven on Gowin) ----
            if (i_de && !i_de_d) i_hcnt <= 0;          // line starts
            else if (i_de)       i_hcnt <= i_hcnt + 1'b1;
            if (!i_de && i_de_d) begin                 // line ends
                i_himax <= i_hcnt;                     // width - 1
                i_vcnt  <= i_vcnt + 1'b1;
            end
            if (i_vs && !i_vs_d) begin                 // frame ends
                i_vimax <= i_vcnt - 1'b1;
                i_vcnt  <= 0;
                i_hdmax <= i_himax;
                i_vdmax <= i_vcnt - 1'b1;
            end

            // ---- pack pixels into words ----
            // Pack by INDEX so pixel k lands at bits [k*16 +: 16] and the
            // reader's [k*16 +: 16] gets the same pixel back. Shift-register
            // packing reverses the order and is easy to get wrong.
            if (i_de && !i_de_d) begin                 // line start
                i_shift <= {{(N_DW-16){1'b0}}, i_pix};
                i_pcnt  <= 3'd1;
            end else if (i_de) begin
                i_shift[i_pcnt*16 +: 16] <= i_pix;
                if (i_pcnt == PPW[$clog2(PPW)-1:0]-1'd1) begin
                    i_word       <= i_shift | ({{(N_DW-16){1'b0}}, i_pix} << (i_pcnt*16));
                    i_word_valid <= 1'b1;
                    i_pcnt       <= '0;
                    i_shift      <= {N_DW{1'b0}};
                end else
                    i_pcnt <= i_pcnt + 1'd1;
            end
        end
    end

    //=========================================================================
    // CDC: source words into the Avalon domain
    //=========================================================================
    wire            wfifo_rd;
    wire            wfifo_valid;
    wire [N_DW-1:0] wfifo_data;
    reg             i_vs_tog = 0;
    always @(posedge i_clk) if (i_ce && i_vs && !i_vs_d) i_vs_tog <= ~i_vs_tog;

    // Own CDC FIFO rather than gbatang's asyncfifo: keeps this module
    // self-contained, and its `output reg` ports trip verilator's BLKANDNBLK.
    // Gray-code pointers, 32 deep. Only ever written by i_clk and read by
    // avl_clk, so the only crossings are the two gray pointers.
    localparam FA = 5;
    reg [N_DW-1:0] fmem [0:(1<<FA)-1];
    reg [FA:0] wptr = 0, rptr = 0;
    reg [FA:0] wgry_a1 = 0, wgry_a2 = 0, rgry_i1 = 0, rgry_i2 = 0;
    wire [FA:0] wgry = wptr ^ (wptr >> 1);
    wire [FA:0] rgry = rptr ^ (rptr >> 1);

    always @(posedge i_clk) begin
        if (!reset_n) wptr <= 0;
        else if (i_word_valid) begin
            fmem[wptr[FA-1:0]] <= i_word;
            wptr <= wptr + 1'b1;
        end
        rgry_i1 <= rgry; rgry_i2 <= rgry_i1;
    end

    always @(posedge avl_clk) begin
        if (!reset_n) rptr <= 0;
        else if (wfifo_rd && wfifo_valid) rptr <= rptr + 1'b1;
        wgry_a1 <= wgry; wgry_a2 <= wgry_a1;
    end

    // Occupancy, so a burst is only started when a WHOLE burst is available.
    // Starting an 8-word burst with one word present writes seven words of
    // garbage: the input side produces a word every 8 pixels (2.5 MHz) while
    // the Avalon side drains at 74.25 MHz, so the FIFO is nearly always
    // near-empty and this fires constantly.
    function automatic [FA:0] g2b(input [FA:0] g);
        integer i;
        begin
            g2b[FA] = g[FA];
            for (i = FA-1; i >= 0; i = i - 1) g2b[i] = g2b[i+1] ^ g[i];
        end
    endfunction
    wire [FA:0] wbin_a = g2b(wgry_a2);
    wire [FA:0] fifo_lvl = wbin_a - rptr;
    wire        fifo_has_burst = (fifo_lvl >= BURSTW[FA:0]);

    assign wfifo_valid = (wgry_a2 != rgry);
    assign wfifo_data  = fmem[rptr[FA-1:0]];

    reg vt_s1 = 0, vt_s2 = 0, vt_s3 = 0;
    always @(posedge avl_clk) begin vt_s1 <= i_vs_tog; vt_s2 <= vt_s1; vt_s3 <= vt_s2; end
    wire a_frame_start = (vt_s3 != vt_s2);

    //=========================================================================
    // TRIPLE BUFFERING - three base addresses, writer never picks the one
    // being read. Straight out of ascal's buf_offset()/buf_next().
    //=========================================================================
    // wr_buf/latest live in avl_clk; rd_buf lives in o_clk. `latest` and
    // `rd_buf` are 2-bit and change only at frame boundaries, so a 2FF
    // synchroniser each way is sufficient and cannot tear mid-transfer.
    reg [1:0] wr_buf = 0, latest = 1;               // avl_clk
    reg [1:0] rd_buf = 1;                           // o_clk
    reg [1:0] rdbuf_a1 = 1, rdbuf_a2 = 1;           // rd_buf  -> avl_clk
    reg [1:0] latest_o1 = 1, latest_o2 = 1;         // latest  -> o_clk
    wire [1:0] free_buf = 2'd3 - wr_buf - rdbuf_a2; // remaining index of {0,1,2}

    function [N_AW-1:0] base_of(input [1:0] b);
        base_of = RAMBASE + (b == 2'd0 ? {N_AW{1'b0}} :
                             b == 2'd1 ? BUF_WORDS[N_AW-1:0]
                                       : {BUF_WORDS[N_AW-2:0], 1'b0});
    endfunction

    //=========================================================================
    // AVALON MASTER - line writes and line reads, both whole bursts
    //=========================================================================
    localparam A_IDLE = 3'd0, A_WR = 3'd1, A_RD = 3'd2, A_RDWAIT = 3'd3;

    reg [2:0]      a_state = A_IDLE;
    reg [N_AW-1:0] a_addr  = 0;
    reg [7:0]      a_beat  = 0;
    reg [N_AW-1:0] wr_ptr  = 0;         // next word address to write
    reg            frame_pend = 0;      // vsync seen, waiting for FIFO drain
    reg [2:0]      drain_cnt  = 0;

    // read request from the output side (crossed below)
    reg            rq_tog = 0, rq_s1 = 0, rq_s2 = 0;
    reg [N_AW-1:0] rq_addr = 0;
    reg [7:0]      rq_len  = 0;
    reg            rq_buf  = 0;         // line buffer half the fetch fills
    // REQUEST LATCH - do not go back to comparing rq_s1/rq_s2 directly.
    // The 2FF synchroniser advances rq_s2 EVERY cycle, so `rq_s1 != rq_s2` is
    // a ONE-CYCLE PULSE, not a level. Treating it as a level silently drops
    // any request that arrives while the FSM is not in A_IDLE - which is the
    // occasional lost line behind the wrong-row glitch.
    reg            rd_req = 0;
    wire           rd_pending = rd_req;
    // read-completion toggle, avl -> o_clk, so the output side can tell
    // whether the prefetched line actually landed before it is needed.
    reg            rd_done = 0, done_s1 = 0, done_s2 = 0;
    // Integrity counters (avl domain). A fetch MUST deliver exactly rq_len
    // words into its half. `short_cnt` counts fetches that did not.
    reg [15:0]     short_cnt = 0;
    reg            seen_rd   = 0;
    // A fill must NEVER target the half currently being displayed. If it
    // does, the intended half keeps its stale content (which is exactly the
    // observed symptom) and the on-screen half is overwritten.
    reg [15:0]     collide_cnt = 0;
    reg [7:0]      rq_len_l = 0;
    reg            rq_buf_l = 0;

    assign avl_byteenable = {(N_DW/8){1'b1}};
    // Write bursts may be SHORT at end of frame - see the drain logic below.
    reg [7:0] wlen_q = BURSTW[7:0];
    assign avl_burstcount = (a_state == A_WR) ? wlen_q : rq_len;
    assign avl_address    = a_addr;
    assign avl_writedata  = wfifo_data;
    assign avl_write      = (a_state == A_WR);
    assign avl_read       = (a_state == A_RD);
    assign wfifo_rd       = (a_state == A_WR) && !avl_waitrequest;

    always @(posedge avl_clk) begin
        rq_s1 <= rq_tog; rq_s2 <= rq_s1;
        rdbuf_a1 <= rd_buf; rdbuf_a2 <= rdbuf_a1;
        if (!reset_n) begin
            a_state <= A_IDLE; wr_ptr <= 0; a_beat <= 0;
            wr_buf <= 0; latest <= 1;
        end else begin
            // Buffer switch is DEFERRED until the write FIFO has drained.
            // Switching immediately at vsync leaves the tail of frame k in the
            // FIFO; those words are then written at wr_ptr 0 of frame k+1's
            // buffer and displace the whole picture by a number of lines that
            // varies with FIFO occupancy at the vsync instant. Measured on
            // hardware as a 1-2 line VERTICAL jitter with horizontal position
            // rock steady - the asymmetry that identifies a whole-line offset.
            // ascal avoids this by deriving each write address from the LINE
            // NUMBER (ascal.vhd:1271) rather than a free-running pointer;
            // draining before the switch achieves the same invariant here.
            if (a_frame_start) begin
                frame_pend <= 1'b1;
                drain_cnt  <= 3'd0;
            end else if (frame_pend && a_state == A_IDLE && fifo_lvl == 0) begin
                // fifo_lvl is derived from a 2FF-synced pointer and so lags by
                // a couple of cycles; settle before believing "empty".
                if (drain_cnt == 3'd7) begin
                    latest     <= wr_buf;
                    wr_buf     <= triple_buf ? free_buf : wr_buf;
                    wr_ptr     <= 0;
                    frame_pend <= 1'b0;
                end else
                    drain_cnt <= drain_cnt + 1'b1;
            end else if (frame_pend) begin
                drain_cnt <= 3'd0;
            end

            case (a_state)
                A_IDLE: begin
                    a_beat <= 0;
                    if (rd_pending) begin           // reads take precedence
                        a_addr  <= rq_addr;
                        a_state <= A_RD;
                    end else if (fifo_has_burst ||
                                 (frame_pend && fifo_lvl != 0)) begin
                        // At frame end allow a SHORT burst so a partial burst
                        // cannot be stranded in the FIFO and carried over.
                        a_addr  <= base_of(wr_buf) + wr_ptr;
                        wlen_q  <= fifo_has_burst ? BURSTW[7:0]
                                                  : {{(8-($bits(fifo_lvl))){1'b0}}, fifo_lvl};
                        a_state <= A_WR;
                    end
                end

                A_WR: if (!avl_waitrequest) begin
                    a_beat <= a_beat + 1'b1;
                    wr_ptr <= wr_ptr + 1'b1;
                    if (a_beat == wlen_q - 8'd1) a_state <= A_IDLE;
                end

                A_RD: if (!avl_waitrequest) begin
                    // Before retargeting the fill side, check the PREVIOUS
                    // fetch actually delivered a full line.
                    if (seen_rd && lb_wr != rq_len_l[LBW-1:0])
                        short_cnt <= short_cnt + 1'b1;
                    seen_rd  <= 1'b1;
                    rq_len_l <= rq_len;             // latch for the fill side
                    rq_buf_l <= rq_buf;
                    a_state  <= A_IDLE;
                end

                default: a_state <= A_IDLE;
            endcase

            // Set beats clear: a request arriving in the same cycle the
            // current one is accepted must not be lost.
            if (rq_s1 != rq_s2)
                rd_req <= 1'b1;
            else if (a_state == A_RD && !avl_waitrequest)
                rd_req <= 1'b0;
        end
    end

    //=========================================================================
    // OUTPUT SIDE (o_clk) - raster, line fetch, nearest-neighbour scaling
    //=========================================================================
    reg        disp_buf = 0;
    reg [11:0] ocx = 0, ocy = 0;
    always @(posedge o_clk) begin
        if (!reset_n) begin ocx <= 0; ocy <= 0; end
        else if (ext_rast) begin
            ocx <= ext_cx; ocy <= ext_cy;
        end else begin
            if (ocx == HTOTAL-1) begin
                ocx <= 0;
                ocy <= (ocy == VTOTAL-1) ? 12'd0 : ocy + 1'b1;
            end else
                ocx <= ocx + 1'b1;
        end
    end

    wire in_win = (ocx >= hmin) && (ocx <= hmax) &&
                  (ocy >= vmin) && (ocy <= vmax);

    // geometry, latched per frame from the input side (slow-changing)
    reg [11:0] o_iw = 12'd512, o_ih = 12'd480;
    reg [3:0]  cdc_geo = 0, cdc_bad = 0, cdc_fly = 0;
    assign dbg_cdc = {cdc_geo, cdc_bad, cdc_fly};

    always @(posedge o_clk) if (ocx == 0 && ocy == 0) begin
        o_iw <= i_hdmax + 1'b1;
        o_ih <= i_vdmax + 1'b1;
        if ((i_hdmax + 1'b1) != o_iw || (i_vdmax + 1'b1) != o_ih)
            if (cdc_geo != 4'hF) cdc_geo <= cdc_geo + 1'b1;
        if (latest_o2 > 2'd2)
            if (cdc_bad != 4'hF) cdc_bad <= cdc_bad + 1'b1;
        if (latest_o1 != latest_o2)
            if (cdc_fly != 4'hF) cdc_fly <= cdc_fly + 1'b1;
    end
    wire [11:0] o_ow = hmax - hmin + 1'b1;
    // Words the WRITER actually emits per line = ceil(width / PPW). Using
    // MAX_WIDTH/PPW here instead made the reader step two writer-lines per
    // source line and read from the wrong addresses entirely.
    wire [11:0] line_words = (o_iw + PPW[11:0] - 12'd1) >> $clog2(PPW);
    wire [11:0] o_oh = vmax - vmin + 1'b1;

    // ---- line buffer: one source line, WORD-wide.
    // Storing pixels would need 8 write ports (we receive 8 pixels per
    // 128-bit word) which no block RAM can provide - GowinSynthesis then
    // builds it from 16k flip-flops and the read becomes a 1024-way mux.
    // Storing WORDS gives one write port (1 BSRAM block) and turns the read
    // into a word fetch plus an 8:1 pixel mux. This is what ascal's o_dpram
    // does, and it is why it is word-wide there too.
    localparam LBW = $clog2(WORDS_PER_LINE);
    // TWO halves, ping-pong: the raster scans one while the next source line
    // is prefetched into the other. With a single buffer the fetch for line L
    // was issued at ocx==1 and filled the very RAM being scanned - and since
    // o_de starts at ocx==0, the only slack was the 160 px pillarbox. A DDR3
    // model answers fast enough to win that race; real DDR3 with refresh and
    // write traffic does not, and the reader then scans a half-written line.
    // That is the colourful-horizontal-streak corruption.
    (* ram_style = "block" *) reg [N_DW-1:0] linebuf [0:2*WORDS_PER_LINE-1];
    reg [LBW-1:0] lb_wr = 0;

    always @(posedge avl_clk) begin
        if (!reset_n) begin
            lb_wr <= 0; rd_done <= 0;
        end else if (a_state == A_RD && !avl_waitrequest) begin
            lb_wr <= 0;
        end else if (avl_readdatavalid) begin
`ifdef ASCALV_TRACE
            if (lb_wr == 0)
                $display("TRACE FILL  half=%0b px4_7=%h", rq_buf_l, avl_readdata[127:64]);
`endif
            if (rq_buf_l == disp_buf) collide_cnt <= collide_cnt + 1'b1;
            linebuf[{rq_buf_l, lb_wr}] <= avl_readdata;
            lb_wr <= lb_wr + 1'b1;
            if (lb_wr == rq_len_l[LBW-1:0] - 1'b1) rd_done <= ~rd_done;
        end
    end

    // ---- Bresenham, plain compare - no modular sign trick (see port notes)
    reg [12:0] xacc = 0;
    reg [11:0] sx   = 0;

    always @(posedge o_clk) begin
        if (ocx == 0) begin                       // new output line
            xacc <= 0; sx <= 0;
        end else if (in_win) begin
            if (xacc + {1'b0,o_iw} >= {1'b0,o_ow}) begin
                xacc <= xacc + {1'b0,o_iw} - {1'b0,o_ow};
                sx   <= sx + 1'b1;
            end else
                xacc <= xacc + {1'b0,o_iw};
        end
    end

    // word fetch, then 8:1 pixel mux one cycle later
    reg [N_DW-1:0] lb_word = 0;
    reg [2:0]      px_sel  = 0;
    reg [15:0]     px      = 0;
    always @(posedge o_clk) begin
`ifdef ASCALV_TRACE
        if (ocx == 200 && ocy >= 118 && ocy <= 125)
            $display("TRACE show  ocy=%0d half=%0b px4_7=%h", ocy, disp_buf,
                     linebuf[{disp_buf, 7'd0}][127:64]);
`endif
        lb_word <= linebuf[{disp_buf, sx[LBW+2:3]}];
        px_sel  <= sx[2:0];
        px      <= lb_word[px_sel*16 +: 16];
    end

    always @(posedge o_clk) begin
        o_hs <= (ocx >= HSSTART) && (ocx < HSEND);
        // Continuous pulse VSSTART..VSEND-1. Asserting only on the two
        // endpoint lines gives a broken vsync: monitors trigger on the
        // leading edge and still show a picture, but capture cards and
        // stricter sinks refuse to lock.
        o_vs <= (ocy >= VSSTART) && (ocy < VSEND);
        o_de <= (ocx < HDISP) && (ocy < VDISP);
        if (!run) begin
            o_r <= 8'h00; o_g <= 8'h00; o_b <= 8'h00;
        end else if (in_win) begin
            o_r <= {px[11:8], px[11:8]};
            o_g <= {px[7:4],  px[7:4]};
            o_b <= {px[3:0],  px[3:0]};
        end else begin
            o_r <= 8'h20; o_g <= 8'h20; o_b <= 8'h20;   // pillarbox
        end
    end

    // ---- line prefetch, ONE FULL OUTPUT LINE AHEAD -------------------------
    // The vertical Bresenham is run a line early so the fetch for output line
    // L+1 is issued at the start of line L and has all HTOTAL cycles to land,
    // into the half that is NOT being scanned. The swap only happens once the
    // fetch has actually completed; if it has not, dbg_underrun counts it so
    // hardware can report starvation instead of us guessing from the picture.
    reg [12:0] yacc_a = 0;
    reg [11:0] sy_a   = 0;          // source line the NEXT output line needs

    // The lookahead value must be visible to the PREFETCH block in the same
    // ocx==0 cycle. Both blocks fire at ocx==0, and with non-blocking
    // assignment the prefetch would read the PRE-update sy_a - i.e. the line
    // needed by the line being displayed right now, not the next one. That
    // silently reduced the lead time from a full output line to just the
    // 160 px pillarbox and starved ~10% of lines (isolated wrong rows,
    // scattered through the high-detail bands, and dbg_underrun pegged).
    // Exposing the next value as a wire gives both blocks the same view.
    wire vstep_a = (yacc_a + {1'b0,o_ih}) >= {1'b0,o_oh};
    wire in_vwin = ((ocy + 1'b1) > vmin) && ((ocy + 1'b1) <= vmax);
    wire [11:0] sy_a_nxt = (ocy == VTOTAL-1) ? 12'd0
                         : (in_vwin && vstep_a) ? sy_a + 12'd1 : sy_a;

    always @(posedge o_clk) if (ocx == 0) begin
        if (ocy == VTOTAL-1) begin
            yacc_a <= 0;
        end else if (in_vwin) begin
            yacc_a <= vstep_a ? (yacc_a + {1'b0,o_ih} - {1'b0,o_oh})
                              : (yacc_a + {1'b0,o_ih});
        end
        sy_a <= sy_a_nxt;
    end

    reg        swap_req  = 0;       // an outstanding fetch is destined for display
    reg [11:0] sy_fill   = 12'hFFF; // source line that fetch is bringing in
    reg [11:0] sy_have   = 12'hFFF; // source line currently in disp_buf
    reg [15:0] underrun  = 0;   // this frame
    reg [15:0] und_rep   = 0;   // last COMPLETE frame - what the beacon shows
    assign dbg_underrun  = collide_cnt; // repurposed: fill-vs-display collisions

    wire rd_busy = (rq_tog != done_s2);
    wire [1:0] nrd = triple_buf ? latest_o2 : rd_buf;   // buffer for the new frame

    reg        rq_tog_d = 0, lat_run = 0;
    reg [15:0] lat_cnt = 0, lat_max = 0, lat_rep = 0;
    reg [11:0] fetches = 0, fetch_rep = 0;
    assign dbg_sy    = sy_have;
    assign dbg_fetch = fetch_rep;
    assign dbg_lat   = lat_rep;

    always @(posedge o_clk) begin
        rq_tog_d <= rq_tog;
        if (rq_tog != rq_tog_d) begin              // a fetch was just issued
            lat_cnt <= 16'd0;
            lat_run <= 1'b1;
            if (fetches != 12'hFFF) fetches <= fetches + 1'b1;
        end else if (lat_run) begin
            lat_cnt <= lat_cnt + 1'b1;
            if (!rd_busy) begin                    // it completed
                lat_run <= 1'b0;
                if (lat_cnt > lat_max) lat_max <= lat_cnt;
            end
        end
        if (ocx == 0 && ocy == 0) begin            // publish, then restart
            fetch_rep <= fetches; fetches <= 12'd0;
            lat_rep   <= lat_max; lat_max <= 16'd0;
        end
    end

    always @(posedge o_clk) begin
        done_s1 <= rd_done; done_s2 <= done_s1;
        latest_o1 <= latest; latest_o2 <= latest_o1;

        if (!reset_n) begin
            disp_buf <= 0; swap_req <= 0; underrun <= 0;
            sy_have  <= 12'hFFF; sy_fill <= 12'hFFF;
        end else if (ocx == 0 && ocy == VTOTAL-1) begin
`ifdef ASCALV_TRACE
            $display("TRACE ===FRAME===");
`endif
            // ---- DETERMINISTIC FRAME START ----------------------------------
            // Every frame must begin from an identical ping-pong phase.
            // Previously swap_req/disp_buf/sy_have/sy_fill carried over from
            // the previous frame, and the old `ocy==0` forced `nsy=12'hFFF`
            // made line 0 fetch a SECOND time (it had usually already been
            // fetched here and swapped in). That redundant fetch flipped the
            // ping-pong parity, so the whole fetch/display schedule could run
            // one output line early or late depending on carry-over state -
            // traced as `issue ocy=116` in one frame vs `issue ocy=115` in the
            // next for the same source line. A line was then stale in one
            // frame and correct in the next, clustered by buffer parity.
            // Setting up line 0 explicitly here also puts source line 0 on
            // output line 0 (it used to land on line 1) and makes the fetch
            // use the NEW rd_buf rather than the pre-update one.
`ifdef ASCALV_TRACE
            $display("TRACE framestart ocy=%0d nrd=%0d latest_o2=%0d", ocy, nrd, latest_o2);
`endif
            rd_buf   <= nrd;
            disp_buf <= 1'b1;               // line 0 lands in half 0, shown next
            sy_have  <= 12'hFFF;
            rq_addr  <= base_of(nrd);       // source line 0 of the new buffer
            rq_len   <= line_words[7:0];
            rq_buf   <= 1'b0;
            rq_tog   <= ~rq_tog;
            sy_fill  <= 12'd0;
            swap_req <= 1'b1;
            und_rep  <= underrun;
            underrun <= 16'd0;
        end else if (ocx == 0) begin
            reg        nd;
            reg [11:0] nsy;
            nd = disp_buf; nsy = sy_have;

            if (swap_req) begin
                nd = ~disp_buf; nsy = sy_fill;
                swap_req <= 1'b0;
                if (rd_busy) underrun <= underrun + 1'b1;
            end

            disp_buf <= nd;
            sy_have  <= nsy;

            // NO GATE HERE - see the note above; a gate on the pre-update
            // swap_req collapses to !rd_busy and silently skips fetches.
            begin
                if (sy_a_nxt != nsy) begin
                    rq_addr  <= base_of(rd_buf) + (sy_a_nxt * line_words);
                    rq_len   <= line_words[7:0];
                    rq_buf   <= ~nd;
                    rq_tog   <= ~rq_tog;
                    sy_fill  <= sy_a_nxt;
                    swap_req <= 1'b1;
                end
            end
        end
    end

endmodule

`default_nettype wire
