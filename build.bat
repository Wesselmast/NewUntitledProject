@echo off

set compile_flags=-c -O2 -D_CRT_SECURE_NO_WARNINGS
set linker_paths=-LLib\\10.0.17763.0\\um\\x64\\ -L.\\lib
set include_paths=-IInclude\\10.0.17763.0\\ -I.\\include
set libraries=-lopengl32 -luser32 -lgdi32 -lfreetype -lglew32s

call duration -c clang++ .\src\Main.cpp %compile_flags% %include_paths% -o .\int\Main.o
call duration -l clang++ -o .\bin\Main.exe .\int\Main.o -Wl %linker_paths% %libraries%
exit
