cls
del /q test.exe
"C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.29.30133/bin/Hostx64/x64/cl.exe" /Zi /EHsc /TP /I.. /I"C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.19041.0\\ucrt\\" /I"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\include\\" test.cpp ..\cell.cpp ..\scan.cpp /link /LIBPATH:"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.19041.0\\ucrt\\x64\\" /LIBPATH:"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.19041.0\\um\\x64\\" /LIBPATH:"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64\\" /out:test.exe
del /q *.obj
del /q *.pdb
