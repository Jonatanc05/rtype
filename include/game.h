#ifndef included_game_h
#define included_game_h

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "entity.h"
#include "collision.h"

#define FPS 60
#define SCREEN_W 1160
#define SCREEN_H 540

#define THEME_SAMPLE_P     "rsc\\sound\\ressurections.ogg"
#define CHARGING_SAMPLE_P  "rsc\\sound\\charging.ogg"
#define BEAM_SAMPLE_P  "rsc\\sound\\beam.ogg"
#define CH_BEAM_SAMPLE_P  "rsc\\sound\\ch-beam.ogg"

#define AIRMINE_SPRITE_P  "rsc\\sprite\\airmine.png"
#define AIRMINE_SPAWN_TEST_INTERVAL 0.2  // in seconds
#define AIRMINE_SPAWN_TEST_CHANCE 50.0   // percentage
#define AIRMINE_MAX_XVEL 100.0
#define AIRMINE_MAX_YVEL 100.0
#define AIRMINE_SPAWN_SIEGE 80
#define AIRMINE_MAX_SCALE 4.0
#define AIRMINE_MIN_SCALE 2.0

#define STAR_SPAWN_CHANCE 75
#define STAR_MIN_SIZE 0.9
#define STAR_MAX_SIZE 2.4
#define STAR_MIN_VEL 480.0
#define STAR_MAX_VEL 960.0

#define BLOCK_SPAWN_TEST_INTERVAL 8  // in seconds
#define BLOCK_SPAWN_TEST_CHANCE 60.0 // percentage
//#define BLOCK_MIN_WIDTH // will be screen width
#define BLOCK_MAX_WIDTH 2 // measured in "screens"
#define BLOCK_VELOCITY 600

typedef enum KEY_STATE {
	KEY_STATE_NULL = 0,
	KEY_STATE_DOWN = 1,
	KEY_STATE_HOLD = 2,
	KEY_STATE_UP = 3
} KEY_STATE;

typedef struct Game {


//---------    Game data    ----------

	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	int score; char* score_str;
	unsigned numEntities;
	Entity *entities,   // All entities in game
		   *soundtrack; // Responsible for background music


//---------- Game resources ----------

	ALLEGRO_FONT *regular_font;

	MySprite *p_idle_spr, *p_up_spr, *p_down_spr,
			 *airmine_spr,
			 *beam_spr, *ch_beam_spr;

	ALLEGRO_SAMPLE *theme_sam, *charging_sam,
				   *beam_sam, *ch_beam_sam;


//----------   Game state   ----------

	int started,
		end,   // should I end?
		ended; // have I ended?
	double time, delta_time;
	long unsigned tick;
	KEY_STATE keyboard[ALLEGRO_KEY_MAX];
	// spawners
	int there_is_block;
	double last_block_spawn_test, last_airmine_spawn_test;

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
