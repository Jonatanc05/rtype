#include "game.h"

void system_sound(Game* game) {
	unsigned mask = SOUND_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		Entity* e = &game->entities[i];
		if ((e->component_mask & mask) != mask)
			continue;

		SoundComponent* s_comp = &e->sound_component;
		if (s_comp->start) {
			s_comp->start = 0;
			al_play_sample(s_comp->sample, s_comp->gain, s_comp->pan, 1, s_comp->playmode, &s_comp->id);
		} else if (s_comp->stop) {
			s_comp->stop = 0;
			al_stop_sample(&s_comp->id);
		}
	}
}
