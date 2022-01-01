#include "game.h"
#include <math.h>

int velocity_towards(int dc, int sc, double max_dist, double max_vel) {
	double c_vel = ((dc - sc)/max_dist)*max_vel;
	if (round(c_vel) == 0.0)
		c_vel = (c_vel > 0) ? ceil(c_vel) : floor(c_vel);
	else
		c_vel = round(c_vel);
	return (int)c_vel;
}

void system_enemy_spawner(Game* game, int(*x_distribution)(int, int), int(*y_distribution)(int, int)) {
	int screen_w = al_get_display_width(game->display);
	int x = x_distribution(screen_w + 2*ENEMY_SPAWN_SIEGE, screen_w) - ENEMY_SPAWN_SIEGE;

	int screen_h = al_get_display_height(game->display);
	int y;
	if (x >= -ENEMY_MAX_WIDTH && x < screen_w)
		y = rand()%2 ? -ENEMY_MAX_HEIGHT : screen_h;
	else
		y = y_distribution(screen_h + 2*ENEMY_SPAWN_SIEGE, screen_h/2+ENEMY_SPAWN_SIEGE) - ENEMY_SPAWN_SIEGE;

	Entity* e = entity_create(game);
	entity_add_position(e, x, y);

	int x_margin = screen_w / 5;
	int x_vel = velocity_towards(x_margin + rand()%(screen_w - 2*x_margin), x, screen_w, ENEMY_MAX_XVEL);
	int y_vel = velocity_towards(rand()%screen_h, y, screen_h, ENEMY_MAX_YVEL);
	entity_add_velocity(e, x_vel, y_vel);

	MySprite* spr = load_sprite("rsc\\sprite\\enemy.png");
	entity_add_sprite(e, spr, 0, 0, 2 + (rand()%6)/2.0);
}
