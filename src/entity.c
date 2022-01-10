#include "game.h"
#include <stdio.h>

Entity* get_entity_slot(Game* game) {
	for (int i = 0; i < game->numEntities; i++) {
		if (0 == game->entities[i].component_mask)
			return &game->entities[i];
	}

	if (game->numEntities == MAX_ENTITIES) {
		printf("O limite de entidades foi atingido\n");
		return NULL;
	}

	return &game->entities[game->numEntities++];
}
Entity* entity_create(Game *game, LAYER layer) {
	Entity* e = get_entity_slot(game);
	e->layer = layer;
	return e;
}

void entity_kill(Entity* e) {
	e->dead = 1;
	e->component_mask = 0;
}

void zerar_entity(Entity* e) {
	e->dead = 0;
	e->component_mask = 0;
	e->layer = LAYER_NULL;
}

void entity_set_position(Entity* e, int x, int y) {
	e->component_mask |= POSITION_COMP_MASK;
	e->position_component.x = x;
	e->position_component.y = y;
}

void entity_set_text(Entity* e, int x, int y, char* t, FONT_SIZE fs) {
	if (!(e->component_mask & POSITION_COMP_MASK))
		entity_set_position(e, 0, 0);
	e->component_mask |= TEXT_COMP_MASK;
	e->text_component.x = x;
	e->text_component.y = y;
	e->text_component.text = t;
	e->text_component.fontSize = fs;
}

void entity_set_velocity(Entity* e, int x, int y) {
	if (!(e->component_mask & POSITION_COMP_MASK))
		entity_set_position(e, 0, 0);
	e->component_mask |= VELOCITY_COMP_MASK;
	e->velocity_component.x = x;
	e->velocity_component.y = y;
}

void entity_set_player(Entity* e, ALLEGRO_KEY u, ALLEGRO_KEY l, ALLEGRO_KEY d, ALLEGRO_KEY r, ALLEGRO_KEY s) {
	if (!(e->component_mask & SPRITE_COMP_MASK))
		entity_set_sprite(e, NULL, 0, 0, 0.0);
	if (!(e->component_mask & VELOCITY_COMP_MASK))
		entity_set_velocity(e, 0, 0);
	e->component_mask |= PLAYER_COMP_MASK;
	e->player_component.up = u;
	e->player_component.left = l;
	e->player_component.down = d;
	e->player_component.right = r;
	e->player_component.shoot = s;
	e->player_component.beamCharge = 0;
}

void entity_set_sprite(Entity* e, MySprite* s, int x, int y, float scale) {
	if (!(e->component_mask & POSITION_COMP_MASK))
		entity_set_position(e, 0, 0);
	e->component_mask |= SPRITE_COMP_MASK;
	e->sprite_component.sprite = s;
	e->sprite_component.scale = scale;
	e->sprite_component.x = x;
	e->sprite_component.y = y;
	if (s) {
		e->sprite_component.w = s->w * scale;
		e->sprite_component.h = s->h * scale;
	}
}

void entity_set_circle_coll(Entity* e, int x, int y, float r, COLLISION_CALLBACK on_collide) {
	if (!(e->component_mask & POSITION_COMP_MASK))
		entity_set_position(e, 0, 0);
	e->component_mask |= CIRCLE_COMP_MASK;
	e->circle_coll_component.x = x;
	e->circle_coll_component.y = y;
	e->circle_coll_component.r = r;
	e->circle_coll_component.on_collide = on_collide;
}

void entity_set_rectangle(Entity* e, float w, float h) {
	if (!(e->component_mask & POSITION_COMP_MASK))
		entity_set_position(e, 0, 0);
	e->component_mask |= RECTANGLE_COMP_MASK;
	e->rectangle_component.w = w;
	e->rectangle_component.h = h;
}

void entity_set_box_coll(Entity* e, int w, int h, COLLISION_CALLBACK on_collide) {
	e->component_mask |= BOX_COMP_MASK;
	e->box_coll_component.on_collide = on_collide;
	e->box_coll_component.w = w;
	e->box_coll_component.h = h;
}

void entity_set_color(Entity* e, int r, int g, int b, int a) {
	e->component_mask |= COLOR_COMP_MASK;
	e->color_component.r = r;
	e->color_component.g = g;
	e->color_component.b = b;
	e->color_component.a = a;
}
