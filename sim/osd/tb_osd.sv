// OSD roster/scrolling testbench.
//
// The menu grew from a fixed 6-row list to a 16-slot scrolling one, and a
// hardware round-trip is a ~20 minute build - so the row->roster mapping,
// the scroll follow and the '>'/'*'/'^'/'V' markers are pinned here instead.
//
//   iverilog -g2012 -I../../src/rtl -o tb_osd tb_osd.sv ../../src/rtl/osd.sv
//   ./tb_osd            (run from sim/osd; osd_font.hex is symlinked in)
//
// It drives a real MCR raster (634x525, hblank per line, vblank at 480) and
// scrapes the 24x14 character grid straight out of the render pipeline.
`timescale 1ns/1ps
module tb_osd;

  parameter NG = 12;               // override: iverilog -Ptb_osd.NG=3

  reg clk = 0;
  always #12.5 clk = ~clk;         // 40 MHz

  reg        rst = 1;
  reg        pixel_tick = 0;
  reg [9:0]  hcnt = 0;
  reg        hblank = 0, vblank = 0;
  reg        b_up = 0, b_dn = 0, b_a = 0, b_b = 0, b_sel = 0, b_sta = 0;
  wire [4:0] game_id;
  wire [8:0] rgb_out;
  wire       osd_active, osd_nocard;

  osd #(
    .GAME_DEFAULT(5'd0), .NUM_GAMES(NG[5:0]), .ROT_MASK(20'h00000),
    .TITLE ("  MERGED GAME SELECT    "),
    .NAME0 ("   AAAA                 "), .NAME1 ("   BBBB                 "),
    .NAME2 ("   CCCC                 "), .NAME3 ("   DDDD                 "),
    .NAME4 ("   EEEE                 "), .NAME5 ("   FFFF                 "),
    .NAME6 ("   GGGG                 "), .NAME7 ("   HHHH                 "),
    .NAME8 ("   IIII                 "), .NAME9 ("   JJJJ                 "),
    .NAME10("   KKKK                 "), .NAME11("   LLLL                 "),
    .NAME12("   MMMM                 "), .NAME13("   NNNN                 "),
    .NAME14("   OOOO                 "), .NAME15("   PPPP                 "),
    .NAME16("   QQQQ                 "), .NAME17("   RRRR                 "),
    .NAME18("   SSSS                 "), .NAME19("   TTTT                 ")
  ) dut (
    .clk(clk), .rst(rst),
    .pixel_tick(pixel_tick), .hcnt(hcnt), .hblank(hblank), .vblank(vblank),
    .mode15(1'b0), .rgb_in(9'h000), .rgb_out(rgb_out),
    .btn_up(b_up), .btn_down(b_dn), .btn_a(b_a), .btn_b(b_b),
    .btn_sel(b_sel), .btn_sta(b_sta), .btn_menu_hold(1'b0),
    .game_id(game_id), .load_slot(), .loader_restart(),
    .loader_done(1'b1), .loader_error(1'b0), .loaded_slot(4'd0),
    .save_req(), .sd_ready(1'b1),
    .osd_active(osd_active), .osd_nocard(osd_nocard)
  );

  // scraped character grid
  reg [7:0] grid [0:13][0:23];
  integer   r, c;
  task clear_grid; begin
    for (r = 0; r < 14; r = r + 1)
      for (c = 0; c < 24; c = c + 1) grid[r][c] = " ";
  end endtask

  // one full frame of MCR-ish raster; scrape while it goes by
  integer line, px;
  task run_frame(input do_scrape); begin
    for (line = 0; line < 525; line = line + 1) begin
      vblank = (line >= 480);
      for (px = 0; px < 634; px = px + 1) begin
        @(posedge clk);
        hcnt       = px[9:0];
        hblank     = (px >= 512);
        pixel_tick = 1'b1;
        @(posedge clk);
        pixel_tick = 1'b0;
        if (do_scrape && dut.p1_in && dut.p1_row < 14 && dut.p1_col < 24)
          grid[dut.p1_row][dut.p1_col] = dut.ch;
      end
    end
  end endtask

  task show(input [255:0] label); begin
    $display("\n--- %0s  (cursor=%0d scroll=%0d) ---", label, dut.cursor, dut.scroll);
    for (r = 0; r < 14; r = r + 1) begin
      $write("  %2d |", r);
      for (c = 0; c < 24; c = c + 1) $write("%c", grid[r][c]);
      $write("|\n");
    end
  end endtask

  task press(input which);  // 0=down 1=up
    begin
      if (which) b_up = 1; else b_dn = 1;
      run_frame(0);
      b_up = 0; b_dn = 0;
      run_frame(0);
    end
  endtask

  integer errors = 0;
  task expect_row(input integer row, input [7:0] first_letter, input [255:0] what);
    begin
      if (grid[row][3] !== first_letter) begin
        $display("FAIL: %0s - row %0d col3 = '%c', expected '%c'",
                 what, row, grid[row][3], first_letter);
        errors = errors + 1;
      end
    end
  endtask

  initial begin
    clear_grid;
    repeat (10) @(posedge clk);
    rst = 0;
    run_frame(0);

    // Short rosters (what ships today: MCR-1/MCR-3 = 3, MCR-2 = 6) must show
    // NO ghost rows from the unused NAME defaults and NO scroll hints.
    // open the menu (Select+Start)
    b_sel = 1; b_sta = 1; run_frame(0);
    b_sel = 0; b_sta = 0; run_frame(0);
    clear_grid; run_frame(1);
    show("menu open, top of a 12-game roster");
    for (r = 3; r <= 10; r = r + 1)
      if ((r - 3) >= NG && grid[r][3] !== " ") begin
        $display("FAIL: ghost row %0d shows '%c' beyond NUM_GAMES=%0d",
                 r, grid[r][3], NG); errors = errors + 1;
      end
    if (NG <= 8 && grid[10][22] === "V") begin
      $display("FAIL: 'V' hint shown but roster fits on screen"); errors=errors+1;
    end
    if (NG == 17) begin
      // full series (MCR-1 3 + MCR-2 7 + MCR-3 4 + Scroll 3): walk to the end
      repeat (16) press(0);
      clear_grid; run_frame(1);
      show("17-game full-series roster, cursor at the end");
      expect_row(10, "Q", "row10 = entry 16 (last of 17)");
      if (grid[10][22] === "V") begin
        $display("FAIL: 'V' hint still shown at the end of the list");
        errors = errors + 1;
      end
      if (grid[3][22] !== "^") begin
        $display("FAIL: no '^' hint while scrolled to the bottom");
        errors = errors + 1;
      end
      $display("%0s (%0d errors) [NG=17 full series]", errors ? "*** FAILURES ***" : "PASS: full-series roster", errors);
      $finish;
    end
    if (NG != 12) begin
      $display("%0s (%0d errors) [NG=%0d]", errors ? "*** FAILURES ***" : "PASS: short roster", errors, NG);
      $finish;
    end
    expect_row(3,  "A", "row3 = entry 0");
    expect_row(10, "H", "row10 = entry 7 (8 visible)");
    if (grid[3][1] !== ">") begin $display("FAIL: cursor '>' not on row 3"); errors=errors+1; end
    if (grid[3][17] !== "*") begin $display("FAIL: running '*' not on row 3"); errors=errors+1; end
    if (grid[10][22] !== "V") begin $display("FAIL: no 'V' more-below hint"); errors=errors+1; end

    // walk down past the visible window -> must scroll
    repeat (9) press(0);
    clear_grid; run_frame(1);
    show("after 9x DOWN (cursor 9, list scrolled)");
    expect_row(3,  "C", "scrolled: row3 = entry 2");
    expect_row(10, "J", "scrolled: row10 = entry 9");
    if (grid[3][22] !== "^") begin $display("FAIL: no '^' more-above hint"); errors=errors+1; end

    // wrap off the bottom -> back to the top
    repeat (3) press(0);
    clear_grid; run_frame(1);
    show("after wrap past the end");
    expect_row(3, "A", "wrapped: row3 = entry 0");
    if (dut.scroll !== 0) begin $display("FAIL: scroll not reset on wrap"); errors=errors+1; end

    // wrap upwards off the top -> jump to the end of the list
    press(1);
    clear_grid; run_frame(1);
    show("after UP from entry 0 (wrap to end)");
    expect_row(10, "L", "wrap-up: row10 = entry 11 (last)");

    $display("\n%0s (%0d errors)", errors ? "*** FAILURES ***" : "PASS: osd roster", errors);
    $finish;
  end
endmodule
