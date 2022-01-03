#include "circle_collider_component.h"
#include "game.h"
#include <math.h>
#include <allegro5/allegro_primitives.h>

void on_collide_die(Game* game, Entity* self, Entity* other) {
	self->dead = 1;
}
void on_collide_die_score(Game* game, Entity* self, Entity* other) {
	on_collide_die(game, self, other);
	if (other->component_mask & SPRITE_COMP_MASK)
		game->score += 10 * (int)other->sprite_component.scale;
}

void on_collide_nop(Game* game, Entity* self, Entity* other) {}
void on_collide_nop_score(Game* game, Entity* self, Entity* other) {
	on_collide_nop(game, self, other);
	if (other->component_mask & SPRITE_COMP_MASK)
		game->score += 10 * (int)other->sprite_component.scale;
}

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
				coll1->on_collide(game, e1, e2);
				coll2->on_collide(game, e2, e1);
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
