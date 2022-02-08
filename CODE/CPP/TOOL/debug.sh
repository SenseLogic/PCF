#!/bin/sh
set -x
reset
rm -f pcf
g++ -g -o pcf -I.. pcf.cpp ../cell.cpp ../scan.cpp 2>&1 | head -n 25
rm -f *.o
