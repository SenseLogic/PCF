#!/bin/sh
set -x
g++ -o test test.cpp && ./test
rm test.o
