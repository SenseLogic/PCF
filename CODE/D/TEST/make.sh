#!/bin/sh
set -x
dmd -debug -g -gf -gs -m64 -oftest test.d ../base.d ../buffer.d ../cell.d ../cloud.d ../component.d ../compression.d ../image.d ../property.d ../scalar.d ../scan.d ../stream.d ../vector_3.d
rm -f test.o
