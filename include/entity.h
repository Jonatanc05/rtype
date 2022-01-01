#ifndef included_entity_h
#define included_entity_h

#include "util.h"
#include "position_component.h"
#include "text_component.h"
#include "velocity_component.h"
#include "player_component.h"
#include "sprite_component.h"

#define POSITION_COMP_MASK	0b00000001
#define TEXT_COMP_MASK		0b00000010
#define VELOCITY_COMP_MASK	0b00000100
#define PLAYER_COMP_MASK	0b00001000
#define SPRITE_COMP_MASK	0b00010000

#define MAX_ENTITIES 500

typedef struct Entity {
	short dead;
	unsigned component_mask;

	TextComponent textComponent;
	PositionComponent positionComponent;
	VelocityComponent velocityComponent;
	PlayerComponent playerComponent;
	SpriteComponent spriteComponent;
} Entity;

void entity_kill(Entity* e);

Entity* entity_create(Game* game);

void entity_add_position(Entity* e, int x, int y);

void entity_add_text(Entity* e, int x, int y, char* t, FONT_SIZE fs);

void entity_add_velocity(Entity* e, int x, int y);

void entity_add_player(Entity* e, ALLEGRO_KEY u, ALLEGRO_KEY l, ALLEGRO_KEY d, ALLEGRO_KEY r, ALLEGRO_KEY s);

void entity_add_sprite(Entity* e, MySprite* s, int x, int y, float scale);

#endif
