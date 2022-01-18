#include "game.h"

void system_sound(Game* game) {
	unsigned mask = SOUND_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		Entity* e = &game->entities[i];
		if ((e->component_mask & mask) != mask)
			continue;

		SoundComponent* s_comp = &e->sound_component;

		al_set_sample_instance_playmode(s_comp->sample, s_comp->playmode);
		if (!al_set_sample_instance_gain(s_comp->sample, s_comp->gain)) printf("\n\nDEU RUIM\n\n");

		// Start/stop
		if (s_comp->start) {
			s_comp->start = 0;
			al_play_sample_instance(s_comp->sample);
		} else if (s_comp->stop) {
			s_comp->stop = 0;
			al_stop_sample_instance(s_comp->sample);
		}

		// Fade in/out
		if (s_comp->fade_in) {
			s_comp->gain += FADE_RATE;
			if (s_comp->gain >= 1.0) {
				s_comp->gain = 1.0;
				s_comp->fade_in = 0;
			}
		}
		else if (s_comp->fade_out) {
			s_comp->gain -= FADE_RATE;
			if (s_comp->gain <= 0.0) {
				s_comp->gain = 0.0;
				s_comp->fade_out = 0;
			}
		}
	}
}
