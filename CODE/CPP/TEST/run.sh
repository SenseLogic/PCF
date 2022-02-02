#!/bin/sh
set -x
cd ..
g++ -g -o TEST/test -I. test.cpp cell.cpp scan.cpp
rm -f test.o
cd TEST
./test
