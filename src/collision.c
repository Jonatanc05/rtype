#include "game.h"
#include <math.h>
#include <allegro5/allegro_primitives.h>

void on_collide_die(Game* game, Entity* self, Entity* other) {
	entity_kill(self);
	if (!any_player_left(game))
		game->over = 1;
}

void on_collide_die_score(Game* game, Entity* self, Entity* other) {
	on_collide_die(game, self, other);
	if (other->layer == LAYER_ENEMY)
		game->score += 10 * (int)other->sprite_component.scale;
}

void on_collide_nop(Game* game, Entity* self, Entity* other)
{}

void on_collide_nop_score(Game* game, Entity* self, Entity* other) {
	on_collide_nop(game, self, other);
	if (other->layer == LAYER_ENEMY)
		game->score += 10 * (int)other->sprite_component.scale;
}

void system_detect_collision(Game* game) {
	unsigned mask = BOX_COMP_MASK | CIRCLE_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		Entity* e1 = &game->entities[i];
		if (!(e1->component_mask & mask))
			continue;

		for (int j = i+1; j < game->numEntities; j++) {
			Entity* e2 = &game->entities[j];
			if (!(e2->component_mask & mask) || !(e1->component_mask & mask))
				continue;

			if ((e1->component_mask & CIRCLE_COMP_MASK & e2->component_mask)
			 && check_coll_circles(&e1->position_component, &e1->circle_coll_component, &e2->position_component, &e2->circle_coll_component)) {
			// both are circle
				e1->circle_coll_component.on_collide(game, e1, e2);
				e2->circle_coll_component.on_collide(game, e2, e1);

			} else if ((e1->component_mask & BOX_COMP_MASK & e2->component_mask)
			 && check_coll_rects(&e1->position_component, &e1->box_coll_component, &e2->position_component, &e2->box_coll_component)) {
			// both are box
				e1->box_coll_component.on_collide(game, e1, e2);
				e2->box_coll_component.on_collide(game, e2, e1);

			} else if ((e1->component_mask & BOX_COMP_MASK)
			 && check_coll_circle_rect(&e2->position_component, &e2->circle_coll_component, &e1->position_component, &e1->box_coll_component)) {
			// e1 is box
				e1->box_coll_component.on_collide(game, e1, e2);
				e2->circle_coll_component.on_collide(game, e2, e1);

			} else if (check_coll_circle_rect(&e1->position_component, &e1->circle_coll_component, &e2->position_component, &e2->box_coll_component)) {
			// e2 is box
				if (e2->box_coll_component.on_collide == NULL) {
					if (e2->circle_coll_component.on_collide)
						e2->circle_coll_component.on_collide(game, e2, e1);
				} else
					e2->box_coll_component.on_collide(game, e2, e1);
				e1->circle_coll_component.on_collide(game, e1, e2);
				printf("%d %d\n", i, j);
			}

		}
	}
}

void system_debug_draw_colliders(Game* game) {
	for (int i = 0; i < game->numEntities; i++) {
		Entity* e = &game->entities[i];
		if (e->component_mask & BOX_COMP_MASK) {
			al_draw_rectangle(
					e->position_component.x,
					e->position_component.y,
					e->position_component.x + e->box_coll_component.w,
					e->position_component.y + e->box_coll_component.h,
					al_map_rgb(255, 55, 55), 2);
		}
		if (e->component_mask & CIRCLE_COMP_MASK) {
			al_draw_circle(
					e->position_component.x + e->circle_coll_component.x,
					e->position_component.y + e->circle_coll_component.y,
					e->circle_coll_component.r,
					al_map_rgb(255, 55, 55),
					2
			);
		}
	}
}

float dist(float x1, float y1, float x2, float y2) {
	return sqrt((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2));
}

int check_coll_circles(PositionComponent* pos1, CircleCollComponent* coll1, PositionComponent* pos2, CircleCollComponent* coll2) {
	int posx1 = pos1->x,
		posy1 = pos1->y,
		posx2 = pos2->x,
		posy2 = pos2->y;
	int x1 = posx1 + coll1->x,
		y1 = posy1 + coll1->y,
		x2 = posx2 + coll2->x,
		y2 = posy2 + coll2->y;
	return dist(x1, y1, x2, y2) < coll1->r + coll2->r;
}

int check_coll_rects(PositionComponent* pos1, BoxCollComponent* coll1, PositionComponent* pos2, BoxCollComponent* coll2) {
	return shadow_intersect(pos1->x, pos1->x + coll1->w, pos2->x, pos2->x + coll2->w)
		&& shadow_intersect(pos1->y, pos1->y + coll1->h, pos2->y, pos2->y + coll2->h);
}

int check_coll_circle_rect(PositionComponent* c_pos, CircleCollComponent* c_coll, PositionComponent* b_pos, BoxCollComponent* b_coll) {
	float cx = c_pos->x + c_coll->x, cy = c_pos->y + c_coll->y;
	float test_x = cx, test_y = cy;
	if (cx < b_pos->x)
		test_x = b_pos->x;
	else if (cx > (b_pos->x + b_coll->w))
		test_x = b_pos->x + b_coll->w;

	if (cy < b_pos->y)
		test_y = b_pos->y;
	else if (cy > (b_pos->y + b_coll->h))
		test_y = b_pos->y + b_coll->h;

	return dist(test_x, test_y, cx, cy) < c_coll->r;
}
