#include "game.h"

void sprite_component_set(SpriteComponent* s_comp, MySprite* s, float scale) {
	if (s_comp->sprite && s_comp->sprite->bm)
		al_destroy_bitmap(s_comp->sprite->bm);
	free(s_comp->sprite);
	s_comp->sprite = s;
	s_comp->w = s->w * scale;
	s_comp->h = s->h * scale;
	s_comp->scale = scale;
}

void system_draw_sprites(Game* game) {
	unsigned mask = POSITION_COMP_MASK | SPRITE_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		Entity *e = &game->entities[i];
		if ((e->component_mask & mask) != mask)
			continue;

		PositionComponent* p_comp = &e->position_component;
		SpriteComponent* s_comp = &e->sprite_component;
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
