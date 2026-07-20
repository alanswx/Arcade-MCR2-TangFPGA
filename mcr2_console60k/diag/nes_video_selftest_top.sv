// 720p HDMI self-test using NESTang's PROVEN clock topology:
//   50MHz -> pll_27 -> 27MHz -> gowin_pll_hdmi -> hclk5 (371.25MHz)
//   hclk5 -> CLKDIV/5 -> hclk (74.25MHz pixel clock)
// One chain: the OSER10 serializers' PCLK and FCLK are phase-locked by
// construction - unlike the gbatang framebuffer, whose pixel clock comes
// from the DDR3 controller and serial clock from a different PLL (fails on
// this board even in a minimal design; see fb_selftest).
// Same hdl-util hdmi stack we already vendor. 720p colour bars.
module nes_video_selftest_top (
    input        sys_clk,
    input        s1,
    output       tmds_clk_p, tmds_clk_n,
    output [2:0] tmds_d_p,   tmds_d_n,
    output       hpd_en,
    output       uart_tx
);

assign hpd_en = 1'b1;

wire clk27, hclk5, hclk;
pll_27 pll27 (.clkin(sys_clk), .clkout0(clk27));
gowin_pll_hdmi pllh (.clkin(clk27), .clkout(hclk5));

reg [7:0] rstn_cnt = 8'd255;
wire resetn = (rstn_cnt == 0);
always @(posedge sys_clk) if (rstn_cnt != 0) rstn_cnt <= rstn_cnt - 8'd1;

CLKDIV #(.DIV_MODE(5)) div5 (
    .CLKOUT(hclk), .HCLKIN(hclk5), .RESETN(resetn), .CALIB(1'b0)
);

// audio clock as the framebuffer makes it (32 kHz from the pixel clock)
localparam AUDIO_RATE = 32000;
localparam AUDIO_CLK_DELAY = 74250 * 1000 / AUDIO_RATE / 2;
reg [$clog2(AUDIO_CLK_DELAY)-1:0] audio_div;
reg clk_audio;
always @(posedge hclk) begin
    if (audio_div != AUDIO_CLK_DELAY - 1) audio_div <= audio_div + 1'b1;
    else begin clk_audio <= ~clk_audio; audio_div <= 0; end
end
reg [15:0] audio_word [1:0];
initial begin audio_word[0] = 0; audio_word[1] = 0; end

wire [10:0] cx;
wire [9:0]  cy;
reg  [23:0] rgb;
always @(posedge hclk) begin
    // 720p colour bars with a diagonal so motion/stride errors are obvious
    rgb <= {cx[9:7], 5'b0, cy[8:6], 5'b0, cx[6] ^ cy[6], 7'b0} |
           ((cx[4:0] == cy[4:0]) ? 24'h404040 : 24'h0);
end

wire [2:0] tmds;
hdmi #( .VIDEO_ID_CODE(4), .DVI_OUTPUT(0), .VIDEO_REFRESH_RATE(60.0),
        .IT_CONTENT(1), .AUDIO_RATE(AUDIO_RATE), .AUDIO_BIT_WIDTH(16),
        .START_X(0), .START_Y(0) )
hdmi_i ( .clk_pixel_x5(hclk5), .clk_pixel(hclk), .clk_audio(clk_audio),
         .rgb(rgb), .reset(1'b0),
         .audio_sample_word(audio_word),
         .tmds(tmds), .tmds_clock(),
         .cx(cx), .cy(cy), .frame_width(), .frame_height() );

ELVDS_OBUF tmds_bufds [3:0] (
    .I({hclk, tmds}),
    .O({tmds_clk_p, tmds_d_p}),
    .OB({tmds_clk_n, tmds_d_n})
);

reg [24:0] hb = 0;
always @(posedge hclk) hb <= hb + 1'b1;
uart_beacon #(.CLK_HZ(50_000_000)) beacon (
    .clk(sys_clk), .calib(resetn), .ddr_rst(1'b0),
    .cnt_x({hb[24:21], 12'h000}), .cnt_q(8'h4E), .aux(8'h4E), .aux2(8'h4E),
    .txd(uart_tx)
);
endmodule
