#include "game.h"

void system_play(Game* game) {
	unsigned mask = PLAYER_COMP_MASK | VELOCITY_COMP_MASK | POSITION_COMP_MASK;
	for (int i = 0; i < game->numEntities; i += VELOCITY) {
		Entity* e = &game->entities[i];
		if ((e->component_mask & mask) != mask)
			continue;

		if (game->keyboard[e->playerComponent.up] == KEY_STATE_DOWN)
			e->velocityComponent.y -= VELOCITY;
		if (game->keyboard[e->playerComponent.up] == KEY_STATE_UP)
			e->velocityComponent.y += VELOCITY;
		if (game->keyboard[e->playerComponent.left] == KEY_STATE_DOWN)
			e->velocityComponent.x -= VELOCITY;
		if (game->keyboard[e->playerComponent.left] == KEY_STATE_UP)
			e->velocityComponent.x += VELOCITY;
		if (game->keyboard[e->playerComponent.down] == KEY_STATE_DOWN)
			e->velocityComponent.y += VELOCITY;
		if (game->keyboard[e->playerComponent.down] == KEY_STATE_UP)
			e->velocityComponent.y -= VELOCITY;
		if (game->keyboard[e->playerComponent.right] == KEY_STATE_DOWN)
			e->velocityComponent.x += VELOCITY;
		if (game->keyboard[e->playerComponent.right] == KEY_STATE_UP)
			e->velocityComponent.x -= VELOCITY;
	}
}
