#ifndef included_util_h
#define included_util_h

#include <allegro5/allegro.h>
#include <stdio.h>
#include "collision_callbacks.h"

typedef struct Game Game;
typedef unsigned ALLEGRO_KEY;

typedef struct {
	ALLEGRO_BITMAP* bm;
	int w, h;
} MySprite;

int record(int score);
void reset_record();

MySprite* load_sprite(const char* path);
void unload_sprite(MySprite* s);

void create_player(Game* game, int r, int g, int b, ALLEGRO_KEY up, ALLEGRO_KEY le, ALLEGRO_KEY dw, ALLEGRO_KEY ri, ALLEGRO_KEY sh);

void create_ui_element(Game* game, char* text, int y, COLLISION_CALLBACK on_collide);

float velocity_towards(int dc, int sc, double max_dist, double max_vel);

#endif
