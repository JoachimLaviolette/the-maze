#include "../include/Game.h"

void game(sf::RenderWindow* window, int l, int c) {
	int xStart = 0;
	int yStart = 0;
	int xEnd = 19;
	int yEnd = 9;
	int gameOver = false;

	Grid grid;
	Player player;

	const int columns = 20;
	const int lines = 10;

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

	/*
	Cell** cells = (Cell**)malloc(columns * sizeof(Cell*));
	Cell** formerCells = (Cell**)malloc(columns * sizeof(Cell*));
	int** h_walls = (int**)malloc(columns * sizeof(int*));
	int** v_walls = (int**)malloc(columns + 1 * sizeof(int*));

	for (int i = 0; i < columns; i++) cells[i] = (Cell*)malloc(lines * sizeof(Cell));
	for (int i = 0; i < columns; i++) formerCells[i] = (Cell*)malloc(lines * sizeof(Cell));
	for (int i = 0; i < columns; i++) h_walls[i] = (int*)malloc(lines + 1 * sizeof(Cell));
	for (int i = 0; i < columns + 1; i++) v_walls[i] = (int*)malloc(lines * sizeof(Cell));

	grid.columns = columns;
	grid.lines = lines;
	grid.cells = cells;
	grid.formerCells = formerCells;
	grid.h_walls = h_walls;
	grid.v_walls = v_walls;
	*/

	createMaze(grid);
	setCellStart(getCellAt(grid, xStart, yStart), 1);
	setCellEnd(getCellAt(grid, xEnd, yEnd), 1);

	player.id = 0;
	player.x = xStart;
	player.y = yStart;

	while (!gameOver && window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event)) if (event.type == sf::Event::Closed) window->close();

		window->clear(sf::Color(0, 0, 0));

		drawMaze(window, grid);
		handlePlayerInputs(grid, &player);
		drawPlayer(window, player);

		window->display();

		gameOver = isGameOver(player, xEnd, yEnd);
	}
}

int isGameOver(Player player, int xEnd, int yEnd) {
	return  player.x == xEnd && player.y == yEnd;
}