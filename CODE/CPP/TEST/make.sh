#!/bin/sh
set -x
reset
cd ..
g++ -g -o TEST/test -I. test.cpp cell.cpp scan.cpp 2>&1 | head -n 25
rm -f test.o
cd TEST
