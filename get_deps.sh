#!/bin/bash

set -e

if [ -d tinyusb ]; then
  rm -rf tinyusb
fi

git clone https://github.com/hathach/tinyusb.git
cd tinyusb
python ./tools/get_deps.py ra
git checkout 0.17.0
python ./tools/get_deps.py ra
patch -p1 < ../0001-fix-arduino-bootloaders.patch
