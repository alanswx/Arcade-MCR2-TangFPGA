reg jsr_en;
reg [11:0] jsr_ua, jsr_ret, uaddr;

// wire [4:0] jsr_sel;
// wire [1:0] carry_sel;
// wire [1:0] ea_sel;
// wire [3:0] alu_sel;
// wire [4:0] cc_sel;
// wire [3:0] ld_sel;
// wire [1:0] opnd_sel;
// wire [3:0] rmux_sel;

// wire       op0inv;
// wire       fetch;
// wire       ni;
// wire       alu16;
// wire       halt;
// wire       brlatch;
// wire       branch;
// wire       alt;
// wire       inc_pc;
// wire       wr;
// wire       md_shift;
// wire       swi;

// THE MICROCODE IS THE BIGGEST BSRAM CONSUMER ON THE TANG, and getting it out
// of block RAM is the make-or-break item for fitting speech into the merged
// core. Measured on GW5AT-LV60 (mcr3_console60k, 2026-08-01):
//
//     u_ctrl (this table, 4096x40)  10 BSRAM
//     16 KB Squawk & Talk board ROM  8 BSRAM
//     TMS5200 coefficient ROMs       2 BSRAM
//     6802 internal 128 B RAM        1 BSRAM
//
// It is read COMBINATIONALLY (see the assign below) from the CPU's control
// path, so it can never move to SDRAM whatever the block pressure -- the right
// destination is LOGIC, which this design has spare (27%). Quartus already
// proves that works: on Cyclone V it lands in logic for ~1.1k ALMs, far less
// than 4096x40 = 164 kbit suggests, because most of the 40 bit-slices are
// constant or unused per address and get stripped.
//
// ATTEMPTED AND MEASURED NOT TO WORK: `(* syn_ramstyle = "registers" *)` here.
// GowinSynthesis ignores it -- the log still says "Extracting RAM for
// identifier 'ucode_rom'" and the build comes out bit-identical (Logic 15726,
// BSRAM 118/118 either way). Note "registers" would be wrong even if honoured:
// 4096x40 is 164k flip-flops against the device's 60,780. "distributed_ram" is
// no better, being far too deep for LUT RAM.
//
// The likely fix is to restructure this into a case statement generated from
// 6801.uc, which a synthesiser can constant-fold and strip the way Quartus
// does. That is a real change to vendored code and has NOT been attempted.
reg  [39:0] ucode_rom[0:2**12-1];
wire [39:0] ucode_data;

initial begin
    $readmemb("6801.uc",ucode_rom);
end

assign ucode_data = ucode_rom[uaddr];

assign op0inv     = ucode_data[ 0+:1];
assign fetch      = ucode_data[10+:1];
assign ni         = ucode_data[20+:1];
assign alu16      = ucode_data[21+:1];
assign halt       = ucode_data[22+:1];
assign brlatch    = ucode_data[23+:1];
assign branch     = ucode_data[24+:1];
assign alt        = ucode_data[25+:1];
assign inc_pc     = ucode_data[32+:1];
assign wr         = ucode_data[37+:1];
assign md_shift   = ucode_data[38+:1];
assign swi        = ucode_data[39+:1];
assign jsr_sel    = ucode_data[ 1+:5];
assign carry_sel  = ucode_data[ 6+:2];
assign ea_sel     = ucode_data[ 8+:2];
assign alu_sel    = ucode_data[11+:4];
assign cc_sel     = ucode_data[15+:5];
assign ld_sel     = ucode_data[26+:4];
assign opnd_sel   = ucode_data[30+:2];
assign rmux_sel   = ucode_data[33+:4];


always @* begin
    case( jsr_sel )
        IVRD_JSR:    begin jsr_en=1; jsr_ua = 12'h00*12'd16; end 
        IDLE4_JSR:   begin jsr_en=1; jsr_ua = 12'h87*12'd16; end 
        IMM_JSR:     begin jsr_en=1; jsr_ua = 12'h8F*12'd16; end 
        IMM16_JSR:   begin jsr_en=1; jsr_ua = 12'hCF*12'd16; end 
        DIRA_JSR:    begin jsr_en=1; jsr_ua = 12'h45*12'd16; end 
        DIR_JSR:     begin jsr_en=1; jsr_ua = 12'h14*12'd16; end 
        DIR16_JSR:   begin jsr_en=1; jsr_ua = 12'h15*12'd16; end 
        EXTA_JSR:    begin jsr_en=1; jsr_ua = 12'h55*12'd16; end 
        EXT_JSR:     begin jsr_en=1; jsr_ua = 12'h1C*12'd16; end 
        EXT16_JSR:   begin jsr_en=1; jsr_ua = 12'h1D*12'd16; end 
        IDXA_JSR:    begin jsr_en=1; jsr_ua = 12'h4B*12'd16; end 
        IDX_JSR:     begin jsr_en=1; jsr_ua = 12'h1E*12'd16; end 
        IDX16_JSR:   begin jsr_en=1; jsr_ua = 12'h1F*12'd16; end 
        PSH8_JSR:    begin jsr_en=1; jsr_ua = 12'h4E*12'd16; end 
        PSH16_JSR:   begin jsr_en=1; jsr_ua = 12'h02*12'd16; end 
        PUL8_JSR:    begin jsr_en=1; jsr_ua = 12'h03*12'd16; end 
        PUL16_JSR:   begin jsr_en=1; jsr_ua = 12'h41*12'd16; end 
        IDLE6_JSR:   begin jsr_en=1; jsr_ua = 12'h42*12'd16; end 
        RTI8_JSR:    begin jsr_en=1; jsr_ua = 12'h51*12'd16; end 
        RET_JSR:     begin jsr_en=1; jsr_ua = jsr_ret; end
        default:     begin jsr_en=0; jsr_ua = 'h00; end
    endcase
end
