#include "game.h"
#include <math.h>
#include <stdio.h>

void on_game_init(Game* game) {
	srand(time(NULL));

	game->over = 0;
	for (int i = 0; i <= ALLEGRO_KEY_MAX; i++)
		game->keyboard[i] = 0;
	game->numEntities = 0;
	game->entities = (Entity*) calloc(MAX_ENTITIES, sizeof(Entity));
	if (game->entities == NULL) printf("Erro ao alocar memoria para entidades\n");

	// Inicializa sprites
	game->airmine_spr = load_sprite(AIRMINE_SPRITE_P);
	game->p_idle_spr =  load_sprite(SHIP_IDLE_SPRITE_P);
	game->p_up_spr =    load_sprite(SHIP_UP_SPRITE_P);
	game->p_down_spr =  load_sprite(SHIP_DOWN_SPRITE_P);
	game->beam_spr =    load_sprite(BEAM_SPRITE_P);
	game->ch_beam_spr = load_sprite(CHARGED_BEAM_SPRITE_P);

	// Criar jogador
	Entity* p = entity_create(game);
	MySprite* ship_spr = game->p_idle_spr;
	entity_set_position(p, 10, SCREEN_H/2 - (ship_spr->h*SHIP_SCALE)/2);
	entity_set_player(p, ALLEGRO_KEY_W,
			ALLEGRO_KEY_A, ALLEGRO_KEY_S, ALLEGRO_KEY_D,
						ALLEGRO_KEY_SPACE
	);
	entity_set_sprite(p, ship_spr, 0, 0, SHIP_SCALE);
	entity_set_box_coll(p, p->sprite_component.w, p->sprite_component.h, on_collide_die);

	// Criar pontuação
	Entity* t = entity_create(game);
	game->score = 0;
	game->score_str = (char*)malloc(sizeof(char)*10);
	*game->score_str = '\0';
	entity_set_text(t, 0, 0, game->score_str, REGULAR_FONTSIZE);
}

int _game_finished = 0;
void on_update(Game* game) {
	game->tick = al_get_timer_count(game->timer);
	if (game->over && !_game_finished) {
		_game_finished = 1;

		Entity* go = entity_create(game);
		entity_set_position(go, SCREEN_W/2 - 140, SCREEN_H/2 - 50);
		entity_set_text(go, 0, 0, "Game Over", REGULAR_FONTSIZE);

		Entity* sc = entity_create(game);
		entity_set_position(sc, SCREEN_W/2 - 220, SCREEN_H/2 + 10);
		char* str = (char*) malloc(sizeof(char)*30); *str = '\0'; sprintf(str, "Your score: %d", game->score);
		entity_set_text(sc, 0, 0, str, REGULAR_FONTSIZE);

		if (record(game->score)) {
			Entity* nr = entity_create(game);
			entity_set_position(nr, SCREEN_W/2 - 160, SCREEN_H/2 + 70);
			entity_set_text(nr, 0, 0, "New record!", REGULAR_FONTSIZE);
		}
	}
	else if (!game->over)
		system_score(game);

	system_play(game);
	system_move(game);
	system_stars(game);
	system_detect_collision(game);
	system_clean_dead_entities(game);
	system_airmine_spawner(game);
	system_block_spawner(game);

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
	unload_sprite(game->airmine_spr);
	unload_sprite(game->p_idle_spr);
	unload_sprite(game->p_up_spr);
	unload_sprite(game->p_down_spr);
	unload_sprite(game->beam_spr);
	unload_sprite(game->ch_beam_spr);
}

int velocity_towards(int dc, int sc, double max_dist, double max_vel) {
	double c_vel = ((dc - sc)/max_dist)*max_vel;
	if (round(c_vel) == 0.0)
		c_vel = (c_vel > 0) ? ceil(c_vel) : floor(c_vel);
	else
		c_vel = round(c_vel);
	return (int)c_vel;
}

void system_airmine_spawner(Game* game) {
	if (game->tick%(int)(FPS/AIRMINES_P_SECOND) != 0)
		return;

	MySprite* spr = game->airmine_spr;
	float spr_scale = AIRMINE_MIN_SCALE + (rand()/(float)RAND_MAX)*(AIRMINE_MAX_SCALE-AIRMINE_MIN_SCALE);
	float radius = spr->w*spr_scale/2.0;
	int w = spr->w*spr_scale, h = spr->h*spr_scale;

	int screen_w = al_get_display_width(game->display);
	int x = rand()%(screen_w + w) - w;

	int screen_h = al_get_display_height(game->display);
	int y = rand()%2 ? -h : screen_h;

	Entity* e = entity_create(game);
	entity_set_position(e, x, y);

	// Set airmine velocity towards a random point in screen within a margin
	int x_margin = screen_w / 5;
	int x_vel = velocity_towards(x_margin + rand()%(screen_w - 2*x_margin), x, screen_w, AIRMINE_MAX_XVEL);
	int y_vel = velocity_towards(rand()%screen_h, y, screen_h, AIRMINE_MAX_YVEL);
	entity_set_velocity(e, x_vel, y_vel);

	entity_set_sprite(e, spr, 0, 0, spr_scale);
	entity_set_circle_coll(e, w/2, h/2, radius, on_collide_die);
}

double _timestamp_of_last_block_spawn = 0.0; // in seconds
int _there_is_block = 0;
void system_block_spawner(Game* game) {
	if (_there_is_block) return;
	double last = _timestamp_of_last_block_spawn,
		   current = game->tick/(double)FPS;
	if (current - last < BLOCK_SPAWN_TEST_INTERVAL)
		return;
	if ((rand()/(float)RAND_MAX)*100 > BLOCK_SPAWN_TEST_CHANCE)
		return;

	_timestamp_of_last_block_spawn = current;

	// Determine position and dimensions
	int s_w = al_get_display_width(game->display),
		s_h = al_get_display_height(game->display),
		sy  = rand()%(4*s_h/5);
	if (sy < game->p_idle_spr->h*SHIP_SCALE) sy = 0;
	int  w = s_w * (1 + ((rand()/(float)RAND_MAX)*BLOCK_MAX_WIDTH)),
		 h = s_h/5 + rand()%(s_h - sy - s_h/5);

	Entity* e = entity_create(game);
	entity_set_position(e, s_w, sy);
	entity_set_velocity(e, -BLOCK_VELOCITY, 0);
	entity_set_rectangle(e, w, h);
	entity_set_box_coll(e, w, h, on_collide_nop);
	e->layer = LAYER_BLOCK;
	_there_is_block = 1;
}

void system_clean_dead_entities(Game* game) {
	for (int i = 0; i < game->numEntities; i++) {
		Entity* e = &game->entities[i];
		int s_w = al_get_display_width(game->display), s_h = al_get_display_height(game->display);
		if (e->component_mask & POSITION_COMP_MASK
			 && e->layer != LAYER_BLOCK
			 && (
				 e->position_component.x > s_w + AIRMINE_SPAWN_SIEGE*2
			  || e->position_component.x < -AIRMINE_SPAWN_SIEGE*2
			  || e->position_component.y > s_h + AIRMINE_SPAWN_SIEGE*2
			  || e->position_component.y < -AIRMINE_SPAWN_SIEGE*2
			 )
		) {
			entity_kill(e);
		} else if (e->layer == LAYER_BLOCK
				&& e->position_component.x + e->box_coll_component.w < 0) {
			_there_is_block = 0;
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
		entity_set_position(e,
				al_get_display_width(game->display),
				(int)rand()%(int)(al_get_display_height(game->display)-size));
		entity_set_velocity(e, -velocity, 0);
		entity_set_rectangle(e, size, size);
	}
}

void system_score(Game* game) {
	if(game->tick%FPS == 0)
		game->score += 50;
	sprintf(game->score_str, "%09d", game->score);
}
