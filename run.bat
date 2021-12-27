@echo off
gcc -o rtype.exe -Iinclude -Llib src\rtype.c lib\liballegro-5.0.10-monolith-mt.a

copy lib\allegro-5.0.10-monolith-mt.dll
.\rtype.exe
del allegro-5.0.10-monolith-mt.dll
del rtype.exe