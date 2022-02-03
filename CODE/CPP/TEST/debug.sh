#!/bin/sh
set -x
rm test
cd ..
g++ -g -o test -I.. test.cpp ../cell.cpp ../scan.cpp
rm -f test.o
cd TEST
nemiver ./test
