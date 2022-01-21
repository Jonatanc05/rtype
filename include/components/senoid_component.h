#ifndef _included_senoid_component_h
#define _included_senoid_component_h

typedef struct Game Game;

typedef struct {
	float base_y, amp, period, shift;
} SenoidComponent;

void system_senoid(Game* game);

#endif
