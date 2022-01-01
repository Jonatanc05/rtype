#include <allegro5/allegro.h>

typedef struct Game Game;

typedef struct {
	MySprite* sprite;
	int x, y;
	float scale;
} SpriteComponent;

void system_draw_sprites(Game* game);
