#!/bin/sh
set -x
dmd -debug -g -gf -gs -m64 -oftest test.d buffer.d cell.d cloud.d component.d compression.d file.d image.d property.d scalar.d scan.d vector_3.d && ./test
rm test.o
