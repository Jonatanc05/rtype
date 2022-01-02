#include "game.h"

void system_move(Game* game) {
	unsigned mask = POSITION_COMP_MASK | VELOCITY_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		Entity *e = &game->entities[i];
		if ((e->component_mask & mask) != mask)
			continue;

		e->position_component.x += e->velocity_component.x;
		e->position_component.y += e->velocity_component.y;

		if ((e->component_mask & PLAYER_COMP_MASK) &&
				(e->position_component.x < 0 || e->position_component.x + e->sprite_component.w > al_get_display_width(game->display)))
			e->position_component.x -= e->velocity_component.x;
		if ((e->component_mask & PLAYER_COMP_MASK) &&
				(e->position_component.y < 0 || e->position_component.y + e->sprite_component.h > al_get_display_height(game->display)))
			e->position_component.y -= e->velocity_component.y;
	}
}
