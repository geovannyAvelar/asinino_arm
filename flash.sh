#!/bin/bash

set -e

FILE="${1:-asinino.hex}"
PORT="${2:-/dev/ttyACM0}"

rfp-cli -device ra -port $PORT -p $FILE