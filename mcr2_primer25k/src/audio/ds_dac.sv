// 1st-order Delta-Sigma DAC (Pulse Density Modulator)
module ds_dac (
    input             clk,
    input             resetn,
    input      [15:0] din,      // 16-bit unsigned input audio sample
    output reg        dout      // 1-bit PWM output
);

reg [16:0] accumulator;

always @(posedge clk or negedge resetn) begin
    if (!resetn) begin
        accumulator <= 17'd0;
        dout        <= 1'b0;
    end else begin
        // Accumulate and output the carry-out (overflow) bit
        accumulator <= accumulator[15:0] + din;
        dout        <= accumulator[16];
    end
end

endmodule
