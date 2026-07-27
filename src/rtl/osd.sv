// On-screen game-select menu, drawn in the CORE video domain.
//
// The overlay is composited onto the core's RGB *before* the video path
// splits, so it appears identically on every output - the DDR3/HDMI
// framebuffer, analog VGA at 31 kHz, and native 15 kHz (the raster is only
// 240 lines there; the window geometry adapts). For the vertical games
// (Tron, Satan's Hollow - MAME ROT90) the text is drawn rotated so it reads
// correctly on a cabinet's rotated monitor.
//
// Controls (USB pad): Select+Start toggles the menu. Up/Down move, A loads
// the highlighted game from the SD pack (rom_loader restarts; the core sits
// in reset meanwhile, so the raster - and this menu - vanish for the ~1 s of
// loading and the new game boots). B exits. While the menu is open the top
// masks all game inputs.
//
// game_id is the game the core is RUNNING (drives the input/DIP mux in the
// top); it only changes after a load completes, so a failed SD load leaves
// the running game's controls intact.
//
// The '>' cursor marks the highlighted row, '*' the running game, and '^'/'V'
// in the last column show the list continues past the visible window.
// Parameterized for the family's roster: MCR-2 keeps the defaults below
// (6 games), MCR-1 passes 3 (kick/solarfox/kickman), MCR-3 passes 3, each
// with its own ROT_MASK. Names are 24-char strings; entries >= NUM_GAMES are
// never drawn and the cursor wraps at NUM_GAMES-1.
// ROSTER SIZE (widened 2026-07-27): up to MAX_GAMES entries, of which
// VIS_ROWS are on screen at once and the list SCROLLS. The window geometry is
// deliberately unchanged - it is 14 rows, and the ROT90 + 15 kHz case has only
// ~24 scanlines of slack, so growing the box risks running off the raster in
// one of the four rot x mode15 combinations. Scrolling costs a few LUTs and no
// geometry risk. 20 slots covers the whole series we are building - MCR-1 (3)
// + MCR-2 (6, +Demolition Derby when Turbo Cheap Squeak lands) + MCR-3 (3,
// +Journey when DDR3 wave audio lands) + MCR3Scroll (3) = 17 - with room for
// a diagnostic/test entry or two. MCR3Mono is NOT in scope.
module osd #(
    parameter [4:0]   GAME_DEFAULT = 5'd5, // pack slot order: 0 shollow,
                                           // 1 tron, 2 wacko, 3 kroozr,
                                           // 4 twotiger, 5 domino
    parameter [5:0]   NUM_GAMES    = 6'd6,
    parameter [19:0]  ROT_MASK     = 20'h00003,    // bit i: game i is ROT90
                                                 // (rotate the OSD text)
    parameter [191:0] TITLE = "    MCR2 GAME SELECT    ",
    parameter [191:0] NAME0 = "   SATANS HOLLOW        ",
    parameter [191:0] NAME1 = "   TRON                 ",
    parameter [191:0] NAME2 = "   WACKO                ",
    parameter [191:0] NAME3 = "   KOZMIK KROOZR        ",
    parameter [191:0] NAME4 = "   TWO TIGERS           ",
    parameter [191:0] NAME5 = "   DOMINO MAN           ",
    parameter [191:0] NAME6  = "                        ",
    parameter [191:0] NAME7  = "                        ",
    parameter [191:0] NAME8  = "                        ",
    parameter [191:0] NAME9  = "                        ",
    parameter [191:0] NAME10 = "                        ",
    parameter [191:0] NAME11 = "                        ",
    parameter [191:0] NAME12 = "                        ",
    parameter [191:0] NAME13 = "                        ",
    parameter [191:0] NAME14 = "                        ",
    parameter [191:0] NAME15 = "                        ",
    parameter [191:0] NAME16 = "                        ",
    parameter [191:0] NAME17 = "                        ",
    parameter [191:0] NAME18 = "                        ",
    parameter [191:0] NAME19 = "                        "
)(
    input             clk,          // clk_sys (40 MHz)
    input             rst,

    // Core raster position (pre-capture-delay; the menu box lands a few px
    // from dead centre, which does not matter)
    input             pixel_tick,   // one strobe per 20 MHz core pixel
    input      [9:0]  hcnt,
    input             hblank,
    input             vblank,
    input             mode15,       // 240-line raster (15 kHz mode)

    input      [8:0]  rgb_in,       // {r,g,b} 3:3:3 from the core
    output     [8:0]  rgb_out,

    // Pad buttons, clk-synchronized, active high, UNMASKED
    input             btn_up,
    input             btn_down,
    input             btn_a,
    input             btn_b,
    input             btn_sel,
    input             btn_sta,
    // Cabinet-side menu chord (roadmap item 6): a LONG-HOLD signal from the
    // coin-door group - the only inputs present identically on every MCR
    // harness (docs/mcr_game_input_matrix.md). Bench: 3s hold of the coin
    // key; shield: the 74HC165 Service line. Must behave the same in every
    // family top so cabinet muscle memory transfers between games.
    input             btn_menu_hold,

    // Game selection / loader handshake
    output reg [4:0]  game_id,        // game the core is running
    // ROSTER INDEX to load (not a pack slot). With a merged multi-family
    // roster the two differ: the top translates index -> (family, slot).
    // 5 bits to match the 20-slot roster.
    output reg [4:0]  load_slot,
    output reg        loader_restart, // 1-cycle pulse: reload load_slot
    input             loader_done,
    input             loader_error,
    input      [4:0]  loaded_slot,    // roster index actually loaded - at boot
                                      // this may be the SD-saved preference,
                                      // not GAME_DEFAULT
    output reg        save_req,       // pulse: persist the selection to SD
    input             sd_ready,       // card initialised

    output            osd_active,
    // High while the INSERT CARD screen owns the display. The tops use it to
    // keep honouring the SD prefs during its retries (osd_active alone would
    // force use_prefs low and lose the owner's saved game) and it is what
    // blanks the core's video underneath.
    output            osd_nocard
);

localparam [2:0] S_CLOSED = 3'd0,
                 S_OPEN   = 3'd1,
                 S_LOAD   = 3'd2,   // restart pulse issued, done not yet low
                 S_LOAD2  = 3'd3,   // loader running
                 S_ERR    = 3'd4,
                 S_NOCARD = 3'd5;   // no usable card - retry until there is

reg [2:0] state = S_CLOSED;
reg [4:0] cursor = GAME_DEFAULT;
// First roster entry drawn, so a list longer than VIS_ROWS can scroll. Kept
// in step with the cursor on every move rather than recomputed while drawing.
reg [4:0] scroll = 5'd0;
localparam [4:0] VIS_ROWS = 5'd8;    // rows 3..10 of the 14-row window
localparam [4:0] ROW_TOP  = 5'd3;

assign osd_active = (state != S_CLOSED);
assign osd_nocard = (state == S_NOCARD);

// INSERT CARD retry cadence. The bitstream carries no ROM data any more
// (licensing), so a missing or unreadable card leaves the core with blank
// RAM and nothing to run - it must say so rather than show whatever empty
// memory renders. rom_loader gives up after MAX_RETRY and latches `error`,
// so recovery needs a fresh restart pulse: retry roughly every 2 s at
// 60 Hz, which makes inserting a card Just Work with no power cycle.
localparam [6:0] NOCARD_RETRY_FRAMES = 7'd120;
reg [6:0] nocard_div = 7'd0;

// ---------------------------------------------------------------------------
// Button events: sampled once per FRAME, not per clock. The USB HID host
// updates its button outputs byte-by-byte while each report streams in, so
// a held button shows transient edges at 40 MHz - the games never notice
// (they poll levels at frame rate) but a per-clock edge detector counts
// them and the cursor skips. One settled sample per vblank debounces all of
// that, and gives natural units for hold-to-repeat: first repeat after
// ~0.5 s (30 frames), then ~8/s (every 8 frames).
// ---------------------------------------------------------------------------
reg vbl_q = 1'b1;
always @(posedge clk) vbl_q <= vblank;
wire frame_tick = vblank & ~vbl_q;

wire combo = (btn_sel & btn_sta) | btn_menu_hold;

reg p_up = 0, p_dn = 0, p_a = 0, p_b = 0, p_combo = 0;
reg [5:0] rpt_cnt = 0;
reg ev_up = 0, ev_dn = 0, ev_a = 0, ev_b = 0, ev_combo = 0;   // 1-clk pulses

always @(posedge clk) begin
    ev_up    <= 1'b0;
    ev_dn    <= 1'b0;
    ev_a     <= 1'b0;
    ev_b     <= 1'b0;
    ev_combo <= 1'b0;
    if (frame_tick) begin
        p_up    <= btn_up;
        p_dn    <= btn_down;
        p_a     <= btn_a;
        p_b     <= btn_b;
        p_combo <= combo;

        ev_a     <= btn_a & ~p_a;
        ev_b     <= btn_b & ~p_b;
        ev_combo <= combo & ~p_combo;

        // Up/Down: event on press, then auto-repeat while held
        if (btn_up ^ btn_down) begin
            if ((btn_up & ~p_up) || (btn_down & ~p_dn)) begin
                ev_up   <= btn_up;
                ev_dn   <= btn_down;
                rpt_cnt <= 6'd0;
            end else if (rpt_cnt >= 6'd30) begin
                ev_up   <= btn_up;
                ev_dn   <= btn_down;
                rpt_cnt <= 6'd22;            // 30-22 = repeat every 8 frames
            end else
                rpt_cnt <= rpt_cnt + 6'd1;
        end else
            rpt_cnt <= 6'd0;
    end
end

// ---------------------------------------------------------------------------
// Menu FSM
// ---------------------------------------------------------------------------
reg done_r = 1'b0;

always @(posedge clk) begin
    loader_restart <= 1'b0;
    save_req       <= 1'b0;

    if (rst) begin
        state     <= S_CLOSED;
        game_id   <= GAME_DEFAULT;
        cursor    <= GAME_DEFAULT;
        load_slot <= GAME_DEFAULT;
        done_r    <= 1'b0;
    end else begin
        // Whatever the loader finished loading is what the core is running
        // - covers both OSD-selected loads and the boot-time load of the
        // SD-saved preference. ROMs and input map switch together, always.
        done_r <= loader_done;
        if (loader_done & ~done_r)
            game_id <= loaded_slot;

        case (state)

        // A load that failed with the menu closed means boot found no usable
        // card. There is no baked fallback any more, so take over the screen.
        S_CLOSED:
            if (loader_error) begin
                state      <= S_NOCARD;
                nocard_div <= 7'd0;
            end else if (ev_combo) begin
                state  <= S_OPEN;
                cursor <= game_id;
                // Scroll so the running game is visible when the menu opens.
                scroll <= (game_id < VIS_ROWS) ? 5'd0
                                               : (game_id - VIS_ROWS + 5'd1);
            end

        // Hold the INSERT CARD message and keep retrying. Any successful load
        // (the card turning up) drops straight back into the game.
        S_NOCARD:
            if (loader_done)
                state <= S_CLOSED;
            // Self-pacing: only count while the loader has GIVEN UP
            // (loader_error high). An attempt takes seconds, so a free-running
            // timer would stack restarts on top of an in-flight retry.
            else if (frame_tick && loader_error) begin
                if (nocard_div == NOCARD_RETRY_FRAMES - 7'd1) begin
                    nocard_div     <= 7'd0;
                    loader_restart <= 1'b1;   // re-arm; rom_loader latched error
                end else
                    nocard_div <= nocard_div + 7'd1;
            end

        S_OPEN: begin
            if (ev_combo || ev_b)
                state <= S_CLOSED;
            else if (ev_up) begin
                if (cursor == 5'd0) begin           // wrap to the end
                    cursor <= NUM_GAMES[4:0] - 5'd1;
                    scroll <= (NUM_GAMES[4:0] > VIS_ROWS)
                              ? (NUM_GAMES[4:0] - VIS_ROWS) : 5'd0;
                end else begin
                    cursor <= cursor - 5'd1;
                    if (cursor - 5'd1 < scroll) scroll <= cursor - 5'd1;
                end
            end else if (ev_dn) begin
                if (cursor == NUM_GAMES[4:0] - 5'd1) begin   // wrap to the top
                    cursor <= 5'd0;
                    scroll <= 5'd0;
                end else begin
                    cursor <= cursor + 5'd1;
                    if (cursor + 5'd1 >= scroll + VIS_ROWS)
                        scroll <= cursor + 5'd2 - VIS_ROWS;
                end
            end
            else if (ev_a) begin
                load_slot      <= cursor;
                loader_restart <= 1'b1;
                state          <= S_LOAD;
            end
        end

        // The loader's done/error take a couple of cycles to drop after the
        // restart pulse; wait for that before watching for completion, or a
        // stale done would "finish" the load instantly.
        S_LOAD:
            if (!loader_done && !loader_error)
                state <= S_LOAD2;

        S_LOAD2:
            if (loader_done) begin
                save_req <= 1'b1;       // persist: next power-on boots this
                state    <= S_CLOSED;
            end else if (loader_error)
                state <= S_ERR;

        S_ERR:
            if (ev_a || ev_b || ev_combo)
                state <= S_OPEN;

        default:
            state <= S_CLOSED;
        endcase
    end
end

// ---------------------------------------------------------------------------
// Raster position: x = hcnt, y = active lines since vblank
// ---------------------------------------------------------------------------
reg [9:0] ycnt = 0;
reg       hb_r = 0;
always @(posedge clk) begin
    if (pixel_tick) begin
        hb_r <= hblank;
        if (vblank) begin
            ycnt <= 10'd0;
            hb_r <= 1'b0;
        end else if (hblank & ~hb_r)
            ycnt <= ycnt + 10'd1;
    end
end

// Window geometry. Text plane is 24 cols x 14 rows of 8x8 = 192 x 112 px.
// ROT0 draws it as-is; ROT90 (Tron/Satan's Hollow) swaps the raster extents
// and remaps so the text reads upright on the cabinet's rotated monitor.
// x positions include the nominal 13 px capture offset of the visible area.
wire rot = ROT_MASK[game_id];   // per-game (MCR-2 default: shollow, tron)

wire [9:0] win_w = rot ? 10'd112 : 10'd192;
wire [9:0] win_h = rot ? 10'd192 : 10'd112;
wire [9:0] x0    = rot ? 10'd213 : 10'd173;
wire [9:0] y0    = rot ? (mode15 ? 10'd24 : 10'd144)
                       : (mode15 ? 10'd64 : 10'd184);

wire [9:0] xr = hcnt - x0;
wire [9:0] yr = ycnt - y0;
wire inwin = ~vblank && (hcnt >= x0) && (xr < win_w)
                     && (ycnt >= y0) && (yr < win_h);

// Text-plane coordinates: u = 0..191 across, v = 0..111 down.
// ROT90 mapping is "rotate clockwise to view" (MAME ROT90); if text comes
// out mirrored on real Tron hardware, swap to u=yr / v=111-xr (= ROT270).
wire [7:0] u = rot ? (8'd191 - yr[7:0]) : xr[7:0];
wire [6:0] v = rot ? xr[6:0] : yr[6:0];

// ---------------------------------------------------------------------------
// Menu text
// ---------------------------------------------------------------------------
// Every row is EXACTLY 24 characters (checked by tools/make_osd_font.py's
// sibling check in the build notes); shorter literals would left-pad with
// NULs and shift the text right.
localparam [191:0] TXT_TITLE   = TITLE;
// (the old TXT_G0..G5 per-row aliases are gone - rows are now mapped to
// roster entries dynamically through name_char(), so the list can scroll)
localparam [191:0] TXT_HELP    = "  A:LOAD  B:EXIT        ";
localparam [191:0] TXT_SDOK    = "  SD CARD: READY        ";
localparam [191:0] TXT_NOSD    = "  SD CARD: NOT FOUND    ";
localparam [191:0] TXT_LOADING = "  LOADING...            ";
localparam [191:0] TXT_FAILED  = "  LOAD FAILED           ";
// INSERT CARD screen. 24 columns; keep every line inside them or row_char
// simply truncates and the message reads wrong.
localparam [191:0] TXT_NC1     = "     NO SD CARD         ";
localparam [191:0] TXT_NC2     = "  INSERT THE CARD TO    ";
localparam [191:0] TXT_NC3     = "  LOAD A GAME           ";
localparam [191:0] TXT_NC4     = "  RETRYING...           ";

function [7:0] row_char(input [191:0] rowtext, input [4:0] col);
    // char 0 sits in the MSBs
    row_char = rowtext[{5'd23 - col, 3'b000} +: 8];
endfunction

// One character of roster entry `g`. Only one branch is live per pixel, so
// this synthesises to a 16:1 mux of small constant ROMs.
// One character of roster entry `g`. Only one branch is live per pixel, so
// this synthesises to a mux of small constant ROMs; entries above the
// instance's NUM_GAMES are pruned because the caller gates on it.
// One character of roster entry `g`. Only one branch is live per pixel, so
// this synthesises to a mux of small constant ROMs; entries above the
// instance's NUM_GAMES are pruned because the caller gates on it.
function [7:0] name_char(input [4:0] g, input [4:0] col);
    case (g)
    5'd0:   name_char = row_char(NAME0,  col);
    5'd1:   name_char = row_char(NAME1,  col);
    5'd2:   name_char = row_char(NAME2,  col);
    5'd3:   name_char = row_char(NAME3,  col);
    5'd4:   name_char = row_char(NAME4,  col);
    5'd5:   name_char = row_char(NAME5,  col);
    5'd6:   name_char = row_char(NAME6,  col);
    5'd7:   name_char = row_char(NAME7,  col);
    5'd8:   name_char = row_char(NAME8,  col);
    5'd9:   name_char = row_char(NAME9,  col);
    5'd10:  name_char = row_char(NAME10, col);
    5'd11:  name_char = row_char(NAME11, col);
    5'd12:  name_char = row_char(NAME12, col);
    5'd13:  name_char = row_char(NAME13, col);
    5'd14:  name_char = row_char(NAME14, col);
    5'd15:  name_char = row_char(NAME15, col);
    5'd16:  name_char = row_char(NAME16, col);
    5'd17:  name_char = row_char(NAME17, col);
    5'd18:  name_char = row_char(NAME18, col);
    default: name_char = row_char(NAME19, col);
    endcase
endfunction

// ---------------------------------------------------------------------------
// Render pipeline: 2 pixel stages (cell/char lookup -> font fetch); the
// whole menu box just lands 2 px right of nominal, which is invisible.
// ---------------------------------------------------------------------------
reg        p1_in = 0;
reg [4:0]  p1_col;
reg [3:0]  p1_row;
reg [2:0]  p1_ub, p1_vb;
always @(posedge clk) begin
    if (pixel_tick) begin
        p1_in  <= inwin;
        p1_col <= u[7:3];
        p1_row <= v[6:3];
        p1_ub  <= u[2:0];
        p1_vb  <= v[2:0];
    end
end

// Roster index shown on the current row, once the list is scrolled. 5 bits so
// scroll+7 cannot wrap, and so it compares cleanly against 5-bit NUM_GAMES.
// Use the FULL p1_row, not p1_row[2:0]: the roster occupies rows 3..10, and
// truncating to 3 bits wraps rows 8/9/10 back to 0/1/2 - which would silently
// repeat the first three entries at the bottom of the list.
// Underflows for rows above ROW_TOP, which is harmless: every use is gated on
// the row being inside the roster block.
// DECLARED BEFORE USE - Gowin turns use-before-declaration into a silent
// 1-bit wire (see CLAUDE.md), which here would collapse the whole roster.
wire [5:0] row_game = {1'b0, scroll} + {2'b0, p1_row} - {1'b0, ROW_TOP};

reg [7:0] ch;
always @(*) begin
    ch = 8'h20;   // space
    if (state == S_NOCARD) begin
        // Dedicated layout - the game roster is meaningless with no card.
        case (p1_row)
            4'd3:  ch = row_char(TXT_NC1, p1_col);
            4'd5:  ch = row_char(TXT_NC2, p1_col);
            4'd6:  ch = row_char(TXT_NC3, p1_col);
            4'd9:  ch = row_char(TXT_NC4, p1_col);
            default: ;
        endcase
    end else
    case (p1_row)
        4'd0:  ch = row_char(TXT_TITLE, p1_col);
        // Roster rows 3..10, scrolled. Entries past NUM_GAMES stay blank -
        // without that gate a short roster shows the unused NAME defaults as
        // ghost rows the cursor cannot reach.
        4'd3, 4'd4, 4'd5, 4'd6, 4'd7, 4'd8, 4'd9, 4'd10:
               ch = (row_game < NUM_GAMES) ? name_char(row_game[4:0], p1_col)
                                           : 8'h20;
        4'd12: ch = row_char(TXT_HELP, p1_col);
        4'd13: begin
            case (state)
                S_LOAD, S_LOAD2: ch = row_char(TXT_LOADING, p1_col);
                S_ERR:           ch = row_char(TXT_FAILED, p1_col);
                default:         ch = row_char(sd_ready ? TXT_SDOK : TXT_NOSD,
                                               p1_col);
            endcase
        end
        default: ;
    endcase
    // Roster markers: '>' = cursor, '*' = running game. Compared against the
    // SCROLLED index, not the raw row. Suppressed on the INSERT CARD screen -
    // there is no roster there and those rows carry the message.
    if (state != S_NOCARD && p1_row >= ROW_TOP && p1_row <= 4'd10
        && row_game < NUM_GAMES) begin
        if (p1_col == 5'd1  && row_game[4:0] == cursor)  ch = ">";
        if (p1_col == 5'd17 && row_game[4:0] == game_id) ch = "*";
    end
    // Scroll hints in the last column when the list runs off either end.
    if (state != S_NOCARD && p1_col == 5'd22) begin
        if (p1_row == ROW_TOP && scroll != 4'd0)                    ch = "^";
        if (p1_row == 4'd10  && (scroll + VIS_ROWS) < NUM_GAMES)    ch = "V";
    end
end

// ASCII 0x20..0x5F -> font index 0..63
wire [5:0] glyph = {ch[6], ch[4:0]};

reg [7:0] font_rom [0:511];
initial $readmemh("osd_font.hex", font_rom);

reg [7:0] p2_byte;
reg [2:0] p2_ub;
reg       p2_in = 0;
always @(posedge clk) begin
    if (pixel_tick) begin
        p2_byte <= font_rom[{glyph, p1_vb}];
        p2_ub   <= p1_ub;
        p2_in   <= p1_in;
    end
end

wire pix = p2_byte[3'd7 - p2_ub];   // bit 7 = leftmost pixel

// White text on a dark blue box; game video passes through untouched
// everywhere else (and entirely, when the menu is closed).
// On the INSERT CARD screen the core has NO ROMs - its RAM is blank and
// whatever it renders is meaningless - so blank the background to black and
// show only the message. Without this the operator sees the message sitting
// on top of undefined video and cannot tell a missing card from a crash.
assign rgb_out = (osd_active && p2_in) ? (pix ? 9'b111_111_111
                                              : 9'b000_000_010)
                 : osd_nocard          ? 9'b000_000_000
                                       : rgb_in;

endmodule
