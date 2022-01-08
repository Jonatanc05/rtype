#ifndef _included_box_collider_component_h
#define _included_box_collider_component_h

#include "collision_callbacks.h"

typedef struct {
	int w, h;
	COLLISION_CALLBACK on_collide;
} BoxCollComponent;

#endif
