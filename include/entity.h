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
#include "components/color_component.h"
#include "components/uielement_component.h"
#include "components/sound_component.h"
#include "collision_callbacks.h"

#define POSITION_COMP_MASK  0b0000000000000001
#define TEXT_COMP_MASK      0b0000000000000010
#define VELOCITY_COMP_MASK  0b0000000000000100
#define PLAYER_COMP_MASK    0b0000000000001000
#define SPRITE_COMP_MASK    0b0000000000010000
#define CIRCLE_COMP_MASK    0b0000000000100000
#define RECTANGLE_COMP_MASK 0b0000000001000000
#define BOX_COMP_MASK       0b0000000010000000
#define COLOR_COMP_MASK     0b0000000100000000
#define UIELEMENT_COMP_MASK 0b0000001000000000
#define SOUND_COMP_MASK     0b0000010000000000

typedef enum LAYER {
	LAYER_NULL = 0,
	LAYER_STAR,
	LAYER_ENEMY,
	LAYER_BLOCK,
	LAYER_BEAM,
	LAYER_PLAYER,
	LAYER_UI,
	LAYER_INVISIBLE
} LAYER;

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
	BoxCollComponent box_coll_component;
	RectangleComponent rectangle_component;
	ColorComponent color_component;
	UiElementComponent uielement_component;
	SoundComponent sound_component;
} Entity;

Entity* entity_create(Game* game, LAYER layer);

void entity_kill(Entity* e);

void zerar_entity(Entity* e);

void entity_set_position(Entity* e, int x, int y);

void entity_set_text(Entity* e, int x, int y, char* t, FONT_SIZE fs);

void entity_set_velocity(Entity* e, int x, int y);

void entity_set_player(Entity* e, ALLEGRO_KEY u, ALLEGRO_KEY l, ALLEGRO_KEY d, ALLEGRO_KEY r, ALLEGRO_KEY s, Entity* cb);

void entity_set_sprite(Entity* e, MySprite* s, int x, int y, float scale);

void entity_set_circle_coll(Entity* e, int x, int y, float r, COLLISION_CALLBACK on_collide);

void entity_set_rectangle(Entity* e, float w, float h);

void entity_set_box_coll(Entity* e, int w, int h, COLLISION_CALLBACK on_collide);

void entity_set_color(Entity* e, int r, int g, int b, int a);

void entity_set_uielement(Entity* e, Entity* r, Entity* t);

void entity_set_sound(Entity* e, ALLEGRO_SAMPLE* s, float g, int pm, int start);

#endif
