#!/usr/bin/env bash
# Headless Gowin build wrapper (macOS + Linux).
#
#   tools/gw_build.sh mcr2_console60k            # build one board
#   tools/gw_build.sh mcr2_console60k domino     # merge_roms first, then build
#
# Both hosts need environment fix-ups before gw_sh will run; this centralises
# them so the invocation is the same everywhere. See CLAUDE.md "Build".
set -euo pipefail

BOARD="${1:?usage: tools/gw_build.sh <board_dir> [game]}"
GAME="${2:-}"
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

[ -d "$ROOT/$BOARD" ] || { echo "no such board dir: $BOARD" >&2; exit 1; }

if [ -n "$GAME" ]; then
  ( cd "$ROOT" && python3 tools/merge_roms.py "$GAME" )
fi

case "$(uname -s)" in
  Darwin)
    GWROOT="${GOWIN_HOME:-/Applications/GowinIDE.app/Contents/Resources/Gowin_EDA/IDE}"
    export DYLD_LIBRARY_PATH="$GWROOT/lib" DYLD_FRAMEWORK_PATH="$GWROOT/lib"
    ;;
  Linux)
    GWROOT="${GOWIN_HOME:-$HOME/IDE}"
    # 1. gw_sh's RPATH prefers its own ancient libfreetype, which the system
    #    libfontconfig then fails against (undefined symbol FT_Done_MM_Var).
    #    Preloading the system freetype wins the symbol back.
    # 2. The bundled Qt plugins have no RPATH, so without LD_LIBRARY_PATH they
    #    load the *system* Qt and abort ("Cannot mix incompatible Qt library").
    # 3. gw_sh builds a QApplication even headless -> needs a QPA platform.
    FT="$(ls /usr/lib/*-linux-gnu/libfreetype.so.6 2>/dev/null | head -1)"
    export LD_LIBRARY_PATH="$GWROOT/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
    [ -n "$FT" ] && export LD_PRELOAD="$FT${LD_PRELOAD:+:$LD_PRELOAD}"
    export QT_QPA_PLATFORM=offscreen
    ;;
  *) echo "unsupported host: $(uname -s)" >&2; exit 1 ;;
esac

GW="$GWROOT/bin/gw_sh"
[ -x "$GW" ] || { echo "gw_sh not found at $GW (set GOWIN_HOME)" >&2; exit 1; }

cd "$ROOT/$BOARD"
"$GW" build.tcl
