#ifndef included_circle_collider_component_h
#define included_circle_collider_component_h

#include "collision_callbacks.h"

typedef struct {
	int x, y;
	float r;
	COLLISION_CALLBACK on_collide;
} CircleCollComponent;

#endif
