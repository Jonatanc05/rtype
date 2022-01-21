#include "game.h"

void system_sound(Game* game) {
	unsigned mask = SOUND_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		Entity* e = &game->entities[i];
		if ((e->component_mask & mask) != mask)
			continue;

		SoundComponent* s_comp = &e->sound_component;

		al_set_sample_instance_playmode(s_comp->sample, s_comp->playmode);
		al_set_sample_instance_gain(s_comp->sample, s_comp->gain);
		al_set_sample_instance_speed(s_comp->sample, s_comp->speed);

		// Start/stop
		if (s_comp->stop) {
			s_comp->stop = 0;
			al_set_sample_instance_playing(s_comp->sample, 0);//al_stop_sample_instance(s_comp->sample);
		}
		if (s_comp->start && !s_comp->fade_out) {
			s_comp->start = 0;
			al_set_sample_instance_position(s_comp->sample, s_comp->start_position);
			al_set_sample_instance_playing(s_comp->sample, 1);//al_play_sample_instance(s_comp->sample);
		}

		// Fade in/out
		if (s_comp->fade_in) {
			if (!al_get_sample_instance_playing(s_comp->sample))
				s_comp->start = 1;
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
				s_comp->stop = 1;
			}
		}
	}
}
