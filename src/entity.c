#include "game.h"
#include <stdio.h>

void zerar_entity(Entity* e) {
	if (e->sprite_component.sprite)
		al_destroy_bitmap(e->sprite_component.sprite->bm);
	free(e->sprite_component.sprite);
	e->sprite_component.sprite = NULL;
	e->dead = 0;
	e->component_mask = 0;
}

Entity* entity_create(Game *game) {
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

void entity_kill(Entity* e) {
	e->dead = 1;
	e->component_mask = 0;
}

void entity_add_position(Entity* e, int x, int y) {
	e->component_mask |= POSITION_COMP_MASK;
	e->position_component.x = x;
	e->position_component.y = y;
}

void entity_add_text(Entity* e, int x, int y, char* t, FONT_SIZE fs) {
	e->component_mask |= TEXT_COMP_MASK;
	e->text_component.x = x;
	e->text_component.y = y;
	e->text_component.text = t;
	e->text_component.fontSize = fs;
}

void entity_add_velocity(Entity* e, int x, int y) {
	if (!(e->component_mask & POSITION_COMP_MASK))
		entity_add_position(e, 0, 0);
	e->component_mask |= VELOCITY_COMP_MASK;
	e->velocity_component.x = x;
	e->velocity_component.y = y;
}

void entity_add_player(Entity* e, ALLEGRO_KEY u, ALLEGRO_KEY l, ALLEGRO_KEY d, ALLEGRO_KEY r, ALLEGRO_KEY s) {
	if (!(e->component_mask & VELOCITY_COMP_MASK))
		entity_add_velocity(e, 0, 0);
	e->component_mask |= PLAYER_COMP_MASK;
	e->player_component.up = u;
	e->player_component.left = l;
	e->player_component.down = d;
	e->player_component.right = r;
	e->player_component.shoot = s;
	e->player_component.beamCharge = 0;
}

void entity_add_sprite(Entity* e, MySprite* s, int x, int y, float scale) {
	if (!(e->component_mask & POSITION_COMP_MASK))
		entity_add_position(e, 0, 0);
	e->component_mask |= SPRITE_COMP_MASK;
	e->sprite_component.x = x;
	e->sprite_component.y = y;
	sprite_component_set(&e->sprite_component, s, scale);
}

void entity_add_circle_coll(Entity* e, int x, int y, float r, void(*on_collide)(Entity* a, Entity* b)) {
	if (!(e->component_mask & POSITION_COMP_MASK))
		entity_add_position(e, 0, 0);
	e->component_mask |= CIRCLE_COMP_MASK;
	e->circle_coll_component.x = x;
	e->circle_coll_component.y = y;
	e->circle_coll_component.r = r;
	e->circle_coll_component.on_collide = on_collide;
}
