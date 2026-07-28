// Parameterized Dual-Port RAM / ROM wrapper optimized for Gowin BSRAM block inference
// Three modes, selected by INIT_FILE / LOADABLE:
//   INIT_FILE set            -> dual-port RAM, port B writable, contents
//                               pre-loaded from the hex file (baked game)
//   LOADABLE=1, no INIT_FILE -> same, but starts blank: the SD loader is the
//                               ONLY source. This is the shipping mode - a
//                               distributed bitstream must not contain ROM
//                               data (licensing), so bakes are being retired.
//   neither                  -> simple dual-port RAM, writes on port A only
//                               (cleanest BSRAM inference); use for scratch
//                               RAM that no downloader writes.
// TRAP: dropping an INIT_FILE without setting LOADABLE silently moves the
// instance into the third mode, where port B writes are DISCARDED - the
// download path dies with no error anywhere. Always pair the two.
module dpram #(
    parameter dWidth = 8,
    parameter aWidth = 10,
    parameter INIT_FILE = "",
    parameter LOADABLE = 0
) (
    input                     clk_a,
    input                     we_a,
    input      [aWidth-1:0]   addr_a,
    input      [dWidth-1:0]   d_a,
    output reg [dWidth-1:0]   q_a,

    input                     clk_b,
    input                     we_b,
    input      [aWidth-1:0]   addr_b,
    input      [dWidth-1:0]   d_b,
    output reg [dWidth-1:0]   q_b
);

(* syn_ramstyle = "block_ram" *) reg [dWidth-1:0] ram [0:(2**aWidth)-1];

generate
    if (INIT_FILE != "" || LOADABLE) begin: rom_mode
        // Dual-port RAM: port A is the core's read port, port B takes ROM
        // downloads (SD loader). With INIT_FILE the contents act as a
        // power-on default, so the bitstream boots a baked-in game with no
        // card and the loader overwrites it when there is one; with
        // LOADABLE alone the array starts blank and the card is required.
        // Leaving we_b tied low reproduces plain-ROM behaviour exactly.
        if (INIT_FILE != "") begin: preload
            initial begin
                $readmemh(INIT_FILE, ram);
            end
        end
        always @(posedge clk_a) begin
            if (we_a) begin
                ram[addr_a] <= d_a;
            end
            q_a <= ram[addr_a];
        end
        // Read only when NOT writing. Reading and writing port B in the same
        // cycle infers write-through (WRITE_MODE 2'b10), which the Gowin
        // BSRAM rejects with PA2122 as soon as q_b is actually connected -
        // "no change on write" is both supported and the right semantics,
        // since anything reading port B (the stored-ROM audit) does so after
        // the load, never during it.
        always @(posedge clk_b) begin
            if (we_b) ram[addr_b] <= d_b;
            else      q_b <= ram[addr_b];
        end
    end else begin: ram_mode
        // Simple Dual-Port RAM mode (Writes only on Port A to ensure clean BSRAM inference)
        always @(posedge clk_a) begin
            if (we_a) begin
                ram[addr_a] <= d_a;
            end
            q_a <= ram[addr_a];
        end
        always @(posedge clk_b) begin
            q_b <= ram[addr_b];
        end
    end
endgenerate

endmodule
