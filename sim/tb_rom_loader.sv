// Testbench: rom_loader + sd_reader + card model.
//
// Instance A: valid pack -> every byte of a 128 KB slot must land on the
//             download bus at the right address, in order, then `done`.
// Instance B: card with no pack (header magic absent) -> must raise `error`
//             rather than hanging, so the product can show a status code
//             instead of a black screen.
module tb_rom_loader;

localparam int CLK_HZ = 40_000_000;
localparam int SLOT   = 0;
localparam int PACK_BASE = 2048;

logic clk = 0;
logic rst = 1;
always #12500 clk = ~clk;   // 40 MHz

int errors = 0;

// ---------------- instance A: good card ---------------------------------
wire        a_ready, a_err, a_rd_start, a_rd_done, a_dv, a_done, a_error;
wire [7:0]  a_dout, a_dl_data;
wire [31:0] a_sector;
wire [16:0] a_dl_addr;
wire        a_dl_wr;
wire        a_sclk, a_mosi, a_miso, a_cs_n;

sd_reader #(.CLK_HZ(CLK_HZ)) a_sd (
    .clk(clk), .rst(rst), .ready(a_ready), .err(a_err),
    .rd_start(a_rd_start), .rd_sector(a_sector),
    .dout(a_dout), .dout_valid(a_dv), .rd_done(a_rd_done),
    .sclk(a_sclk), .mosi(a_mosi), .miso(a_miso), .cs_n(a_cs_n)
);
sd_card_model #(.HDR_SECTOR(PACK_BASE)) a_card (
    .sclk(a_sclk), .cs_n(a_cs_n), .mosi(a_mosi), .miso(a_miso)
);
rom_loader #(.PACK_BASE(PACK_BASE), .SLOT_SECTORS(256)) a_ldr (
    .clk(clk), .rst(rst), .slot(SLOT[3:0]),
    .sd_ready(a_ready), .sd_err(a_err),
    .sd_rd_start(a_rd_start), .sd_sector(a_sector),
    .sd_dout(a_dout), .sd_dout_valid(a_dv), .sd_rd_done(a_rd_done),
    .dl_addr(a_dl_addr), .dl_data(a_dl_data), .dl_wr(a_dl_wr),
    .done(a_done), .error(a_error)
);

// check every downloaded byte against the model's pattern
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
        sec  = PACK_BASE + 1 + SLOT*256 + (expect_addr / 512);
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
    .sd_ready(b_ready), .sd_err(b_err),
    .sd_rd_start(b_rd_start), .sd_sector(b_sector),
    .sd_dout(b_dout), .sd_dout_valid(b_dv), .sd_rd_done(b_rd_done),
    .dl_addr(b_dl_addr), .dl_data(b_dl_data), .dl_wr(b_dl_wr),
    .done(b_done), .error(b_error)
);

int t;
initial begin
    repeat (10) @(posedge clk);
    rst = 0;

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
