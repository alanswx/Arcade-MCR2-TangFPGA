//-----------------------------------------------------------------------------
// dvi_tx_ext - DVI transmitter driven by EXTERNAL video timing, at 74.25 MHz
//-----------------------------------------------------------------------------
// Same job and same ports as src/dvi_tx/hdmi_tx.sv, but it encodes with
// hdl-util's PIPELINED `tmds_channel` instead of the single-cycle
// `tmds_encoder`.
//
// WHY.  hdmi_tx.sv computes the whole TMDS 8b/10b transition-minimising
// encode combinationally between two registers.  That is fine at the 25K's
// 25 MHz pixel clock, which is all it was ever asked to do.  Feeding it
// ascal's 720p output at 74.25 MHz produced a MEASURED Fmax of 71.66 MHz
// against a 74.25 MHz requirement - 66 setup-violated endpoints, all of them
// on the ascal -> encoder path.  `tmds_channel` splits the same function
// across pipeline stages and is already proven at 74.25 MHz on this board
// inside the gbatang framebuffer, so it closes timing with no new risk.
//
// This is DVI, not HDMI: `mode` only ever selects control (0) or video (1),
// so no data islands and therefore no audio.  Audio would need the full
// hdl-util `hdmi` module, which owns the raster and so needs ascal's output
// fed through a line FIFO instead of driving the timing directly.
//
// tmds_channel registers its output, adding a fixed latency that is IDENTICAL
// on all three channels, so de/hsync/vsync stay aligned with the pixels and
// no compensation is needed.
//-----------------------------------------------------------------------------
`default_nettype none

module dvi_tx_ext (
    input  wire       clk_pixel,      // 74.25 MHz for 720p
    input  wire       clk_5x_pixel,   // 371.25 MHz
    input  wire       resetn,
    input  wire [7:0] rgb_r,
    input  wire [7:0] rgb_g,
    input  wire [7:0] rgb_b,
    input  wire       de,             // active video
    input  wire       hsync,          // ACTIVE HIGH (as ascal emits)
    input  wire       vsync,          // ACTIVE HIGH

    output wire       tmds_clk_p,
    output wire       tmds_clk_n,
    output wire [2:0] tmds_d_p,
    output wire [2:0] tmds_d_n
);

    // Control period vs video period. No data islands in DVI.
    wire [2:0] mode = de ? 3'd1 : 3'd0;

    wire [9:0] tmds_blue, tmds_green, tmds_red;

    // Channel 0 (blue) carries HSYNC/VSYNC on its control bits; 1 and 2 idle.
    tmds_channel #(.CN(0)) ch_blue (
        .clk_pixel(clk_pixel), .video_data(rgb_b),
        .data_island_data(4'd0), .control_data({vsync, hsync}),
        .mode(mode), .tmds(tmds_blue)
    );
    tmds_channel #(.CN(1)) ch_green (
        .clk_pixel(clk_pixel), .video_data(rgb_g),
        .data_island_data(4'd0), .control_data(2'b00),
        .mode(mode), .tmds(tmds_green)
    );
    tmds_channel #(.CN(2)) ch_red (
        .clk_pixel(clk_pixel), .video_data(rgb_r),
        .data_island_data(4'd0), .control_data(2'b00),
        .mode(mode), .tmds(tmds_red)
    );

    // Serialiser + differential buffers, lifted verbatim from hdmi_tx.sv
    // (explicit OSER10 instances - see the note there about Gowin's
    // array-of-instance handling).
    wire [2:0] tmds_d;
    OSER10 tmds_serdes_blue (
        .Q(tmds_d[0]),
        .D0(tmds_blue[0]), .D1(tmds_blue[1]), .D2(tmds_blue[2]),
        .D3(tmds_blue[3]), .D4(tmds_blue[4]), .D5(tmds_blue[5]),
        .D6(tmds_blue[6]), .D7(tmds_blue[7]), .D8(tmds_blue[8]),
        .D9(tmds_blue[9]),
        .PCLK(clk_pixel), .FCLK(clk_5x_pixel), .RESET(~resetn)
    );
    OSER10 tmds_serdes_green (
        .Q(tmds_d[1]),
        .D0(tmds_green[0]), .D1(tmds_green[1]), .D2(tmds_green[2]),
        .D3(tmds_green[3]), .D4(tmds_green[4]), .D5(tmds_green[5]),
        .D6(tmds_green[6]), .D7(tmds_green[7]), .D8(tmds_green[8]),
        .D9(tmds_green[9]),
        .PCLK(clk_pixel), .FCLK(clk_5x_pixel), .RESET(~resetn)
    );
    OSER10 tmds_serdes_red (
        .Q(tmds_d[2]),
        .D0(tmds_red[0]), .D1(tmds_red[1]), .D2(tmds_red[2]),
        .D3(tmds_red[3]), .D4(tmds_red[4]), .D5(tmds_red[5]),
        .D6(tmds_red[6]), .D7(tmds_red[7]), .D8(tmds_red[8]),
        .D9(tmds_red[9]),
        .PCLK(clk_pixel), .FCLK(clk_5x_pixel), .RESET(~resetn)
    );

    ELVDS_OBUF tmds_bufds [3:0] (
        .I ({clk_pixel, tmds_d}),
        .O ({tmds_clk_p, tmds_d_p}),
        .OB({tmds_clk_n, tmds_d_n})
    );

endmodule

`default_nettype wire
