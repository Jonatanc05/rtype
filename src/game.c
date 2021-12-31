#include "game.h"
#include <math.h>

int uniform(int max, int expected) {
	return rand()%max;
}

// Based on https://en.wikipedia.org/wiki/Poisson_distribution#Generating_Poisson-distributed_random_variables
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

int velocity_towards(int dc, int sc, double max_dist, double max_vel) {
	double c_vel = ((dc - sc)/max_dist)*max_vel;
	if (round(c_vel) == 0.0)
		c_vel = (c_vel > 0) ? ceil(c_vel) : floor(c_vel);
	else
		c_vel = round(c_vel);
	return (int)c_vel;
}

#define ENEMY_MAX_XVEL 4.0
#define ENEMY_MAX_YVEL 3.0
void system_enemy_spawner(Game* game, int(*x_distribution)(int, int), int(*y_distribution)(int, int)) {
	int screen_w = al_get_display_width(game->display);
	int x = x_distribution(screen_w + 20, screen_w);

	int screen_h = al_get_display_height(game->display);
	int y = y_distribution(screen_h, screen_h/2);

	Entity* e = entity_create(game);
	entity_add_position(e, x, y);

	int x_margin = screen_w / 5;
	int x_vel = velocity_towards(x_margin + rand()%(screen_w - 2*x_margin), x, screen_w, ENEMY_MAX_XVEL);
	int y_vel = velocity_towards(rand()%screen_h, y, screen_h, ENEMY_MAX_YVEL);
	entity_add_velocity(e, x_vel, y_vel);

	ALLEGRO_BITMAP* b = al_load_bitmap("rsc\\sprite\\enemy.png");
	if (!b) printf("Erro\n");
	entity_add_sprite(e, b, 0, 0, al_get_bitmap_width(b), al_get_bitmap_height(b));
}
