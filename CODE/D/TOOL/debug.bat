del /q pcf.exe
dmd -debug -g -gf -gs -m64 -ofpcf.exe pcf.d ../base.d ../buffer.d ../cell.d ../cell_position_vector.d ../cloud.d ../component.d ../compression.d ../image.d ../property.d ../scalar.d ../scan.d ../stream.d ../vector_3.d ../vector_4.d
del /q *.obj
del /q *.ilk
pause
