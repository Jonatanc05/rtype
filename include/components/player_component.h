#ifndef _included_player_component_h
#define _included_player_component_h

#include <allegro5/allegro.h>

#define VELOCITY 3
#define SHIP_SCALE (2.5)
#define SHIP_IDLE_SPRITE_P "rsc\\sprite\\ship-idle.png"
#define   SHIP_UP_SPRITE_P "rsc\\sprite\\ship-up.png"
#define SHIP_DOWN_SPRITE_P "rsc\\sprite\\ship-down.png"

#define SHOT_SCALE 2
#define MAX_BEAM_CHARGE 50
#define BEAM_VELOCITY 10
#define BEAM_SPRITE_P "rsc\\sprite\\beam.png"
#define CHARGED_BEAM_SPRITE_P "rsc\\sprite\\charged-beam.png"

typedef struct Game Game;
typedef unsigned ALLEGRO_KEY;

typedef struct {
	int beamCharge;
	ALLEGRO_KEY up, left, down, right, shoot;
} PlayerComponent;

void system_play(Game* game);

int any_player_left(Game* game);

#endif
