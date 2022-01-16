#include "game.h"

void on_collide_die(Game* game, Entity* self, Entity* other) {
	entity_kill(self);
}

void on_collide_player(Game* game, Entity* self, Entity* other) {
	entity_kill(self->player_component.charge_bar);
	entity_kill(self);
	if (!any_player_left(game))
		game->over = 1;
}

void on_collide_block(Game* game, Entity* self, Entity* other)
{}

void on_collide_beam(Game* game, Entity* self, Entity* other) {
	switch (other->layer) {
		case LAYER_PLAYER:
		case LAYER_BEAM:
			break;
		case LAYER_ENEMY:
			game->score += 10 * (int)other->sprite_component.scale;
		default:
			entity_kill(self);
	}
}

void on_collide_charged_beam(Game* game, Entity* self, Entity* other) {
	switch (other->layer) {
		case LAYER_ENEMY:
			game->score += 10 * (int)other->sprite_component.scale;
			break;
		case LAYER_BLOCK:
		case LAYER_UI:
			entity_kill(self);
			break;
	}
}

void on_collide_start_game(Game* game, Entity* self, Entity* other) {
	if (other->layer == LAYER_BEAM) {
		game->started = 1;
		for (int i = 0; i < game->numEntities; i++) {
			Entity* e = &game->entities[i];
			if (e->component_mask & UIELEMENT_COMP_MASK) {
				entity_kill(e->uielement_component.rect);
				entity_kill(e->uielement_component.text);
				entity_kill(e);
			}
		}
	}
}

void on_collide_add_player(Game* game, Entity* self, Entity* other) {

}

void on_collide_reset_record(Game* game, Entity* self, Entity* other) {

}
