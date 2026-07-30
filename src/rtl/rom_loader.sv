// Loads a game's ROM image from SD into the core's memories at boot.
//
// Card layout (written by tools/make_rompack.py, raw sectors - no filesystem):
//   sector PACK_BASE-1          prefs: "MCRPREF1" + last-selected slot,
//                               written by THIS module on save_req so the
//                               cabinet boots back into the owner's game.
//                               Deliberately outside the pack image, so
//                               rewriting the pack keeps the preference.
//   sector PACK_BASE            header: "MCRPACK1" + slot count
//   sector PACK_BASE+1 + N*256  slot N payload, 128 KB
//
// Payload layout == the core's download address map:
//   0x00000-0x0FFFF  CPU program ROM   (64 KB)
//   0x10000-0x13FFF  sound CPU ROM     (16 KB)
//   0x14000-0x1BFFF  sprite gfx2       (32 KB)
//   0x1C000-0x1DFFF  background gfx1_1 ( 8 KB)
//   0x1E000-0x1FFFF  background gfx1_2 ( 8 KB)
//
// The core must be held in reset until `done` rises. `error` means the card
// is missing/unreadable or holds no valid pack - the caller should surface
// that (status LED / test pattern) rather than sit on a black screen.
module rom_loader #(
    parameter [31:0] PACK_BASE   = 32'd2048,   // first sector of the pack
    parameter int    SLOT_SECTORS = 256,       // 128 KB per slot
    // Transient-failure retries. Each attempt can cost up to the watchdog
    // (~3.4 s), and a card-less board only boots off baked BSRAM ROMs once
    // `error` asserts - so the default stays low to keep that path fast.
    // Boards that must have the card (MCR-3: sprites live there) raise it.
    parameter [2:0]  MAX_RETRY   = 3'd3,
    // Which family's entries this core loads from a v2 pack
    // (0=mcr1, 1=mcr2, 2=mcr3)
    // Default family for single-core boards. The MERGED top drives `family`
    // instead, because which family to load is a runtime choice there.
    parameter [7:0]  FAMILY      = 8'd1,
    // Download-address width. 18 bits (256 KB) covers every family up to
    // MCR-3; MCR3Scroll's payload runs to 0x48000 (288 KB) because its char
    // plane and the Cheap Squeak Deluxe 68000 ROM sit above the 128 KB sprite
    // blob, so the merged 3-family top passes 19. Keep it a parameter so the
    // existing single-family boards are bit-for-bit unaffected.
    parameter int    DL_AW       = 18
)(
    input             clk,
    input             rst,
    input      [3:0]  slot,          // default slot (the baked-in game)
    // Which family's pack entry to load. Single-core boards tie this to the
    // FAMILY parameter; the merged top drives it from the OSD selection, so
    // one bitstream can load MCR-2 and MCR-3 games from the same card.
    input      [7:0]  family,
    input             use_prefs,     // boot path: consult the prefs sector;
                                     // low when the OSD demands `slot` verbatim
    input             save_req,      // pulse: persist cur_slot to the card
    output reg        saved,         // pulse: save attempt finished
    output reg [3:0]  cur_slot,      // slot actually loaded (valid with done)

    // Which CORE (family) the cabinet was last running, from prefs byte 9.
    // Only meaningful with pref_core_valid high: that means the prefs sector
    // carried a good "MCRPREF1" magic, so byte 9 is a real family id rather
    // than a blank/garbage sector. Read on the boot path only (use_prefs);
    // an OSD-commanded reload leaves both untouched. The top uses this to
    // decide whether it is the right core for this cabinet and, if not, to
    // hand off to the next one (multiboot chain - roadmap items 4/5).
    output reg [7:0]  pref_core,
    output reg        pref_core_valid,

    // sd_reader interface
    input             sd_ready,
    input             sd_err,
    // Pulsed high to force a full sd_reader re-init between retries. The
    // reader latches `err`, so restarting only this FSM cannot clear a
    // transient failure - the reader has to be reset too. Wire this into
    // the sd_reader's rst (OR'd with the board reset) in the top.
    output reg        sd_rst,
    output reg        sd_rd_start,
    output reg [31:0] sd_sector,
    input      [7:0]  sd_dout,
    input             sd_dout_valid,
    input             sd_rd_done,

    // sd_reader block-write channel (prefs sector only)
    output reg        sd_wr_start,
    output reg [7:0]  sd_wr_din,
    input             sd_wr_next,
    input             sd_wr_done,

    // ROM download bus (see map above)
    output reg [DL_AW-1:0] dl_addr,   // v2 payloads: 18 bits = 256 KB
    output reg        v2_mode,   // 1 = MCRPACK2 pack detected
    output reg [7:0]  dl_data,
    output reg        dl_wr,

    output reg        done,
    output reg        error
);

localparam [3:0]
    L_WAIT    = 4'd0,   // wait for the card to come up
    L_HDR     = 4'd1,   // read and check the pack header
    L_HDRCHK  = 4'd2,
    L_DATA    = 4'd3,   // stream the slot payload
    L_NEXT    = 4'd4,
    L_DONE    = 4'd5,
    L_ERR     = 4'd6,
    L_PREF    = 4'd7,   // read the prefs sector (boot only)
    L_PREFCHK = 4'd8,
    L_SAVE    = 4'd9,   // write the prefs sector (core keeps running)
    L_RETRY   = 4'd10;  // transient failure: reset the card and try again

// "MCRPACK1" / "MCRPREF1"
localparam [63:0] MAGIC      = 64'h4D_43_52_50_41_43_4B_31;
localparam [63:0] MAGIC_V2   = 64'h4D_43_52_50_41_43_4B_32;   // "MCRPACK2"
localparam [63:0] MAGIC_PREF = 64'h4D_43_52_50_52_45_46_31;

reg [3:0]  st;
reg [26:0] watchdog;     // hard upper bound on the whole load (~1.7s @40MHz)
reg [63:0] hdr;
reg [7:0]  slot_cnt;     // header byte 8: number of slots in the pack
reg [7:0]  pref_slot;    // prefs sector byte 8: last-selected slot
                         // (pref_core / pref_core_valid are output ports)
reg [8:0]  hdr_cnt;
reg [15:0] sect_left_hi;   // sectors remaining in this slot (0..256)
// v2 superblock parsing (within the single header-sector stream)
reg        is_v2;
reg [3:0]  ent_b;
reg [7:0]  ent_fam, ent_typ, ent_slot;
reg [31:0] ent_lba, ent_cnt;
reg        v2_found;
reg [31:0] v2_lba;
reg [15:0] v2_cnt;
reg [31:0] sector;
reg [DL_AW-1:0] addr;
reg        save_pend;
reg [9:0]  save_idx;
reg [2:0]  retry_cnt;    // transient failures so far
reg [21:0] retry_wait;   // ~0.1 s @40MHz settling delay between attempts

// Content of the prefs sector: 8-byte magic, the slot, zeros to 512.
function [7:0] pref_byte(input [9:0] i);
    case (i)
    10'd0:   pref_byte = 8'h4D;   // M
    10'd1:   pref_byte = 8'h43;   // C
    10'd2:   pref_byte = 8'h52;   // R
    10'd3:   pref_byte = 8'h50;   // P
    10'd4:   pref_byte = 8'h52;   // R
    10'd5:   pref_byte = 8'h45;   // E
    10'd6:   pref_byte = 8'h46;   // F
    10'd7:   pref_byte = 8'h31;   // 1
    10'd8:   pref_byte = {4'd0, cur_slot};
    10'd9:   pref_byte = family;      // roadmap item 5: which CORE was
                                      // running when the pref was saved.
                                      // Multiboot (item 4) will read this
                                      // at boot and jump to that core's
                                      // flash slot; until then it is
                                      // recorded but unused.
    default: pref_byte = 8'h00;
    endcase
endfunction

always @(posedge clk) begin
    sd_rd_start <= 1'b0;
    sd_wr_start <= 1'b0;
    dl_wr       <= 1'b0;
    saved       <= 1'b0;
    sd_rst      <= 1'b0;

    if (rst) begin
        st         <= L_WAIT;
        done       <= 1'b0;
        error      <= 1'b0;
        addr       <= '0;
        hdr_cnt    <= 9'd0;
        is_v2      <= 1'b0;
        v2_mode    <= 1'b0;
        v2_found   <= 1'b0;
        hdr        <= 64'd0;
        watchdog   <= 27'd0;
        save_pend  <= 1'b0;
        cur_slot   <= slot;
        retry_cnt  <= 3'd0;
        retry_wait <= 22'd0;
        pref_core       <= 8'd0;
        pref_core_valid <= 1'b0;
    end else begin
        if (save_req) save_pend <= 1'b1;

        // Nothing here may hang: a card that answers but then stops mid
        // transfer would otherwise leave the game core in reset forever.
        // A hung SAVE merely returns to DONE - the game is already running
        // and must not be reset over a failed prefs write.
        // L_RETRY is excluded: its settling delay must not trip the watchdog.
        if (st != L_DONE && st != L_ERR && st != L_RETRY) begin
            watchdog <= watchdog + 27'd1;
            if (watchdog == 27'h7FF_FFFF)
                st <= (st == L_SAVE) ? L_DONE : L_RETRY;
        end

        case (st)

        L_WAIT: begin
            if (sd_err) st <= L_RETRY;
            else if (sd_ready) begin
                cur_slot    <= slot;
                hdr_cnt     <= 9'd0;
                sd_rd_start <= 1'b1;
                if (use_prefs) begin
                    sd_sector <= PACK_BASE - 32'd1;
                    st        <= L_PREF;
                end else begin
                    sd_sector <= PACK_BASE;
                    st        <= L_HDR;
                end
            end
        end

        // capture the prefs sector's magic + slot byte
        L_PREF: begin
            if (sd_err) st <= L_RETRY;
            else begin
                if (sd_dout_valid) begin
                    if (hdr_cnt < 9'd8) hdr <= {hdr[55:0], sd_dout};
                    if (hdr_cnt == 9'd8) pref_slot <= sd_dout;
                    if (hdr_cnt == 9'd9) pref_core <= sd_dout;   // saved core id
                    hdr_cnt <= hdr_cnt + 9'd1;
                end
                if (sd_rd_done) st <= L_PREFCHK;
            end
        end

        // A valid preference overrides the baked-in default; anything else
        // (blank sector, garbage) silently falls through to `slot`.
        L_PREFCHK: begin
            if (hdr == MAGIC_PREF) begin
                if (pref_slot[7:4] == 4'd0) cur_slot <= pref_slot[3:0];
                pref_core_valid <= 1'b1;   // byte 9 is a real family id
            end
            hdr_cnt     <= 9'd0;
            sd_sector   <= PACK_BASE;
            sd_rd_start <= 1'b1;
            st          <= L_HDR;
        end

        // capture the first 8 bytes of the header sector
        L_HDR: begin
            if (sd_err) st <= L_RETRY;
            else begin
                if (sd_dout_valid) begin
                    if (hdr_cnt < 9'd8) hdr <= {hdr[55:0], sd_dout};
                    if (hdr_cnt == 9'd7) is_v2 <= ({hdr[47:0], sd_dout} == MAGIC_V2[55:0]);
                    if (hdr_cnt == 9'd8) slot_cnt <= sd_dout;   // v1 slot count / v2 entry count
                    // v2: 16-byte mini-entries from byte 16 onward
                    if (hdr_cnt >= 9'd16) begin
                        ent_b <= ent_b + 4'd1;   // wraps 0..15 per entry
                        case (ent_b)
                        4'd0:  ent_fam  <= sd_dout;
                        4'd1:  ent_typ  <= sd_dout;
                        4'd2:  ent_slot <= sd_dout;
                        4'd4:  ent_lba[7:0]    <= sd_dout;
                        4'd5:  ent_lba[15:8]   <= sd_dout;
                        4'd6:  ent_lba[23:16]  <= sd_dout;
                        4'd7:  ent_lba[31:24]  <= sd_dout;
                        4'd8:  ent_cnt[7:0]    <= sd_dout;
                        4'd9:  ent_cnt[15:8]   <= sd_dout;
                        4'd10: ent_cnt[23:16]  <= sd_dout;
                        4'd11: ent_cnt[31:24]  <= sd_dout;
                        4'd15: if (!v2_found && ent_fam == family && ent_typ == 8'd0
                                   && ent_slot == {4'd0, cur_slot}) begin
                                   v2_found <= 1'b1;
                                   v2_lba   <= ent_lba;
                                   v2_cnt   <= ent_cnt[15:0];
                               end
                        default: ;
                        endcase
                    end else ent_b <= 4'd0;
                    hdr_cnt <= hdr_cnt + 9'd1;
                end
                if (sd_rd_done) st <= L_HDRCHK;
            end
        end

        L_HDRCHK: begin
            if (is_v2 && hdr == MAGIC_V2) begin
                v2_mode <= 1'b1;
                if (!v2_found) st <= L_ERR;   // no entry for (family, slot)
                else begin
                    sector       <= v2_lba;
                    sect_left_hi <= v2_cnt;
                    addr         <= '0;
                    st           <= L_NEXT;
                end
            end else if (hdr != MAGIC) begin
                st <= L_ERR;            // blank or foreign card
            end else if ({4'd0, cur_slot} >= slot_cnt) begin
                st <= L_ERR;            // pack has no such slot - loading it
                                        // would stream zeros over the ROMs
            end else begin
                v2_mode      <= 1'b0;
                sector       <= PACK_BASE + 32'd1 + (cur_slot * SLOT_SECTORS);
                sect_left_hi <= 16'(SLOT_SECTORS);
                addr         <= '0;
                st           <= L_NEXT;
            end
        end

        // request the next sector of the payload
        L_NEXT: begin
            if (sect_left_hi == 16'd0) begin
                st   <= L_DONE;
                done <= 1'b1;
            end else begin
                sd_sector   <= sector;
                sd_rd_start <= 1'b1;
                st          <= L_DATA;
            end
        end

        // stream its bytes onto the download bus
        L_DATA: begin
            if (sd_err) st <= L_RETRY;
            else begin
                if (sd_dout_valid) begin
                    dl_addr <= addr;
                    dl_data <= sd_dout;
                    dl_wr   <= 1'b1;
                    addr    <= addr + 1'b1;
                end
                if (sd_rd_done) begin
                    sector       <= sector + 32'd1;
                    sect_left_hi <= sect_left_hi - 16'd1;
                    st           <= L_NEXT;
                end
            end
        end

        // Idle with the game running. done stays HIGH through a save -
        // dropping it would reset the core mid-game.
        L_DONE: begin
            if (save_pend) begin
                save_pend   <= 1'b0;
                sd_sector   <= PACK_BASE - 32'd1;
                sd_wr_start <= 1'b1;
                save_idx    <= 10'd0;
                watchdog    <= 27'd0;
                st          <= L_SAVE;
            end
        end

        L_SAVE: begin
            if (sd_wr_next) begin
                sd_wr_din <= pref_byte(save_idx);
                save_idx  <= save_idx + 10'd1;
            end
            if (sd_wr_done) begin
                saved <= 1'b1;
                st    <= L_DONE;
            end
        end

        // Transient failure (card not answering, or a load that stalled).
        // JTAG reconfiguration leaves the card mid-command, so the FIRST
        // attempt after a reflash routinely fails; before this state that
        // latched `error` forever, `rom_ready` released the core anyway, and
        // the sprite SDRAM was simply never loaded - which is what made
        // Tapper need the "OSD in/out + A" dance to start (that path resets
        // this FSM via osd_restart, i.e. it WAS the only retry mechanism).
        //
        // Pulse sd_rst so the reader re-runs its init (it latches `err`, so
        // restarting this FSM alone cannot clear the failure), wait for the
        // card to settle, then start over. After MAX_RETRY attempts give up
        // and assert `error` - the caller relies on that to boot a card-less
        // board off its baked-in BSRAM ROMs.
        L_RETRY: begin
            if (retry_wait == 22'd0) begin
                sd_rst <= 1'b1;              // one-cycle reader reset pulse
                if (retry_cnt == MAX_RETRY) st <= L_ERR;
            end
            retry_wait <= retry_wait + 22'd1;
            if (&retry_wait) begin           // ~0.1 s settle, then retry
                retry_wait <= 22'd0;
                retry_cnt  <= retry_cnt + 3'd1;
                watchdog   <= 27'd0;
                hdr_cnt    <= 9'd0;
                hdr        <= 64'd0;
                addr       <= '0;
                is_v2      <= 1'b0;
                v2_found   <= 1'b0;
                st         <= L_WAIT;
            end
        end

        L_ERR: begin
            error <= 1'b1;
            done  <= 1'b0;
        end

        default: st <= L_ERR;
        endcase
    end
end

endmodule
