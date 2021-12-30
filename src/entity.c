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
	e->positionComponent.x = 0;
	e->positionComponent.y = 0;
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
	e->velocityComponent.x = 0;
	e->velocityComponent.y = 0;
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
}
