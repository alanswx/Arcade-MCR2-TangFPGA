// Testbench: sd_reader against the behavioural card model.
// Verifies that the card initialises and that two different sectors read
// back with the expected pattern.  Run with:  make -C sim sd
module tb_sd_reader;

localparam int CLK_HZ = 40_000_000;

logic clk = 0;
logic rst = 1;
always #12500 clk = ~clk;      // 40 MHz (12.5 ns half period, in ps units)

logic        ready, err, rd_start, rd_done, dout_valid;
logic [7:0]  dout;
logic [31:0] rd_sector;
wire         sclk, mosi, miso, cs_n;

sd_reader #(.CLK_HZ(CLK_HZ)) dut (
    .clk(clk), .rst(rst),
    .ready(ready), .err(err),
    .rd_start(rd_start), .rd_sector(rd_sector),
    .dout(dout), .dout_valid(dout_valid), .rd_done(rd_done),
    .sclk(sclk), .mosi(mosi), .miso(miso), .cs_n(cs_n)
);

sd_card_model card (.sclk(sclk), .cs_n(cs_n), .mosi(mosi), .miso(miso));

// collect the streamed bytes
logic [7:0] got [512];
int         ngot = 0;
int         errors = 0;

always @(posedge clk) begin
    if (dout_valid) begin
        if (ngot < 512) got[ngot] = dout;
        ngot++;
    end
end

task automatic read_sector(input int unsigned sec);
    int timeout;
    begin
        ngot = 0;
        rd_sector = sec;
        @(posedge clk); rd_start = 1;
        @(posedge clk); rd_start = 0;

        timeout = 0;
        while (!rd_done && timeout < 20_000_000) begin
            @(posedge clk);
            timeout++;
        end
        if (!rd_done) begin
            $display("FAIL: sector %0d timed out", sec);
            errors++;
        end else if (ngot != 512) begin
            $display("FAIL: sector %0d returned %0d bytes, expected 512", sec, ngot);
            errors++;
        end else begin
            for (int i = 0; i < 512; i++) begin
                logic [7:0] want = 8'((sec*13 + i) & 32'hFF);
                if (got[i] !== want) begin
                    $display("FAIL: sector %0d byte %0d = %02x, expected %02x",
                             sec, i, got[i], want);
                    errors++;
                    break;
                end
            end
            if (errors == 0)
                $display("  sector %0d: 512 bytes OK (first=%02x last=%02x)",
                         sec, got[0], got[511]);
        end
    end
endtask

int t;
initial begin
    rd_start = 0;
    rd_sector = 0;
    repeat (10) @(posedge clk);
    rst = 0;

    // wait for init
    t = 0;
    while (!ready && !err && t < 50_000_000) begin
        @(posedge clk);
        t++;
    end

    if (err) begin
        $display("FAIL: card init reported an error");
        errors++;
    end else if (!ready) begin
        $display("FAIL: card init timed out after %0d cycles", t);
        errors++;
    end else begin
        $display("  init OK after %0d clk cycles (%0d us)", t, t/40);
        read_sector(5);
        read_sector(6);
    end

    if (errors == 0) $display("PASS: sd_reader");
    else             $display("FAIL: sd_reader (%0d errors)", errors);
    $finish;
end

endmodule
