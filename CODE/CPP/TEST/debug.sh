#!/bin/sh
set -x
g++ -o test -I../ test.cpp ../cell.cpp ../scan.cpp && nemiver ./test
rm test.o
