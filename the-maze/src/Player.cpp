#include "../include/Constants.h"
#include "../include/Player.h"

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

	if (!isWallDestroyed(dir == UP || dir == DOWN, grid, xOut, yOut)) return;

	player->x = xOut;
	player->y = yOut;
}

void drawPlayer(sf::RenderWindow* window, Player player) {
	using namespace sf;

	CircleShape playerShape(CELL_SIZE / 3);
	playerShape.setFillColor(Color::Blue);
	playerShape.setOrigin(Vector2f(.5, .5));
	playerShape.setPosition(Vector2f(player.x * CELL_SIZE + playerShape.getRadius() / 2, player.y * CELL_SIZE + playerShape.getRadius() / 2));
	window->draw(playerShape);
}

void handlePlayerInputs(Grid grid, Player* player) {
	using namespace sf;

	int isKeyPressed = false;
	int dir = NONE;

	if (!isKeyPressed) {
		if (Keyboard::isKeyPressed(Keyboard::Up)) dir = UP;
		if (Keyboard::isKeyPressed(Keyboard::Right)) dir = RIGHT;
		if (Keyboard::isKeyPressed(Keyboard::Down)) dir = DOWN;
		if (Keyboard::isKeyPressed(Keyboard::Left)) dir = LEFT;
		if (dir != NONE) {
			movePlayer(grid, player, dir);
			isKeyPressed = true;
		}
	}
	else isKeyPressed = false;	
}