#include "include/Constants.h"
#include "include/Grid.h"
#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), WINDOW_TITLE);

	const int columns = 6;
	const int lines = 6;

	int cells[columns][lines];
	int h_walls[columns][lines + 1];
	int v_walls[columns + 1][lines];

	Grid grid;
	grid.columns = columns;
	grid.lines = lines;
	grid.cells = (int *)cells;
	grid.h_walls = (int *)h_walls;
	grid.v_walls = (int *)v_walls;
	
	initializeGrid(&grid);
	setCellAt(&grid, 2, 1, 1);
	DEBUG_displayGrid(grid);

	while (window.isOpen())
	{
		window.clear(sf::Color(59,59,59));
		drawGrid(&window, grid);
		window.display();
	}

	return 0;
}