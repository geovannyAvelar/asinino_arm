#!/bin/bash

set -e

if [ ! -d tinyusb ]; then
  echo "TinyUSB not found."
  exit 1
fi

if [ -d build ]; then
  rm -R build
fi

cd tinyusb
export TINYUSB_ROOT=$PWD
cd ..

make
mv _build/uno_r4/asinino_arm.hex asinino.hex
rm -rf _build