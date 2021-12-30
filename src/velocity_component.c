#include "game.h"

void system_move(Game* game) {
	unsigned mask = POSITION_COMP_MASK | VELOCITY_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		Entity *e = &game->entities[i];
		if ((e->component_mask & mask) != mask)
			continue;

		e->positionComponent.x += e->velocityComponent.x;
		e->positionComponent.y += e->velocityComponent.y;
	}
}
