#ifndef included_entity_h
#define included_entity_h

#include "util.h"
#include "position_component.h"
#include "text_component.h"
#include "velocity_component.h"
#include "player_component.h"
#include "sprite_component.h"
#include "circle_collider_component.h"
#include "rectangle_component.h"

typedef unsigned LAYER;
#define LAYER_STAR		0b00000001
#define LAYER_ENEMY		0b00000010
#define LAYER_PLAYER	0b00000100
#define LAYER_UI		0b00001000

#define POSITION_COMP_MASK	0b00000001
#define TEXT_COMP_MASK		0b00000010
#define VELOCITY_COMP_MASK	0b00000100
#define PLAYER_COMP_MASK	0b00001000
#define SPRITE_COMP_MASK	0b00010000
#define CIRCLE_COMP_MASK	0b00100000
#define RECTANGLE_COMP_MASK	0b01000000

#define MAX_ENTITIES 100

typedef struct Entity {
	short dead;
	unsigned component_mask;
	LAYER layer;

	TextComponent text_component;
	PositionComponent position_component;
	VelocityComponent velocity_component;
	PlayerComponent player_component;
	SpriteComponent sprite_component;
	CircleCollComponent circle_coll_component;
	RectangleComponent rectangle_component;
} Entity;

Entity* entity_create(Game* game);

void entity_kill(Entity* e);

void zerar_entity(Entity* e);

void entity_add_position(Entity* e, int x, int y);

void entity_add_text(Entity* e, int x, int y, char* t, FONT_SIZE fs);

void entity_add_velocity(Entity* e, int x, int y);

void entity_add_player(Entity* e, ALLEGRO_KEY u, ALLEGRO_KEY l, ALLEGRO_KEY d, ALLEGRO_KEY r, ALLEGRO_KEY s);

void entity_add_sprite(Entity* e, MySprite* s, int x, int y, float scale);

void entity_add_circle_coll(Entity* e, int x, int y, float r, void(*on_collide)(Game* game, Entity* a, Entity* b));

void entity_add_rectangle(Entity* e, float w, float h);

#endif
