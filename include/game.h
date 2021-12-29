#ifndef included_game_h
#define included_game_h

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "entity.h"

typedef struct Game {
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *regular_font;

	unsigned numEntities;
	Entity* entities;
} Game;

#endif
