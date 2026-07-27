--------------------------------------------------------------------------------
-- Minimal reproducer for GowinSynthesis PA2122.
--------------------------------------------------------------------------------
-- Instantiates UNMODIFIED upstream ascal.vhd and does nothing else.
-- Synthesis succeeds; PnR then fails with
--   ERROR (PA2122) : Not support '...'(SPX9) WRITE_MODE = 2'b10,
--                    please change write mode WRITE_MODE = 2'b00 or 2'b01.
-- because GowinSynthesis packs plain register pipelines (o_h_poly_phase_a*,
-- o_hpixq, ...) into block-RAM shift registers and then requests a write mode
-- those primitives reject.
--   gw_sh build_defect2_PA2122.tcl
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY pa2122_min IS
  PORT (
    i_clk, o_clk, avl_clk, reset_na : IN std_logic;
    i_rgb : IN  std_logic_vector(23 DOWNTO 0);
    i_hs, i_vs, i_de, i_ce : IN std_logic;
    o_rgb : OUT std_logic_vector(23 DOWNTO 0);
    o_hs, o_vs, o_de : OUT std_logic;
    mode_i : IN std_logic_vector(4 DOWNTO 0);
    avl_waitrequest   : IN  std_logic;
    avl_readdata      : IN  std_logic_vector(127 DOWNTO 0);
    avl_readdatavalid : IN  std_logic;
    avl_burstcount    : OUT std_logic_vector(7 DOWNTO 0);
    avl_writedata     : OUT std_logic_vector(127 DOWNTO 0);
    avl_address       : OUT std_logic_vector(27 DOWNTO 0);
    avl_write, avl_read : OUT std_logic;
    avl_byteenable    : OUT std_logic_vector(15 DOWNTO 0));
END ENTITY;

ARCHITECTURE rtl OF pa2122_min IS
  SIGNAL o_r, o_g, o_b : unsigned(7 DOWNTO 0);
BEGIN
  o_rgb <= std_logic_vector(o_r) & std_logic_vector(o_g) & std_logic_vector(o_b);

  u_ascal : ENTITY work.ascal
    GENERIC MAP (
      MASK => x"FF", RAMBASE => x"0000_0000", RAMSIZE => x"0080_0000",
      INTER => false, HEADER => false, DOWNSCALE => false, BYTESWAP => false,
      PALETTE => false, PALETTE2 => false, ADAPTIVE => false,
      FRAC => 8, OHRES => 2304, IHRES => 1024,
      N_DW => 128, N_AW => 28, N_BURST => 2048)
    PORT MAP (
      i_r => unsigned(i_rgb(23 DOWNTO 16)),
      i_g => unsigned(i_rgb(15 DOWNTO 8)),
      i_b => unsigned(i_rgb(7 DOWNTO 0)),
      i_hs => i_hs, i_vs => i_vs, i_fl => '0',
      i_de => i_de, i_ce => i_ce, i_clk => i_clk,
      o_r => o_r, o_g => o_g, o_b => o_b,
      o_hs => o_hs, o_vs => o_vs, o_de => o_de,
      o_vbl => OPEN, o_brd => OPEN, o_ce => '1', o_clk => o_clk,
      o_lltune => OPEN, i_hdmax => OPEN, i_vdmax => OPEN,
      iauto => '1', run => '1', freeze => '0',
      mode => unsigned(mode_i),
      htotal => 1650, hsstart => 1390, hsend => 1430, hdisp => 1280,
      hmin => 160, hmax => 1119,
      vtotal => 750, vsstart => 725, vsend => 730, vdisp => 720,
      vmin => 0, vmax => 719,
      format => "01",
      poly_clk => avl_clk, poly_dw => (OTHERS => '0'),
      poly_a => (OTHERS => '0'), poly_wr => '0',
      avl_clk => avl_clk, avl_waitrequest => avl_waitrequest,
      avl_readdata => avl_readdata, avl_readdatavalid => avl_readdatavalid,
      avl_burstcount => avl_burstcount, avl_writedata => avl_writedata,
      avl_address => avl_address, avl_write => avl_write,
      avl_read => avl_read, avl_byteenable => avl_byteenable,
      reset_na => reset_na);
END ARCHITECTURE;
