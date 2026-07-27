-- Standalone testbench for the mcr3.vhd sprite machine (copied VERBATIM from
-- src/rtl/mcr3.vhd lines 507-623) + a cycle-accurate model of sdram_gw's sp
-- port (7-cycle rounds @80MHz, CL2, commit at READ1b). Purpose: reproduce the
-- on-hardware artifact where the last-drawn 8px word of every sprite is
-- displaced ~8px right with a transparent gap where it belongs.
-- Tile data: every pixel nibble of word w = w+1, so the rendered scanline
-- shows exactly which fetch word landed at which screen slot.
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use std.textio.all;

entity sp_tb is
  generic ( T0 : integer := 0;          -- SDRAM round phase offset 0..6
            HFLIP_ATTR : integer := 0 );-- 16 = hflip bit set
end entity;

architecture sim of sp_tb is
  signal clock_vid  : std_logic := '0';
  signal clock_vidn : std_logic;
  signal clk80      : std_logic := '0';
  signal done_sim   : boolean := false;

  -- raster
  signal clock_cnt : std_logic_vector(3 downto 0) := (others=>'0');
  signal pix_ena   : std_logic;
  signal hcnt      : std_logic_vector(9 downto 0) := (others=>'0');
  signal vcnt      : std_logic_vector(9 downto 0) := (others=>'0');
  constant tv15Khz_mode : std_logic := '0';
  constant video_hflip  : std_logic := '0';
  constant video_vflip  : std_logic := '0';
  constant top_frame    : std_logic := '1';
  signal cpu_addr : std_logic_vector(15 downto 0) := (others=>'0');

  -- sprite machine signals (verbatim names from mcr3.vhd)
  signal hflip      : std_logic_vector(9 downto 0);
  signal vflip      : std_logic_vector(9 downto 0);
  signal vflip_base : std_logic_vector(9 downto 0);
  signal sp_cnt          : std_logic_vector(6 downto 0) := (others=>'0');
  signal sp_input_phase  : std_logic_vector(5 downto 0) := (others=>'0');
  signal sp_on_line      : std_logic := '0';
  signal sp_done         : std_logic := '0';
  signal sp_vcnt         : std_logic_vector(9 downto 0);
  signal sp_line         : std_logic_vector(4 downto 0) := (others=>'0');
  signal sp_byte_cnt     : std_logic_vector(1 downto 0) := (others=>'0');
  signal sp_attr         : std_logic_vector(7 downto 0) := (others=>'0');
  signal sp_code         : std_logic_vector(7 downto 0) := (others=>'0');
  signal sp_hcnt         : std_logic_vector(8 downto 0) := (others=>'0');
  signal sp_hflip        : std_logic_vector(1 downto 0);
  signal sp_vflip        : std_logic_vector(4 downto 0);
  signal sp_mux_roms     : std_logic_vector(1 downto 0) := (others=>'0');
  signal sp_graphx_do    : std_logic_vector(7 downto 0);
  signal sp_graphx32_do_r: std_logic_vector(31 downto 0) := (others=>'0');
  signal sp_graphx_a     : std_logic_vector(3 downto 0);
  signal sp_graphx_b     : std_logic_vector(3 downto 0);
  signal sp_graphx_a_ok  : std_logic;
  signal sp_graphx_b_ok  : std_logic;
  signal sp_addr         : std_logic_vector(14 downto 0) := (others=>'0');
  signal sp_graphx32_do  : std_logic_vector(31 downto 0) := (others=>'0');
  signal sp_ram_addr     : std_logic_vector(8 downto 0);
  signal sp_ram_we       : std_logic;
  signal sp_ram_do       : std_logic_vector(7 downto 0) := (others=>'0');
  signal move_buf        : std_logic;

  signal sp_buffer_ram1_addr : std_logic_vector(7 downto 0);
  signal sp_buffer_ram1a_we  : std_logic;
  signal sp_buffer_ram1b_we  : std_logic;
  signal sp_buffer_ram1a_di  : std_logic_vector(7 downto 0);
  signal sp_buffer_ram1b_di  : std_logic_vector(7 downto 0);
  signal sp_buffer_ram1a_do  : std_logic_vector(7 downto 0) := (others=>'0');
  signal sp_buffer_ram1b_do  : std_logic_vector(7 downto 0) := (others=>'0');
  signal sp_buffer_ram1_do_r : std_logic_vector(15 downto 0) := (others=>'0');
  signal sp_buffer_ram2_addr : std_logic_vector(7 downto 0);
  signal sp_buffer_ram2a_we  : std_logic;
  signal sp_buffer_ram2b_we  : std_logic;
  signal sp_buffer_ram2a_di  : std_logic_vector(7 downto 0);
  signal sp_buffer_ram2b_di  : std_logic_vector(7 downto 0);
  signal sp_buffer_ram2a_do  : std_logic_vector(7 downto 0) := (others=>'0');
  signal sp_buffer_ram2b_do  : std_logic_vector(7 downto 0) := (others=>'0');
  signal sp_buffer_ram2_do_r : std_logic_vector(15 downto 0) := (others=>'0');
  signal sp_buffer_sel       : std_logic;
  signal sp_vid : std_logic_vector(3 downto 0);
  signal sp_col : std_logic_vector(3 downto 0);

  -- sprite list ram model (entry0 = the sprite, rest y=0)
  type ram512 is array(0 to 511) of std_logic_vector(7 downto 0);
  function init_list return ram512 is
    variable r : ram512 := (others => (others=>'0'));
  begin
    r(0) := x"C8";  -- y = 200
    if HFLIP_ATTR = 16 then r(1) := x"10"; else r(1) := x"00"; end if; -- attr
    r(2) := x"01";  -- code
    r(3) := x"20";  -- x = 32 -> sp_hcnt 64
    return r;
  end function;
  signal list_ram : ram512 := init_list;

  -- SDRAM sp-port model
  signal sd_t       : integer range 0 to 6 := T0;
  signal sd_last    : std_logic_vector(14 downto 0) := (others=>'1');
  signal sd_oe      : std_logic := '0';
  signal sd_alat    : std_logic_vector(14 downto 0) := (others=>'0');
  signal sd_qlo     : std_logic_vector(15 downto 0) := (others=>'0');

  -- tile data: word w of any line -> 8 nibbles of value w+1
  function tile_word(addr : std_logic_vector(14 downto 0)) return std_logic_vector is
    variable n : std_logic_vector(3 downto 0);
    variable w : std_logic_vector(31 downto 0);
  begin
    case addr(1 downto 0) is
      when "00" => n := x"1";
      when "01" => n := x"2";
      when "10" => n := x"3";
      when others => n := x"4";
    end case;
    w := n&n&n&n&n&n&n&n;
    return w;
  end function;

begin
  clock_vid  <= not clock_vid after 12500 ps when not done_sim else '0';
  clock_vidn <= not clock_vid;
  clk80      <= not clk80 after 6250 ps when not done_sim else '0';

  -- raster (from mcr3.vhd process, 31kHz progressive)
  process(clock_vid)
  begin
    if rising_edge(clock_vid) then
      clock_cnt <= clock_cnt + 1;
      if pix_ena = '1' then
        hcnt <= hcnt + 1;
        if hcnt = 633 then
          hcnt <= (others=>'0');
          vcnt <= vcnt + 1;
          if vcnt = 524 then vcnt <= (others=>'0'); end if;
        end if;
      end if;
    end if;
  end process;
  pix_ena <= '1' when clock_cnt(0) = '1' else '0';

  ---------------------------------------------------------------------------
  -- SDRAM sp port model: 7-cycle round @80MHz. RAS1 at t=4 launches when
  -- sp_addr != last; commit q_lo at t=2, full sp_q at t=3 of the next round.
  ---------------------------------------------------------------------------
  process(clk80)
  begin
    if rising_edge(clk80) then
      if sd_t = 6 then sd_t <= 0; else sd_t <= sd_t + 1; end if;
      if sd_t = 4 then
        sd_oe <= '0';
        if sp_addr /= sd_last then
          sd_last <= sp_addr;
          sd_alat <= sp_addr;
          sd_oe   <= '1';
        end if;
      elsif sd_t = 2 and sd_oe = '1' then
        sd_qlo <= tile_word(sd_alat)(15 downto 0);
      elsif sd_t = 3 and sd_oe = '1' then
        sp_graphx32_do <= tile_word(sd_alat)(31 downto 16) & sd_qlo;
      end if;
    end if;
  end process;

  ---------------------------------------------------------------------------
  -- sprite machine: VERBATIM from mcr3.vhd
  ---------------------------------------------------------------------------
  hflip <= hcnt when video_hflip = '0' else not hcnt;
  vflip <= vflip_base when video_vflip = '0' else "0111011111" - vflip_base;
  vflip_base <= vcnt(8 downto 0) & not top_frame when tv15Khz_mode = '1' else vcnt;

  sp_buffer_sel <= vflip(1) when tv15Khz_mode = '1' else vflip(0);

  process (clock_vid)
  begin
    if rising_edge(clock_vid) then
      if hcnt = 0 then
        sp_cnt <= (others => '0');
        sp_input_phase <= (others => '0');
        sp_on_line <= '0';
        sp_done <= '0';
      end if;

      if sp_done = '0' then
        sp_input_phase <= sp_input_phase + 1;
        if sp_input_phase >= 10 then sp_hcnt <= sp_hcnt + 1; end if;

        case sp_input_phase is
          when "000000" =>
            if sp_vcnt(8 downto 5) = x"F" then
              sp_line <= sp_vcnt(4 downto 0);
            else
              sp_input_phase <= (others => '0');
              sp_cnt <= sp_cnt + 1;
              if sp_cnt = "1111111" then sp_done <= '1'; end if;
            end if;
            sp_byte_cnt <= (others => '0');
          when "000001" =>
            sp_attr <= sp_ram_do;
          when "000010" =>
            sp_code <= sp_ram_do;
            sp_addr <= sp_ram_do(7 downto 0) & (sp_line xor sp_vflip) & (sp_byte_cnt xor sp_hflip);
          when "000011" =>
            sp_hcnt <= sp_ram_do & '0';
          when "001010" =>
            sp_graphx32_do_r <= sp_graphx32_do;
            sp_addr <= sp_code(7 downto 0) & (sp_line xor sp_vflip) & (sp_byte_cnt+1 xor sp_hflip);
            sp_on_line <= '1';
          when "010010"|"011010"|"100010" =>
            sp_graphx32_do_r <= sp_graphx32_do;
            sp_addr <= sp_code(7 downto 0) & (sp_line xor sp_vflip) & (sp_byte_cnt+2 xor sp_hflip);
            sp_byte_cnt <= sp_byte_cnt + 1;
          when "101010" =>
            sp_on_line <= '0';
            sp_input_phase <= (others => '0');
            sp_cnt <= sp_cnt + 1;
            if sp_cnt = "1111111" then sp_done <= '1'; end if;
          when others =>
            null;
        end case;
        sp_mux_roms <= sp_input_phase(2 downto 1);
      end if;

      if pix_ena = '1' then
        if hcnt(0) = '0' then
          sp_buffer_ram1_do_r <= sp_buffer_ram1b_do & sp_buffer_ram1a_do;
          sp_buffer_ram2_do_r <= sp_buffer_ram2b_do & sp_buffer_ram2a_do;
        end if;
      end if;
    end if;
  end process;

  move_buf <= '1' when (vcnt(8 downto 1) = 250 and tv15Khz_mode = '0') else '0';
  sp_ram_addr <= vcnt(0) & hcnt(8 downto 1) when move_buf = '1' else sp_cnt & sp_input_phase(1 downto 0);
  sp_ram_we   <= hcnt(0) when move_buf = '1' else '0';

  sp_vcnt <= vflip + (sp_ram_do & '0') -1;

  sp_hflip <= (others => sp_attr(4));
  sp_vflip <= (others => sp_attr(5));

  sp_graphx_do <= sp_graphx32_do_r( 7 downto  0) when (sp_hflip(0) = '0' and sp_mux_roms = "01") or (sp_hflip(0) = '1' and sp_mux_roms = "00") else
                  sp_graphx32_do_r(15 downto  8) when (sp_hflip(0) = '0' and sp_mux_roms = "10") or (sp_hflip(0) = '1' and sp_mux_roms = "11") else
                  sp_graphx32_do_r(23 downto 16) when (sp_hflip(0) = '0' and sp_mux_roms = "11") or (sp_hflip(0) = '1' and sp_mux_roms = "10") else
                  sp_graphx32_do_r(31 downto 24);

  sp_graphx_a <= sp_graphx_do(7 downto 4) when sp_hflip(0) = '1' else sp_graphx_do(3 downto 0);
  sp_graphx_b <= sp_graphx_do(3 downto 0) when sp_hflip(0) = '1' else sp_graphx_do(7 downto 4);

  sp_graphx_a_ok <= '1' when sp_graphx_a /= x"0" else '0';
  sp_graphx_b_ok <= '1' when sp_graphx_b /= x"0" else '0';

  sp_buffer_ram1a_di  <= sp_attr(3 downto 0) & sp_graphx_a                when sp_buffer_sel = '1' else x"00";
  sp_buffer_ram1b_di  <= sp_attr(3 downto 0) & sp_graphx_b                when sp_buffer_sel = '1' else x"00";
  sp_buffer_ram1_addr <= sp_hcnt(8 downto 1)                              when sp_buffer_sel = '1' else hflip(8 downto 1) + x"0C" when video_hflip = '1' else hflip(8 downto 1) - x"04";
  sp_buffer_ram1a_we  <= (not sp_hcnt(0)) and sp_on_line and sp_graphx_a_ok when sp_buffer_sel = '1' else hcnt(0);
  sp_buffer_ram1b_we  <= (not sp_hcnt(0)) and sp_on_line and sp_graphx_b_ok when sp_buffer_sel = '1' else hcnt(0);

  sp_buffer_ram2a_di  <= sp_attr(3 downto 0) & sp_graphx_a                when sp_buffer_sel = '0' else x"00";
  sp_buffer_ram2b_di  <= sp_attr(3 downto 0) & sp_graphx_b                when sp_buffer_sel = '0' else x"00";
  sp_buffer_ram2_addr <= sp_hcnt(8 downto 1)                              when sp_buffer_sel = '0' else hflip(8 downto 1) + x"0C" when video_hflip = '1' else hflip(8 downto 1) - x"04";
  sp_buffer_ram2a_we  <= (not sp_hcnt(0)) and sp_on_line and sp_graphx_a_ok when sp_buffer_sel = '0' else hcnt(0);
  sp_buffer_ram2b_we  <= (not sp_hcnt(0)) and sp_on_line and sp_graphx_b_ok when sp_buffer_sel = '0' else hcnt(0);

  sp_vid <= sp_buffer_ram1_do_r(11 downto  8) when (sp_buffer_sel = '0') and (hflip(0) = '1') else
            sp_buffer_ram1_do_r( 3 downto  0) when (sp_buffer_sel = '0') and (hflip(0) = '0') else
            sp_buffer_ram2_do_r(11 downto  8) when (sp_buffer_sel = '1') and (hflip(0) = '1') else
            sp_buffer_ram2_do_r( 3 downto  0);

  sp_col <= sp_buffer_ram1_do_r(15 downto 12) when (sp_buffer_sel = '0') and (hflip(0) = '1') else
            sp_buffer_ram1_do_r( 7 downto  4) when (sp_buffer_sel = '0') and (hflip(0) = '0') else
            sp_buffer_ram2_do_r(15 downto 12) when (sp_buffer_sel = '1') and (hflip(0) = '1') else
            sp_buffer_ram2_do_r( 7 downto  4);

  ---------------------------------------------------------------------------
  -- memories (gen_ram semantics: falling edge = clock_vidn rising)
  ---------------------------------------------------------------------------
  -- sprite list ram (sprite_ram in mcr3): read-only here, preloaded
  process(clock_vidn)
  begin
    if rising_edge(clock_vidn) then
      sp_ram_do <= list_ram(conv_integer(sp_ram_addr));
    end if;
  end process;

  blk_buf : block
    signal ram1a, ram1b, ram2a, ram2b : ram512 := (others => (others=>'0'));
  begin
    process(clock_vidn)
    begin
      if rising_edge(clock_vidn) then
        if sp_buffer_ram1a_we = '1' then
          ram1a(conv_integer(sp_buffer_ram1_addr)) <= sp_buffer_ram1a_di;
          sp_buffer_ram1a_do <= sp_buffer_ram1a_di;
        else
          sp_buffer_ram1a_do <= ram1a(conv_integer(sp_buffer_ram1_addr));
        end if;
        if sp_buffer_ram1b_we = '1' then
          ram1b(conv_integer(sp_buffer_ram1_addr)) <= sp_buffer_ram1b_di;
          sp_buffer_ram1b_do <= sp_buffer_ram1b_di;
        else
          sp_buffer_ram1b_do <= ram1b(conv_integer(sp_buffer_ram1_addr));
        end if;
        if sp_buffer_ram2a_we = '1' then
          ram2a(conv_integer(sp_buffer_ram2_addr)) <= sp_buffer_ram2a_di;
          sp_buffer_ram2a_do <= sp_buffer_ram2a_di;
        else
          sp_buffer_ram2a_do <= ram2a(conv_integer(sp_buffer_ram2_addr));
        end if;
        if sp_buffer_ram2b_we = '1' then
          ram2b(conv_integer(sp_buffer_ram2_addr)) <= sp_buffer_ram2b_di;
          sp_buffer_ram2b_do <= sp_buffer_ram2b_di;
        else
          sp_buffer_ram2b_do <= ram2b(conv_integer(sp_buffer_ram2_addr));
        end if;
      end if;
    end process;
  end block;

  ---------------------------------------------------------------------------
  -- capture: print sp_vid per pixel for scanlines 84..87 of frame 2
  ---------------------------------------------------------------------------
  process(clock_vid)
    variable l : line;
    variable frame : integer := 0;
    variable lastv : integer := -1;
    variable started : boolean := false;
  begin
    if rising_edge(clock_vid) then
      if conv_integer(vcnt) /= lastv then
        if conv_integer(vcnt) = 0 and lastv > 0 then frame := frame + 1; end if;
        lastv := conv_integer(vcnt);
        if frame = 1 and lastv >= 84 and lastv <= 87 then
          started := true;
          write(l, string'("LINE "));
          write(l, lastv);
          write(l, string'(" "));
        elsif started then
          writeline(output, l);
          started := false;
          if lastv > 87 then
            done_sim <= true;
          end if;
        end if;
      end if;
      if started and pix_ena = '1' then
        if sp_vid = x"0" then
          write(l, string'("."));
        else
          write(l, conv_integer(sp_vid));
        end if;
      end if;
    end if;
  end process;

  process(clock_vid)
    variable l2 : line;
  begin
    if rising_edge(clock_vid) then
      if conv_integer(vcnt) = 84 then
        if false then
          write(l2, string'("DBG h=")); write(l2, conv_integer(hcnt));
          write(l2, string'(" ph=")); write(l2, conv_integer(sp_input_phase));
          write(l2, string'(" cnt=")); write(l2, conv_integer(sp_cnt));
          write(l2, string'(" onl=")); write(l2, std_logic'image(sp_on_line));
          write(l2, string'(" shc=")); write(l2, conv_integer(sp_hcnt));
          write(l2, string'(" do=")); write(l2, conv_integer(sp_ram_do));
          write(l2, string'(" done=")); write(l2, std_logic'image(sp_done));
          write(l2, string'(" svc=")); write(l2, conv_integer(sp_vcnt));
          writeline(output, l2);
        end if;
      end if;
    end if;
  end process;

end architecture;
-- debug monitor appended by hand: report engine activity on line 84
