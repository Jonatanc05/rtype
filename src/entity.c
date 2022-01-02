#include "game.h"
#include <stdio.h>

void zerar_entity(Entity* e) {
	if (e->spriteComponent.sprite)
		al_destroy_bitmap(e->spriteComponent.sprite->bm);
	free(e->spriteComponent.sprite);
	e->spriteComponent.sprite = NULL;
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
	e->positionComponent.x = x;
	e->positionComponent.y = y;
}

void entity_add_text(Entity* e, int x, int y, char* t, FONT_SIZE fs) {
	e->component_mask |= TEXT_COMP_MASK;
	e->textComponent.x = x;
	e->textComponent.y = y;
	e->textComponent.text = t;
	e->textComponent.fontSize = fs;
}

void entity_add_velocity(Entity* e, int x, int y) {
	if (!(e->component_mask & POSITION_COMP_MASK))
		entity_add_position(e, 0, 0);
	e->component_mask |= VELOCITY_COMP_MASK;
	e->velocityComponent.x = x;
	e->velocityComponent.y = y;
}

void entity_add_player(Entity* e, ALLEGRO_KEY u, ALLEGRO_KEY l, ALLEGRO_KEY d, ALLEGRO_KEY r, ALLEGRO_KEY s) {
	if (!(e->component_mask & VELOCITY_COMP_MASK))
		entity_add_velocity(e, 0, 0);
	e->component_mask |= PLAYER_COMP_MASK;
	e->playerComponent.up = u;
	e->playerComponent.left = l;
	e->playerComponent.down = d;
	e->playerComponent.right = r;
	e->playerComponent.shoot = s;
	e->playerComponent.beamCharge = 0;
}

void entity_add_sprite(Entity* e, MySprite* s, int x, int y, float scale) {
	if (!(e->component_mask & POSITION_COMP_MASK))
		entity_add_position(e, 0, 0);
	e->component_mask |= SPRITE_COMP_MASK;
	e->spriteComponent.x = x;
	e->spriteComponent.y = y;
	sprite_component_set(&e->spriteComponent, s, scale);
}

void entity_add_circle_coll(Entity* e, int x, int y, float r, void(*on_collide)(Entity* a, Entity* b)) {
	if (!(e->component_mask & POSITION_COMP_MASK))
		entity_add_position(e, 0, 0);
	e->component_mask |= CIRCLE_COMP_MASK;
	e->circleCollComponent.x = x;
	e->circleCollComponent.y = y;
	e->circleCollComponent.r = r;
	e->circleCollComponent.on_collide = on_collide;
}
