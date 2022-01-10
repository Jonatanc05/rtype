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
			entity_kill(self);
			break;
	}
}

