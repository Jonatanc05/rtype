#include "game.h"

void system_draw_sprites(Game* game) {
	unsigned mask = POSITION_COMP_MASK | SPRITE_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		Entity *e = &game->entities[i];
		if ((e->component_mask & mask) != mask)
			continue;

		PositionComponent* p_comp = &e->position_component;
		SpriteComponent* s_comp = &e->sprite_component;
		al_draw_scaled_bitmap(s_comp->sprite->bm,
				.0, .0, // source x y
				(int)(s_comp->sprite->w), // source width
				(int)(s_comp->sprite->h), // source height
				(int)(p_comp->x + s_comp->x), // final x
				(int)(p_comp->y + s_comp->y), // final y
				(int)(s_comp->w), // final width
				(int)(s_comp->h), // final height
				0 // flags
		);
	}
}
