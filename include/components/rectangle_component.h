#ifndef included_rectangle_component_h
#define included_rectangle_component_h

typedef struct Game Game;

typedef struct {
	float w, h;
} RectangleComponent;

void system_draw_rectangles(Game* game);

#endif
