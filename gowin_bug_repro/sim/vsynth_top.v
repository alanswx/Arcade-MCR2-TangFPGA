// Simulation top: real pattern generator + GHDL-synthesised ascal + real
// Avalon->DDR3 bridge + DDR3 model. Clocks are driven from C++.
module synth_top (
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
    output wire [11:0] dbg_o_dcpt
);
    wire       ce_pix, p_hs, p_vs, p_de;
    wire [7:0] p_r, p_g, p_b;
    mcr_testpattern src (
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

    ascal_gw dut (
        .i_clk(i_clk), .i_ce(ce_pix),
        .i_r(p_r), .i_g(p_g), .i_b(p_b),
        .i_hs(p_hs), .i_vs(~p_vs), .i_de(p_de), .i_fl(1'b0),
        .o_clk(o_clk),
        .o_r(o_r), .o_g(o_g), .o_b(o_b),
        .o_hs(o_hs), .o_vs(o_vs), .o_de(o_de),
        .mode(5'b00010), .run(1'b1),
        .hmin(12'd0), .hmax(12'd639), .vmin(12'd0), .vmax(12'd479),
        .i_hdmax(), .i_vdmax(),
        .iauto(1'b1), .himin(12'd0), .himax(12'd0),
        .vimin(12'd0), .vimax(12'd0),
        .dbg_o_hacc(), .dbg_o_dcpt(dbg_o_dcpt), .dbg_i_himax(dbg_i_himax),
        .dbg_i_hsize(), .dbg_o_ihsize(), .dbg_i_hdown(),
        .poly_clk(1'b0), .poly_a(12'd0), .poly_dw(10'd0), .poly_wr(1'b0),
        .avl_clk(o_clk), .avl_waitrequest(avl_waitrequest),
        .avl_readdata(avl_readdata), .avl_readdatavalid(avl_readdatavalid),
        .avl_burstcount(avl_burstcount), .avl_writedata(avl_writedata),
        .avl_address(avl_address), .avl_write(avl_write), .avl_read(avl_read),
        .avl_byteenable(avl_byteenable),
        .reset_na(reset_na)
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
