#include "../include/Constants.h"
#include "../include/Player.h"

int isKeyPressed = 0;

void movePlayer(Grid grid, Player* player, int dir) {
	// First, check maze's edges
	if (dir == UP && player->y == 0) return;
	if (dir == DOWN && player->y == grid.lines - 1) return;
	if (dir == LEFT && player->x == 0) return;
	if (dir == RIGHT && player->x == grid.columns - 1) return;

	// Then, check if walls
	int xOut = player->x;
	int yOut = player->y;

	if (dir == UP) --yOut;
	else if (dir == DOWN) ++yOut;
	else if (dir == LEFT) --xOut;
	else ++xOut;

	switch (dir) {
		case UP: if (!isWallDestroyed(1, grid, xOut, yOut + 1)) return; break;
		case DOWN: if (!isWallDestroyed(1, grid, xOut, yOut)) return; break;
		case LEFT: if (!isWallDestroyed(0, grid, xOut + 1, yOut)) return; break;
		default: if (!isWallDestroyed(0, grid, xOut, yOut)) return; break;
	}

	player->x = xOut;
	player->y = yOut;
}

void drawPlayer(sf::RenderWindow* window, Player player) {
	using namespace sf;

	CircleShape playerShape(CELL_SIZE / 4);
	playerShape.setFillColor(sf::Color(224, 38, 100));
	playerShape.setPosition(
		Vector2f(
			player.x * (float) CELL_SIZE + (float) CELL_SIZE / 2 - playerShape.getRadius(), 
			player.y * (float) CELL_SIZE + (float) CELL_SIZE / 2 - playerShape.getRadius()
		)
	);
	window->draw(playerShape);
}

void handlePlayerInputs(Grid grid, Player* player) {
	using namespace sf;
	
	int dir = LEFT;

	if (isMoveKeyPressed()) {
		if (!isKeyPressed) {
			if (Keyboard::isKeyPressed(Keyboard::Up)) dir = UP;
			else if (Keyboard::isKeyPressed(Keyboard::Right)) dir = RIGHT;
			else if (Keyboard::isKeyPressed(Keyboard::Down)) dir = DOWN;
			movePlayer(grid, player, dir);
			isKeyPressed = 1;
		}
	}
	else isKeyPressed = 0;
}

int isMoveKeyPressed() {
	using namespace sf;

	return (Keyboard::isKeyPressed(Keyboard::Up)) 
		|| (Keyboard::isKeyPressed(Keyboard::Right)) 
		|| (Keyboard::isKeyPressed(Keyboard::Down)) 
		|| (Keyboard::isKeyPressed(Keyboard::Left));
}