#include "game.h"

void system_draw_sprites(Game* game) {
	unsigned mask = POSITION_COMP_MASK | SPRITE_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		Entity *e = &game->entities[i];
		if ((e->component_mask & mask) != mask)
			continue;

		PositionComponent* p_comp = &e->positionComponent;
		SpriteComponent* s_comp = &e->spriteComponent;
		MySprite* spr = s_comp->sprite;
		// improvable
		al_draw_scaled_bitmap(s_comp->sprite->bm,
				.0, .0, // source x y
				spr->w, // source width
				spr->h, // source height
				p_comp->x + s_comp->x, // final x
				p_comp->y + s_comp->y, // final y
				s_comp->w, // final width
				s_comp->h, // final height
				0
		);
	}
}
