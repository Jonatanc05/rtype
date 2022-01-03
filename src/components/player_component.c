#include "game.h"

void shoot(Game* game, Entity* player, char isCharged) {
	Entity *beam = entity_create(game);
	MySprite *spr = load_sprite(isCharged ? CHARGED_BEAM_SPRITE_P : BEAM_SPRITE_P);

	SpriteComponent* s_comp = &player->sprite_component;

	entity_add_position(beam,
			player->position_component.x + s_comp->w,
			player->position_component.y + (s_comp->h/2) - ((spr->h * SHOT_SCALE)/2)
		);
	entity_add_velocity(beam, BEAM_VELOCITY, 0);
	entity_add_sprite(beam, spr, 0, 0, SHOT_SCALE);
	float r = beam->sprite_component.h/2.0;
	entity_add_circle_coll(beam,
			beam->sprite_component.w - r, // x
			r, // y
			r, // radius
			isCharged ? on_collide_nop_score : on_collide_die_score); // on_collide callback
}

void system_play(Game* game) {
	unsigned mask = PLAYER_COMP_MASK | VELOCITY_COMP_MASK | POSITION_COMP_MASK;
	for (int i = 0; i < game->numEntities; i += VELOCITY) {
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

		// Shoot
		char isCharged = p_comp->beamCharge == MAX_BEAM_CHARGE;
		if (kb[p_comp->shoot] == KEY_STATE_HOLD && !isCharged)
			p_comp->beamCharge++;
		if (kb[p_comp->shoot] == KEY_STATE_UP) {
			shoot(game, e, isCharged);
			p_comp->beamCharge = 0;
		}

		// Animation
		if (v_comp->y > 0)
			sprite_component_set(s_comp, load_sprite(SHIP_DOWN_SPRITE_P), SHIP_SCALE);
		else if (v_comp->y < 0)
			sprite_component_set(s_comp, load_sprite(SHIP_UP_SPRITE_P), SHIP_SCALE);
		else
			sprite_component_set(s_comp, load_sprite(SHIP_IDLE_SPRITE_P), SHIP_SCALE);
	}
}
