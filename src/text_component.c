#include "text_component.h"
#include "game.h"

void system_draw_text(Game* game) {
	unsigned mask = POSITION_COMP_MASK | TEXT_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		if ((game->entities[i].component_mask & mask) != mask)
			continue;

		TextComponent *t_comp = &game->entities[i].textComponent;
		PositionComponent *p_comp = &game->entities[i].positionComponent;
		ALLEGRO_FONT* font = NULL;
		if (t_comp->fontSize == REGULAR_FONTSIZE)
			font = game->regular_font;

		al_draw_text(font, al_map_rgb(255, 255, 255),
				p_comp->x + t_comp->x,
				p_comp->y + t_comp->y,
				0, t_comp->text);
	}
}
