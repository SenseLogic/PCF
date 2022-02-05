#!/bin/sh
set -x
rm pcf
cd ..
g++ -g -o pcf -I.. pcf.cpp ../cell.cpp ../scan.cpp
rm -f pcf.o
cd TEST
nemiver ./pcf
