//-----------------------------------------------------------------------------
// ascal_test60k - scaler / video-path bring-up rig for the Tang Console 60K
//-----------------------------------------------------------------------------
// PURPOSE.  Answer two questions without the game core, ROMs or SD card in
// the way:
//   1. does native 15 kHz / 31 kHz arcade video come out of the J10 VGA pins
//      cleanly?   (test pattern -> vga_*, exactly the core's timing)
//   2. can MiSTer's ascal scaler run on Gowin and drive HDMI from it?
//      (same pattern -> ascal -> DDR3 -> 720p TMDS)
// Both paths run simultaneously off ONE source, so a fault is immediately
// attributable to the source, the analog path, or the scaler path.
//
// This is deliberately NOT wired into mcr2_console60k - the point is a rig
// with no other moving parts.  Once it is proven, the ascal + bridge pair
// drops into the real top in place of ddr3_framebuffer.
//
// CLOCK CHAINS (five PLLAs of eight used):
//   50 MHz pad -> gowin_pll_mcr2  -> clk_sys 40 MHz (pattern gen, = the core)
//                                 -> clk_50 (PLL-buffered, DDR3 clk_g).  The
//                                    DDR3 controller's clk_g MUST come from a
//                                    PLL output, not the pad (see CLAUDE.md).
//   50 MHz pad -> pll_27          -> 27 MHz reference
//   27 MHz     -> pll_ddr3        -> 297 MHz memory_clk (+ mDRP port)
//                 DDR3 IP         -> clk_x1 74.25 MHz  (Avalon / ascal avl_clk)
//   27 MHz     -> gowin_pll_hdmi  -> 371.25 MHz -> CLKDIV/5 -> hclk 74.25 MHz
//                                    (ascal o_clk AND the TMDS serialiser -
//                                     one chain, per the CLAUDE.md rule)
//
// WHY THIS NEEDS NO PIXEL FIFO.  The existing gbatang framebuffer has to
// invent a shadow raster to hand pixels from clk_x1 to hclk, because its HDMI
// module owns the output timing.  ascal generates output timing itself and
// crosses the memory/output domains internally, so it drives src/dvi_tx
// (which takes EXTERNAL de/hs/vs) directly.  Cost: dvi_tx is DVI only, so
// this rig has no HDMI audio.  Audio needs the hdl-util hdmi module back,
// with ascal's output feeding it through a line FIFO.
//
// CONTROLS
//   s1      (AA13) reset
//   key2    (AB13) tap = next scaler mode (nearest/bilinear/sharp/bicubic/poly)
//   mode15_n (J10-37) open = 31 kHz 480p source, GND = 15 kHz 240p source
// UART beacon on U15 @115200: "FB c<calib> r<ddr_rst> x<..> q<..> dXX LXX"
//   d = {3'b0, scaler mode}, L = {mode15, 3'b0, detected input width[11:8]}
//-----------------------------------------------------------------------------
`default_nettype none

module ascal_test60k_top (
    input  wire        sys_clk,        // 50 MHz, V22
    input  wire        s1,             // user key, ACTIVE LOW on the Console
    input  wire        key2,           // user key, ACTIVE LOW
    input  wire        mode15_n,       // strap: GND = 15 kHz

    // analog RGB on J10 (PmodVGA wiring per mcr2_console60k.cst)
    output wire [3:0]  vga_r,
    output wire [3:0]  vga_g,
    output wire [3:0]  vga_b,
    output wire        vga_hs,
    output wire        vga_vs,

    // HDMI / DVI
    output wire        tmds_clk_p,
    output wire        tmds_clk_n,
    output wire [2:0]  tmds_d_p,
    output wire [2:0]  tmds_d_n,
    output wire        hpd_en,

    output wire        uart_tx,
    output wire [3:0]  debug_o,

    // DDR3 (on-SOM 4 Gb x16)
    output wire [14:0] ddr_addr,
    output wire [2:0]  ddr_bank,
    output wire        ddr_cs,
    output wire        ddr_ras,
    output wire        ddr_cas,
    output wire        ddr_we,
    output wire        ddr_ck,
    output wire        ddr_ck_n,
    output wire        ddr_cke,
    output wire        ddr_odt,
    output wire        ddr_reset_n,
    output wire [1:0]  ddr_dm,
    inout  wire [15:0] ddr_dq,
    inout  wire [1:0]  ddr_dqs,
    inout  wire [1:0]  ddr_dqs_n
);

    assign hpd_en = 1'b1;

    //-------------------------------------------------------------------------
    // Clocks
    //-------------------------------------------------------------------------
    wire clk_sys;      // 40 MHz
    wire clk_p5_unused;
    wire clk50_pll;    // PLL-buffered 50 MHz -> DDR3 clk_g
    wire pll_sys_lock;

    gowin_pll_mcr2 pll_inst (
        .clkin  (sys_clk),
        .clk_sys(clk_sys),
        .clk_p5 (clk_p5_unused),
        .clk_50 (clk50_pll),
        .lock   (pll_sys_lock)
    );

    wire clk27;
    pll_27 pll27_inst (.clkin(sys_clk), .clkout0(clk27));

    //-------------------------------------------------------------------------
    // Reset (keys are active low on the Console 60K)
    //-------------------------------------------------------------------------
    wire key_rst = ~s1;
    reg [23:0] por = 0;
    always @(posedge clk_sys) if (!por[23]) por <= por + 1'b1;
    wire rst_sys = !por[23] || key_rst;

    //-------------------------------------------------------------------------
    // Source: MCR-timed test pattern
    //-------------------------------------------------------------------------
    reg mode15_s1 = 0, mode15 = 0;
    always @(posedge clk_sys) begin
        mode15_s1 <= ~mode15_n;
        mode15    <= mode15_s1;
    end

    wire       ce_pix;
    wire [7:0] pat_r, pat_g, pat_b;
    wire       pat_hs, pat_vs, pat_de, pat_hblank, pat_vblank;

    mcr_testpattern pattern (
        .clk(clk_sys), .rst(rst_sys), .mode15(mode15),
        .ce_pix(ce_pix),
        .r(pat_r), .g(pat_g), .b(pat_b),
        .hs(pat_hs), .vs(pat_vs), .de(pat_de),
        .hblank(pat_hblank), .vblank(pat_vblank),
        .hcnt_o(), .vcnt_o()
    );

    //-------------------------------------------------------------------------
    // Analog path - native timing, zero buffering, straight to the DAC ladder
    //-------------------------------------------------------------------------
    wire blanked = pat_hblank | pat_vblank;
    assign vga_r = blanked ? 4'h0 : pat_r[7:4];
    assign vga_g = blanked ? 4'h0 : pat_g[7:4];
    assign vga_b = blanked ? 4'h0 : pat_b[7:4];
    assign vga_hs = pat_hs;   // pattern gen already emits active-low sync
    assign vga_vs = pat_vs;

    //-------------------------------------------------------------------------
    // Scaler mode selector - key2 tap cycles 0..4
    //-------------------------------------------------------------------------
    reg [2:0] scaler = 3'd2;    // sharp bilinear: a good default, no coeffs
    reg key2_r = 1'b0, key2_rr = 1'b0;
    always @(posedge clk_sys) begin
        key2_r  <= ~key2;
        key2_rr <= key2_r;
        if (key2_r && !key2_rr) scaler <= (scaler == 3'd4) ? 3'd0 : scaler + 1'b1;
    end
    // mode[3] = triple buffering.  Left at 0 here: single-buffer is the
    // lowest-latency setting and makes tearing visible on the moving bar,
    // which is exactly what this rig is for.
    wire [4:0] ascal_mode = {2'b00, scaler};

    //-------------------------------------------------------------------------
    // HDMI clock chain: 27 -> 371.25 -> /5 -> 74.25.  One chain feeds both
    // ascal's output domain and the serialiser (CLAUDE.md structural rule).
    //-------------------------------------------------------------------------
    wire hclk5, hclk;
    gowin_pll_hdmi pll_hdmi27_inst (.clkin(clk27), .clkout(hclk5), .lock());
    CLKDIV #(.DIV_MODE(5)) hclk_div (
        .CLKOUT(hclk), .HCLKIN(hclk5), .RESETN(por[23]), .CALIB(1'b0)
    );

    //-------------------------------------------------------------------------
    // DDR3 controller (+ its PLL and mDRP plumbing, lifted from
    // ddr3_framebuffer.v - this is the part of gbatang we still need)
    //-------------------------------------------------------------------------
    wire         memory_clk, pll_lock, pll_stop;
    wire         mdrp_inc;
    wire [1:0]   mdrp_op;
    wire [7:0]   mdrp_wdata, mdrp_rdata;

    pll_ddr3 pll_ddr3_inst (
        .lock(pll_lock), .clkout0(), .clkout2(memory_clk),
        .clkin(clk27), .reset(1'b0),
        .mdclk(clk50_pll), .mdopc(mdrp_op), .mdainc(mdrp_inc),
        .mdwdi(mdrp_wdata), .mdrdo(mdrp_rdata)
    );

    reg  mdrp_wr = 0;
    reg  pll_stop_r = 0;
    pll_mDRP_intf u_pll_mDRP_intf (
        .clk(clk50_pll), .rst_n(1'b1), .pll_lock(pll_lock),
        .wr(mdrp_wr), .mdrp_inc(mdrp_inc), .mdrp_op(mdrp_op),
        .mdrp_wdata(mdrp_wdata), .mdrp_rdata(mdrp_rdata)
    );
    always @(posedge clk50_pll) begin
        pll_stop_r <= pll_stop;
        mdrp_wr    <= pll_stop ^ pll_stop_r;
    end

    wire         clk_x1;             // 74.25 MHz DDR3 app clock
    wire         ddr_rst;
    wire         init_calib_complete;

    wire         app_rdy, app_wdf_rdy;
    wire         app_en, app_wdf_wren, app_wdf_end;
    wire [2:0]   app_cmd;
    wire [27:0]  app_addr;
    wire [127:0] app_wdf_data, app_rd_data;
    wire [15:0]  app_wdf_mask;
    wire         app_rd_data_valid;

    DDR3_Memory_Interface_Top u_ddr3 (
        .memory_clk(memory_clk),
        .pll_stop  (pll_stop),
        .clk       (clk50_pll),
        .rst_n     (1'b1),
        .cmd_ready (app_rdy),
        .cmd       (app_cmd),
        .cmd_en    (app_en),
        .addr      (app_addr),
        .wr_data_rdy (app_wdf_rdy),
        .wr_data     (app_wdf_data),
        .wr_data_en  (app_wdf_wren),
        .wr_data_end (app_wdf_end),
        .wr_data_mask(app_wdf_mask),
        .rd_data      (app_rd_data),
        .rd_data_valid(app_rd_data_valid),
        .rd_data_end  (),
        .sr_req(1'b0), .ref_req(1'b0), .sr_ack(), .ref_ack(),
        .init_calib_complete(init_calib_complete),
        .clk_out (clk_x1),
        .pll_lock(pll_lock),
        .burst   (1'b1),
        .ddr_rst (ddr_rst),
        .O_ddr_addr(ddr_addr), .O_ddr_ba(ddr_bank),
        .O_ddr_cs_n(ddr_cs), .O_ddr_ras_n(ddr_ras),
        .O_ddr_cas_n(ddr_cas), .O_ddr_we_n(ddr_we),
        .O_ddr_clk(ddr_ck), .O_ddr_clk_n(ddr_ck_n),
        .O_ddr_cke(ddr_cke), .O_ddr_odt(ddr_odt),
        .O_ddr_reset_n(ddr_reset_n), .O_ddr_dqm(ddr_dm),
        .IO_ddr_dq(ddr_dq), .IO_ddr_dqs(ddr_dqs), .IO_ddr_dqs_n(ddr_dqs_n)
    );

    //-------------------------------------------------------------------------
    // ascal + the Avalon -> Gowin DDR3 bridge
    //-------------------------------------------------------------------------
    localparam N_DW = 128, N_AW = 25;

    wire [N_AW-1:0] avl_address;
    wire            avl_write, avl_read, avl_waitrequest, avl_readdatavalid;
    wire [N_DW-1:0] avl_writedata, avl_readdata;
    wire [7:0]      avl_burstcount;
    wire [15:0]     avl_byteenable;

    wire [7:0] o_r, o_g, o_b;
    wire       o_hs, o_vs, o_de;     // ascal sync is ACTIVE HIGH
    wire [11:0] det_hdmax, det_vdmax;
    wire [11:0] dbg_himax, dbg_hsize, dbg_ihsize, dbg_dcpt;
    wire [15:0] dbg_hacc;
    wire        dbg_hdown;

    // 512 px of source in a 960-wide window = 4:3 inside the 720p canvas,
    // matching what the DDR3 framebuffer does today (disp_width = 960).
    ascal_gw #(
        .MASK    (8'hFF),      // all five interpolators
        .RAMBASE (32'h0000_0000),
        .RAMSIZE (32'h0080_0000),
        .OHRES   (2304),   // MiSTer default - see the note in ascal_gw.vhd
        .IHRES   (1024),
        .N_DW    (N_DW),
        .N_AW    (N_AW),
        .N_BURST (2048)
    ) u_ascal (
        .i_clk(clk_sys), .i_ce(ce_pix),
        .i_r(pat_r), .i_g(pat_g), .i_b(pat_b),
        .i_hs(pat_hs), .i_vs(~pat_vs),   // ascal wants ACTIVE-HIGH vsync
        .i_de(pat_de), .i_fl(1'b0),

        .o_clk(hclk),
        .o_r(o_r), .o_g(o_g), .o_b(o_b),
        .o_hs(o_hs), .o_vs(o_vs), .o_de(o_de),

        .mode(ascal_mode),
        .run (1'b1),
        .hmin(12'd160), .hmax(12'd1119),
        .vmin(12'd0),   .vmax(12'd719),
        .i_hdmax(det_hdmax), .i_vdmax(det_vdmax),

        // Input window: leave ascal auto-detecting. These ports exist so a
        // future core that defeats auto-detect (or needs overscan cropped)
        // can pin the window without touching the wrapper.
        // HARD-BAKED input geometry: iauto=0 pins the window to
        // himin..himax / vimin..vimax instead of measuring it from i_de/i_vs.
        // Auto-detect was already proven correct (i_himax=511, i_hsize=512),
        // but this removes the whole detection path - and its i_clk->o_clk
        // <ASYNC> crossings - from the equation.
        // Auto-detect. Hard-baking these to 512x480 via iauto=0 was TESTED
        // and made no difference to the fault, so the general-purpose path
        // stays: it measures any source, which is the point of using ascal.
        .iauto(1'b1),
        .himin(12'd0), .himax(12'd0), .vimin(12'd0), .vimax(12'd0),

        .dbg_o_hacc(dbg_hacc), .dbg_o_dcpt(dbg_dcpt),
        .dbg_i_himax(dbg_himax), .dbg_i_hsize(dbg_hsize),
        .dbg_o_ihsize(dbg_ihsize), .dbg_i_hdown(dbg_hdown),

        .poly_clk(1'b0), .poly_a(12'd0), .poly_dw(10'd0), .poly_wr(1'b0),

        .avl_clk(clk_x1),
        .avl_waitrequest(avl_waitrequest),
        .avl_readdata(avl_readdata),
        .avl_readdatavalid(avl_readdatavalid),
        .avl_burstcount(avl_burstcount),
        .avl_writedata(avl_writedata),
        .avl_address(avl_address),
        .avl_write(avl_write),
        .avl_read(avl_read),
        .avl_byteenable(avl_byteenable),

        .reset_na(por[23])
    );

    ascal_avl_ddr3 #(
        .N_DW(N_DW), .N_AW(N_AW), .N_BURST(2048)
    ) u_bridge (
        .clk(clk_x1), .rst(ddr_rst),
        .avl_address(avl_address), .avl_write(avl_write), .avl_read(avl_read),
        .avl_writedata(avl_writedata), .avl_burstcount(avl_burstcount),
        .avl_byteenable(avl_byteenable),
        .avl_waitrequest(avl_waitrequest),
        .avl_readdata(avl_readdata), .avl_readdatavalid(avl_readdatavalid),
        .app_rdy(app_rdy), .app_en(app_en), .app_cmd(app_cmd),
        .app_addr(app_addr),
        .app_wdf_rdy(app_wdf_rdy), .app_wdf_wren(app_wdf_wren),
        .app_wdf_end(app_wdf_end), .app_wdf_data(app_wdf_data),
        .app_wdf_mask(app_wdf_mask),
        .app_rd_data_valid(app_rd_data_valid), .app_rd_data(app_rd_data),
        .dbg_wr_beat(dbg_wr_beat), .dbg_rd_beat(dbg_rd_beat)
    );

    //-------------------------------------------------------------------------
    // DIAGNOSTIC (temporary): words per frame across the Avalon bridge.
    // A 512x480 24bpp frame is 737280 bytes = 46080 16-byte words, so a
    // healthy write count is 0xB400 and the beacon should show wr = B4.
    // Quarter of that (2D) would mean the bridge is dropping 3 of every 4
    // write beats; four times (D0) means it is issuing too many.
    //-------------------------------------------------------------------------
    wire dbg_wr_beat, dbg_rd_beat;
    reg  ovs_x1a = 0, ovs_x1b = 0, ovs_x1c = 0;
    always @(posedge clk_x1) begin
        ovs_x1a <= o_vs; ovs_x1b <= ovs_x1a; ovs_x1c <= ovs_x1b;
    end
    wire frame_edge = ovs_x1b & ~ovs_x1c;

    reg [23:0] wr_cnt = 0, rd_cnt = 0, wr_lat = 0, rd_lat = 0;
    always @(posedge clk_x1) begin
        if (frame_edge) begin
            wr_lat <= wr_cnt; rd_lat <= rd_cnt;
            wr_cnt <= {23'd0, dbg_wr_beat};
            rd_cnt <= {23'd0, dbg_rd_beat};
        end else begin
            wr_cnt <= wr_cnt + dbg_wr_beat;
            rd_cnt <= rd_cnt + dbg_rd_beat;
        end
    end
    // sample into clk_sys for the beacon (slow-changing, debug only)
    reg [7:0] wr_b = 0, rd_b = 0;
    always @(posedge clk_sys) begin
        wr_b <= wr_lat[15:8];
        rd_b <= rd_lat[15:8];
    end

    //-------------------------------------------------------------------------
    // DVI output - ascal drives the timing directly
    //-------------------------------------------------------------------------
    dvi_tx_ext dvi_out (
        .clk_pixel(hclk),
        .clk_5x_pixel(hclk5),
        .resetn(por[23]),
        .rgb_r(o_r), .rgb_g(o_g), .rgb_b(o_b),
        .de(o_de), .hsync(o_hs), .vsync(o_vs),
        .tmds_clk_p(tmds_clk_p), .tmds_clk_n(tmds_clk_n),
        .tmds_d_p(tmds_d_p), .tmds_d_n(tmds_d_n)
    );


    //-------------------------------------------------------------------------
    // Sim-vs-hardware probe: latch ascal's horizontal accumulator and
    // destination counter at a FIXED output raster position (line 100,
    // pixel 300 counted from o_vs / o_de). sim/tb_ascal_bridge.vhd samples
    // the identical point, so the two numbers are directly comparable.
    //   o_hacc differs  -> accumulator arithmetic miscompiled
    //   o_hacc matches  -> fault is in the pixel data path / line buffers
    //-------------------------------------------------------------------------
    localparam PROBE_Y = 100, PROBE_X = 300;
    reg [11:0] pline = 0, ppix = 0;
    reg ovs_p = 0, ode_p = 0;
    reg [15:0] probe_hacc = 0;
    reg [11:0] probe_dcpt = 0;
    reg [11:0] probe_lev = 0, probe_hsz = 0;
    always @(posedge hclk) begin
        ovs_p <= o_vs; ode_p <= o_de;
        if (o_vs && !ovs_p) pline <= 0;
        else if (!o_de && ode_p) pline <= pline + 1'b1;
        if (o_de && !ode_p) ppix <= 0;
        else if (o_de) ppix <= ppix + 1'b1;
        if (o_de && pline == PROBE_Y && ppix == PROBE_X) begin
            probe_hacc <= dbg_hacc;
            probe_dcpt <= dbg_dcpt;
            probe_lev  <= dbg_ihsize;   // o_hacpt  (source px consumed)
            probe_hsz  <= dbg_hsize;    // o_ihsizem (line-end threshold)
        end
    end
    reg [15:0] probe_hacc_s;
    reg [11:0] probe_dcpt_s, probe_lev_s, probe_hsz_s;
    always @(posedge clk_sys) begin
        probe_hacc_s <= probe_hacc; probe_dcpt_s <= probe_dcpt;
        probe_lev_s  <= probe_lev;
        probe_hsz_s  <= probe_hsz;
    end
    //-------------------------------------------------------------------------
    // Diagnostics
    //-------------------------------------------------------------------------
    // Count ascal's own output frames in the hclk domain, then gray-free
    // sample the low 3 bits into clk_sys for the beacon (a 3-bit counter
    // read asynchronously can only be off by one, which is fine here).
    reg [2:0] ovs_cnt = 0;
    reg       o_vs_r = 0;
    always @(posedge hclk) begin
        o_vs_r <= o_vs;
        if (o_vs && !o_vs_r) ovs_cnt <= ovs_cnt + 1'b1;
    end
    reg [2:0] ovs_cnt_s1 = 0, ovs_cnt_sync = 0;
    always @(posedge clk_sys) begin
        ovs_cnt_s1   <= ovs_cnt;
        ovs_cnt_sync <= ovs_cnt_s1;
    end

    reg [25:0] hb_x1 = 0;
    reg [24:0] hb_27 = 0, hb_h = 0;
    always @(posedge clk_x1) hb_x1 <= hb_x1 + 1'b1;
    always @(posedge clk27)  hb_27 <= hb_27 + 1'b1;
    always @(posedge hclk)   hb_h  <= hb_h  + 1'b1;

    assign debug_o = {ddr_rst, hb_27[24], hb_x1[25], init_calib_complete};

    // ddr_rst and init_calib_complete are generated inside the DDR3 IP, in a
    // clock domain the SDC cannot name (it is internal to the hard IP), so
    // feeding them straight to the beacon leaves a genuinely unconstrained
    // crossing - it showed up as the design's only real setup violation
    // (-1.258 ns, u_ddr3/.../ddr_rsti_reg -> beacon/l_rst). These are slow
    // status bits sampled twice a second, so a 2FF synchroniser is both the
    // correct fix and free. NOTE: mcr2_console60k_top.sv wires the same two
    // signals to its beacon directly and has the same latent crossing.
    reg calib_s1 = 0, calib_s2 = 0, ddrrst_s1 = 1, ddrrst_s2 = 1;
    always @(posedge clk_sys) begin
        calib_s1  <= init_calib_complete;  calib_s2  <= calib_s1;
        ddrrst_s1 <= ddr_rst;              ddrrst_s2 <= ddrrst_s1;
    end

    uart_beacon #(.CLK_HZ(40_000_000), .BAUD(115200)) beacon (
        .clk(clk_sys),
        .calib(calib_s2),
        .ddr_rst(ddrrst_s2),
        .cnt_x({hb_h[24:21], hb_x1[25:14]}),
        .cnt_q(hb_27[24:17]),
        // d = {00, ascal output-frame counter[2:0], scaler mode[2:0]}.
        // The frame counter is incremented by ascal's OWN o_vs in the hclk
        // domain, so if it advances between beacon lines the scaler is
        // actively generating a 720p raster - which is exactly what feeds
        // the TMDS encoder. A frozen counter with c1/r0 means the fault is
        // downstream of ascal (encoder/serialiser/cable); an advancing one
        // means the FPGA is transmitting and a dark screen is a sink or
        // cabling problem.
        // PROBE at (line 100, pixel 300) - compare against the GHDL sim.
        // d = {o_off(0), o_pshift} @probe. Both are 0..15; o_pshift should
        // equal o_off(0)-1. A large o_off(0) means sSHIFT runs long and
        // over-advances o_hacpt independently of the carry logic.
        // L = {mode15, detected input height[10:8], detected width[11:8]}.
        // Expect 0x11 for 31 kHz (512x480 -> hdmax 511, vdmax 479) and
        // 0x81 for 15 kHz (512x240 -> vdmax 239).

        .aux(probe_hsz_s[7:0]),
        // L = o_hacpt[11:4] @probe. Correct = 140*512/960 = 75 -> 04.
        // 4x too fast would be ~300 -> 12.
        .aux2(probe_lev_s[11:4]),
        .txd(uart_tx)
    );

endmodule

`default_nettype wire
