//-----------------------------------------------------------------------------
// ascal_fb - drop-in replacement for ddr3_framebuffer, built on ascal_v
//-----------------------------------------------------------------------------
// Same port list as ddr3_framebuffer plus TWO extra inputs, so swapping a core
// over is a module-name change and two wires.
//
// Why the extra inputs: ddr3_framebuffer takes a write-enable stream (`fb_we`
// = one pulse per active pixel). ascal_v takes a VIDEO stream and needs the
// pixel enable and the active-video level SEPARATELY - it detects line starts
// from i_de edges, so feeding it fb_we (which drops between pixels whenever the
// core's pixel enable is slower than the clock) would make every pixel look
// like its own line. `i_ce` is the pixel tick, `i_de` is active-video.
//
// What this brings over ddr3_framebuffer: triple buffering (no tearing), input
// auto-detect, parameterised output timing, and better scaling - measured
// h-stripe duplicate rate 0.333 (ideal) vs 0.385. Costs ~117 LUT and ~10 BSRAM
// more; the BSRAM is width-driven (128-bit line buffer + write FIFO), so
// shrinking depth does NOT reclaim it - narrow N_DW if you need those blocks.
//
// The DDR3 controller, its PLL/mDRP plumbing and the HDMI clock chain are
// lifted from ddr3_framebuffer/ascalv_top unchanged - the structural rule in
// CLAUDE.md (one 27 -> 371.25 -> /5 -> 74.25 chain feeding both the output
// domain and the serialiser) still applies.
//-----------------------------------------------------------------------------
`default_nettype none

module ascal_fb #(
    parameter WIDTH          = 512,
    parameter HEIGHT         = 480,
    parameter COLOR_BITS     = 12,
    parameter PREFETCH_DELAY = 44,   // accepted for interface compatibility
    parameter DVI_MODE       = 0,
    parameter AUDIO_RATE     = 32000,
    parameter DISP_HMIN      = 158,  // 2 px left of 160: ascal_v's pixel
    parameter DISP_HMAX      = 1117  // pipeline is 2 cycles behind ocx
)(
    output wire         hclk_dbg,
    output wire         hclk5_dbg,
    input  wire         clk_27,
    input  wire         clk_g,
    input  wire         pll_lock_27,
    input  wire         rst_n,
    output wire         clk_out,
    output wire         ddr_rst,
    output wire         init_calib_complete,

    input  wire         clk,
    input  wire [10:0]  fb_width,
    input  wire [9:0]   fb_height,
    input  wire [10:0]  disp_width,
    input  wire         fb_vsync,
    input  wire         fb_we,
    input  wire [COLOR_BITS-1:0] fb_data,
    input  wire [5:0]   ddr_prefetch_delay,

    // ---- the two extra inputs (see header) ----
    input  wire         i_ce,        // core pixel tick
    input  wire         i_de,        // core active-video level

    input  wire [15:0]  sound_left,
    input  wire [15:0]  sound_right,

    output wire [14:0]  ddr_addr,
    output wire [2:0]   ddr_bank,
    output wire         ddr_cs,
    output wire         ddr_ras,
    output wire         ddr_cas,
    output wire         ddr_we,
    output wire         ddr_ck,
    output wire         ddr_ck_n,
    output wire         ddr_cke,
    output wire         ddr_odt,
    output wire         ddr_reset_n,
    output wire [1:0]   ddr_dm,
    inout  wire [15:0]  ddr_dq,
    inout  wire [1:0]   ddr_dqs,
    inout  wire [1:0]   ddr_dqs_n,

    output wire         tmds_clk_n,
    output wire         tmds_clk_p,
    output wire [2:0]   tmds_d_n,
    output wire [2:0]   tmds_d_p
);
    localparam N_DW = 128, N_AW = 25;

    //---------------------------------------------------------------- clocks
    wire hclk5, hclk;
    gowin_pll_hdmi pll_hdmi27_inst (.clkin(clk_27), .clkout(hclk5), .lock());
    CLKDIV #(.DIV_MODE(5)) hclk_div (
        .CLKOUT(hclk), .HCLKIN(hclk5), .RESETN(rst_n), .CALIB(1'b0)
    );
    assign hclk_dbg  = hclk;
    assign hclk5_dbg = hclk5;

    //------------------------------------------------- DDR3 controller + PLL
    wire        memory_clk, pll_lock, pll_stop;
    wire        mdrp_inc;
    wire [1:0]  mdrp_op;
    wire [7:0]  mdrp_wdata, mdrp_rdata;

    pll_ddr3 pll_ddr3_inst (
        .lock(pll_lock), .clkout0(), .clkout2(memory_clk),
        .clkin(clk_27), .reset(1'b0),
        .mdclk(clk_g), .mdopc(mdrp_op), .mdainc(mdrp_inc),
        .mdwdi(mdrp_wdata), .mdrdo(mdrp_rdata)
    );

    reg  mdrp_wr = 0, pll_stop_r = 0;
    pll_mDRP_intf u_pll_mDRP_intf (
        .clk(clk_g), .rst_n(1'b1), .pll_lock(pll_lock),
        .wr(mdrp_wr), .mdrp_inc(mdrp_inc), .mdrp_op(mdrp_op),
        .mdrp_wdata(mdrp_wdata), .mdrp_rdata(mdrp_rdata)
    );
    always @(posedge clk_g) begin
        pll_stop_r <= pll_stop;
        mdrp_wr    <= pll_stop ^ pll_stop_r;
    end

    wire         clk_x1 /* synthesis syn_keep=1 */;
    wire         app_rdy, app_wdf_rdy, app_en, app_wdf_wren, app_wdf_end;
    wire [2:0]   app_cmd;
    wire [27:0]  app_addr;
    wire [127:0] app_wdf_data, app_rd_data;
    wire [15:0]  app_wdf_mask;
    wire         app_rd_data_valid;

    DDR3_Memory_Interface_Top u_ddr3 (
        // rst_n MUST be tied high here - both ddr3_framebuffer and ascalv_top do
        // this. Feeding the core's reset in stops the controller calibrating
        // (observed: beacon stuck at c0, black screen). The controller has its
        // own init sequence and reports readiness via init_calib_complete.
        .memory_clk(memory_clk), .pll_stop(pll_stop), .clk(clk_g), .rst_n(1'b1),
        .cmd_ready(app_rdy), .cmd(app_cmd), .cmd_en(app_en), .addr(app_addr),
        .wr_data_rdy(app_wdf_rdy), .wr_data(app_wdf_data),
        .wr_data_en(app_wdf_wren), .wr_data_end(app_wdf_end),
        .wr_data_mask(app_wdf_mask),
        .rd_data(app_rd_data), .rd_data_valid(app_rd_data_valid), .rd_data_end(),
        .sr_req(1'b0), .ref_req(1'b0), .sr_ack(), .ref_ack(),
        .init_calib_complete(init_calib_complete),
        .clk_out(clk_x1), .pll_lock(pll_lock), .burst(1'b1), .ddr_rst(ddr_rst),
        .O_ddr_addr(ddr_addr), .O_ddr_ba(ddr_bank), .O_ddr_cs_n(ddr_cs),
        .O_ddr_ras_n(ddr_ras), .O_ddr_cas_n(ddr_cas), .O_ddr_we_n(ddr_we),
        .O_ddr_clk(ddr_ck), .O_ddr_clk_n(ddr_ck_n), .O_ddr_cke(ddr_cke),
        .O_ddr_odt(ddr_odt), .O_ddr_reset_n(ddr_reset_n), .O_ddr_dqm(ddr_dm),
        .IO_ddr_dq(ddr_dq), .IO_ddr_dqs(ddr_dqs), .IO_ddr_dqs_n(ddr_dqs_n)
    );
    assign clk_out = clk_x1;

    //-------------------------------------------------------- scaler + bridge
    wire [N_AW-1:0] avl_address;
    wire            avl_write, avl_read, avl_waitrequest, avl_readdatavalid;
    wire [N_DW-1:0] avl_writedata, avl_readdata;
    wire [7:0]      avl_burstcount;
    wire [15:0]     avl_byteenable;

    // fb_data is COLOR_BITS wide (RGB444 for the MCR cores). Expand each
    // nibble to 8 bits by MSB replication, as the cabinet DAC path does.
    wire [3:0] cr = fb_data[COLOR_BITS-1 -: 4];
    wire [3:0] cg = fb_data[COLOR_BITS-5 -: 4];
    wire [3:0] cb = fb_data[3:0];

    wire [7:0] o_r, o_g, o_b;
    wire       o_hs, o_vs, o_de;
    wire [11:0] hdmi_cx, hdmi_cy;

    ascal_v #(
        .N_DW(N_DW), .N_AW(N_AW), .MAX_WIDTH(512),
        .RAMBASE(25'd0), .BUF_WORDS(25'd65536),
        .HTOTAL(1650), .HSSTART(1390), .HSEND(1430), .HDISP(1280),
        .VTOTAL(750),  .VSSTART(725),  .VSEND(730),  .VDISP(720)
    ) u_ascal (
        .i_clk(clk), .i_ce(i_ce),
        .i_r({cr, cr}), .i_g({cg, cg}), .i_b({cb, cb}),
        .i_vs(fb_vsync), .i_de(i_de),
        .o_clk(hclk),
        .o_r(o_r), .o_g(o_g), .o_b(o_b),
        .o_hs(o_hs), .o_vs(o_vs), .o_de(o_de),
        .run(1'b1), .triple_buf(1'b1),
        .ext_rast(1'b1), .ext_cx(hdmi_cx), .ext_cy(hdmi_cy),
        .hmin(DISP_HMIN[11:0]), .hmax(DISP_HMAX[11:0]),
        .vmin(12'd0), .vmax(12'd719),
        .i_hdmax(), .i_vdmax(),
        .avl_clk(clk_x1), .avl_waitrequest(avl_waitrequest),
        .avl_readdata(avl_readdata), .avl_readdatavalid(avl_readdatavalid),
        .avl_burstcount(avl_burstcount), .avl_writedata(avl_writedata),
        .avl_address(avl_address), .avl_write(avl_write), .avl_read(avl_read),
        .avl_byteenable(avl_byteenable),
        // MUST be gated on calibration. ddr3_framebuffer holds its own state
        // machines in reset via ddr_rst until the controller is ready; without
        // the equivalent, ascal_v starts issuing Avalon reads/writes DURING the
        // DDR3 training sequence and calibration never completes (beacon stuck
        // at c0, black window with correct grey pillarbox - the video path is
        // fine, only the memory link is dead).
        .reset_n(rst_n & init_calib_complete & ~ddr_rst),
        .dbg_underrun(), .dbg_cdc(), .dbg_fetch(), .dbg_lat(), .dbg_sy()
    );

    ascal_avl_ddr3 #(.N_DW(N_DW), .N_AW(N_AW), .N_BURST(2048)) u_bridge (
        .clk(clk_x1), .rst(ddr_rst),
        .avl_write(avl_write), .avl_read(avl_read),
        .avl_address(avl_address), .avl_burstcount(avl_burstcount),
        .avl_writedata(avl_writedata), .avl_byteenable(avl_byteenable),
        .avl_readdata(avl_readdata), .avl_readdatavalid(avl_readdatavalid),
        .avl_waitrequest(avl_waitrequest),
        .app_rdy(app_rdy), .app_en(app_en), .app_cmd(app_cmd), .app_addr(app_addr),
        .app_wdf_rdy(app_wdf_rdy), .app_wdf_wren(app_wdf_wren),
        .app_wdf_end(app_wdf_end), .app_wdf_data(app_wdf_data),
        .app_wdf_mask(app_wdf_mask),
        .app_rd_data_valid(app_rd_data_valid), .app_rd_data(app_rd_data),
        .dbg_wr_beat(), .dbg_rd_beat()
    );

    //--------------------------------------------------------- HDMI + audio
    // INTEGER divider - a fractional-exact one made dropouts WORSE, and a
    // declared-vs-actual rate mismatch was the original 50% rate lie.
    localparam AUDIO_CLK_DELAY = 74250 * 1000 / AUDIO_RATE / 2;
    reg [$clog2(AUDIO_CLK_DELAY)-1:0] audio_divider = 0;
    reg clk_audio = 0;
    always @(posedge hclk) begin
        if (audio_divider != AUDIO_CLK_DELAY[$clog2(AUDIO_CLK_DELAY)-1:0] - 1)
            audio_divider <= audio_divider + 1'b1;
        else begin
            clk_audio     <= ~clk_audio;
            audio_divider <= 0;
        end
    end

    reg [15:0] audio_word [1:0];
    always @(posedge hclk) begin
        audio_word[0] <= sound_left;
        audio_word[1] <= sound_right;
    end

    wire [2:0] tmds;
    hdmi #( .VIDEO_ID_CODE(4), .DVI_OUTPUT(DVI_MODE),
            .VIDEO_REFRESH_RATE(60.0), .IT_CONTENT(1),
            .AUDIO_RATE(AUDIO_RATE), .AUDIO_BIT_WIDTH(16),
            .START_X(0), .START_Y(0) )
    hdmi_out (
        .clk_pixel_x5(hclk5), .clk_pixel(hclk), .clk_audio(clk_audio),
        .reset(~rst_n), .rgb({o_r, o_g, o_b}), .audio_sample_word(audio_word),
        .tmds(tmds), .tmds_clock(), .cx(hdmi_cx), .cy(hdmi_cy),
        .frame_width(), .frame_height(), .screen_width(), .screen_height()
    );

    ELVDS_OBUF tmds_bufds [3:0] (
        .I({hclk, tmds}), .O({tmds_clk_p, tmds_d_p}), .OB({tmds_clk_n, tmds_d_n})
    );

endmodule

`default_nettype wire
