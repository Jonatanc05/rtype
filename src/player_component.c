#include "game.h"

void system_play(Game* game) {
	unsigned mask = PLAYER_COMP_MASK | VELOCITY_COMP_MASK | POSITION_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		Entity e = game->entities[i];
		if ((e.component_mask & mask) != mask)
			continue;

		//logic here
	}
}
