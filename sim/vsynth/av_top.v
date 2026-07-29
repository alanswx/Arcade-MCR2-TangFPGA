// Simulation top (ascal_v hand port variant): real pattern generator + GHDL-synthesised ascal + real
// Avalon->DDR3 bridge + DDR3 model. Clocks are driven from C++.
module synth_top (
    input  wire        avl_clk_in,
    input  wire        i_clk,
    input  wire        o_clk,
    input  wire        reset_na,
    output wire [7:0]  o_r,
    output wire [7:0]  o_g,
    output wire [7:0]  o_b,
    output wire        o_hs,
    output wire        o_vs,
    output wire        o_de,
    output wire [11:0] dbg_i_himax,
    output wire [11:0] dbg_o_dcpt,
    output wire [15:0] dbg_und
);
    wire       ce_pix, p_hs, p_vs, p_de;
    wire [7:0] p_r, p_g, p_b;
    mcr_testpattern #(.FREEZE_BAR(1)) src (
        .clk(i_clk), .rst(~reset_na), .mode15(1'b0),
        .ce_pix(ce_pix), .r(p_r), .g(p_g), .b(p_b),
        .hs(p_hs), .vs(p_vs), .de(p_de),
        .hblank(), .vblank(), .hcnt_o(), .vcnt_o()
    );

    wire [24:0]  avl_address;
    wire         avl_write, avl_read, avl_waitrequest, avl_readdatavalid;
    wire [127:0] avl_writedata, avl_readdata;
    wire [7:0]   avl_burstcount;
    wire [15:0]  avl_byteenable;
    wire         app_rdy, app_en, app_wdf_rdy, app_wdf_wren, app_rd_data_valid;
    wire [2:0]   app_cmd;
    wire [27:0]  app_addr;
    wire [127:0] app_wdf_data, app_rd_data;

    ascal_v #(
        .N_DW(128), .N_AW(25), .MAX_WIDTH(1024),
        .RAMBASE(25'd0), .BUF_WORDS(25'd65536),
        .HTOTAL(1650), .HSSTART(1390), .HSEND(1430), .HDISP(1280),
        .VTOTAL(750), .VSSTART(725), .VSEND(730), .VDISP(720)
    ) dut (
        .i_clk(i_clk), .i_ce(ce_pix),
        .i_r(p_r), .i_g(p_g), .i_b(p_b),
        .i_vs(~p_vs), .i_de(p_de),
        .o_clk(o_clk),
        .o_r(o_r), .o_g(o_g), .o_b(o_b),
        .o_hs(o_hs), .o_vs(o_vs), .o_de(o_de),
        .run(1'b1), .triple_buf(1'b1),
        .ext_rast(1'b0), .ext_cx(12'd0), .ext_cy(12'd0),
        .hmin(12'd160), .hmax(12'd1119), .vmin(12'd0), .vmax(12'd719),
        .i_hdmax(dbg_i_himax), .i_vdmax(),
        .dbg_sy(dbg_o_dcpt), .dbg_underrun(dbg_und),
        .avl_clk(avl_clk_in), .avl_waitrequest(avl_waitrequest),
        .avl_readdata(avl_readdata), .avl_readdatavalid(avl_readdatavalid),
        .avl_burstcount(avl_burstcount), .avl_writedata(avl_writedata),
        .avl_address(avl_address), .avl_write(avl_write), .avl_read(avl_read),
        .avl_byteenable(avl_byteenable),
        .reset_n(reset_na)
    );


    ascal_avl_ddr3 #(.N_DW(128), .N_AW(25), .N_BURST(2048)) bridge (
        .clk(o_clk), .rst(~reset_na),
        .avl_address(avl_address), .avl_write(avl_write), .avl_read(avl_read),
        .avl_writedata(avl_writedata), .avl_burstcount(avl_burstcount),
        .avl_byteenable(avl_byteenable), .avl_waitrequest(avl_waitrequest),
        .avl_readdata(avl_readdata), .avl_readdatavalid(avl_readdatavalid),
        .app_rdy(app_rdy), .app_en(app_en), .app_cmd(app_cmd), .app_addr(app_addr),
        .app_wdf_rdy(app_wdf_rdy), .app_wdf_wren(app_wdf_wren), .app_wdf_end(),
        .app_wdf_data(app_wdf_data), .app_wdf_mask(),
        .app_rd_data_valid(app_rd_data_valid), .app_rd_data(app_rd_data),
        .dbg_wr_beat(), .dbg_rd_beat()
    );

    ddr3_model ddr (
        .clk(o_clk), .cmd_ready(app_rdy), .cmd(app_cmd), .cmd_en(app_en),
        .addr(app_addr), .wr_data_rdy(app_wdf_rdy), .wr_data(app_wdf_data),
        .wr_data_en(app_wdf_wren),
        .rd_data(app_rd_data), .rd_data_valid(app_rd_data_valid)
    );
endmodule
