#ifndef included_util_h
#define included_util_h

#include <allegro5/allegro.h>
#include <stdio.h>

typedef struct {
	ALLEGRO_BITMAP* bm;
	int w, h;
} MySprite;

int record(int score);

MySprite* load_sprite(const char* path);
void unload_sprite(MySprite* s);

#endif
