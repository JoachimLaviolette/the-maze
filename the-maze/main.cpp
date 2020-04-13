#include "include/Constants.h"
#include "include/Maze.h"
#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), WINDOW_TITLE);

	const int columns = 5;
	const int lines = 5;

	Cell cells[columns][lines];
	int h_walls[columns][lines + 1];
	int v_walls[columns + 1][lines];

	Grid grid;
	grid.columns = columns;
	grid.lines = lines;
	grid.cells = (Cell *)cells;
	grid.h_walls = (int *)h_walls;
	grid.v_walls = (int *)v_walls;

	createMaze(&grid);

	while (window.isOpen())
	{
		window.clear(sf::Color(59,59,59));
		drawMaze(&window, grid);
		window.display();
	}

	return 0;
}