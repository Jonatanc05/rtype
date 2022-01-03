#ifndef included_game_h
#define included_game_h

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "entity.h"

#define FPS 100
#define SCREEN_W 1160
#define SCREEN_H 540

typedef char KEY_STATE;
#define KEY_STATE_NULL 0
#define KEY_STATE_DOWN 1
#define KEY_STATE_HOLD 2
#define KEY_STATE_UP 3

#define ENEMY_SPRITE_P  "rsc\\sprite\\enemy.png"
#define ENEMY_MAX_XVEL 4.0
#define ENEMY_MAX_YVEL 3.0
#define ENEMY_SPAWN_SIEGE 80
#define ENEMY_MAX_WIDTH 10
#define ENEMY_MAX_HEIGHT 10
#define ENEMIES_P_SECOND 6

#define STAR_SPAWN_CHANCE 10
#define STAR_MIN_SIZE 0.6
#define STAR_MAX_SIZE 2.4
#define STAR_MIN_VEL 4
#define STAR_MAX_VEL 8

typedef struct Game {
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *regular_font;

	int score;
	char* score_str;
	KEY_STATE keyboard[ALLEGRO_KEY_MAX];
	unsigned numEntities;
	Entity* entities;
} Game;

void on_game_init(Game* game);
void on_update(Game* game);
void on_game_exit(Game* game);

void system_enemy_spawner(Game* game, int(*x_distribution)(int, int), int(*y_distribution)(int, int));

void system_clean_dead_entities(Game* game);

void system_stars(Game* game);

void system_score(Game* game);

#endif
