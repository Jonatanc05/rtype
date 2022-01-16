#include "util.h"
#include "game.h"
#include <math.h>
#include <stdlib.h>

const char* const _record_filename = "record.txt";

int record(int score) {
	FILE* f = fopen(_record_filename, "w+");
	if (!f) printf("Erro ao abrir arquivo\n");
	char str[512] = "0";
	int record = 0;
	if (!fgets(str, 512, f)) printf("Arquivo de recorde nao existe, criando um...\n");
	if (!sscanf(str, "%d", &record)) printf("Erro no parse do arquivo\n");
	if (score > record) {
		fseek(f, 0, 0);
		fprintf(f, "%d", score);
	}
	fclose(f);
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

	Entity* p = entity_create(game, LAYER_PLAYER);
	MySprite* ship_spr = game->p_idle_spr;
	entity_set_position(p, 10, SCREEN_H/2 - (ship_spr->h*SHIP_SCALE)/2);
	entity_set_player(p, up, le, dw, ri, sh, bcb);
	entity_set_sprite(p, ship_spr, 0, 0, SHIP_SCALE);
	entity_set_box_coll(p, p->sprite_component.w, p->sprite_component.h, on_collide_player);
}
