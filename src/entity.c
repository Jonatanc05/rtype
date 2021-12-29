#include "game.h"
#include <stdio.h>

void zerar_entity(Entity* e) {
	for (int i = 0; i < sizeof(Entity); i++) {
		*((char*)e + i) = 0;
	}
}

Entity* create_entity(Game *game) {
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

void entity_add_position(Entity* e, int x, int y) {
	e->positionComponent = (PositionComponent*) malloc(sizeof(PositionComponent));
	e->positionComponent->x = 0;
	e->positionComponent->y = 0;
}

void entity_add_text(Entity* e, int x, int y, char* t, FONT_SIZE fs) {
	e->textComponent = (TextComponent*) malloc(sizeof(TextComponent));
	e->textComponent->x = 0;
	e->textComponent->y = 0;
	e->textComponent->text = "Hello World!";
	e->textComponent->fontSize = REGULAR_FONT;
}
