@echo off
gcc -o rtype.exe -Iinclude -Iinclude\components -Llib src\rtype.c src\game.c src\entity.c src\util.c src\components\text_component.c src\components\velocity_component.c src\components\player_component.c src\components\sprite_component.c src\components\circle_collider_component.c lib\liballegro-5.0.10-monolith-mt.a
pause

copy lib\allegro-5.0.10-monolith-mt.dll
.\rtype.exe
del allegro-5.0.10-monolith-mt.dll
del rtype.exe
