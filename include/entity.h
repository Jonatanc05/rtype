#ifndef included_entity_h
#define included_entity_h

#include "position_component.h"
#include "text_component.h"

#define MAX_ENTITIES 500

typedef struct Entity {
	short dead;
	TextComponent* textComponent;
	PositionComponent* positionComponent;
} Entity;

Entity* create_entity(Game* game);

void entity_add_position(Entity* e, int x, int y);

void entity_add_text(Entity* e, int x, int y, char* t, FONT_SIZE fs);

#endif
