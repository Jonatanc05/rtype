#include "util.h"
#include "game.h"
#include <math.h>
#include <stdlib.h>

const char* const _record_filename = "record.txt";

int record(int score) {
	int record = 0;
	FILE* r = fopen(_record_filename, "r");
	if (r) {
		char str[512] = "0";
		if (!fgets(str, 512, r)) printf("Erro na leitura do arquivo\n");
		if (!sscanf(str, "%d", &record))
			record = printf("Erro no parse do arquivo\n") && 0;
		fclose(r);
	} else printf("Arquivo de recorde nao existe, criando um...\n");

	if (score > record) {
		FILE* w = fopen(_record_filename, "w");
		fprintf(w, "%d", score);
		fclose(w);
	}
	return score > record;
}

void reset_record() {
	if (remove(_record_filename))
		printf("Erro ao resetar recorde\n");
}

MySprite* load_sprite(const char* path) {
	MySprite* s = (MySprite*) malloc(sizeof(MySprite));
	s->bm = al_load_bitmap(path);
	if (!s->bm) {
		printf("Erro ao carregar '%s'\n", path);
		return NULL;
	}
	s->w = al_get_bitmap_width(s->bm);
	s->h = al_get_bitmap_height(s->bm);
	return s;
}

void unload_sprite(MySprite* s) {
	if (!s) return;
	al_destroy_bitmap(s->bm);
	free(s);
}

void create_player(Game* game, int r, int g, int b, ALLEGRO_KEY up, ALLEGRO_KEY le, ALLEGRO_KEY dw, ALLEGRO_KEY ri, ALLEGRO_KEY sh) {
	Entity* bcb = entity_create(game, LAYER_UI);
	entity_set_position(bcb, 0, 0);
	entity_set_rectangle(bcb, 0, 5);
	entity_set_color(bcb, r, g, b, 255);
	entity_set_sound(bcb, game->charging_sam, 1, 2.0, ALLEGRO_PLAYMODE_ONCE, 0);

	Entity* p = entity_create(game, LAYER_PLAYER);
	MySprite* ship_spr = game->p_idle_spr;
	entity_set_position(p, 10, SCREEN_H/2 - (ship_spr->h*SHIP_SCALE)/2);
	entity_set_player(p, up, le, dw, ri, sh, bcb);
	entity_set_sprite(p, ship_spr, 0, 0, SHIP_SCALE);
	entity_set_box_coll(p, p->sprite_component.w, p->sprite_component.h, on_collide_player);
}

void create_ui_element(Game* game, char* text, int y, COLLISION_CALLBACK on_collide) {
	int margin = 10;
	int element_w = al_get_text_width(game->regular_font, text)+2*margin,
		element_h = al_get_font_line_height(game->regular_font)+2*margin;
	int x = SCREEN_W - SCREEN_W/4 - element_w/2;
	Entity *e_rect, *e_text, *e_element;

	e_text = entity_create(game, LAYER_UI);
	entity_set_position(e_text, x, y);
	entity_set_text(e_text, margin, margin, text, REGULAR_FONTSIZE);

	e_rect = entity_create(game, LAYER_UI);
	entity_set_position(e_rect, x, y);
	entity_set_rectangle(e_rect, element_w, element_h);
	entity_set_color(e_rect, 50, 20, 200, 255);

	e_element = entity_create(game, LAYER_UI);
	entity_set_position(e_element, x, y);
	entity_set_uielement(e_element, e_rect, e_text);
	entity_set_box_coll(e_element, element_w, element_h, on_collide);
}

float velocity_towards(int dc, int sc, double max_dist, double max_vel) {
	return ((dc - sc)/max_dist)*max_vel;
}
