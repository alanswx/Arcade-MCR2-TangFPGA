//-----------------------------------------------------------------------------
// sine_gen - clean test tone for measuring HDMI audio dropouts
//-----------------------------------------------------------------------------
// A steady sine is the right probe for this: capture the HDMI audio back
// through the capture card and ANY dropout shows up objectively -
//   * a sample-rate/ACR mismatch  -> slow phase drift or periodic clicks
//   * a sink resync               -> a gap of silence
//   * a starved sample path       -> repeated or zeroed samples
// all of which are obvious in the recording, unlike "did the picture flicker?"
//
// Phase accumulator + quarter-wave lookup. The tone frequency is exact by
// construction: PHASE_INC = 2^32 * f_tone / f_sample, evaluated at elaboration.
// Left and right are generated 180 degrees apart so a channel swap or a stuck
// channel is also visible in the capture.
//-----------------------------------------------------------------------------
`default_nettype none

module sine_gen #(
    parameter int SAMPLE_RATE = 32000,
    parameter int TONE_HZ     = 1000,
    parameter int AMPLITUDE   = 12000   // of 32767, leaves headroom
)(
    input  wire        clk,        // any clock
    input  wire        sample_en,  // one pulse per audio sample (clk_audio edge)
    output reg  signed [15:0] left  = 0,
    output reg  signed [15:0] right = 0
);

    // 256-entry quarter wave, 16-bit unsigned, generated at elaboration.
    localparam int N = 256;
    logic [15:0] quarter [0:N-1];
    initial begin
        for (int i = 0; i < N; i++)
            quarter[i] = 16'($rtoi($sin(3.14159265358979 * 0.5 * i / N) * 32767.0));
    end

    // 2^32 * TONE_HZ / SAMPLE_RATE
    localparam longint unsigned PHASE_INC =
        longint'((real'(TONE_HZ) * 4294967296.0) / real'(SAMPLE_RATE));

    reg [31:0] phase = 0;

    // full sine from the quarter table: top 2 bits select the quadrant
    function automatic signed [15:0] sine(input [31:0] ph);
        logic [1:0]  quad;
        logic [7:0]  idx;
        logic [15:0] mag;
        begin
            quad = ph[31:30];
            idx  = ph[29:22];
            mag  = (quad[0]) ? quarter[N-1-idx] : quarter[idx];
            sine = quad[1] ? -$signed({1'b0, mag[15:1]}) : $signed({1'b0, mag[15:1]});
        end
    endfunction

    always @(posedge clk) begin
        if (sample_en) begin
            phase <= phase + PHASE_INC[31:0];
            // scale to AMPLITUDE; >>>15 keeps it a signed multiply
            left  <= 16'((sine(phase) * AMPLITUDE) >>> 15);
            right <= 16'((sine(phase + 32'h8000_0000) * AMPLITUDE) >>> 15);
        end
    end

endmodule

`default_nettype wire
