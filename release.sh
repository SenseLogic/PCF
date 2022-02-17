#!/bin/sh
set -x
dmd -O -inline -m64 -ofpcf CODE/D/TOOL/pcf.d CODE/D/base.d CODE/D/buffer.d CODE/D/cell.d CODE/D/cell_position_vector.d CODE/D/cloud.d CODE/D/component.d CODE/D/compression.d CODE/D/image.d CODE/D/property.d CODE/D/scalar.d CODE/D/scan.d CODE/D/stream.d CODE/D/vector_3.d CODE/D/vector_4.d
rm pcf.o
