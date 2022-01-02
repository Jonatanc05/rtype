#ifndef included_text_component_h
#define included_text_component_h

#include "allegro5/allegro_font.h"

typedef struct Game Game;

typedef enum FONT_SIZE {
	SMALL_FONTSIZE = 0,
	REGULAR_FONTSIZE,
	BIG_FONTSIZE
} FONT_SIZE;

typedef struct TextComponent {
	char* text;
	FONT_SIZE fontSize;
	int x, y;
} TextComponent;

void system_draw_text(Game* game);

#endif
