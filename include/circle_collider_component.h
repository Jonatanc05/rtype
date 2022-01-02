#ifndef included_circle_collider_component_h
#define included_circle_collider_component_h

typedef struct Game Game;
typedef struct Entity Entity;

typedef struct {
	int x, y;
	float r;
	void(*on_collide)(Entity* self, Entity* other);
} CircleCollComponent;

void on_collide_die(Entity* self, Entity* other);
void on_collide_nop(Entity* self, Entity* other);

void system_detect_collision(Game* game);

void system_debug_draw_colliders(Game* game);

#endif
