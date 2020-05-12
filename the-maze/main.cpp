#include "include/Constants.h"
#include "include/Maze.h"
#include "include/Player.h"
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>

int main() {
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), WINDOW_TITLE);

	const int columns = 18;
	const int lines = 13;

	Cell cells[columns][lines];
	Cell formerCells[columns][lines];
	int h_walls[columns][lines + 1];
	int v_walls[columns + 1][lines];

	Grid grid;
	grid.columns = columns;
	grid.lines = lines;
	grid.cells = (Cell *)cells;
	grid.formerCells = (Cell *)formerCells;
	grid.h_walls = (int *)h_walls;
	grid.v_walls = (int *)v_walls;

	Player player;
	player.id = 0;
	player.x = 0;
	player.y = 0;

	createMaze(grid);

	while (window.isOpen())
	{
		window.clear(sf::Color(59,59,59));
		drawMaze(&window, grid);
		handlePlayerInputs(grid, &player);
		drawPlayer(&window, player);
		window.display();
	}

	return 0;
}