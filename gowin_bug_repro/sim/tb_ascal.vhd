--------------------------------------------------------------------------------
-- tb_ascal - GHDL testbench for the ascal video path
--------------------------------------------------------------------------------
-- Purpose: decide whether the "horizontal 4x too fast, image repeats every 512
-- output pixels" fault seen on the Tang Console 60K is an ascal
-- configuration/usage error or a GowinSynthesis miscompile.
--
-- It drives ascal_gw with the SAME source the hardware rig uses (512x480 at
-- MCR timing, 8 colour bars) and the SAME output window (720p, hmin=160,
-- hmax=1119), but replaces the Avalon side with an IDEAL memory model: zero
-- wait states, exact burst semantics, a plain array. So this run also settles
-- whether ascal_avl_ddr3 is implicated, despite its beat counters matching.
--
-- Output: sim/ascal_out.txt, one line per active output pixel,
--   "<x> <y> <rr><gg><bb>"
-- which tools/ascal_sim_check.py turns into the same column measurement used
-- on the capture-card frames.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
USE std.textio.ALL;

ENTITY tb_ascal IS
END ENTITY;

ARCHITECTURE sim OF tb_ascal IS

  CONSTANT N_DW : natural := 128;
  CONSTANT N_AW : natural := 25;

  -- Output timing: 720p60, matching ascal_gw's defaults
  CONSTANT HTOTAL : natural := 1650;
  CONSTANT VTOTAL : natural := 750;
  CONSTANT FRAMES : natural := 4;      -- let ascal settle, measure the last

  SIGNAL i_clk : std_logic := '0';     -- 40 MHz core clock
  SIGNAL o_clk : std_logic := '0';     -- 74.25 MHz output clock
  SIGNAL a_clk : std_logic := '0';     -- 74.25 MHz Avalon clock
  SIGNAL reset_na : std_logic := '0';

  SIGNAL i_ce : std_logic := '0';
  SIGNAL i_r, i_g, i_b : std_logic_vector(7 DOWNTO 0) := (OTHERS => '0');
  SIGNAL i_hs, i_vs, i_de : std_logic := '0';

  SIGNAL o_r, o_g, o_b : std_logic_vector(7 DOWNTO 0);
  SIGNAL o_hs, o_vs, o_de : std_logic;

  SIGNAL avl_waitrequest   : std_logic := '0';
  SIGNAL avl_readdata      : std_logic_vector(N_DW-1 DOWNTO 0) := (OTHERS=>'0');
  SIGNAL avl_readdatavalid : std_logic := '0';
  SIGNAL avl_burstcount    : std_logic_vector(7 DOWNTO 0);
  SIGNAL avl_writedata     : std_logic_vector(N_DW-1 DOWNTO 0);
  SIGNAL avl_address       : std_logic_vector(N_AW-1 DOWNTO 0);
  SIGNAL avl_write, avl_read : std_logic;
  SIGNAL avl_byteenable    : std_logic_vector(N_DW/8-1 DOWNTO 0);

  SIGNAL dbg_himax, dbg_hsize, dbg_ihsize : std_logic_vector(11 DOWNTO 0);
  SIGNAL dbg_hdown : std_logic;
  SIGNAL det_hdmax, det_vdmax : std_logic_vector(11 DOWNTO 0);

  SIGNAL done : boolean := false;

BEGIN

  ------------------------------------------------------------------ clocks
  i_clk <= NOT i_clk AFTER 12.5 ns WHEN NOT done ELSE '0';   -- 40 MHz
  o_clk <= NOT o_clk AFTER 6.734 ns WHEN NOT done ELSE '0';  -- 74.25 MHz
  a_clk <= NOT a_clk AFTER 6.734 ns WHEN NOT done ELSE '0';
  reset_na <= '0', '1' AFTER 200 ns;

  ------------------------------------------------- source: MCR 512x480 bars
  -- Mirrors src/testpat/mcr_testpattern.sv: hcnt 0..633, vcnt 0..524,
  -- active 512x480, i_ce at 20 MHz (every other 40 MHz edge).
  src : PROCESS(i_clk)
    VARIABLE hcnt : natural := 0;
    VARIABLE vcnt : natural := 0;
    VARIABLE tog  : std_logic := '0';
    VARIABLE bar  : natural;
    VARIABLE active : boolean;
  BEGIN
    IF rising_edge(i_clk) THEN
      tog := NOT tog;
      i_ce <= tog;
      IF tog = '1' THEN
        active := (hcnt < 512) AND (vcnt < 480);
        i_de <= '1' WHEN active ELSE '0';
        -- vsync active HIGH for ascal, 2 lines from vcnt 489
        i_vs <= '1' WHEN (vcnt >= 489 AND vcnt < 491) ELSE '0';
        i_hs <= '1' WHEN (hcnt >= 525 AND hcnt < 602) ELSE '0';

        IF active THEN
          bar := hcnt / 64;             -- 8 colour bars, 64 px each
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
        ELSE
          i_r<=x"00"; i_g<=x"00"; i_b<=x"00";
        END IF;

        hcnt := hcnt + 1;
        IF hcnt = 634 THEN
          hcnt := 0;
          vcnt := vcnt + 1;
          IF vcnt = 525 THEN vcnt := 0; END IF;
        END IF;
      END IF;
    END IF;
  END PROCESS;

  ------------------------------------------------------------------ DUT
  dut : ENTITY work.ascal_gw
    PORT MAP (
      i_clk => i_clk, i_ce => i_ce,
      i_r => i_r, i_g => i_g, i_b => i_b,
      i_hs => i_hs, i_vs => i_vs, i_de => i_de, i_fl => '0',

      o_clk => o_clk,
      o_r => o_r, o_g => o_g, o_b => o_b,
      o_hs => o_hs, o_vs => o_vs, o_de => o_de,

      mode => "00010",                 -- sharp bilinear, single buffer
      run  => '1',
      hmin => std_logic_vector(to_unsigned(160,12)),
      hmax => std_logic_vector(to_unsigned(1119,12)),
      vmin => std_logic_vector(to_unsigned(0,12)),
      vmax => std_logic_vector(to_unsigned(719,12)),
      i_hdmax => det_hdmax, i_vdmax => det_vdmax,

      iauto => '1',
      himin => (OTHERS=>'0'), himax => (OTHERS=>'0'),
      vimin => (OTHERS=>'0'), vimax => (OTHERS=>'0'),

      dbg_i_himax => dbg_himax, dbg_i_hsize => dbg_hsize,
      dbg_o_ihsize => dbg_ihsize, dbg_i_hdown => dbg_hdown,

      poly_clk => '0', poly_a => (OTHERS=>'0'),
      poly_dw => (OTHERS=>'0'), poly_wr => '0',

      avl_clk => a_clk,
      avl_waitrequest => avl_waitrequest,
      avl_readdata => avl_readdata,
      avl_readdatavalid => avl_readdatavalid,
      avl_burstcount => avl_burstcount,
      avl_writedata => avl_writedata,
      avl_address => avl_address,
      avl_write => avl_write,
      avl_read => avl_read,
      avl_byteenable => avl_byteenable,

      reset_na => reset_na);

  ------------------------------------------------- ideal Avalon-MM slave
  -- Zero wait states. Write: consume one word per cycle while avl_write.
  -- Read: latch address+burstcount on the accepted cycle, then stream that
  -- many words back with readdatavalid. This is textbook Avalon burst - if
  -- ascal misbehaves against THIS, the bridge is exonerated.
  mem : PROCESS(a_clk)
    TYPE ram_t IS ARRAY (0 TO 2**18-1) OF std_logic_vector(N_DW-1 DOWNTO 0);
    VARIABLE ram : ram_t := (OTHERS => (OTHERS => '0'));
    VARIABLE wadr : natural := 0;
    VARIABLE wcnt : natural := 0;
    VARIABLE radr : natural := 0;
    VARIABLE rcnt : natural := 0;
  BEGIN
    IF rising_edge(a_clk) THEN
      avl_readdatavalid <= '0';

      IF rcnt > 0 THEN
        avl_readdata <= ram(radr MOD (2**18));
        avl_readdatavalid <= '1';
        radr := radr + 1;
        rcnt := rcnt - 1;
      END IF;

      IF avl_write = '1' THEN
        IF wcnt = 0 THEN
          wadr := to_integer(unsigned(avl_address));
          wcnt := to_integer(unsigned(avl_burstcount));
        END IF;
        ram(wadr MOD (2**18)) := avl_writedata;
        wadr := wadr + 1;
        wcnt := wcnt - 1;
      ELSIF avl_read = '1' AND rcnt = 0 THEN
        radr := to_integer(unsigned(avl_address));
        rcnt := to_integer(unsigned(avl_burstcount));
      END IF;
    END IF;
  END PROCESS;

  avl_waitrequest <= '0';   -- ideal memory: never stall

  ------------------------------------------------------------ output dump
  dump : PROCESS(o_clk)
    FILE f : text;
    VARIABLE l : line;
    VARIABLE opened : boolean := false;
    VARIABLE ox, oy : integer := 0;
    VARIABLE frame : natural := 0;
    VARIABLE vs_d : std_logic := '0';
    VARIABLE de_d : std_logic := '0';
  BEGIN
    IF rising_edge(o_clk) THEN
      IF NOT opened THEN
        file_open(f, "ascal_out.txt", write_mode);
        opened := true;
        -- report the geometry ascal settled on, same values the beacon shows
      END IF;

      -- count output pixels using de rising edges for x, vs for y/frame
      IF o_vs = '1' AND vs_d = '0' THEN
        frame := frame + 1;
        oy := 0;
        IF frame = FRAMES THEN
          write(l, string'("# i_hsize=")); write(l, to_integer(unsigned(dbg_hsize)));
          write(l, string'(" o_ihsize=")); write(l, to_integer(unsigned(dbg_ihsize)));
          write(l, string'(" i_himax="));  write(l, to_integer(unsigned(dbg_himax)));
          write(l, string'(" hdown="));    write(l, std_logic'image(dbg_hdown));
          writeline(f, l);
        END IF;
      END IF;
      vs_d := o_vs;

      IF o_de = '1' AND de_d = '0' THEN ox := 0; END IF;

      IF o_de = '1' THEN
        IF frame = FRAMES THEN
          write(l, ox); write(l, string'(" ")); write(l, oy); write(l, string'(" "));
          hwrite(l, o_r); hwrite(l, o_g); hwrite(l, o_b);
          writeline(f, l);
        END IF;
        ox := ox + 1;
      END IF;

      IF o_de = '0' AND de_d = '1' THEN oy := oy + 1; END IF;
      de_d := o_de;

      IF frame > FRAMES THEN
        file_close(f);
        done <= true;
        REPORT "simulation complete" SEVERITY note;
      END IF;
    END IF;
  END PROCESS;

END ARCHITECTURE;
