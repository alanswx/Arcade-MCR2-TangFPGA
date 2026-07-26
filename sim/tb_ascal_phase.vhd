--------------------------------------------------------------------------------
-- tb_ascal_phase - ascal + a VHDL transcription of ascal_avl_ddr3 + a Gowin
-- DDR3 app-interface model.
--------------------------------------------------------------------------------
-- tb_ascal.vhd proved ascal renders PERFECTLY (one 960-wide image, 120 px per
-- colour bar) when its Avalon port is an ideal memory. The hardware, which
-- uses ascal_avl_ddr3 against the real Gowin DDR3 controller, renders the
-- source 4x too narrow and repeats it every 512 output pixels. The only thing
-- between those two results is the bridge, so this testbench puts it in the
-- loop.
--
-- bridge_sim below is a line-for-line transcription of ascal_avl_ddr3.sv.
-- Keep the two in sync; if you change the .sv, change this too.
--
-- ddr3_app_model mimics DDR3_Memory_Interface_Top as gbatang drives it:
--   * a command is accepted on cmd_en AND cmd_ready
--   * cmd 0 = write (data taken on the same cycle, wr_data_rdy high)
--   * cmd 1 = read, one 128-bit beat returned per command, IN ORDER, after a
--     fixed latency
--   * addr counts 2-BYTE units; one command moves 16 bytes = 8 addr units
--   * cmd_ready drops periodically, because the real controller cannot accept
--     a command every cycle (refresh/activate) - this is the flow control the
--     bridge has to honour and the most likely place for it to go wrong.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

-- ================================================================ bridge
ENTITY bridge_sim IS
  GENERIC (
    N_DW    : natural := 128;
    N_AW    : natural := 25;
    BLEN    : natural := 128);      -- N_BURST 2048 / N_DW 128 * 8
  PORT (
    clk : IN std_logic;
    rst : IN std_logic;
    avl_address       : IN  std_logic_vector(N_AW-1 DOWNTO 0);
    avl_write         : IN  std_logic;
    avl_read          : IN  std_logic;
    avl_writedata     : IN  std_logic_vector(N_DW-1 DOWNTO 0);
    avl_burstcount    : IN  std_logic_vector(7 DOWNTO 0);
    avl_waitrequest   : OUT std_logic;
    avl_readdata      : OUT std_logic_vector(N_DW-1 DOWNTO 0);
    avl_readdatavalid : OUT std_logic;
    app_rdy           : IN  std_logic;
    app_en            : OUT std_logic;
    app_cmd           : OUT std_logic_vector(2 DOWNTO 0);
    app_addr          : OUT std_logic_vector(27 DOWNTO 0);
    app_wdf_rdy       : IN  std_logic;
    app_wdf_wren      : OUT std_logic;
    app_wdf_data      : OUT std_logic_vector(N_DW-1 DOWNTO 0);
    app_rd_data_valid : IN  std_logic;
    app_rd_data       : IN  std_logic_vector(N_DW-1 DOWNTO 0));
END ENTITY;

ARCHITECTURE rtl OF bridge_sim IS
  CONSTANT ST_IDLE  : natural := 0;
  CONSTANT ST_WRITE : natural := 1;
  CONSTANT ST_READ  : natural := 2;
  SIGNAL state  : natural RANGE 0 TO 3 := ST_IDLE;
  SIGNAL addr_q : unsigned(N_AW-1 DOWNTO 0) := (OTHERS=>'0');
  SIGNAL beat   : unsigned(7 DOWNTO 0) := (OTHERS=>'0');
  SIGNAL blen_q : unsigned(7 DOWNTO 0) := to_unsigned(BLEN MOD 256,8);
  SIGNAL wr_go, rd_go : std_logic;
BEGIN
  wr_go <= '1' WHEN state=ST_WRITE AND app_rdy='1' AND app_wdf_rdy='1' ELSE '0';
  rd_go <= '1' WHEN state=ST_READ  AND app_rdy='1' ELSE '0';

  avl_waitrequest <= '0' WHEN (wr_go='1' OR (rd_go='1' AND beat=0)) ELSE '1';
  app_en       <= wr_go OR rd_go;
  app_cmd      <= "001" WHEN state=ST_READ ELSE "000";
  app_addr     <= std_logic_vector(resize(addr_q & "000", 28));
  app_wdf_wren <= wr_go;
  app_wdf_data <= avl_writedata;
  avl_readdata      <= app_rd_data;
  avl_readdatavalid <= app_rd_data_valid;

  PROCESS(clk) BEGIN
    IF rising_edge(clk) THEN
      IF rst='1' THEN
        state<=ST_IDLE; beat<=(OTHERS=>'0'); addr_q<=(OTHERS=>'0');
        blen_q<=to_unsigned(BLEN MOD 256,8);
      ELSE
        CASE state IS
          WHEN ST_IDLE =>
            beat   <= (OTHERS=>'0');
            addr_q <= unsigned(avl_address);
            IF unsigned(avl_burstcount)=0 THEN
              blen_q <= to_unsigned(BLEN MOD 256,8);
            ELSE
              blen_q <= unsigned(avl_burstcount);
            END IF;
            IF avl_write='1' THEN state<=ST_WRITE;
            ELSIF avl_read='1' THEN state<=ST_READ; END IF;
          WHEN ST_WRITE =>
            IF wr_go='1' THEN
              addr_q<=addr_q+1; beat<=beat+1;
              IF beat=blen_q-1 THEN state<=ST_IDLE; END IF;
            END IF;
          WHEN ST_READ =>
            IF rd_go='1' THEN
              addr_q<=addr_q+1; beat<=beat+1;
              IF beat=blen_q-1 THEN state<=ST_IDLE; END IF;
            END IF;
          WHEN OTHERS => state<=ST_IDLE;
        END CASE;
      END IF;
    END IF;
  END PROCESS;
END ARCHITECTURE;

-- ========================================================== DDR3 model
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY ddr3_app_model IS
  -- LAT: read latency in app clocks. gbatang's ddr3_framebuffer.v says the
  -- real Gowin controller is "about 22 cycles" and prefetches 32-44 pixels
  -- ahead to cover it, so 12 was optimistic; 40 is deliberately pessimistic.
  GENERIC (LAT : natural := 40; STALL : boolean := true);
  PORT (
    clk : IN std_logic;
    cmd_ready : OUT std_logic;
    cmd       : IN  std_logic_vector(2 DOWNTO 0);
    cmd_en    : IN  std_logic;
    addr      : IN  std_logic_vector(27 DOWNTO 0);
    wr_data_rdy : OUT std_logic;
    wr_data     : IN  std_logic_vector(127 DOWNTO 0);
    wr_data_en  : IN  std_logic;
    rd_data       : OUT std_logic_vector(127 DOWNTO 0);
    rd_data_valid : OUT std_logic);
END ENTITY;

ARCHITECTURE sim OF ddr3_app_model IS
  TYPE ram_t IS ARRAY (0 TO 2**18-1) OF std_logic_vector(127 DOWNTO 0);
  TYPE pipe_t IS ARRAY (0 TO LAT) OF integer;
  SIGNAL rdy : std_logic := '1';
  SIGNAL cnt : natural := 0;
BEGIN
  -- Refuse a command every 16th cycle, standing in for refresh/activate.
  PROCESS(clk) BEGIN
    IF rising_edge(clk) THEN
      cnt <= (cnt+1) MOD 16;
      IF STALL AND cnt >= 8 THEN rdy <= '0'; ELSE rdy <= '1'; END IF;
    END IF;
  END PROCESS;
  cmd_ready   <= rdy;
  wr_data_rdy <= rdy;

  PROCESS(clk)
    VARIABLE ram   : ram_t := (OTHERS => (OTHERS=>'0'));
    VARIABLE pipe  : pipe_t := (OTHERS => -1);
    VARIABLE widx  : natural;
  BEGIN
    IF rising_edge(clk) THEN
      -- read-return pipeline, strictly in order
      rd_data_valid <= '0';
      IF pipe(LAT) >= 0 THEN
        rd_data <= ram(pipe(LAT) MOD (2**18));
        rd_data_valid <= '1';
      END IF;
      FOR i IN LAT DOWNTO 1 LOOP pipe(i) := pipe(i-1); END LOOP;
      pipe(0) := -1;

      IF cmd_en='1' AND rdy='1' THEN
        widx := to_integer(unsigned(addr)) / 8;   -- 8 addr units per 16B word
        IF cmd = "000" THEN
          IF wr_data_en='1' THEN ram(widx MOD (2**18)) := wr_data; END IF;
        ELSE
          pipe(0) := widx;
        END IF;
      END IF;
    END IF;
  END PROCESS;
END ARCHITECTURE;

-- ============================================================ testbench
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
USE std.textio.ALL;

ENTITY tb_ascal_phase IS
END ENTITY;

ARCHITECTURE sim OF tb_ascal_phase IS
  CONSTANT N_DW : natural := 128;
  CONSTANT N_AW : natural := 25;
  CONSTANT FRAMES : natural := 4;

  SIGNAL i_clk, o_clk, a_clk : std_logic := '0';
  SIGNAL reset_na : std_logic := '0';
  SIGNAL rst_a : std_logic := '1';

  SIGNAL i_ce : std_logic := '0';
  SIGNAL i_r, i_g, i_b : std_logic_vector(7 DOWNTO 0) := (OTHERS=>'0');
  SIGNAL i_hs, i_vs, i_de : std_logic := '0';
  SIGNAL o_r, o_g, o_b : std_logic_vector(7 DOWNTO 0);
  SIGNAL o_hs, o_vs, o_de : std_logic;

  SIGNAL avl_waitrequest, avl_readdatavalid, avl_write, avl_read : std_logic;
  SIGNAL avl_readdata, avl_writedata : std_logic_vector(N_DW-1 DOWNTO 0);
  SIGNAL avl_burstcount : std_logic_vector(7 DOWNTO 0);
  SIGNAL avl_address : std_logic_vector(N_AW-1 DOWNTO 0);
  SIGNAL avl_byteenable : std_logic_vector(N_DW/8-1 DOWNTO 0);

  SIGNAL app_rdy, app_en, app_wdf_rdy, app_wdf_wren, app_rd_data_valid : std_logic;
  SIGNAL app_cmd : std_logic_vector(2 DOWNTO 0);
  SIGNAL app_addr : std_logic_vector(27 DOWNTO 0);
  SIGNAL app_wdf_data, app_rd_data : std_logic_vector(127 DOWNTO 0);

  SIGNAL dbg_himax, dbg_hsize, dbg_ihsize, det_hdmax, det_vdmax : std_logic_vector(11 DOWNTO 0);
  SIGNAL dbg_hacc : std_logic_vector(15 DOWNTO 0);
  SIGNAL dbg_dcpt : std_logic_vector(11 DOWNTO 0);
  SIGNAL dbg_hdown : std_logic;
  SIGNAL done : boolean := false;
BEGIN
  i_clk <= NOT i_clk AFTER 12.5 ns WHEN NOT done ELSE '0';
  o_clk <= NOT o_clk AFTER 6.734 ns WHEN NOT done ELSE '0';
  -- PHASE TEST: on hardware clk_x1 (DDR3 controller PLL) and hclk (HDMI PLL)
  -- are both 74.25 MHz but from SEPARATE PLLs, so their phase relationship is
  -- arbitrary. The original testbench made them phase-identical, which masks
  -- every <ASYNC> crossing inside ascal. Offset a_clk by ~90 degrees.
  a_phase : PROCESS BEGIN
    WAIT FOR 3.367 ns;
    WHILE NOT done LOOP
      a_clk <= '1'; WAIT FOR 6.734 ns;
      a_clk <= '0'; WAIT FOR 6.734 ns;
    END LOOP;
    WAIT;
  END PROCESS;
  reset_na <= '0', '1' AFTER 200 ns;
  rst_a    <= '1', '0' AFTER 200 ns;

  src : PROCESS(i_clk)
    VARIABLE hcnt, vcnt : natural := 0;
    VARIABLE tog : std_logic := '0';
    VARIABLE bar : natural;
    VARIABLE active : boolean;
  BEGIN
    IF rising_edge(i_clk) THEN
      tog := NOT tog; i_ce <= tog;
      IF tog='1' THEN
        active := (hcnt<512) AND (vcnt<480);
        i_de <= '1' WHEN active ELSE '0';
        i_vs <= '1' WHEN (vcnt>=489 AND vcnt<491) ELSE '0';
        i_hs <= '1' WHEN (hcnt>=525 AND hcnt<602) ELSE '0';
        IF active THEN
          bar := hcnt/64;
          CASE bar IS
            WHEN 0 => i_r<=x"FF"; i_g<=x"FF"; i_b<=x"FF";
            WHEN 1 => i_r<=x"FF"; i_g<=x"FF"; i_b<=x"00";
            WHEN 2 => i_r<=x"00"; i_g<=x"FF"; i_b<=x"FF";
            WHEN 3 => i_r<=x"00"; i_g<=x"FF"; i_b<=x"00";
            WHEN 4 => i_r<=x"FF"; i_g<=x"00"; i_b<=x"FF";
            WHEN 5 => i_r<=x"FF"; i_g<=x"00"; i_b<=x"00";
            WHEN 6 => i_r<=x"00"; i_g<=x"00"; i_b<=x"FF";
            WHEN OTHERS => i_r<=x"40"; i_g<=x"40"; i_b<=x"40";
          END CASE;
        ELSE i_r<=x"00"; i_g<=x"00"; i_b<=x"00"; END IF;
        hcnt := hcnt+1;
        IF hcnt=634 THEN hcnt:=0; vcnt:=vcnt+1;
          IF vcnt=525 THEN vcnt:=0; END IF; END IF;
      END IF;
    END IF;
  END PROCESS;

  dut : ENTITY work.ascal_gw
    PORT MAP (
      i_clk=>i_clk, i_ce=>i_ce, i_r=>i_r, i_g=>i_g, i_b=>i_b,
      i_hs=>i_hs, i_vs=>i_vs, i_de=>i_de, i_fl=>'0',
      o_clk=>o_clk, o_r=>o_r, o_g=>o_g, o_b=>o_b,
      o_hs=>o_hs, o_vs=>o_vs, o_de=>o_de,
      mode=>"00010", run=>'1',
      hmin=>std_logic_vector(to_unsigned(160,12)),
      hmax=>std_logic_vector(to_unsigned(1119,12)),
      vmin=>std_logic_vector(to_unsigned(0,12)),
      vmax=>std_logic_vector(to_unsigned(719,12)),
      i_hdmax=>det_hdmax, i_vdmax=>det_vdmax,
      iauto=>'1', himin=>(OTHERS=>'0'), himax=>(OTHERS=>'0'),
      vimin=>(OTHERS=>'0'), vimax=>(OTHERS=>'0'),
      dbg_o_hacc=>dbg_hacc, dbg_o_dcpt=>dbg_dcpt,
      dbg_i_himax=>dbg_himax, dbg_i_hsize=>dbg_hsize,
      dbg_o_ihsize=>dbg_ihsize, dbg_i_hdown=>dbg_hdown,
      poly_clk=>'0', poly_a=>(OTHERS=>'0'), poly_dw=>(OTHERS=>'0'), poly_wr=>'0',
      avl_clk=>a_clk, avl_waitrequest=>avl_waitrequest,
      avl_readdata=>avl_readdata, avl_readdatavalid=>avl_readdatavalid,
      avl_burstcount=>avl_burstcount, avl_writedata=>avl_writedata,
      avl_address=>avl_address, avl_write=>avl_write, avl_read=>avl_read,
      avl_byteenable=>avl_byteenable, reset_na=>reset_na);

  br : ENTITY work.bridge_sim
    GENERIC MAP (N_DW=>N_DW, N_AW=>N_AW, BLEN=>128)
    PORT MAP (
      clk=>a_clk, rst=>rst_a,
      avl_address=>avl_address, avl_write=>avl_write, avl_read=>avl_read,
      avl_writedata=>avl_writedata, avl_burstcount=>avl_burstcount,
      avl_waitrequest=>avl_waitrequest, avl_readdata=>avl_readdata,
      avl_readdatavalid=>avl_readdatavalid,
      app_rdy=>app_rdy, app_en=>app_en, app_cmd=>app_cmd, app_addr=>app_addr,
      app_wdf_rdy=>app_wdf_rdy, app_wdf_wren=>app_wdf_wren,
      app_wdf_data=>app_wdf_data,
      app_rd_data_valid=>app_rd_data_valid, app_rd_data=>app_rd_data);

  ddr : ENTITY work.ddr3_app_model
    PORT MAP (
      clk=>a_clk, cmd_ready=>app_rdy, cmd=>app_cmd, cmd_en=>app_en,
      addr=>app_addr, wr_data_rdy=>app_wdf_rdy, wr_data=>app_wdf_data,
      wr_data_en=>app_wdf_wren, rd_data=>app_rd_data,
      rd_data_valid=>app_rd_data_valid);

  dump : PROCESS(o_clk)
    FILE f : text;
    VARIABLE l : line;
    VARIABLE opened : boolean := false;
    VARIABLE ox, oy : integer := 0;
    VARIABLE frame : natural := 0;
    VARIABLE vs_d, de_d : std_logic := '0';
  BEGIN
    IF rising_edge(o_clk) THEN
      IF NOT opened THEN
        file_open(f, "ascal_phase_out.txt", write_mode); opened := true;
      END IF;
      IF o_vs='1' AND vs_d='0' THEN
        frame := frame+1; oy := 0;
        IF frame=FRAMES THEN
          write(l,string'("# o_hsize=")); write(l,to_integer(unsigned(dbg_hsize)));
          write(l,string'(" o_hmax="));   write(l,to_integer(unsigned(dbg_ihsize)));
          write(l,string'(" i_himax="));  write(l,to_integer(unsigned(dbg_himax)));
          writeline(f,l);
        END IF;
      END IF;
      vs_d := o_vs;
      IF o_de='1' AND de_d='0' THEN ox := 0; END IF;
      -- PROBE: identical trigger to ascal_test60k_top.sv (line 100, pixel 300)
      IF o_de='1' AND oy=100 AND ox=300 AND frame=FRAMES THEN
        write(l,string'("# PROBE o_hburst=")); write(l,to_integer(unsigned(dbg_hsize)));
        write(l,string'(" copylev_hbcpt=")); hwrite(l,dbg_ihsize(11 DOWNTO 4));
        write(l,string'(" o_hacc=")); write(l,to_integer(unsigned(dbg_hacc)));
        write(l,string'(" (aux=")); hwrite(l,dbg_hacc(13 DOWNTO 6));
        write(l,string'(") o_dcpt=")); write(l,to_integer(unsigned(dbg_dcpt)));
        write(l,string'(" (aux2=")); hwrite(l,dbg_dcpt(7 DOWNTO 0));
        write(l,string'(")")); writeline(f,l);
      END IF;
      IF o_de='1' THEN
        IF frame=FRAMES AND oy < 40 THEN     -- 40 lines is plenty to measure
          write(l,ox); write(l,string'(" ")); write(l,oy); write(l,string'(" "));
          hwrite(l,o_r); hwrite(l,o_g); hwrite(l,o_b); writeline(f,l);
        END IF;
        ox := ox+1;
      END IF;
      IF o_de='0' AND de_d='1' THEN oy := oy+1; END IF;
      de_d := o_de;
      IF frame>FRAMES THEN file_close(f); done<=true; END IF;
    END IF;
  END PROCESS;
END ARCHITECTURE;
