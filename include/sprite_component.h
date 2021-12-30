#include <allegro5/allegro.h>

typedef struct Game Game;

typedef struct {
	int x, y, w, h;
	ALLEGRO_BITMAP *bitmap;
} SpriteComponent;

void system_draw_sprites(Game* game);
