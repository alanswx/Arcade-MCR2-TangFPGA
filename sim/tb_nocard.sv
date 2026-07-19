// The bench case: no SD card inserted at all. MISO idles high (the pin has a
// pull-up), so the card never answers. rom_loader MUST give up and raise
// `error` - the 60K top holds the game core in reset until done|error, so a
// hang here means a permanently black screen.
module tb_nocard;
localparam int CLK_HZ = 40_000_000;
logic clk = 0, rst = 1;
always #12500 clk = ~clk;

wire ready, err, rd_start, rd_done, dv, done, error;
wire [7:0] dout, dl_data;
wire [31:0] sector;
wire [16:0] dl_addr;
wire dl_wr, sclk, mosi, cs_n;

sd_reader #(.CLK_HZ(CLK_HZ)) sd (
    .clk(clk), .rst(rst), .ready(ready), .err(err),
    .rd_start(rd_start), .rd_sector(sector),
    .dout(dout), .dout_valid(dv), .rd_done(rd_done),
    .sclk(sclk), .mosi(mosi), .miso(1'b1), .cs_n(cs_n)   // <-- no card
);
rom_loader #(.PACK_BASE(32'd2048), .SLOT_SECTORS(256)) ldr (
    .clk(clk), .rst(rst), .slot(4'd0),
    .sd_ready(ready), .sd_err(err),
    .sd_rd_start(rd_start), .sd_sector(sector),
    .sd_dout(dout), .sd_dout_valid(dv), .sd_rd_done(rd_done),
    .dl_addr(dl_addr), .dl_data(dl_data), .dl_wr(dl_wr),
    .done(done), .error(error)
);

int t;
initial begin
    repeat (10) @(posedge clk); rst = 0;
    t = 0;
    while (!done && !error && t < 200_000_000) begin @(posedge clk); t++; end
    if (error)      $display("PASS: gave up after %0d clk (%0d ms) - core would start", t, t/40000);
    else if (done)  $display("FAIL: reported success with no card present");
    else            $display("FAIL: HUNG with no card - core stays in reset, screen stays black");
    $finish;
end
endmodule
