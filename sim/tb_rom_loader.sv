// Testbench: rom_loader + sd_reader + card model.
//
// Instance A: valid pack. Three phases:
//   1. boot with an unwritten prefs sector -> falls back to the `slot`
//      input (2); every byte of the 128 KB slot must land on the download
//      bus at the right address, in order, then `done`.
//   2. save_req -> the loader must CMD24 the prefs sector ("MCRPREF1"+slot)
//      while `done` stays high (a save must never reset the running core).
//   3. reset with the slot input changed to 0 -> the loader must boot the
//      SAVED slot 2, proving the power-on-into-owner's-game round trip.
// Instance B: card with no pack (header magic absent) -> must raise `error`
//             rather than hanging, so the product can show a status code
//             instead of a black screen.
module tb_rom_loader;

localparam int CLK_HZ = 40_000_000;
localparam int PACK_BASE = 2048;

logic clk = 0;
logic rst = 1;
always #12500 clk = ~clk;   // 40 MHz

int errors = 0;

// ---------------- instance A: good card ---------------------------------
logic [3:0] a_slot = 4'd2;
logic       a_save_req = 0;
wire        a_ready, a_err, a_rd_start, a_rd_done, a_dv, a_done, a_error;
wire        a_saved;
wire [3:0]  a_cur_slot;
wire [7:0]  a_dout, a_dl_data;
wire [31:0] a_sector;
wire [16:0] a_dl_addr;
wire        a_dl_wr;
wire        a_wr_start, a_wr_next, a_wr_done;
wire [7:0]  a_wr_din;
wire        a_sclk, a_mosi, a_miso, a_cs_n;

sd_reader #(.CLK_HZ(CLK_HZ)) a_sd (
    .clk(clk), .rst(rst), .ready(a_ready), .err(a_err),
    .rd_start(a_rd_start), .rd_sector(a_sector),
    .dout(a_dout), .dout_valid(a_dv), .rd_done(a_rd_done),
    .wr_start(a_wr_start), .wr_din(a_wr_din),
    .wr_next(a_wr_next), .wr_done(a_wr_done), .wr_err(),
    .sclk(a_sclk), .mosi(a_mosi), .miso(a_miso), .cs_n(a_cs_n)
);
sd_card_model #(.HDR_SECTOR(PACK_BASE)) a_card (
    .sclk(a_sclk), .cs_n(a_cs_n), .mosi(a_mosi), .miso(a_miso)
);
rom_loader #(.PACK_BASE(PACK_BASE), .SLOT_SECTORS(256)) a_ldr (
    .clk(clk), .rst(rst), .slot(a_slot),
    .use_prefs(1'b1),
    .save_req(a_save_req), .saved(a_saved), .cur_slot(a_cur_slot),
    .sd_ready(a_ready), .sd_err(a_err),
    .sd_rd_start(a_rd_start), .sd_sector(a_sector),
    .sd_dout(a_dout), .sd_dout_valid(a_dv), .sd_rd_done(a_rd_done),
    .sd_wr_start(a_wr_start), .sd_wr_din(a_wr_din),
    .sd_wr_next(a_wr_next), .sd_wr_done(a_wr_done),
    .dl_addr(a_dl_addr), .dl_data(a_dl_data), .dl_wr(a_dl_wr),
    .done(a_done), .error(a_error)
);

// check every downloaded byte against the model's pattern for exp_slot
int exp_slot = 2;
int unsigned expect_addr = 0;
int unsigned nwritten = 0;
always @(posedge clk) begin
    if (a_dl_wr) begin
        int unsigned sec, off;
        logic [7:0] want;
        if (a_dl_addr !== 17'(expect_addr) && errors < 5) begin
            $display("FAIL: dl_addr %0d, expected %0d", a_dl_addr, expect_addr);
            errors++;
        end
        sec  = PACK_BASE + 1 + exp_slot*256 + (expect_addr / 512);
        off  = expect_addr % 512;
        want = 8'((sec*13 + off) & 32'hFF);
        if (a_dl_data !== want && errors < 5) begin
            $display("FAIL: dl_data at %0d = %02x, expected %02x",
                     expect_addr, a_dl_data, want);
            errors++;
        end
        expect_addr++;
        nwritten++;
    end
end

// done must never drop while a save is in flight
always @(posedge clk) begin
    if (!rst && a_ldr.st == 4'd9 /* L_SAVE */ && !a_done) begin
        $display("FAIL: done dropped during prefs save");
        errors++;
    end
end

// ---------------- instance B: card with no pack -------------------------
wire        b_ready, b_err, b_rd_start, b_rd_done, b_dv, b_done, b_error;
wire [7:0]  b_dout, b_dl_data;
wire [31:0] b_sector;
wire [16:0] b_dl_addr;
wire        b_dl_wr;
wire        b_sclk, b_mosi, b_miso, b_cs_n;

sd_reader #(.CLK_HZ(CLK_HZ)) b_sd (
    .clk(clk), .rst(rst), .ready(b_ready), .err(b_err),
    .rd_start(b_rd_start), .rd_sector(b_sector),
    .dout(b_dout), .dout_valid(b_dv), .rd_done(b_rd_done),
    .sclk(b_sclk), .mosi(b_mosi), .miso(b_miso), .cs_n(b_cs_n)
);
// header sector far away => the loader reads pattern data and sees no magic
sd_card_model #(.HDR_SECTOR(999999)) b_card (
    .sclk(b_sclk), .cs_n(b_cs_n), .mosi(b_mosi), .miso(b_miso)
);
rom_loader #(.PACK_BASE(PACK_BASE), .SLOT_SECTORS(256)) b_ldr (
    .clk(clk), .rst(rst), .slot(4'd0),
    .use_prefs(1'b1),
    .save_req(1'b0), .saved(), .cur_slot(),
    .sd_ready(b_ready), .sd_err(b_err),
    .sd_rd_start(b_rd_start), .sd_sector(b_sector),
    .sd_dout(b_dout), .sd_dout_valid(b_dv), .sd_rd_done(b_rd_done),
    .sd_wr_start(), .sd_wr_din(), .sd_wr_next(1'b0), .sd_wr_done(1'b0),
    .dl_addr(b_dl_addr), .dl_data(b_dl_data), .dl_wr(b_dl_wr),
    .done(b_done), .error(b_error)
);

int t;
initial begin
    repeat (10) @(posedge clk);
    rst = 0;

    // ---- phase 1: boot, prefs sector blank -> falls back to slot 2 ------
    t = 0;
    while (!a_done && !a_error && t < 400_000_000) begin
        @(posedge clk);
        t++;
    end

    if (a_error) begin
        $display("FAIL: good card reported error");
        errors++;
    end else if (!a_done) begin
        $display("FAIL: load timed out (%0d bytes written)", nwritten);
        errors++;
    end else begin
        $display("  loaded %0d bytes in %0d clk (%0d ms), last addr %0d",
                 nwritten, t, t/40000, expect_addr-1);
        if (nwritten != 131072) begin
            $display("FAIL: expected 131072 bytes, got %0d", nwritten);
            errors++;
        end
        if (a_cur_slot !== 4'd2) begin
            $display("FAIL: blank prefs should boot the default slot 2, got %0d",
                     a_cur_slot);
            errors++;
        end
    end

    // ---- phase 2: persist the selection ---------------------------------
    a_save_req = 1;
    @(posedge clk);
    a_save_req = 0;
    t = 0;
    while (!a_saved && t < 40_000_000) begin
        @(posedge clk);
        t++;
    end
    if (!a_saved) begin
        $display("FAIL: prefs save timed out");
        errors++;
    end else
        $display("  prefs saved in %0d clk (%0d us)", t, t/40);

    // ---- phase 3: reboot with a DIFFERENT default; prefs must win -------
    rst = 1;
    a_slot = 4'd0;            // baked default changes; saved slot 2 rules
    expect_addr = 0;
    nwritten = 0;
    repeat (10) @(posedge clk);
    rst = 0;

    t = 0;
    while (!a_done && !a_error && t < 400_000_000) begin
        @(posedge clk);
        t++;
    end
    if (!a_done || a_error) begin
        $display("FAIL: reboot with saved prefs did not complete");
        errors++;
    end else begin
        if (a_cur_slot !== 4'd2) begin
            $display("FAIL: saved prefs ignored - booted slot %0d, wanted 2",
                     a_cur_slot);
            errors++;
        end else
            $display("  reboot loaded the SAVED slot %0d over default %0d (%0d bytes)",
                     a_cur_slot, a_slot, nwritten);
        if (nwritten != 131072) begin
            $display("FAIL: reboot expected 131072 bytes, got %0d", nwritten);
            errors++;
        end
    end

    // instance B should have given up by now
    if (!b_error) begin
        $display("FAIL: card without a pack did not report error (done=%0b)", b_done);
        errors++;
    end else begin
        $display("  no-pack card correctly reported error");
    end

    if (errors == 0) $display("PASS: rom_loader");
    else             $display("FAIL: rom_loader (%0d errors)", errors);
    $finish;
end

endmodule
