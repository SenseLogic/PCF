#!/bin/sh
set -x
reset
rm -f test
g++ -g -o test -I.. test.cpp ../cell.cpp ../scan.cpp 2>&1 | head -n 25
rm -f test.o
