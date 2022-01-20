typedef struct Game Game;

typedef struct {
	float x, y;
} VelocityComponent;

void system_move(Game* game);
