#include "game.h"

void system_move(Game* game) {
	unsigned mask = POSITION_COMP_MASK | VELOCITY_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		Entity *e = &game->entities[i];
		if ((e->component_mask & mask) != mask)
			continue;

		e->positionComponent.x += e->velocityComponent.x;
		e->positionComponent.y += e->velocityComponent.y;

		if ((e->component_mask & PLAYER_COMP_MASK) &&
				(e->positionComponent.x < 0 || e->positionComponent.x + e->spriteComponent.sprite->w > al_get_display_width(game->display)))
			e->positionComponent.x -= e->velocityComponent.x;
		if ((e->component_mask & PLAYER_COMP_MASK) &&
				(e->positionComponent.y < 0 || e->positionComponent.y + e->spriteComponent.sprite->h > al_get_display_height(game->display)))
			e->positionComponent.y -= e->velocityComponent.y;
	}
}
