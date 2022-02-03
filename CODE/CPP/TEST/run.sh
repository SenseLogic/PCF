#!/bin/sh
set -x
rm -f test
g++ -g -o test -I.. test.cpp ../cell.cpp ../scan.cpp
rm -f test.o
./test
