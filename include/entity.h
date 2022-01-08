#ifndef included_entity_h
#define included_entity_h

#include "util.h"
#include "components/position_component.h"
#include "components/text_component.h"
#include "components/velocity_component.h"
#include "components/player_component.h"
#include "components/sprite_component.h"
#include "components/circle_collider_component.h"
#include "components/rectangle_component.h"
#include "components/box_collider_component.h"
#include "collision_callbacks.h"

typedef unsigned LAYER;
#define LAYER_STAR			0b00000001
#define LAYER_ENEMY			0b00000010
#define LAYER_PLAYER		0b00000100
#define LAYER_UI			0b00001000
#define LAYER_PROJECTILE	0b00010000

#define POSITION_COMP_MASK	0b00000001
#define TEXT_COMP_MASK		0b00000010
#define VELOCITY_COMP_MASK	0b00000100
#define PLAYER_COMP_MASK	0b00001000
#define SPRITE_COMP_MASK	0b00010000
#define CIRCLE_COMP_MASK	0b00100000
#define RECTANGLE_COMP_MASK	0b01000000
#define BOX_COMP_MASK		0b10000000

#define MAX_ENTITIES 100

typedef struct Entity {
	short dead;
	unsigned component_mask;

	TextComponent text_component;
	PositionComponent position_component;
	VelocityComponent velocity_component;
	PlayerComponent player_component;
	SpriteComponent sprite_component;
	CircleCollComponent circle_coll_component;
	BoxCollComponent box_coll_component;
	RectangleComponent rectangle_component;
} Entity;

Entity* entity_create(Game* game);

void entity_kill(Entity* e);

void zerar_entity(Entity* e);

void entity_set_position(Entity* e, int x, int y);

void entity_set_text(Entity* e, int x, int y, char* t, FONT_SIZE fs);

void entity_set_velocity(Entity* e, int x, int y);

void entity_set_player(Entity* e, ALLEGRO_KEY u, ALLEGRO_KEY l, ALLEGRO_KEY d, ALLEGRO_KEY r, ALLEGRO_KEY s);

void entity_set_sprite(Entity* e, MySprite* s, int x, int y, float scale);

void entity_set_circle_coll(Entity* e, int x, int y, float r, COLLISION_CALLBACK on_collide);

void entity_set_rectangle(Entity* e, float w, float h);

void entity_set_box_coll(Entity* e, int w, int h, COLLISION_CALLBACK on_collide);

#endif
