#include "components/rectangle_component.h"
#include "game.h"
#include <allegro5/allegro_primitives.h>

void draw_layer(Game* game, LAYER layer) {
	unsigned mask = POSITION_COMP_MASK | RECTANGLE_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		Entity *e = &game->entities[i];
		if ((e->component_mask & mask) != mask || e->layer != layer)
			continue;

		PositionComponent* p_comp = &e->position_component;
		RectangleComponent* r_comp = &e->rectangle_component;

		int r = 255, g = 255, b = 255, a = 255;
		if (e->component_mask & COLOR_COMP_MASK) {
			r = e->color_component.r;
			g = e->color_component.g;
			b = e->color_component.b;
			a = e->color_component.a;
		}

		al_draw_filled_rectangle(p_comp->x, p_comp->y, p_comp->x+r_comp->w, p_comp->y+r_comp->h, al_map_rgba(r, g, b, a));
	}
}

void system_draw_rectangles(Game* game) {
	draw_layer(game, LAYER_STAR);
	draw_layer(game, LAYER_BLOCK);
}
