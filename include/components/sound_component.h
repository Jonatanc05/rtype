#ifndef _included_sound_component_h
#define _included_sound_component_h

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define FADE_RATE 0.003

typedef struct Game Game;

typedef struct {
	ALLEGRO_SAMPLE_INSTANCE* sample;
	float gain;
	int start, stop, playmode, fade_in, fade_out;
	unsigned start_position;
} SoundComponent;

void system_sound(Game* game);

#endif
