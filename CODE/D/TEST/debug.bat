dmd -debug -g -gf -gs -m64 -oftest.exe test.d ../base.d ../buffer.d ../cell.d ../cloud.d ../component.d ../compression.d ../image.d ../scalar.d ../scan.d ../stream.d ../vector_3.d
del /q test.obj
del /q test.ilk
del /q test.pdb
test.exe
