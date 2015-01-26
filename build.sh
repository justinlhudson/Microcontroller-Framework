#!/bin/bash

set -e

#avrdude -F -c STK500v2 -p m328 -P /dev/tty.usbmodem1421 -U flash:w:Core.hex
#screen /dev/tty.usbmodem1421 9600
make clean && make MODEL=atmega2560 CLOCK=16000000