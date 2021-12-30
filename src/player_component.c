#include "game.h"

void shoot(Game* game, Entity* e, char isCharged) {
	Entity *beam = entity_create(game);
	ALLEGRO_BITMAP *b = al_load_bitmap(isCharged ? CHARGED_BEAM_SPRITE_P : BEAM_SPRITE_P);
	if (!b)
		printf("Erro ao carregar bitmap '%s'", isCharged ? CHARGED_BEAM_SPRITE_P : BEAM_SPRITE_P);
	int bh = al_get_bitmap_height(b);
	int bw = al_get_bitmap_width(b);

	entity_add_position(beam,
			e->positionComponent.x + e->spriteComponent.w,
			e->positionComponent.y + (e->spriteComponent.h/2) - (bh/2)
		);
	entity_add_velocity(beam, BEAM_VELOCITY, 0);
	entity_add_sprite(beam, b, 0, 0, bw*SHOT_SCALE, bh*SHOT_SCALE);
}

void system_play(Game* game) {
	unsigned mask = PLAYER_COMP_MASK | VELOCITY_COMP_MASK | POSITION_COMP_MASK;
	for (int i = 0; i < game->numEntities; i += VELOCITY) {
		Entity* e = &game->entities[i];
		if ((e->component_mask & mask) != mask)
			continue;

		KEY_STATE *kb = game->keyboard;
		PlayerComponent *p_comp = &e->playerComponent;
		VelocityComponent *v_comp = &e->velocityComponent;

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
	}
}
