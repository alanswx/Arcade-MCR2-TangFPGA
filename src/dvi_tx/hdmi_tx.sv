// DVI/HDMI Transmitter for Gowin GW5A FPGAs
module hdmi_tx (
    input            clk_pixel,      // Pixel clock (e.g. 74.25 MHz)
    input            clk_5x_pixel,   // 5x Pixel clock (e.g. 371.25 MHz)
    input            resetn,
    input      [7:0] rgb_r,          // Red channel data (8-bit)
    input      [7:0] rgb_g,          // Green channel data (8-bit)
    input      [7:0] rgb_b,          // Blue channel data (8-bit)
    input            de,             // Data enable (active video)
    input            hsync,          // Horizontal sync
    input            vsync,          // Vertical sync

    // Physical HDMI differential outputs
    output           tmds_clk_p,
    output           tmds_clk_n,
    output     [2:0] tmds_d_p,
    output     [2:0] tmds_d_n
);

// 10-bit encoded TMDS symbols
wire [9:0] tmds_red;
wire [9:0] tmds_green;
wire [9:0] tmds_blue;

// Instantiation of TMDS Encoders
// Blue channel encodes HSync and VSync on control bits [1:0]
tmds_encoder encode_blue (
    .clk(clk_pixel),
    .resetn(resetn),
    .de(de),
    .ctrl({vsync, hsync}),
    .din(rgb_b),
    .dout(tmds_blue)
);

// Green channel encodes 2'b00
tmds_encoder encode_green (
    .clk(clk_pixel),
    .resetn(resetn),
    .de(de),
    .ctrl(2'b00),
    .din(rgb_g),
    .dout(tmds_green)
);

// Red channel encodes 2'b00
tmds_encoder encode_red (
    .clk(clk_pixel),
    .resetn(resetn),
    .de(de),
    .ctrl(2'b00),
    .din(rgb_r),
    .dout(tmds_red)
);

// Multiplexing inputs for OSER10 primitives
wire [2:0] tmds_d;
wire [2:0] tmds_d0 = {tmds_red[0], tmds_green[0], tmds_blue[0]};
wire [2:0] tmds_d1 = {tmds_red[1], tmds_green[1], tmds_blue[1]};
wire [2:0] tmds_d2 = {tmds_red[2], tmds_green[2], tmds_blue[2]};
wire [2:0] tmds_d3 = {tmds_red[3], tmds_green[3], tmds_blue[3]};
wire [2:0] tmds_d4 = {tmds_red[4], tmds_green[4], tmds_blue[4]};
wire [2:0] tmds_d5 = {tmds_red[5], tmds_green[5], tmds_blue[5]};
wire [2:0] tmds_d6 = {tmds_red[6], tmds_green[6], tmds_blue[6]};
wire [2:0] tmds_d7 = {tmds_red[7], tmds_green[7], tmds_blue[7]};
wire [2:0] tmds_d8 = {tmds_red[8], tmds_green[8], tmds_blue[8]};
wire [2:0] tmds_d9 = {tmds_red[9], tmds_green[9], tmds_blue[9]};

// Serialize the 3 channels using Gowin OSER10 blocks
OSER10 tmds_serdes [2:0] (
    .Q(tmds_d),
    .D0(tmds_d0),
    .D1(tmds_d1),
    .D2(tmds_d2),
    .D3(tmds_d3),
    .D4(tmds_d4),
    .D5(tmds_d5),
    .D6(tmds_d6),
    .D7(tmds_d7),
    .D8(tmds_d8),
    .D9(tmds_d9),
    .PCLK(clk_pixel),
    .FCLK(clk_5x_pixel),
    .RESET(~resetn)
);

// Output differential TMDS buffers using Gowin ELVDS_OBUF blocks
ELVDS_OBUF tmds_bufds [3:0] (
    .I({clk_pixel, tmds_d}),
    .O({tmds_clk_p, tmds_d_p}),
    .OB({tmds_clk_n, tmds_d_n})
);

endmodule
