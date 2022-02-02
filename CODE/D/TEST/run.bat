dmd -debug -g -gf -gs -m64 -oftest.exe test.d ../base.d ../buffer.d ../cell.d ../cloud.d ../component.d ../compression.d ../image.d ../property.d ../scalar.d ../scan.d ../stream.d ../vector_3.d
del test.obj
del test.ilk
del test.pdb
test.exe
