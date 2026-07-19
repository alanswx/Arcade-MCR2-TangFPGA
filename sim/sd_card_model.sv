// Behavioural SD card (SPI mode) for simulation only.
// Answers CMD0/CMD8/CMD55/ACMD41/CMD58/CMD17 well enough to exercise
// sd_reader's init and block-read paths. Block data is a deterministic
// pattern so the testbench can verify what came back:
//     byte i of sector S = (S*13 + i) & 0xFF
module sd_card_model #(
    parameter int unsigned HDR_SECTOR = 2048   // this sector returns a valid
                                               // "MCRPACK1" header
)(
    input  logic sclk,
    input  logic cs_n,
    input  logic mosi,
    output logic miso
);

localparam int QSZ = 1024;
logic [7:0] q [QSZ];
int qhead = 0, qtail = 0;

function automatic void push(input logic [7:0] b);
    q[qtail] = b;
    qtail = (qtail + 1) % QSZ;
endfunction

// ---- output side: slave changes MISO on the falling edge ----------------
logic [7:0] outbyte = 8'hFF;
int obit = 0;

assign miso = cs_n ? 1'b1 : outbyte[7-obit];

always @(negedge sclk) begin
    if (!cs_n) begin
        if (obit == 7) begin
            obit = 0;
            if (qhead != qtail) begin
                outbyte = q[qhead];
                qhead = (qhead + 1) % QSZ;
            end else begin
                outbyte = 8'hFF;
            end
        end else begin
            obit++;
        end
    end
end

// ---- input side: sample MOSI on the rising edge --------------------------
logic [7:0] rx = 8'hFF;
int ibit = 0;
logic [7:0] cmdbuf [6];
int cmdidx = 0;
bit in_cmd = 0;
int acmd41_seen = 0;
bit last_was_55 = 0;

always @(posedge sclk) begin
    if (!cs_n) begin
        rx = {rx[6:0], mosi};
        ibit++;
        if (ibit == 8) begin
            ibit = 0;
            if (in_cmd) begin
                cmdbuf[cmdidx] = rx;
                cmdidx++;
                if (cmdidx == 6) begin
                    in_cmd = 0;
                    do_command();
                end
            end else if (rx[7:6] == 2'b01) begin
                in_cmd = 1;
                cmdbuf[0] = rx;
                cmdidx = 1;
            end
        end
    end
end

function automatic void do_command();
    logic [5:0]  cmd;
    logic [31:0] arg;
    int unsigned sector;
    cmd = cmdbuf[0][5:0];
    arg = {cmdbuf[1], cmdbuf[2], cmdbuf[3], cmdbuf[4]};

    push(8'hFF);   // NCR gap before the response

    case (cmd)
    6'd0:  begin push(8'h01); last_was_55 = 0; end          // GO_IDLE_STATE
    6'd8:  begin                                            // SEND_IF_COND (R7)
               push(8'h01); push(8'h00); push(8'h00); push(8'h01); push(8'hAA);
               last_was_55 = 0;
           end
    6'd55: begin push(8'h01); last_was_55 = 1; end           // APP_CMD
    6'd41: begin                                             // ACMD41
               if (last_was_55) begin
                   acmd41_seen++;
                   // report busy a few times, like a real card
                   push(acmd41_seen >= 3 ? 8'h00 : 8'h01);
               end else begin
                   push(8'h05);                              // illegal command
               end
               last_was_55 = 0;
           end
    6'd58: begin                                             // READ_OCR (R3)
               push(8'h00);
               push(8'hC0); push(8'hFF); push(8'h80); push(8'h00); // CCS=1 (SDHC)
               last_was_55 = 0;
           end
    6'd17: begin                                             // READ_SINGLE_BLOCK
               push(8'h00);                                  // R1 ok
               push(8'hFF);                                  // pre-token gap
               push(8'hFE);                                  // data token
               sector = arg;
               if (sector == HDR_SECTOR) begin
                   // "MCRPACK1", slot count, then zeros
                   push(8'h4D); push(8'h43); push(8'h52); push(8'h50);
                   push(8'h41); push(8'h43); push(8'h4B); push(8'h31);
                   push(8'd8);
                   for (int i = 9; i < 512; i++) push(8'h00);
               end else begin
                   for (int i = 0; i < 512; i++)
                       push(8'((sector*13 + i) & 32'hFF));
               end
               push(8'h12); push(8'h34);                     // CRC16 (ignored)
               last_was_55 = 0;
           end
    default: begin push(8'h04); last_was_55 = 0; end          // illegal command
    endcase
endfunction

endmodule
