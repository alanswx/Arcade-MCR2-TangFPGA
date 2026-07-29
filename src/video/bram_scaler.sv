//-----------------------------------------------------------------------------
// bram_scaler - nestang-style on-chip framebuffer + nearest-neighbour upscaler
//-----------------------------------------------------------------------------
// A direct port of the architecture in nand2mario's nes2hdmi.sv, which drives
// HDMI on this same silicon with no dropouts. The point of copying it exactly
// is that it removes, by construction, every mechanism that can drop a frame:
//
//   * ONE dual-port BRAM. The writer owns port A, the reader owns port B, so
//     they never contend. No arbitration, no shared memory port, no refresh.
//   * The writer is FRAME-STATELESS: it writes mem[{y,x}] as pixels arrive and
//     is never gated by vsync, never stalled, never back-pressured. A late or
//     early source vsync cannot truncate a frame.
//   * The reader is a 1-cycle BRAM read off the scaling counters. It cannot
//     underrun, so there is no "substitute grey on empty" path.
//   * The whole read side lives in ONE clock domain (clk_pixel). There is no
//     shadow raster, no second copy of the raster counters, and no async FIFO
//     between the scanout and the TMDS encoder.
//
// Contrast with the DDR3 framebuffer, which has five places where timing can
// slip between a source pixel and the TMDS pin. See docs / TODO.md.
//
// Single-buffered and free-running, exactly like nestang: a source/output rate
// mismatch (e.g. 60.09 vs 60.00 Hz) shows up as a slowly drifting tear line,
// NOT as a dropped or duplicated frame.
//
// COST. BSRAM is the price of admission. Usable BSRAM on a GW5AT-60 is
// 118 x 16 Kbit. At WIDTH x HEIGHT x (3*CBITS) bits:
//     512x480 @ CBITS=2 (RGB222, 6 bpp) ->  90 blocks   <- default
//     512x240 @ CBITS=4 (RGB444,12 bpp) ->  90 blocks
//     512x480 @ CBITS=4 (RGB444,12 bpp) -> 180 blocks   TOO BIG
// nestang gets away with 256x240x6 = 23 blocks because the NES is a quarter
// of our pixel count and it stores a 6-bit PALETTE INDEX, expanding to RGB
// after the buffer. The same trick applies to MCR (64-entry palette).
//-----------------------------------------------------------------------------
`default_nettype none

module bram_scaler #(
    parameter WIDTH      = 512,   // source active width
    parameter HEIGHT     = 480,   // source active height
    parameter CBITS      = 2,     // stored bits PER CHANNEL
    parameter DISP_WIDTH = 960,   // output window width (960 = 4:3 in 720p)
    parameter OUT_WIDTH  = 1280,
    parameter OUT_HEIGHT = 720
)(
    // ---- write side: source clock domain ----
    input  wire        wr_clk,
    input  wire        wr_en,      // one pulse per source pixel
    input  wire [7:0]  wr_r,
    input  wire [7:0]  wr_g,
    input  wire [7:0]  wr_b,
    input  wire        wr_hsync_n, // active-low; used only to reset wr_x
    input  wire        wr_vsync_n, // active-low; used only to reset wr_y
    input  wire        wr_active,  // source pixel is inside the active area

    // ---- read side: pixel clock domain ----
    input  wire        rd_clk,
    input  wire [10:0] cx,         // raster position from the HDMI module
    input  wire [9:0]  cy,
    output reg  [23:0] rgb
);

    localparam CB    = 3*CBITS;
    localparam DEPTH = WIDTH*HEIGHT;
    localparam AW    = $clog2(DEPTH);

    (* ram_style = "block" *) reg [CB-1:0] mem [0:DEPTH-1];

    //------------------------------------------------------------------ write
    // Frame-stateless by design: x resets on hsync, y on vsync, and pixels are
    // written as they arrive. Nothing here can stall or be back-pressured.
    reg [$clog2(WIDTH)-1:0]  wr_x = 0;
    reg [$clog2(HEIGHT)-1:0] wr_y = 0;
    reg hs_d = 1, vs_d = 1;

    wire [CB-1:0] wr_pix = {wr_r[7 -: CBITS], wr_g[7 -: CBITS], wr_b[7 -: CBITS]};

    always @(posedge wr_clk) begin
        if (wr_en) begin
            hs_d <= wr_hsync_n;
            vs_d <= wr_vsync_n;
            // falling edge of active-low sync = start of line / frame
            if (!wr_hsync_n && hs_d) begin
                wr_x <= 0;
                if (wr_y != HEIGHT-1) wr_y <= wr_y + 1'b1;
            end
            if (!wr_vsync_n && vs_d) wr_y <= 0;

            if (wr_active) begin
                mem[wr_y*WIDTH + wr_x] <= wr_pix;
                if (wr_x != WIDTH-1) wr_x <= wr_x + 1'b1;
            end
        end
    end

    //------------------------------------------------------------------- read
    // Bresenham fractional counters, straight out of nes2hdmi.sv. xcnt/ycnt
    // accumulate the SOURCE size and wrap on the OUTPUT size.
    localparam XSTART = (OUT_WIDTH - DISP_WIDTH)/2;
    localparam XSTOP  = (OUT_WIDTH + DISP_WIDTH)/2;

    reg [$clog2(WIDTH)-1:0]  xx = 0;
    reg [$clog2(HEIGHT)-1:0] yy = 0;
    reg [11:0] xcnt = 0, ycnt = 0;
    reg        active = 0;
    reg [9:0]  cy_r = 0;

    wire [AW-1:0] rd_addr = yy*WIDTH + xx;
    reg  [CB-1:0] rd_data;
    always @(posedge rd_clk) rd_data <= mem[rd_addr];

    always @(posedge rd_clk) begin
        reg active_t;
        reg [11:0] xcnt_next, ycnt_next;
        xcnt_next = xcnt + WIDTH[11:0];
        ycnt_next = ycnt + HEIGHT[11:0];

        active_t = 1'b0;
        if (cx == XSTART-1)     begin active_t = 1'b1; active <= 1'b1; end
        else if (cx == XSTOP-1) begin active_t = 1'b0; active <= 1'b0; end

        if (active_t | active) begin
            xcnt <= xcnt_next;
            if (xcnt_next >= DISP_WIDTH[11:0]) begin
                xcnt <= xcnt_next - DISP_WIDTH[11:0];
                xx   <= xx + 1'b1;
            end
        end

        cy_r <= cy;
        if (cy[0] != cy_r[0]) begin          // one step per output line
            ycnt <= ycnt_next;
            if (ycnt_next >= OUT_HEIGHT[11:0]) begin
                ycnt <= ycnt_next - OUT_HEIGHT[11:0];
                yy   <= yy + 1'b1;
            end
        end

        if (cx == 0) begin xx <= 0; xcnt <= 0; end
        if (cy == 0) begin yy <= 0; ycnt <= 0; end
    end

    // expand stored channels back to 8 bits by MSB replication
    function [7:0] expand(input [CBITS-1:0] v);
        integer k;
        begin
            expand = 8'd0;
            for (k = 0; k < 8; k = k + CBITS)
                expand = (expand << CBITS) | v;
        end
    endfunction

    // registered one cycle after rd_data, matching nestang's pipeline
    reg active_d = 0;
    always @(posedge rd_clk) begin
        active_d <= active;
        rgb <= active_d ? {expand(rd_data[CB-1 -: CBITS]),
                           expand(rd_data[2*CBITS-1 -: CBITS]),
                           expand(rd_data[CBITS-1 -: CBITS])}
                        : 24'h202020;   // pillarbox grey, as nestang uses
    end

endmodule

`default_nettype wire
