#!/usr/bin/env bash
# Build the RTI Connext publisher + subscriber (arm64 macOS, C++11 API).
set -e
export NDDSHOME="${NDDSHOME:-/Applications/rti_connext_dds-7.7.0}"
ARCH=arm64Darwin23clang16.0
HERE="$(cd "$(dirname "$0")" && pwd)"
cd "$HERE"

CXXFLAGS="-std=c++14 -DRTI_UNIX -DRTI_DARWIN -DRTI_64BIT"
INCLUDES="-I. -I$NDDSHOME/include -I$NDDSHOME/include/ndds -I$NDDSHOME/include/ndds/hpp"
LIBS="-L$NDDSHOME/lib/$ARCH -lnddscpp2 -lnddsc -lnddscore -Wl,-rpath,$NDDSHOME/lib/$ARCH"

for app in rti_publisher rti_subscriber; do
    echo "building $app ..."
    c++ $CXXFLAGS $INCLUDES "$app.cxx" smart_home.cxx smart_homePlugin.cxx $LIBS -o "$app"
done
echo "built: rti_publisher, rti_subscriber"
