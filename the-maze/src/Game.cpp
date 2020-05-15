#include "../include/Game.h"

void game(sf::RenderWindow* window) {
	int xStart = 0;
	int yStart = 6;
	int xEnd = 15;
	int yEnd = 9;
	int isGameOver = false;
	
	Grid grid;
	Player player;

	const int columns = 18;
	const int lines = 13;

	Cell cells[columns][lines];
	Cell formerCells[columns][lines];
	int h_walls[columns][lines + 1];
	int v_walls[columns + 1][lines];

	grid.columns = columns;
	grid.lines = lines;
	grid.cells = (Cell *)cells;
	grid.formerCells = (Cell *)formerCells;
	grid.h_walls = (int *)h_walls;
	grid.v_walls = (int *)v_walls;

	createMaze(grid);
	setCellStart(getCellAt(grid, xStart, yStart), 1);
	setCellEnd(getCellAt(grid, xEnd, yEnd), 1);

	player.id = 0;
	player.x = xStart;
	player.y = yStart;

	while (!isGameOver && window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event)) if (event.type == sf::Event::Closed) window->close();

		window->clear(sf::Color(0, 0, 0));

		drawMaze(window, grid);
		handlePlayerInputs(grid, &player);
		drawPlayer(window, player);

		window->display();
	}
}