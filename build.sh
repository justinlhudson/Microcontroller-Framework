#!/bin/bash

set -e

# Configure
_name=development
_baud=115200

if [ ! -z "$2" ]; then
  _port="$2"
else
  _port=/dev/tty.usbmodem1411
fi

if [ ! -z "$1" ] && [[ "$1" == "-p" ]]; then
  screen -X -S $(lsof | grep $_port | awk '{print $2}') quit || true
  avrdude -F -D -c stk500v2 -p m2560 -b $_baud -P $_port -U flash:w:$_name.hex -U eeprom:w:$_name.eep
elif [ ! -z "$1" ] && [[ "$1" == "-s" ]]; then
  screen $_port $_baud
else
  make clean && make BOARD=arduino_mega MODEL=atmega2560 FREQUENCY=16000000 NAME=$_name
fi
