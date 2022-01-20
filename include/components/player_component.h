#ifndef _included_player_component_h
#define _included_player_component_h

#include <allegro5/allegro.h>

#define VELOCITY 180.0
#define SHIP_SCALE (2.5)
#define SHIP_IDLE_SPRITE_P "rsc\\sprite\\ship-idle.png"
#define   SHIP_UP_SPRITE_P "rsc\\sprite\\ship-up.png"
#define SHIP_DOWN_SPRITE_P "rsc\\sprite\\ship-down.png"

#define SHOT_SCALE 2
#define MAX_BEAM_CHARGE 1.0 // in seconds
#define BEAM_VELOCITY 600.0
#define BEAM_SPRITE_P "rsc\\sprite\\beam.png"
#define CHARGED_BEAM_SPRITE_P "rsc\\sprite\\charged-beam.png"

typedef struct Game Game;
typedef struct Entity Entity;
typedef unsigned ALLEGRO_KEY;

typedef struct {
	float beam_charge;
	ALLEGRO_KEY up, left, down, right, shoot;
	Entity* charge_bar;
} PlayerComponent;

void system_play(Game* game);

int any_player_left(Game* game);

#endif
