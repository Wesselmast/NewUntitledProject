@echo off

set compile_flags=-c -O2 -D_CRT_SECURE_NO_WARNINGS
set linker_paths=-L.\\lib
set include_paths=-I.\\include
set libraries=-lopengl32 -luser32 -lgdi32 -lfreetype -lglew32s

call duration -c clang++ .\src\Main.cpp %compile_flags% %include_paths% -o .\int\Main.o
call duration -l clang++ -o .\bin\Main.exe .\int\Main.o -Wl %linker_paths% %libraries%

robocopy .\res .\bin\res /E /NFL /NDL /NJH /NJS
exit
