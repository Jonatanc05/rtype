@echo off
gcc -o rtype.exe ^
	-Iinclude ^
	-Llib ^
	-lallegro-5.0.10-monolith-mt ^
	-l:allegro-5.0.10-monolith-mt.dll ^
	src\rtype.c ^
	src\game.c ^
	src\entity.c ^
	src\util.c ^
	src\collision.c ^
	src\collision_callbacks.c ^
	src\components\text_component.c ^
	src\components\velocity_component.c ^
	src\components\player_component.c ^
	src\components\sprite_component.c ^
	src\components\rectangle_component.c ^
	src\components\sound_component.c ^
	src\components\senoid_component.c
pause

copy lib\allegro-5.0.10-monolith-mt.dll
.\rtype.exe
