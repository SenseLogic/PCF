pcf --read-ptx IN/test.ptx 32 0 --write-pcf OUT/test_32.pcf
pcf --read-pcf OUT/test_32.pcf --write-pts OUT/test_32.pts --write-ptx OUT/test_32.ptx
pcf --read-ptx IN/test.ptx 8 0.01 --write-pcf OUT/test_8.pcf
pcf --read-pcf OUT/test_8.pcf --write-pts OUT/test_8.pts --write-ptx OUT/test_8.ptx
pause
