@echo off
gcc -o rtype.exe -Iinclude -Llib src\rtype.c src\game.c src\entity.c src\util.c src\text_component.c src\velocity_component.c src\player_component.c src\sprite_component.c lib\liballegro-5.0.10-monolith-mt.a
pause

copy lib\allegro-5.0.10-monolith-mt.dll
.\rtype.exe
del allegro-5.0.10-monolith-mt.dll
del rtype.exe
