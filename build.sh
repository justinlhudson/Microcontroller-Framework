#!/bin/bash

set -e

#avrdude -F -D -c stk500v2 -p m2560 -b 115200 -P /dev/tty.usbmodem1411 -U flash:w:Core.hex
#avrdude -F -c arduino-p m328 -P /dev/tty.usbmodem1421 -U flash:w:Core.hex
#screen /dev/tty.usbmodem1421 9600
make clean && make MODEL=atmega2560 CLOCK=16000000