#include "text_component.h"
#include "game.h"

void text_draw(Game* game) {
	for (int i = 0; i < game->numEntities; i++) {
		TextComponent* t_comp = game->entities[i].textComponent;
		PositionComponent* p_comp = game->entities[i].positionComponent;
		if (!t_comp || !p_comp) continue;
		ALLEGRO_FONT* font = NULL;
		if (t_comp->fontSize == REGULAR_FONT)
			font = game->regular_font;

		al_draw_text(font, al_map_rgb(255, 255, 255),
				p_comp->x + t_comp->x,
				p_comp->y + t_comp->y,
				0, t_comp->text);
	}
}
