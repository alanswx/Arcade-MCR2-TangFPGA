#!/usr/bin/env bash
# Build with the COMMERCIAL Gowin V1.9.12.03 in ~/gowin_1.9.12.03 (licence at
# ~/gowin_1.9.12.03/gowin.lic, node-locked). The free 1.9.11.03 in ~/IDE is
# untouched; use tools/gw_build.sh for that one.
set -euo pipefail
BOARD="${1:?usage: tools/gw_build_1912.sh <board_dir> [tcl]}"
TCL="${2:-build.tcl}"
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
GWROOT="${GOWIN_1912:-$HOME/gowin_1.9.12.03/IDE}"
FT="$(ls /usr/lib/*-linux-gnu/libfreetype.so.6 2>/dev/null | head -1)"
export LD_LIBRARY_PATH="$GWROOT/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
[ -n "$FT" ] && export LD_PRELOAD="$FT${LD_PRELOAD:+:$LD_PRELOAD}"
export QT_QPA_PLATFORM=offscreen
unset DISPLAY WAYLAND_DISPLAY || true
cd "$ROOT/$BOARD"
"$GWROOT/bin/gw_sh" "$TCL"
