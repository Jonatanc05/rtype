#include "game.h"

void system_draw_sprites(Game* game) {
	unsigned mask = POSITION_COMP_MASK | SPRITE_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		Entity *e = &game->entities[i];
		if ((e->component_mask & mask) != mask)
			continue;

		PositionComponent* p_comp = &e->positionComponent;
		SpriteComponent* s_comp = &e->spriteComponent;
		// improvable
		int w =  al_get_bitmap_width(s_comp->bitmap);
		int h = al_get_bitmap_height(s_comp->bitmap);
		al_draw_scaled_bitmap(s_comp->bitmap,
				.0, .0, // source x y
				w, h,   // source w h
				p_comp->x + s_comp->x, p_comp->y + s_comp->y,
				s_comp->w, s_comp->h,
				0
		);
	}
}
