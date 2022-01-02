#include "circle_collider_component.h"
#include "game.h"
#include <math.h>
#include <allegro5/allegro_primitives.h>

void on_collide_die(Entity* self, Entity* other) {
	self->dead = 1;
}

void on_collide_nop(Entity* self, Entity* other) {}

float dist(Entity* e1, Entity* e2) {
	int posx1 = e1->position_component.x,
		posy1 = e1->position_component.y,
		posx2 = e2->position_component.x,
		posy2 = e2->position_component.y;
	int x1 = posx1 + e1->circle_coll_component.x,
		y1 = posy1 + e1->circle_coll_component.y,
		x2 = posx2 + e2->circle_coll_component.x,
		y2 = posy2 + e2->circle_coll_component.y;
	return sqrt((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2));
}
void system_detect_collision(Game* game) {
	unsigned mask = CIRCLE_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		Entity* e1 = &game->entities[i];
		if ((e1->component_mask & mask) != mask)
			continue;
		for (int j = i+1; j < game->numEntities; j++) {
			Entity* e2 = &game->entities[j];
			if ((e2->component_mask & mask) != mask)
				continue;

			CircleCollComponent *coll1 = &e1->circle_coll_component,
								*coll2 = &e2->circle_coll_component;
			if (dist(e1, e2) < coll1->r + coll2->r) {
				coll1->on_collide(e1, e2);
				coll2->on_collide(e2, e1);
			}
		}
	}
}

void system_debug_draw_colliders(Game* game) {
	for (int i = 0; i < game->numEntities; i++) {
		Entity* e = &game->entities[i];
		if (!(e->component_mask & CIRCLE_COMP_MASK))
			continue;
		al_draw_circle(
				e->position_component.x + e->circle_coll_component.x,
				e->position_component.y + e->circle_coll_component.y,
				e->circle_coll_component.r,
				al_map_rgb(255, 55, 55),
				2
		);
	}
}
