#!/usr/bin/env bash
# Build the host-side led_cmd publisher.
# Requires the Micro-XRCE-DDS-Client + Micro-CDR built for the host at $EPRO_HOME.
set -e
HERE="$(cd "$(dirname "$0")" && pwd)"
EPRO_HOME="${EPRO_HOME:-$HOME/esp/eprosima-host}"

cc -O2 -o "$HERE/led_publisher" \
   "$HERE/led_publisher.c" "$HERE/../main/smart_home.c" \
   -I"$HERE/../main" -I"$EPRO_HOME/include" \
   -L"$EPRO_HOME/lib" -lmicroxrcedds_client -lmicrocdr

echo "built: $HERE/led_publisher"
