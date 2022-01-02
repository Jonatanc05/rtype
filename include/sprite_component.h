#include <allegro5/allegro.h>

typedef struct Game Game;
struct MySprite;

typedef struct {
	MySprite* sprite;
	int x, y;
	float scale, w, h;
} SpriteComponent;

void system_draw_sprites(Game* game);

void sprite_component_set(SpriteComponent* s_comp, MySprite* s, float scale);
