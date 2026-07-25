//-----------------------------------------------------------------------------
// mcr_testpattern - MCR-faithful video timing + a scaler-evaluation pattern
//-----------------------------------------------------------------------------
// Stands in for mcr2.vhd so the video chain (analog VGA, ascal, HDMI) can be
// brought up and judged with no core, no ROMs and no SD card in the way.
//
// Timing is copied from mcr2.vhd's counters, NOT invented, so anything that
// works here works with the real core:
//   both modes : hcnt 0..633
//   31 kHz     : pixel enable 20 MHz, vcnt 0..524  -> 31.55 kHz / 60.09 Hz
//                active 512x480, hblank at hcnt>=512, hs low 525..601
//   15 kHz     : pixel enable 10 MHz, vcnt 0..263  -> 15.77 kHz / 59.75 Hz
//                active 512x240 at hcnt 17..528 (mcr2.vhd's 1+16 / 513+16)
// The one deliberate difference: mcr2.vhd synthesises proper equalisation and
// serration pulses for composite sync in 15 kHz mode (hsync0..hsync4).  This
// generator emits plain separate H/V, which is what the 60K top outputs by
// default anyway (see the sync-format note in mcr2_console60k_top.sv) - a
// csync ladder is a core feature, not a scaler-path feature.
//
// The pattern is chosen to make scaler differences visible:
//   band 0  colour bars            - palette / DAC ladder sanity
//   band 1  1-px vertical stripes  - horizontal filtering: nearest shimmers,
//                                    bicubic rings, polyphase should be clean
//   band 2  1-px horizontal stripes- vertical filtering (and interlace bugs)
//   band 3  grey ramp              - banding / bit depth through the chain
//   band 4  1-px checkerboard      - the classic upscaler torture test
//   band 5  32-px crosshatch       - geometry, aspect ratio, integer scaling
//   overlay moving vertical bar    - tearing, judder and latency
//   overlay 1-px white border      - proves nothing is cropped (hmin/hmax)
//-----------------------------------------------------------------------------
`default_nettype none

module mcr_testpattern (
    input  wire        clk,          // 40 MHz clk_sys, as the core uses
    input  wire        rst,          // active high
    input  wire        mode15,       // 1 = 15 kHz 240p, 0 = 31 kHz 480p

    output wire        ce_pix,       // pixel clock enable (10 or 20 MHz)
    output reg  [7:0]  r,
    output reg  [7:0]  g,
    output reg  [7:0]  b,
    output reg         hs,           // active low
    output reg         vs,           // active low
    output reg         de,           // active video
    output reg         hblank,
    output reg         vblank,
    output wire [9:0]  hcnt_o,
    output wire [9:0]  vcnt_o
);

    // ---- pixel clock enable: /4 for 10 MHz, /2 for 20 MHz (mcr2.vhd:319) ----
    reg [1:0] clkdiv = 0;
    always @(posedge clk) clkdiv <= clkdiv + 1'b1;
    assign ce_pix = mode15 ? (clkdiv == 2'b11) : clkdiv[0];

    // ---- raster counters ----
    reg [9:0] hcnt = 0, vcnt = 0;
    assign hcnt_o = hcnt;
    assign vcnt_o = vcnt;

    wire [9:0] vlast = mode15 ? 10'd263 : 10'd524;

    always @(posedge clk) begin
        if (rst) begin
            hcnt <= 0;
            vcnt <= 0;
        end else if (ce_pix) begin
            hcnt <= hcnt + 1'b1;
            if (hcnt == 10'd633) begin
                hcnt <= 0;
                vcnt <= (vcnt == vlast) ? 10'd0 : vcnt + 1'b1;
            end
        end
    end

    // ---- frame counter, for the animated bar ----
    reg [9:0] frame = 0;
    always @(posedge clk)
        if (ce_pix && hcnt == 10'd633 && vcnt == vlast) frame <= frame + 1'b1;

    // ---- active window and sync ----
    // 15 kHz shifts the active window right by 16 pixels, exactly as the core.
    wire [9:0] hstart = mode15 ? 10'd17  : 10'd0;
    wire [9:0] hstop  = mode15 ? 10'd529 : 10'd512;   // exclusive
    wire [9:0] vstop  = mode15 ? 10'd240 : 10'd480;   // exclusive

    wire hblank_c = !(hcnt >= hstart && hcnt < hstop);
    wire vblank_c = !(vcnt < vstop);

    // H sync: 31 kHz = front porch 13 then 77 wide (mcr2.vhd:352-353)
    //         15 kHz = 47 clocks at 10 MHz = 4.7 us
    wire hs_c = mode15 ? !(hcnt >= 10'd545 && hcnt < 10'd592)
                       : !(hcnt >= 10'd525 && hcnt < 10'd602);
    // V sync: 31 kHz = 2 lines after a 10-line front porch (mcr2.vhd:348-349)
    wire vs_c = mode15 ? !(vcnt >= 10'd245 && vcnt < 10'd248)
                       : !(vcnt >= 10'd489 && vcnt < 10'd491);

    // ---- pattern ----
    // x/y are 0-based inside the active window
    wire [9:0] x = hcnt - hstart;
    wire [9:0] y = vcnt;
    // Six equal horizontal bands across whichever height is active.
    // 480/6 = 80, 240/6 = 40.
    wire [9:0] bandh = mode15 ? 10'd40 : 10'd80;
    wire [2:0] band  = (y < bandh)     ? 3'd0 :
                       (y < bandh*2)   ? 3'd1 :
                       (y < bandh*3)   ? 3'd2 :
                       (y < bandh*4)   ? 3'd3 :
                       (y < bandh*5)   ? 3'd4 : 3'd5;

    // colour bars: 512/8 = 64 px each
    wire [2:0] bar = x[8:6];
    reg [23:0] bar_rgb;
    always @(*) case (bar)
        3'd0: bar_rgb = 24'hFFFFFF;   // white
        3'd1: bar_rgb = 24'hFFFF00;   // yellow
        3'd2: bar_rgb = 24'h00FFFF;   // cyan
        3'd3: bar_rgb = 24'h00FF00;   // green
        3'd4: bar_rgb = 24'hFF00FF;   // magenta
        3'd5: bar_rgb = 24'hFF0000;   // red
        3'd6: bar_rgb = 24'h0000FF;   // blue
        3'd7: bar_rgb = 24'h000000;   // black
    endcase

    // moving bar: 8 px wide, wraps across the 512-px window once per ~8.5 s
    wire [9:0] barpos = {frame[8:0], 1'b0} % 10'd512;
    wire in_movbar = (x >= barpos) && (x < barpos + 10'd8);

    // 1-px white border around the active area
    wire in_border = (x == 0) || (x == 10'd511) ||
                     (y == 0) || (y == vstop - 1'b1);

    // crosshatch every 32 px
    wire in_hatch = (x[4:0] == 5'd0) || (y[4:0] == 5'd0);

    wire [7:0] ramp = x[8:1];   // 512 px -> 0..255

    reg [23:0] pat;
    always @(*) begin
        case (band)
            3'd0: pat = bar_rgb;
            3'd1: pat = x[0]    ? 24'hFFFFFF : 24'h000000;  // vertical stripes
            3'd2: pat = y[0]    ? 24'hFFFFFF : 24'h000000;  // horizontal stripes
            3'd3: pat = {ramp, ramp, ramp};                 // grey ramp
            3'd4: pat = (x[0]^y[0]) ? 24'hFFFFFF : 24'h000000; // checkerboard
            default: pat = in_hatch ? 24'h00FF00 : 24'h101010;
        endcase
        if (in_movbar) pat = 24'hFF8000;   // orange
        if (in_border) pat = 24'hFFFFFF;
    end

    // ---- register the outputs on the pixel enable ----
    always @(posedge clk) begin
        if (rst) begin
            {r, g, b} <= 24'h0;
            hs <= 1'b1; vs <= 1'b1; de <= 1'b0;
            hblank <= 1'b1; vblank <= 1'b1;
        end else if (ce_pix) begin
            hblank <= hblank_c;
            vblank <= vblank_c;
            de     <= !hblank_c && !vblank_c;
            hs     <= hs_c;
            vs     <= vs_c;
            {r, g, b} <= (!hblank_c && !vblank_c) ? pat : 24'h0;
        end
    end

endmodule

`default_nettype wire
