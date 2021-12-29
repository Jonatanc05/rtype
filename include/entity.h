#ifndef included_entity_h
#define included_entity_h

#include "position_component.h"
#include "text_component.h"

#define POSITION_COMP_MASK	0b00000001
#define TEXT_COMP_MASK		0b00000010

#define MAX_ENTITIES 500

typedef struct Entity {
	short dead;
	unsigned component_mask;

	TextComponent textComponent;
	PositionComponent positionComponent;
} Entity;

Entity* entity_create(Game* game);

void entity_add_position(Entity* e, int x, int y);

void entity_add_text(Entity* e, int x, int y, char* t, FONT_SIZE fs);

void entity_kill(Entity* e);

#endif
