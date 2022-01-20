#ifndef _included_sprite_component_h
#define _included_sprite_component_h

#include <allegro5/allegro.h>

typedef struct Game Game;

typedef struct {
	MySprite* sprite;
	float x, y;
	float scale, w, h;
} SpriteComponent;

void system_draw_sprites(Game* game);

#endif
