#ifndef included_text_component_h
#define included_text_component_h

#include "allegro5/allegro_font.h"

typedef struct Game Game;

typedef enum FONT_SIZE {
	SMALL_FONT = 0,
	REGULAR_FONT,
	BIG_FONT
} FONT_SIZE;

typedef struct TextComponent {
	char* text;
	FONT_SIZE fontSize;
	int x, y;
} TextComponent;

void text_draw(Game* game);

#endif
