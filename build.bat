@echo off

set linker_paths=-LLib\\10.0.17763.0\\um\\x86\\
set include_paths=-IInclude\\10.0.17763.0\\ 
set libraries=-lopengl32 -luser32 -lgdi32

call duration -c clang++ .\src\Main.cpp -c -O2 %include_paths% -o .\int\Main.o
call duration -l clang++ -o .\bin\Main.exe .\int\Main.o -Wl %linker_paths% %libraries%
exit
