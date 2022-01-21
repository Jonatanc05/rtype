#include "game.h"
#include <math.h>

void system_senoid(Game* game) {
	for (int i = 0; i < game->numEntities; i++) {
		Entity* e = &game->entities[i];
		if (!(e->component_mask & SENOID_COMP_MASK))
			continue;

		SenoidComponent* s_comp = &e->senoid_component;
		float x = e->position_component.x;
		e->position_component.y = s_comp->base_y
			+ s_comp->amp * sin(s_comp->period*(x + s_comp->shift));
	}
}
