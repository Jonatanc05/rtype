#include "util.h"
#include <math.h>

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

// Based on https://en.wikipedia.org/wiki/Poisson_distribution#Generating_Poisson-distributed_random_variables
// (not working tho)
int poisson(int max, int expected) {
	int limit = (int)exp(-expected), k = 0;
	double p = 1.0;
	do {
		k++;
		p *= rand()/(double)INT_MAX;
	} while (p < limit);
	if (k > max)
		return 2*max - k;
	return k;
}
