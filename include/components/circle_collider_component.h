#ifndef included_circle_collider_component_h
#define included_circle_collider_component_h

typedef struct Game Game;
typedef struct Entity Entity;

typedef struct {
	int x, y;
	float r;
	void(*on_collide)(Game* game, Entity* self, Entity* other);
} CircleCollComponent;

void on_collide_die(Game* game, Entity* self, Entity* other);
void on_collide_die_score(Game* game, Entity* self, Entity* other);
void on_collide_nop(Game* game, Entity* self, Entity* other);
void on_collide_nop_score(Game* game, Entity* self, Entity* other);

void system_detect_collision(Game* game);

void system_debug_draw_colliders(Game* game);

#endif
