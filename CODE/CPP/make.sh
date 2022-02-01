#!/bin/sh
set -x
reset
g++ -o test test.cpp 2>&1 | head -n 25
rm test.o
