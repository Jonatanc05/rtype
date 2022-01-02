typedef struct Game Game;

typedef struct {
	int x, y;
} VelocityComponent;

void system_move(Game* game);
