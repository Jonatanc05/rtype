#include "game.h"

void shoot(Game* game, Entity* player, char isCharged) {
	Entity *beam = entity_create(game, LAYER_BEAM);
	MySprite *spr = isCharged ? game->ch_beam_spr : game->beam_spr;

	SpriteComponent* s_comp = &player->sprite_component;

	entity_set_position(beam,
			player->position_component.x + s_comp->w,
			player->position_component.y + (s_comp->h/2) - ((spr->h * SHOT_SCALE)/2)
		);
	entity_set_velocity(beam, BEAM_VELOCITY, 0);
	entity_set_sprite(beam, spr, 0, 0, SHOT_SCALE);
	float r = beam->sprite_component.h/2.0;
	entity_set_circle_coll(beam,
			beam->sprite_component.w - r, // x
			r, // y
			r, // radius
			isCharged ? on_collide_charged_beam : on_collide_beam); // on_collide callback
	if (isCharged)
		al_play_sample(game->ch_beam_sam, .75, .0, 1.5, ALLEGRO_PLAYMODE_ONCE, NULL);
	//	entity_set_sound(beam, game->ch_beam_sam, 0.75, 1.5, ALLEGRO_PLAYMODE_ONCE, 1);
	else
		al_play_sample(game->beam_sam, 1, .0, 1.4, ALLEGRO_PLAYMODE_ONCE, NULL);
	//	entity_set_sound(beam, game->beam_sam, 1, 1.4, ALLEGRO_PLAYMODE_ONCE, 1);
}

void system_play(Game* game) {
	unsigned mask = PLAYER_COMP_MASK | VELOCITY_COMP_MASK | POSITION_COMP_MASK;
	for (int i = 0; i < game->numEntities; i++) {
		Entity* e = &game->entities[i];
		if ((e->component_mask & mask) != mask)
			continue;

		KEY_STATE *kb = game->keyboard;
		PlayerComponent *p_comp = &e->player_component;
		VelocityComponent *v_comp = &e->velocity_component;
		SpriteComponent *s_comp = &e->sprite_component;

		// Movement
		if (kb[p_comp->up] == KEY_STATE_DOWN)
			v_comp->y -= VELOCITY;
		if (kb[p_comp->up] == KEY_STATE_UP)
			v_comp->y += VELOCITY;
		if (kb[p_comp->left] == KEY_STATE_DOWN)
			v_comp->x -= VELOCITY;
		if (kb[p_comp->left] == KEY_STATE_UP)
			v_comp->x += VELOCITY;
		if (kb[p_comp->down] == KEY_STATE_DOWN)
			v_comp->y += VELOCITY;
		if (kb[p_comp->down] == KEY_STATE_UP)
			v_comp->y -= VELOCITY;
		if (kb[p_comp->right] == KEY_STATE_DOWN)
			v_comp->x += VELOCITY;
		if (kb[p_comp->right] == KEY_STATE_UP)
			v_comp->x -= VELOCITY;

		if (kb[p_comp->shoot] == KEY_STATE_DOWN) {
			p_comp->charge_bar->sound_component.start = 1;
		}
		// Shoot
		char is_charged = p_comp->beam_charge == MAX_BEAM_CHARGE;
		if (kb[p_comp->shoot] == KEY_STATE_HOLD && !is_charged) {
			p_comp->beam_charge += game->delta_time;
			if (p_comp->beam_charge >= MAX_BEAM_CHARGE)
				p_comp->beam_charge  = MAX_BEAM_CHARGE;
		}
		if (kb[p_comp->shoot] == KEY_STATE_UP) {
			p_comp->charge_bar->sound_component.stop = 1;
			shoot(game, e, is_charged);
			p_comp->beam_charge = 0.0;
		}
		p_comp->charge_bar->position_component.x = e->position_component.x;
		p_comp->charge_bar->position_component.y = e->position_component.y - 15;
		p_comp->charge_bar->rectangle_component.w = ((p_comp->beam_charge/MAX_BEAM_CHARGE)*s_comp->w);

		// Animation
		MySprite *correct_spr = NULL;
		if (v_comp->y > 0)
			correct_spr = game->p_down_spr;
		else if (v_comp->y < 0)
			correct_spr = game->p_up_spr;
		else
			correct_spr = game->p_idle_spr;

		s_comp->sprite = correct_spr;
	}
}

int any_player_left(Game* game) {
	for (int i = 0; i < game->numEntities; i++) {
		if (game->entities[i].component_mask & PLAYER_COMP_MASK)
			return 1;
	}
	return 0;
}
