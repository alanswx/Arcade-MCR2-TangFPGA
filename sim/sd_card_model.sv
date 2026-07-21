// Behavioural SD card (SPI mode) for simulation only.
// Answers CMD0/CMD8/CMD55/ACMD41/CMD58/CMD17/CMD24 well enough to exercise
// sd_reader's init, block-read and block-write paths. Unwritten block data
// is a deterministic pattern so the testbench can verify what came back:
//     byte i of sector S = (S*13 + i) & 0xFF
// CMD24 writes land in a sparse memory and shadow the pattern on read-back,
// which is exactly what the prefs-sector round trip needs.
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

// CMD24 write capture
logic [7:0] wmem [int unsigned];   // sparse: key = sector*512 + offset
bit in_write = 0;
int wr_phase = 0;                  // 0 token, 1 data, 2/3 CRC
int unsigned wr_sector = 0;
int wr_cnt = 0;

always @(posedge sclk) begin
    if (!cs_n) begin
        rx = {rx[6:0], mosi};
        ibit++;
        if (ibit == 8) begin
            ibit = 0;
            if (in_write) begin
                case (wr_phase)
                0: if (rx == 8'hFE) begin wr_phase = 1; wr_cnt = 0; end
                1: begin
                       wmem[wr_sector*512 + wr_cnt] = rx;
                       wr_cnt++;
                       if (wr_cnt == 512) wr_phase = 2;
                   end
                2: wr_phase = 3;                    // CRC byte 1
                3: begin                            // CRC byte 2 -> respond
                       push(8'h05);                 // data accepted
                       push(8'h00); push(8'h00);    // busy for two byte-times
                       in_write = 0;
                   end
                endcase
            end else if (in_cmd) begin
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

// One byte of block `sector`: written data shadows the built-in pattern.
function automatic logic [7:0] block_byte(input int unsigned sector,
                                          input int i);
    if (wmem.exists(sector*512 + i))
        return wmem[sector*512 + i];
    if (sector == HDR_SECTOR) begin
        case (i)
        0: return 8'h4D; 1: return 8'h43; 2: return 8'h52; 3: return 8'h50;
        4: return 8'h41; 5: return 8'h43; 6: return 8'h4B; 7: return 8'h31;
        8: return 8'd8;                       // slot count
        default: return 8'h00;
        endcase
    end
    return 8'((sector*13 + i) & 32'hFF);
endfunction

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
               for (int i = 0; i < 512; i++) push(block_byte(sector, i));
               push(8'h12); push(8'h34);                     // CRC16 (ignored)
               last_was_55 = 0;
           end
    6'd24: begin                                             // WRITE_BLOCK
               push(8'h00);                                  // R1 ok
               wr_sector = arg;
               wr_phase  = 0;
               in_write  = 1;
               last_was_55 = 0;
           end
    default: begin push(8'h04); last_was_55 = 0; end          // illegal command
    endcase
endfunction

endmodule
