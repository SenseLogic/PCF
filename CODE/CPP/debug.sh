#!/bin/sh
set -x
g++ -o test.cpp && nemiver ./test
rm test.o
