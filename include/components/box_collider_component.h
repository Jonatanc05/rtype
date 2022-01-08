#ifndef _included_box_collider_component_h
#define _included_box_collider_component_h

#include "components/circle_collider_component.h"

typedef struct {
	int w, h;
	COLLISION_CALLBACK on_collide;
} BoxCollComponent;

#endif
