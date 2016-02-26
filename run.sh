#!/bin/bash

set -e

# Configure
_name=dev
_baud=115200
_port=/dev/tty.usbmodem1411

if [ ! -z "$1" ] && [[ "$1" == "-p" ]]; then
  avrdude -F -D -c stk500v2 -p m2560 -b $_baud -P $_port -U flash:w:$_name.hex -U eeprom:w:$_name.eep
elif [ ! -z "$1" ] && [[ "$1" == "-s" ]]; then
  screen $_port $_baud
else
  make clean && make MODEL=atmega2560 CLOCK=16000000 NAME=$_name
fi