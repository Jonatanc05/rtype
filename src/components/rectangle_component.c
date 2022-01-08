#include "components/rectangle_component.h"
#include "game.h"
#include <allegro5/allegro_primitives.h>

void system_draw_rectangles(Game* game) {
	unsigned mask = POSITION_COMP_MASK | RECTANGLE_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		Entity *e = &game->entities[i];
		if ((e->component_mask & mask) != mask)
			continue;

		PositionComponent* p_comp = &e->position_component;
		RectangleComponent* r_comp = &e->rectangle_component;
		al_draw_filled_rectangle(p_comp->x, p_comp->y, p_comp->x+r_comp->w, p_comp->y+r_comp->h, al_map_rgb(255, 255, 255));
	}
}
