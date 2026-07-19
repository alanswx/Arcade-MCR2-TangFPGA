// Byte-level SPI master for the SD card, mode 0 (CPOL=0, CPHA=0):
// MISO is sampled on the rising edge, MOSI changes on the falling edge.
// `div` is the half-period in clk cycles, so the SCLK frequency is
// clk / (2*(div+1)). It is an input so the card can be clocked slowly
// during initialisation (SD spec requires 100-400 kHz) and fast afterwards.
module sd_spi_phy (
    input             clk,
    input             rst,
    input      [15:0] div,        // half-period - 1, in clk cycles
    input             start,      // pulse: begin transferring `tx`
    input      [7:0]  tx,
    output reg [7:0]  rx,
    output reg        busy,
    output reg        done,       // 1-cycle pulse: `rx` is valid
    output reg        sclk,
    output reg        mosi,
    input             miso
);

reg [15:0] cnt;
reg [3:0]  bits;
reg [7:0]  shreg;
reg        phase;   // 0 = waiting to raise sclk, 1 = waiting to lower it

always @(posedge clk) begin
    done <= 1'b0;

    if (rst) begin
        busy  <= 1'b0;
        sclk  <= 1'b0;
        mosi  <= 1'b1;   // idle high
        bits  <= 4'd0;
        cnt   <= 16'd0;
        phase <= 1'b0;
    end else if (!busy) begin
        sclk <= 1'b0;
        if (start) begin
            shreg <= tx;
            mosi  <= tx[7];      // present the MSB before the first rising edge
            bits  <= 4'd8;
            cnt   <= 16'd0;
            phase <= 1'b0;
            busy  <= 1'b1;
        end
    end else begin
        if (cnt != div) begin
            cnt <= cnt + 16'd1;
        end else begin
            cnt <= 16'd0;
            if (!phase) begin
                sclk  <= 1'b1;              // rising edge: card presents, we sample
                rx    <= {rx[6:0], miso};
                phase <= 1'b1;
            end else begin
                sclk  <= 1'b0;              // falling edge: advance our output
                phase <= 1'b0;
                bits  <= bits - 4'd1;
                if (bits == 4'd1) begin
                    busy <= 1'b0;
                    done <= 1'b1;
                    mosi <= 1'b1;
                end else begin
                    shreg <= {shreg[6:0], 1'b0};
                    mosi  <= shreg[6];
                end
            end
        end
    end
end

endmodule
