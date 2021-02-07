#!/bin/sh

alias build="arduino-cli compile -b arduino:avr:uno && arduino-cli upload --port /dev/ttyUSB0 && /bin/cat /dev/ttyUSB0"
