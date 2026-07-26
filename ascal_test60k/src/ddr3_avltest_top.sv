//-----------------------------------------------------------------------------
// ddr3_avltest_top - memtest through ascal_avl_ddr3, no scaler
//-----------------------------------------------------------------------------
// Same clocks, same bridge, same DDR3 controller and same constraints as
// ascal_test60k_top - ascal is simply replaced by avl_ddr3_memtest, which
// writes a known address-derived pattern through the Avalon port and reads it
// back. See src/ascal/avl_ddr3_memtest.sv for why.
//
// UART beacon on U15 @115200:
//   c/r  DDR3 calibration and reset, as usual
//   dXX  = mismatch count, SATURATING at FF.  d00 = memory path is clean.
//   LXX  = {running, pass_cnt[6:0]} - the low bits must keep incrementing,
//          otherwise the test is wedged and d00 means nothing.
// TMDS is left dark on purpose; this build is about memory, not video.
//-----------------------------------------------------------------------------
`default_nettype none

module ddr3_avltest_top (
    input  wire        sys_clk,
    input  wire        s1,
    output wire        uart_tx,
    output wire [3:0]  debug_o,
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
    // Reset
    //-------------------------------------------------------------------------
    wire key_rst = ~s1;
    reg [23:0] por = 0;
    always @(posedge clk_sys) if (!por[23]) por <= por + 1'b1;

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
    // Memtest -> the SAME bridge -> the SAME controller
    //-------------------------------------------------------------------------
    localparam N_DW = 128, N_AW = 25;
    wire [N_AW-1:0] avl_address;
    wire            avl_write, avl_read, avl_waitrequest, avl_readdatavalid;
    wire [N_DW-1:0] avl_writedata, avl_readdata;
    wire [7:0]      avl_burstcount;
    wire [15:0]     avl_byteenable;
    wire [7:0]      err_cnt;
    wire [6:0]      pass_cnt;
    wire            running;
    wire            dbg_wr_beat, dbg_rd_beat;

    avl_ddr3_memtest #(.N_DW(N_DW), .N_AW(N_AW), .N_BURST(2048), .BURSTS(256))
    u_test (
        .clk(clk_x1), .rst(ddr_rst),
        .avl_address(avl_address), .avl_write(avl_write), .avl_read(avl_read),
        .avl_writedata(avl_writedata), .avl_burstcount(avl_burstcount),
        .avl_byteenable(avl_byteenable),
        .avl_waitrequest(avl_waitrequest),
        .avl_readdata(avl_readdata), .avl_readdatavalid(avl_readdatavalid),
        .err_cnt(err_cnt), .pass_cnt(pass_cnt), .running(running)
    );

    ascal_avl_ddr3 #(.N_DW(N_DW), .N_AW(N_AW), .N_BURST(2048)) u_bridge (
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
    // Beacon
    //-------------------------------------------------------------------------
    reg [25:0] hb_x1 = 0;
    reg [24:0] hb_27 = 0;
    always @(posedge clk_x1) hb_x1 <= hb_x1 + 1'b1;
    always @(posedge clk27)  hb_27 <= hb_27 + 1'b1;

    reg calib_s1 = 0, calib_s2 = 0, ddrrst_s1 = 1, ddrrst_s2 = 1;
    reg [7:0] err_s = 0; reg [6:0] pass_s = 0; reg run_s = 0;
    always @(posedge clk_sys) begin
        calib_s1  <= init_calib_complete;  calib_s2  <= calib_s1;
        ddrrst_s1 <= ddr_rst;              ddrrst_s2 <= ddrrst_s1;
        err_s <= err_cnt; pass_s <= pass_cnt; run_s <= running;
    end

    assign debug_o = {ddrrst_s2, hb_27[24], hb_x1[25], calib_s2};

    uart_beacon #(.CLK_HZ(40_000_000), .BAUD(115200)) beacon (
        .clk(clk_sys),
        .calib(calib_s2), .ddr_rst(ddrrst_s2),
        .cnt_x(hb_x1[25:10]), .cnt_q(hb_27[24:17]),
        .aux(err_s),                 // d00 = clean
        .aux2({run_s, pass_s}),      // must keep incrementing
        .txd(uart_tx)
    );

endmodule

`default_nettype wire
