#include "util.h"
#include <math.h>
#include <stdlib.h>

int record(int score) {
	FILE* f = fopen("record.txt", "r+");
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

int uniform(int max, int expected) {
	return rand()%max;
}

int linear(int max, int expected) {
	int s = rand()%max;
	double multiplier = expected / (double)s;
	multiplier *= rand()/(double)RAND_MAX;
	return multiplier * s;
}

int quadratic(int max, int expected) {
	int s = rand()%max;
	double multiplier = expected / (double)s;
	multiplier *= rand()/(double)RAND_MAX;
	s *= multiplier;
	multiplier = expected / (double)s;
	multiplier *= rand()/(double)RAND_MAX;
	return s * multiplier;
}

// Baseado em https://en.wikipedia.org/wiki/Poisson_distribution#Generating_Poisson-distributed_random_variables
// (mas nao funciona)
/*int poisson(int max, int expected) {
	int k = 0;
	double limit = exp(-expected), p = 1.0;
	do {
		k++;
		p *= rand()/(double)RAND_MAX;
	} while (p > limit);
	if (k > max)
		return 2*max - k;
	return k;
}*/
