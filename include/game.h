#ifndef included_game_h
#define included_game_h

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "entity.h"
#include "collision.h"

#define FPS 60
#define SCREEN_W 1160
#define SCREEN_H 540

#define THEME_SAMPLE_P  "rsc\\sound\\ressurections.ogg"

#define AIRMINE_SPRITE_P  "rsc\\sprite\\airmine.png"
#define AIRMINE_SPAWN_TEST_INTERVAL 25  // in ticks
#define AIRMINE_SPAWN_TEST_CHANCE 30.0 // percentage
#define AIRMINE_MAX_XVEL 4.0
#define AIRMINE_MAX_YVEL 3.0
#define AIRMINE_SPAWN_SIEGE 80
#define AIRMINE_MIN_SCALE 5.0
#define AIRMINE_MAX_SCALE 2.0
#define AIRMINES_P_SECOND 1

#define STAR_SPAWN_CHANCE 20
#define STAR_MIN_SIZE 0.6
#define STAR_MAX_SIZE 2.4
#define STAR_MIN_VEL 4
#define STAR_MAX_VEL 8

#define BLOCK_SPAWN_TEST_INTERVAL 2  // in seconds
#define BLOCK_SPAWN_TEST_CHANCE 20.0 // percentage
//#define BLOCK_MIN_WIDTH // will be screen width
#define BLOCK_MAX_WIDTH 2 // measured in "screens"
#define BLOCK_VELOCITY 2

typedef enum KEY_STATE {
	KEY_STATE_NULL = 0,
	KEY_STATE_DOWN = 1,
	KEY_STATE_HOLD = 2,
	KEY_STATE_UP = 3
} KEY_STATE;

typedef struct Game {
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *regular_font;
	ALLEGRO_SAMPLE *theme_sam;

	int score, started, over;
	long unsigned tick;
	char* score_str;
	KEY_STATE keyboard[ALLEGRO_KEY_MAX];
	unsigned numEntities;
	Entity* entities;

	MySprite *p_idle_spr, *p_up_spr, *p_down_spr,
			 *airmine_spr,
			 *beam_spr, *ch_beam_spr;
} Game;

void on_game_init(Game* game);
void on_update(Game* game);
void on_game_exit(Game* game);

void system_airmine_spawner(Game* game);

void system_block_spawner(Game* game);

void system_clean_dead_entities(Game* game);

void system_stars(Game* game);

void system_score(Game* game);

#endif
