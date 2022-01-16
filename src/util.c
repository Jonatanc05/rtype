#include "util.h"
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
