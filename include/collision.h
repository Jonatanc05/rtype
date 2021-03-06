#ifndef _included_collision_h
#define _included_collision_h

typedef struct Game Game;
typedef struct Entity Entity;

#include "components/position_component.h"
#include "components/circle_collider_component.h"
#include "components/box_collider_component.h"

#define shadow_intersect(s1, f1, s2, f2) (((f1)>(s2))&&((s1)<(f2)))

void system_detect_collision(Game* game);

void system_debug_draw_colliders(Game* game);

float dist(float x1, float y1, float x2, float y2);
int check_coll_circles(PositionComponent* pos1, CircleCollComponent* coll1, PositionComponent* pos2, CircleCollComponent* coll2);
int check_coll_rects(PositionComponent* pos1, BoxCollComponent* coll1, PositionComponent* pos2, BoxCollComponent* coll2);
int check_coll_circle_rect(PositionComponent* c_pos, CircleCollComponent* c_coll, PositionComponent* b_pos, BoxCollComponent* b_coll);

#endif
