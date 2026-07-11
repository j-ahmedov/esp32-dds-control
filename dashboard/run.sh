#!/usr/bin/env bash
# One-command launcher for the Smart-Home DDS web dashboard.
#   1) builds the host tools if needed
#   2) starts the NATIVE XRCE agent if not already running
#   3) opens the dashboard in your browser and runs the bridge server
#
# Uses the NATIVE agent (not Docker): Docker Desktop's UDP forwarding to the LAN
# is unreliable on macOS, so the ESP32 often can't reach a Docker agent. The
# native agent binds the Mac's real port 8888 and the board reaches it directly.
#
# You still need the ESP32 powered & connected — press its RST button once so it
# joins the agent. Then use the buttons/sliders in the browser. Ctrl-C to stop.
set -e
HERE="$(cd "$(dirname "$0")" && pwd)"
TOOLS="$HERE/../smart_home_dds/host_tools"
AGENT_BIN="$HOME/esp/Micro-XRCE-DDS-Agent/build/MicroXRCEAgent"

# 1) host tools
if [ ! -x "$TOOLS/led_publisher" ]; then
  echo "Building host tools…"; bash "$TOOLS/build.sh"
fi

# 2) native agent (start if not already running)
if ! pgrep -f MicroXRCEAgent >/dev/null 2>&1; then
  echo "Starting native XRCE agent…"
  DYLD=$(ls -d "$HOME"/esp/Micro-XRCE-DDS-Agent/build/temp_install/*/lib 2>/dev/null | tr '\n' ':')
  DYLD_LIBRARY_PATH="$DYLD" nohup "$AGENT_BIN" udp4 -p 8888 -v6 > /tmp/xrce_agent.log 2>&1 &
  sleep 3
fi
echo "Agent (native): $(pgrep -f MicroXRCEAgent >/dev/null && echo running || echo 'NOT running — check ~/esp/Micro-XRCE-DDS-Agent build')"
echo ""
echo ">>> Make sure the ESP32 is powered, then press its RST button once. <<<"
echo ">>> Dashboard: http://localhost:8080 <<<"
echo ""

# 3) open browser + run the bridge server (foreground; Ctrl-C to stop)
( sleep 1.5; open "http://localhost:8080" >/dev/null 2>&1 || true ) &
exec python3 "$HERE/server.py"
