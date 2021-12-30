#include <allegro5/allegro.h>

#define VELOCITY 3

#define SHOT_SCALE 2
#define MAX_BEAM_CHARGE 100
#define BEAM_VELOCITY 6
#define BEAM_SPRITE_P "rsc\\sprite\\beam.png"
#define CHARGED_BEAM_SPRITE_P "rsc\\sprite\\charged-beam.png"

typedef struct Game Game;
typedef unsigned ALLEGRO_KEY;

typedef struct {
	int beamCharge;
	ALLEGRO_KEY up, left, down, right, shoot;
} PlayerComponent;

void system_play(Game* game);
