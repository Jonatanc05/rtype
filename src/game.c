#include "game.h"
#include <math.h>
#include <stdio.h>

void on_game_init(Game* game) {
	srand(time(NULL));

	for (int i = 0; i <= ALLEGRO_KEY_MAX; i++)
		game->keyboard[i] = 0;
	game->over = 0;
	game->numEntities = 0;
	game->entities = (Entity*) calloc(MAX_ENTITIES, sizeof(Entity));
	if (game->entities == NULL) printf("Erro ao alocar memoria para entidades\n");

	// Criar jogador
	Entity* p = entity_create(game);
	MySprite* ship_spr = load_sprite(SHIP_IDLE_SPRITE_P);
	entity_add_position(p, 10, SCREEN_H/2 - (ship_spr->h*SHIP_SCALE)/2);
	entity_add_player(p, ALLEGRO_KEY_W,
			ALLEGRO_KEY_A, ALLEGRO_KEY_S, ALLEGRO_KEY_D,
						ALLEGRO_KEY_SPACE
	);
	entity_add_sprite(p, ship_spr, 0, 0, SHIP_SCALE);
	entity_add_box_coll(p, p->sprite_component.w, p->sprite_component.h, on_collide_die);

	// Criar pontuação
	Entity* t = entity_create(game);
	game->score = 0;
	game->score_str = (char*)malloc(sizeof(char)*10);
	*game->score_str = '\0';
	entity_add_text(t, 0, 0, game->score_str, REGULAR_FONTSIZE);
}

int _record = 0;
void on_update(Game* game) {
	if (game->over && !_record) {
		_record = 1;

		Entity* go = entity_create(game);
		entity_add_position(go, SCREEN_W/2 - 140, SCREEN_H/2 - 50);
		entity_add_text(go, 0, 0, "Game Over", REGULAR_FONTSIZE);

		Entity* sc = entity_create(game);
		entity_add_position(sc, SCREEN_W/2 - 220, SCREEN_H/2 + 10);
		char* str = (char*) malloc(sizeof(char)*30); *str = '\0'; sprintf(str, "Your score: %d", game->score);
		entity_add_text(sc, 0, 0, str, REGULAR_FONTSIZE);

		if (record(game->score)) { // Read record.dat
			Entity* nr = entity_create(game);
			entity_add_position(nr, SCREEN_W/2 - 160, SCREEN_H/2 + 70);
			entity_add_text(nr, 0, 0, "New record!", REGULAR_FONTSIZE);
		}
	}
	else if (!game->over)
		system_score(game);

	system_play(game);
	system_move(game);
	system_stars(game);
	system_detect_collision(game);
	system_clean_dead_entities(game);
	system_enemy_spawner(game, quadratic, linear);

	al_clear_to_color(al_map_rgb(0, 0, 0));
	system_draw_rectangles(game);
	system_draw_sprites(game);
	system_draw_text(game);
#ifdef _DEBUG
	system_debug_draw_colliders(game);
#endif
}

void on_game_exit(Game* game) {
	free(game->entities);
	free(game->score_str);
}

int velocity_towards(int dc, int sc, double max_dist, double max_vel) {
	double c_vel = ((dc - sc)/max_dist)*max_vel;
	if (round(c_vel) == 0.0)
		c_vel = (c_vel > 0) ? ceil(c_vel) : floor(c_vel);
	else
		c_vel = round(c_vel);
	return (int)c_vel;
}

void system_enemy_spawner(Game* game, int(*x_distribution)(int, int), int(*y_distribution)(int, int)) {
	if (al_get_timer_count(game->timer)%(int)(FPS/ENEMIES_P_SECOND) != 0)
		return;

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

	entity_add_sprite(e, load_sprite(ENEMY_SPRITE_P), 0, 0, 2 + (rand()%6)/2.0);
	entity_add_circle_coll(e,
			e->sprite_component.w/2,
			e->sprite_component.h/2,
			e->sprite_component.h < e->sprite_component.w/2 ? e->sprite_component.h : e->sprite_component.w/2,
			on_collide_die
	);
}

void system_clean_dead_entities(Game* game) {
	for (int i = 0; i < game->numEntities; i++) {
		Entity* e = &game->entities[i];
		if (e->component_mask & POSITION_COMP_MASK
			 && (
				 e->position_component.x > al_get_display_width(game->display) + ENEMY_SPAWN_SIEGE
			  || e->position_component.x < -ENEMY_SPAWN_SIEGE
			  || e->position_component.y > al_get_display_height(game->display) + ENEMY_SPAWN_SIEGE
			  || e->position_component.y < -ENEMY_SPAWN_SIEGE
			 )
		) {
			entity_kill(e);
		}
		if (e->dead)
			zerar_entity(e);

	}
}

void system_stars(Game* game) {
	if (rand()%100 < STAR_SPAWN_CHANCE) {
		float mul = (rand()/(float)RAND_MAX);
		float size = STAR_MIN_SIZE + ((STAR_MAX_SIZE - STAR_MIN_SIZE) * mul);
		int velocity = (int)(STAR_MIN_VEL + ((STAR_MAX_VEL - STAR_MIN_VEL) * (1.0-mul)));
		Entity* e = entity_create(game);
		entity_add_position(e,
				al_get_display_width(game->display),
				(int)rand()%(int)(al_get_display_height(game->display)-size));
		entity_add_velocity(e, -velocity, 0);
		entity_add_rectangle(e, size, size);
	}
}

void system_score(Game* game) {
	if(al_get_timer_count(game->timer)%FPS == 0)
		game->score += 50;
	sprintf(game->score_str, "%09d", game->score);
}
