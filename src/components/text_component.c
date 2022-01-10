#include "components/text_component.h"
#include "game.h"

void system_draw_text(Game* game) {
	unsigned mask = POSITION_COMP_MASK | TEXT_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		Entity* e = &game->entities[i];
		if ((e->component_mask & mask) != mask)
			continue;

		TextComponent *t_comp = &e->text_component;
		PositionComponent *p_comp = &e->position_component;
		ALLEGRO_FONT* font = NULL;
		if (t_comp->fontSize == REGULAR_FONTSIZE)
			font = game->regular_font;

		int r = 255, g = 255, b = 255, a = 255;
		if (e->component_mask & COLOR_COMP_MASK) {
			r = e->color_component.r;
			g = e->color_component.g;
			b = e->color_component.b;
			a = e->color_component.a;
		}

		al_draw_text(font, al_map_rgba(r, g, b, a),
				p_comp->x + t_comp->x,
				p_comp->y + t_comp->y,
				0, t_comp->text);
	}
}
