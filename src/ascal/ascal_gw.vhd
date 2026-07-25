--------------------------------------------------------------------------------
-- ascal_gw - Gowin/Tang wrapper around Temlib's ascal.vhd (MiSTer's scaler)
--------------------------------------------------------------------------------
-- Vendored 2026-07-25 from refs/Template_MiSTer/sys/ascal.vhd (byte-identical
-- to Arcade-MCR3_MiSTer's copy and to upstream master).  ascal itself is
-- UNMODIFIED - keep it that way so upstream fixes drop straight in; every
-- adaptation lives here.
--
-- Why a wrapper at all:
--   * ascal's generics are `unsigned(31 DOWNTO 0)` / VHDL naturals.  Passing
--     those across the mixed-language boundary from a SystemVerilog top is
--     asking for trouble on GowinSynthesis, so they are pinned here instead.
--   * ascal's ports are `unsigned` and VHDL `natural`; the top wants plain
--     std_logic_vector.
--   * The output video *timing* is a set of ~12 naturals.  They are wired to
--     generics here (720p by default) with only the image WINDOW left as a
--     runtime port, which is what you actually want to tweak live.
--
-- MEASURED cost on GW5AT-LV60 (synthesis only, this configuration):
--   MASK=FF (all 5 interpolators)   3274 logic / 2186 reg / 23 BSRAM / 51 DSP
--   MASK=07 (no bicubic/polyphase)  2263 logic / 1794 reg / 23 BSRAM / 25 DSP
-- BSRAM is dominated by the OHRES-sized output line buffers and is NOT
-- reduced by dropping interpolators.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY ascal_gw IS
  GENERIC (
    -- Which interpolators to build. Bit0 Nearest, 1 Bilinear, 2 SharpBilinear,
    -- 3 Bicubic, 4 Polyphase.  Dropping 3+4 saves ~1000 LUT and 26 DSP.
    MASK      : unsigned(7 DOWNTO 0) := x"FF";
    RAMBASE   : unsigned(31 DOWNTO 0) := x"0000_0000";
    RAMSIZE   : unsigned(31 DOWNTO 0) := x"0080_0000";  -- 8 MB per buffer
    OHRES     : natural := 2048;   -- >= output width (1280 -> 2048)
    IHRES     : natural := 1024;   -- >= input width  (512 -> 1024)
    N_DW      : natural := 128;    -- Gowin DDR3 app data width
    N_AW      : natural := 25;     -- 16-byte word address -> 25b = 512 MB
    N_BURST   : natural := 256;    -- bytes per burst -> BLEN = 16 words
    -- Output timing.  Defaults = 1280x720p60 (74.25 MHz).
    --   SYNC |_______________________/"""""\_____|
    --   DE   |""""""""""\________________________|
    --             ^HMIN ^HMAX   ^HSSTART ^HSEND  ^HTOTAL
    G_HTOTAL  : natural := 1650;
    G_HSSTART : natural := 1390;
    G_HSEND   : natural := 1430;
    G_HDISP   : natural := 1280;
    G_VTOTAL  : natural := 750;
    G_VSSTART : natural := 725;
    G_VSEND   : natural := 730;
    G_VDISP   : natural := 720
  );
  PORT (
    ------------------------------------------------ input video (core domain)
    i_clk    : IN  std_logic;
    i_ce     : IN  std_logic;                       -- pixel clock enable
    i_r      : IN  std_logic_vector(7 DOWNTO 0);
    i_g      : IN  std_logic_vector(7 DOWNTO 0);
    i_b      : IN  std_logic_vector(7 DOWNTO 0);
    i_hs     : IN  std_logic;                       -- NOTE: ascal ignores this
    i_vs     : IN  std_logic;
    i_de     : IN  std_logic;
    i_fl     : IN  std_logic := '0';                -- interlaced field

    ----------------------------------------------- output video (hclk domain)
    o_clk    : IN  std_logic;
    o_r      : OUT std_logic_vector(7 DOWNTO 0);
    o_g      : OUT std_logic_vector(7 DOWNTO 0);
    o_b      : OUT std_logic_vector(7 DOWNTO 0);
    o_hs     : OUT std_logic;
    o_vs     : OUT std_logic;
    o_de     : OUT std_logic;

    ------------------------------------------------------------ control
    -- mode[2:0] 0=Nearest 1=Bilinear 2=SharpBilinear 3=Bicubic 4=Polyphase
    -- mode[3]   0=single buffer (lowest lag) 1=triple buffer (no tearing)
    mode     : IN  std_logic_vector(4 DOWNTO 0);
    run      : IN  std_logic := '1';
    -- Image window inside the output canvas.  For 4:3 inside 720p use
    -- hmin=160 hmax=1119 (=960 wide), vmin=0 vmax=719.
    hmin     : IN  std_logic_vector(11 DOWNTO 0);
    hmax     : IN  std_logic_vector(11 DOWNTO 0);
    vmin     : IN  std_logic_vector(11 DOWNTO 0);
    vmax     : IN  std_logic_vector(11 DOWNTO 0);
    -- Detected input size, for the UART beacon / OSD readout
    i_hdmax  : OUT std_logic_vector(11 DOWNTO 0);
    i_vdmax  : OUT std_logic_vector(11 DOWNTO 0);

    ------------------------------------------- polyphase coefficient load
    poly_clk : IN  std_logic := '0';
    poly_a   : IN  std_logic_vector(7 DOWNTO 0) := (OTHERS => '0');
    poly_dw  : IN  std_logic_vector(9 DOWNTO 0) := (OTHERS => '0');
    poly_wr  : IN  std_logic := '0';

    --------------------------------------------------- Avalon-MM master
    avl_clk           : IN  std_logic;
    avl_waitrequest   : IN  std_logic;
    avl_readdata      : IN  std_logic_vector(N_DW-1 DOWNTO 0);
    avl_readdatavalid : IN  std_logic;
    avl_burstcount    : OUT std_logic_vector(7 DOWNTO 0);
    avl_writedata     : OUT std_logic_vector(N_DW-1 DOWNTO 0);
    avl_address       : OUT std_logic_vector(N_AW-1 DOWNTO 0);
    avl_write         : OUT std_logic;
    avl_read          : OUT std_logic;
    avl_byteenable    : OUT std_logic_vector(N_DW/8-1 DOWNTO 0);

    reset_na          : IN  std_logic                -- async, active low
  );
END ENTITY ascal_gw;

ARCHITECTURE rtl OF ascal_gw IS
  SIGNAL ur, ug, ub : unsigned(7 DOWNTO 0);
  SIGNAL hdmax_i, vdmax_i : natural RANGE 0 TO 4095;
BEGIN

  o_r <= std_logic_vector(ur);
  o_g <= std_logic_vector(ug);
  o_b <= std_logic_vector(ub);
  i_hdmax <= std_logic_vector(to_unsigned(hdmax_i, 12));
  i_vdmax <= std_logic_vector(to_unsigned(vdmax_i, 12));

  u_ascal : ENTITY work.ascal
    GENERIC MAP (
      MASK         => MASK,
      RAMBASE      => RAMBASE,
      RAMSIZE      => RAMSIZE,
      -- Progressive-only source (MCR is 15 kHz 240p or 31 kHz 480p, never
      -- interlaced), no image header (nothing else reads this framebuffer),
      -- no downscaling (we only ever upscale 512x240/480 -> 720p), no
      -- palette (we feed RGB directly).  Each of these costs logic.
      INTER        => false,
      HEADER       => false,
      DOWNSCALE    => false,
      BYTESWAP     => false,
      PALETTE      => false,
      PALETTE2     => false,
      ADAPTIVE     => false,
      DOWNSCALE_NN => false,
      FRAC         => 4,
      OHRES        => OHRES,
      IHRES        => IHRES,
      N_DW         => N_DW,
      N_AW         => N_AW,
      N_BURST      => N_BURST)
    PORT MAP (
      i_r => unsigned(i_r), i_g => unsigned(i_g), i_b => unsigned(i_b),
      i_hs => i_hs, i_vs => i_vs, i_fl => i_fl,
      i_de => i_de, i_ce => i_ce, i_clk => i_clk,

      o_r => ur, o_g => ug, o_b => ub,
      o_hs => o_hs, o_vs => o_vs, o_de => o_de,
      o_vbl => OPEN, o_brd => OPEN,
      o_ce => '1', o_clk => o_clk,

      o_lltune => OPEN,
      i_hdmax => hdmax_i, i_vdmax => vdmax_i,

      iauto => '1',                       -- autodetect the input window
      run => run, freeze => '0',
      mode => unsigned(mode),

      htotal  => G_HTOTAL,  hsstart => G_HSSTART, hsend => G_HSEND,
      hdisp   => G_HDISP,
      hmin    => to_integer(unsigned(hmin)), hmax => to_integer(unsigned(hmax)),
      vtotal  => G_VTOTAL,  vsstart => G_VSSTART, vsend => G_VSEND,
      vdisp   => G_VDISP,
      vmin    => to_integer(unsigned(vmin)), vmax => to_integer(unsigned(vmax)),

      format  => "01",                    -- 24 bpp in RAM

      poly_clk => poly_clk,
      poly_a   => unsigned(poly_a),
      poly_dw  => unsigned(poly_dw),
      poly_wr  => poly_wr,

      avl_clk           => avl_clk,
      avl_waitrequest   => avl_waitrequest,
      avl_readdata      => avl_readdata,
      avl_readdatavalid => avl_readdatavalid,
      avl_burstcount    => avl_burstcount,
      avl_writedata     => avl_writedata,
      avl_address       => avl_address,
      avl_write         => avl_write,
      avl_read          => avl_read,
      avl_byteenable    => avl_byteenable,

      reset_na => reset_na);

END ARCHITECTURE rtl;
