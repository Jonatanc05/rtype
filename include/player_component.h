#include <allegro5/allegro.h>

#define VELOCITY 3

typedef struct Game Game;
typedef unsigned ALLEGRO_KEY;

typedef struct {
	ALLEGRO_KEY up, left, down, right, shoot;
} PlayerComponent;

void system_play(Game* game);
