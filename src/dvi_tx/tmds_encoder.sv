// Standard DVI TMDS Encoder
module tmds_encoder (
    input            clk,
    input            resetn,
    input            de,
    input      [1:0] ctrl,
    input      [7:0] din,
    output reg [9:0] dout
);

wire [7:0] D = din;

function automatic [3:0] N1(input [7:0] bits);
    integer i;
    begin
        N1 = 0;
        for (i = 0; i < 8; i = i+1)
            N1 = N1 + bits[i];
    end
endfunction

function automatic [3:0] N0(input [7:0] bits);
    integer i;
    begin
        N0 = 0;
        for (i = 0; i < 8; i = i+1)
            N0 = N0 + !bits[i];
    end
endfunction

reg [9:0] q_out;
reg [3:0] N0_q_m, N1_q_m;
reg signed [7:0] cnt, cnt_next, cnt_tmp;
reg [8:0] q_m;

always @(posedge clk) begin
    if (!resetn) begin
        cnt   <= 0;
        dout  <= 0;
    end else if (!de) begin
        cnt   <= 0;
        case (ctrl)
            2'b00: dout <= 10'b1101010100;
            2'b01: dout <= 10'b0010101011;
            2'b10: dout <= 10'b0101010100;
            2'b11: dout <= 10'b1010101011;
        endcase
    end else begin
        if ((N1(D) > 4) || ((N1(D) == 4) && (D[0] == 0))) begin
            q_m[0] =           D[0];
            q_m[1] = q_m[0] ^~ D[1];
            q_m[2] = q_m[1] ^~ D[2];
            q_m[3] = q_m[2] ^~ D[3];
            q_m[4] = q_m[3] ^~ D[4];
            q_m[5] = q_m[4] ^~ D[5];
            q_m[6] = q_m[5] ^~ D[6];
            q_m[7] = q_m[6] ^~ D[7];
            q_m[8] = 1'b0;
        end else begin
            q_m[0] =          D[0];
            q_m[1] = q_m[0] ^ D[1];
            q_m[2] = q_m[1] ^ D[2];
            q_m[3] = q_m[2] ^ D[3];
            q_m[4] = q_m[3] ^ D[4];
            q_m[5] = q_m[4] ^ D[5];
            q_m[6] = q_m[5] ^ D[6];
            q_m[7] = q_m[6] ^ D[7];
            q_m[8] = 1'b1;
        end

        N0_q_m = N0(q_m[7:0]);
        N1_q_m = N1(q_m[7:0]);

        if ((cnt == 0) || (N1_q_m == N0_q_m)) begin
            dout[9]    <= ~q_m[8];
            dout[8]    <=  q_m[8];
            dout[7:0]  <= (q_m[8] ? q_m[7:0] : ~q_m[7:0]);
            if (q_m[8] == 0) begin
                cnt <= cnt + (N0_q_m - N1_q_m);
            end else begin
                cnt <= cnt + (N1_q_m - N0_q_m);
            end
        end else if (((cnt > 0) && (N1_q_m > N0_q_m)) || (((cnt < 0) && (N0_q_m > N1_q_m)))) begin
            dout[9]    <=  1'b1;
            dout[8]    <=  q_m[8];
            dout[7:0]  <= ~q_m[7:0];
            cnt_tmp     = cnt + (N0_q_m - N1_q_m);
            if (q_m[8]) begin
                cnt <= cnt_tmp + 2'h2;
            end else begin
                cnt <= cnt_tmp;
            end
        end else begin
            dout[9]    <=  1'b0;
            dout[8]    <=  q_m[8];
            dout[7:0]  <=  q_m[7:0];
            cnt_tmp     = cnt + (N1_q_m - N0_q_m);
            if (q_m[8]) begin
                cnt <= cnt_tmp;
            end else begin
                cnt <= cnt_tmp - 2'h2;
            end
        end
    end
end

endmodule
