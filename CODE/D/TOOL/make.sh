#!/bin/sh
set -x
rm -f pcf
dmd -debug -g -gf -gs -m64 -ofpcf pcf.d ../base.d ../buffer.d ../cell.d ../cell_position_vector.d ../cloud.d ../component.d ../compression.d ../image.d ../property.d ../scalar.d ../scan.d ../stream.d ../vector_3.d ../vector_4.d
rm -f pcf.o
