#ifndef _included_sound_component_h
#define _included_sound_component_h

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

typedef struct Game Game;

typedef struct {
	ALLEGRO_SAMPLE* sample;
	ALLEGRO_SAMPLE_ID id;
	float gain, pan;
	int start, stop, playmode;
} SoundComponent;

void system_sound(Game* game);

#endif
