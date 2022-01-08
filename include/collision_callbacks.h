#ifndef _included_collision_callbacks_h
#define _included_collision_callbacks_h

typedef struct Game Game;
typedef struct Entity Entity;
typedef void(*COLLISION_CALLBACK)(Game* game, Entity* self, Entity* other);

// Collision callbacks
void on_collide_die(Game* game, Entity* self, Entity* other);
void on_collide_die_score(Game* game, Entity* self, Entity* other);
void on_collide_nop(Game* game, Entity* self, Entity* other);
void on_collide_nop_score(Game* game, Entity* self, Entity* other);

#endif
