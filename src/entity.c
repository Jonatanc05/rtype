#include "game.h"
#include <stdio.h>

void zerar_entity(Entity* e) {
	e->dead = 0;
	e->component_mask = 0;
}

Entity* entity_create(Game *game) {
	int pos = -1;
	for (int i = 0; i < game->numEntities; i++) {
		if (game->entities[i].dead) {
			pos = i;
			break;
		}
	}

	if (pos != -1) {
		zerar_entity(&game->entities[pos]);
		return &game->entities[pos];
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
	if (e->component_mask & SPRITE_COMP_MASK) {
		al_destroy_bitmap(e->spriteComponent.sprite->bm);
		free(e->spriteComponent.sprite);
	}
	e->component_mask |= SPRITE_COMP_MASK;
	e->spriteComponent.sprite = s;
	e->spriteComponent.x = x;
	e->spriteComponent.y = y;
	e->spriteComponent.scale = scale;
}
