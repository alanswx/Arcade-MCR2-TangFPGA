// SD card reader/writer (SPI mode): initialises the card, streams out
// 512-byte blocks on request (CMD17), and writes single blocks (CMD24) -
// the latter used for the one prefs sector that persists the selected game.
//
// Init sequence per the SD Physical Layer spec:
//   >=74 clocks with CS high -> CMD0 (idle) -> CMD8 (interface condition)
//   -> ACMD41 until ready -> CMD58 (read OCR, learn block vs byte addressing)
// SDHC/SDXC cards address by block; older SDSC cards address by byte, hence
// the `ccs` shift below. The clock runs at ~250 kHz during init (the spec
// requires 100-400 kHz) and switches to ~10 MHz once the card is up.
module sd_reader #(
    parameter CLK_HZ = 40_000_000
)(
    input             clk,
    input             rst,

    output reg        ready,       // card initialised and idle
    output reg        err,         // init or read failed (latched)

    input             rd_start,    // pulse: read the block at rd_sector
    input      [31:0] rd_sector,
    output reg [7:0]  dout,        // block data, streamed
    output reg        dout_valid,
    output reg        rd_done,     // pulse: 512 bytes delivered

    // Block write (CMD24) - used for the prefs sector. Same address input
    // as reads. A failed/rejected write raises wr_err but still completes
    // with wr_done and returns to READY: a bad write must never take down
    // the reader (the game keeps running; prefs just did not persist).
    input             wr_start,    // pulse: write the block at rd_sector
    input      [7:0]  wr_din,      // byte to send; update after each wr_next
    output reg        wr_next,     // pulse: present the NEXT byte on wr_din
    output reg        wr_done,     // pulse: write finished (check wr_err)
    output reg        wr_err,      // valid with wr_done: card rejected it

    output            sclk,
    output            mosi,
    input             miso,
    output reg        cs_n
);

localparam [15:0] DIV_INIT = 16'(CLK_HZ / 500_000  - 1);   // ~250 kHz
localparam [15:0] DIV_FAST = 16'(CLK_HZ / 20_000_000 - 1); // ~10 MHz

reg  [15:0] div;
reg  [7:0]  tx_byte;
reg         tx_go;
wire [7:0]  rx_byte;
wire        tx_done, tx_busy;

sd_spi_phy phy (
    .clk(clk), .rst(rst), .div(div),
    .start(tx_go), .tx(tx_byte), .rx(rx_byte),
    .busy(tx_busy), .done(tx_done),
    .sclk(sclk), .mosi(mosi), .miso(miso)
);

localparam [3:0]
    S_PWR      = 4'd0,   // 80 clocks with CS high
    S_SEND     = 4'd1,   // shift out the 6 command bytes
    S_R1       = 4'd2,   // poll for the R1 response
    S_EXTRA    = 4'd3,   // read trailing response bytes (R3/R7)
    S_DISPATCH = 4'd4,   // decide the next init step
    S_READY    = 4'd5,
    S_RD_TOKEN = 4'd6,   // poll for the 0xFE data token
    S_RD_DATA  = 4'd7,
    S_RD_CRC   = 4'd8,
    S_GAP      = 4'd9,   // one idle byte between transactions
    S_ERR      = 4'd10,
    S_WR_TOKEN = 4'd11,  // CMD24 accepted -> send the 0xFE data token
    S_WR_DATA  = 4'd12,  // stream 512 bytes from wr_din
    S_WR_RESP  = 4'd13,  // 2 dummy CRC bytes, then poll the data response
    S_WR_BUSY  = 4'd14;  // wait out the card's internal programming

reg [3:0]  st, st_after;
reg [47:0] cmd_sr;       // command being shifted out, MSB first
reg [2:0]  cmd_cnt;
reg [7:0]  r1;
reg [31:0] extra;        // OCR / interface condition payload
reg [2:0]  extra_cnt;
reg [15:0] poll;         // response / busy poll counter
reg [15:0] acmd_tries;
reg [9:0]  byte_cnt;
reg [2:0]  init_step;
reg        ccs;          // 1 = block addressing (SDHC/SDXC)
reg        rd_pending;   // rd_start is a pulse and the FSM only advances
                         // between SPI bytes, so latch the request
reg        wr_pending;
reg [19:0] busy_cnt;     // write-busy can last many ms; 2^20 bytes ~ 0.8 s cap
reg [31:0] sector_q;

localparam [15:0] POLL_MAX = 16'd1000;
localparam [15:0] ACMD_MAX = 16'd20000;

task issue(input [5:0] cmd, input [31:0] arg, input [7:0] crc, input [3:0] nxt,
           input [2:0] nextra);
begin
    cmd_sr    <= {2'b01, cmd, arg, crc};
    cmd_cnt   <= 3'd6;
    extra_cnt <= nextra;
    st_after  <= nxt;
    st        <= S_SEND;
end
endtask

always @(posedge clk) begin
    tx_go      <= 1'b0;
    dout_valid <= 1'b0;
    rd_done    <= 1'b0;
    wr_next    <= 1'b0;
    wr_done    <= 1'b0;

    if (rst) begin
        st         <= S_PWR;
        div        <= DIV_INIT;
        cs_n       <= 1'b1;
        ready      <= 1'b0;
        err        <= 1'b0;
        poll       <= 16'd0;
        byte_cnt   <= 10'd0;
        init_step  <= 3'd0;
        ccs        <= 1'b0;
        rd_pending <= 1'b0;
        wr_pending <= 1'b0;
        wr_err     <= 1'b0;
        acmd_tries <= 16'd0;
    end else begin
      if (rd_start) rd_pending <= 1'b1;
      if (wr_start) wr_pending <= 1'b1;
      if (!tx_busy && !tx_go) begin
        case (st)

        // ---- 80 clocks with CS high so the card enters SPI mode ----------
        S_PWR: begin
            if (poll == 16'd10) begin
                poll <= 16'd0;
                cs_n <= 1'b0;
                issue(6'd0, 32'd0, 8'h95, S_DISPATCH, 3'd0);   // CMD0
                init_step <= 3'd0;
            end else begin
                tx_byte <= 8'hFF;
                tx_go   <= 1'b1;
                poll    <= poll + 16'd1;
            end
        end

        // ---- shift out the 6 command bytes -------------------------------
        S_SEND: begin
            tx_byte <= cmd_sr[47:40];
            tx_go   <= 1'b1;
            cmd_sr  <= {cmd_sr[39:0], 8'hFF};
            cmd_cnt <= cmd_cnt - 3'd1;
            if (cmd_cnt == 3'd1) begin
                st   <= S_R1;
                poll <= 16'd0;
            end
        end

        // ---- poll for R1 (first byte with MSB clear) ---------------------
        S_R1: begin
            tx_byte <= 8'hFF;
            tx_go   <= 1'b1;
            poll    <= poll + 16'd1;
            if (poll != 16'd0 && !rx_byte[7]) begin
                r1 <= rx_byte;
                if (extra_cnt != 3'd0) begin
                    extra_cnt <= extra_cnt;
                    st        <= S_EXTRA;
                end else begin
                    st <= st_after;
                end
                poll <= 16'd0;
            end else if (poll > POLL_MAX) begin
                st <= S_ERR;
            end
        end

        // ---- trailing bytes of an R3/R7 response -------------------------
        S_EXTRA: begin
            tx_byte   <= 8'hFF;
            tx_go     <= 1'b1;
            extra     <= {extra[23:0], rx_byte};
            extra_cnt <= extra_cnt - 3'd1;
            if (extra_cnt == 3'd1) st <= st_after;
        end

        // ---- init sequencer ----------------------------------------------
        S_DISPATCH: begin
            case (init_step)
            3'd0: begin  // after CMD0
                if (r1 != 8'h01) st <= S_ERR;
                else begin
                    init_step <= 3'd1;
                    issue(6'd8, 32'h0000_01AA, 8'h87, S_DISPATCH, 3'd4); // CMD8
                end
            end
            3'd1: begin  // after CMD8 (illegal-command => v1 card, still fine)
                init_step  <= 3'd2;
                acmd_tries <= 16'd0;
                issue(6'd55, 32'd0, 8'hFF, S_DISPATCH, 3'd0);            // CMD55
            end
            3'd2: begin  // after CMD55 -> send ACMD41
                init_step <= 3'd3;
                issue(6'd41, 32'h4000_0000, 8'hFF, S_DISPATCH, 3'd0);    // ACMD41, HCS
            end
            3'd3: begin  // after ACMD41
                if (r1 == 8'h00) begin
                    init_step <= 3'd4;
                    issue(6'd58, 32'd0, 8'hFF, S_DISPATCH, 3'd4);        // CMD58
                end else if (acmd_tries > ACMD_MAX) begin
                    st <= S_ERR;
                end else begin
                    acmd_tries <= acmd_tries + 16'd1;
                    init_step  <= 3'd2;
                    issue(6'd55, 32'd0, 8'hFF, S_DISPATCH, 3'd0);
                end
            end
            3'd4: begin  // after CMD58: OCR bit30 = CCS
                ccs       <= extra[30];
                div       <= DIV_FAST;
                ready     <= 1'b1;
                init_step <= 3'd5;
                cs_n      <= 1'b1;
                st        <= S_GAP;
                st_after  <= S_READY;
            end
            default: st <= S_READY;
            endcase
        end

        // ---- idle --------------------------------------------------------
        S_READY: begin
            if (rd_pending) begin
                rd_pending <= 1'b0;
                sector_q   <= rd_sector;
                ready      <= 1'b0;
                cs_n       <= 1'b0;
                // CMD17: block address for SDHC, byte address for SDSC
                issue(6'd17, ccs ? rd_sector : (rd_sector << 9), 8'hFF,
                      S_RD_TOKEN, 3'd0);
                poll <= 16'd0;
            end else if (wr_pending) begin
                wr_pending <= 1'b0;
                wr_err     <= 1'b0;
                sector_q   <= rd_sector;
                ready      <= 1'b0;
                cs_n       <= 1'b0;
                // CMD24: same block/byte addressing rule as CMD17
                issue(6'd24, ccs ? rd_sector : (rd_sector << 9), 8'hFF,
                      S_WR_TOKEN, 3'd0);
                poll <= 16'd0;
            end
        end

        // ---- wait for the data token, then stream the block --------------
        S_RD_TOKEN: begin
            if (r1 != 8'h00) begin
                st <= S_ERR;
            end else begin
                tx_byte <= 8'hFF;
                tx_go   <= 1'b1;
                poll    <= poll + 16'd1;
                if (poll != 16'd0 && rx_byte == 8'hFE) begin
                    st       <= S_RD_DATA;
                    byte_cnt <= 10'd0;
                end else if (poll > POLL_MAX) begin
                    st <= S_ERR;
                end
            end
        end

        // The transfer issued when the token was seen has already completed,
        // so rx_byte holds data byte 0 on the first pass here. Each pass
        // emits the byte just received and launches the next transfer; the
        // 512th launch fetches the first CRC byte.
        S_RD_DATA: begin
            tx_byte    <= 8'hFF;
            tx_go      <= 1'b1;
            dout       <= rx_byte;
            dout_valid <= 1'b1;
            byte_cnt   <= byte_cnt + 10'd1;
            if (byte_cnt == 10'd511) begin
                st       <= S_RD_CRC;
                byte_cnt <= 10'd0;
            end
        end

        // Two CRC bytes, neither of them checked: the first is already in
        // rx_byte, so only one more transfer is needed.
        S_RD_CRC: begin
            if (byte_cnt == 10'd0) begin
                tx_byte  <= 8'hFF;
                tx_go    <= 1'b1;
                byte_cnt <= 10'd1;
            end else begin
                cs_n     <= 1'b1;
                st       <= S_GAP;
                st_after <= S_READY;
                rd_done  <= 1'b1;
                ready    <= 1'b1;
            end
        end

        // ---- write path: token + 512 bytes + CRC + response + busy -------
        // R1 was captured by S_R1; a non-zero R1 means the card refused the
        // command - flag it and fall through the busy wait so the bus is
        // left clean either way.
        S_WR_TOKEN: begin
            if (r1 != 8'h00) begin
                wr_err   <= 1'b1;
                busy_cnt <= 20'd0;
                st       <= S_WR_BUSY;
            end else begin
                tx_byte  <= 8'hFE;      // single-block data token
                tx_go    <= 1'b1;
                wr_next  <= 1'b1;       // request byte 0
                byte_cnt <= 10'd0;
                st       <= S_WR_DATA;
            end
        end

        // Each pass sends the byte the requester presented and asks for the
        // next one; SPI is slow enough (~40 clk/byte) that the one-cycle
        // wr_next -> wr_din latency never races the shifter.
        S_WR_DATA: begin
            tx_byte  <= wr_din;
            tx_go    <= 1'b1;
            byte_cnt <= byte_cnt + 10'd1;
            if (byte_cnt == 10'd511) begin
                byte_cnt <= 10'd0;
                poll     <= 16'd0;
                st       <= S_WR_RESP;
            end else begin
                wr_next <= 1'b1;
            end
        end

        // Two dummy CRC bytes (CRC is off in SPI mode), then poll for the
        // data-response token xxx0sss1; sss = 010 means accepted.
        S_WR_RESP: begin
            tx_byte <= 8'hFF;
            tx_go   <= 1'b1;
            if (byte_cnt < 10'd2) begin
                byte_cnt <= byte_cnt + 10'd1;
            end else begin
                poll <= poll + 16'd1;
                if (!rx_byte[4] && rx_byte[0]) begin
                    if (rx_byte[3:1] != 3'b010) wr_err <= 1'b1;
                    busy_cnt <= 20'd0;
                    st       <= S_WR_BUSY;
                end else if (poll > POLL_MAX) begin
                    wr_err   <= 1'b1;
                    busy_cnt <= 20'd0;
                    st       <= S_WR_BUSY;
                end
            end
        end

        // The card holds DO low while programming (can be many ms). Wait it
        // out - or give up after ~0.8 s - then hand the bus back.
        S_WR_BUSY: begin
            tx_byte  <= 8'hFF;
            tx_go    <= 1'b1;
            busy_cnt <= busy_cnt + 20'd1;
            if ((busy_cnt != 20'd0 && rx_byte == 8'hFF) || (&busy_cnt)) begin
                if (&busy_cnt) wr_err <= 1'b1;
                cs_n     <= 1'b1;
                st       <= S_GAP;
                st_after <= S_READY;
                wr_done  <= 1'b1;
                ready    <= 1'b1;
            end
        end

        // ---- one idle byte with CS high between transactions -------------
        S_GAP: begin
            tx_byte <= 8'hFF;
            tx_go   <= 1'b1;
            st      <= st_after;
        end

        S_ERR: begin
            err   <= 1'b1;
            ready <= 1'b0;
            cs_n  <= 1'b1;
        end

        default: st <= S_ERR;
        endcase
      end
    end
end

endmodule
