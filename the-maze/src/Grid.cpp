#include "../include/Constants.h"
#include "../include/Grid.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void initializeGrid(Grid* grid) {
	for (int x = 0; x < grid->columns * grid->lines; ++x) *(grid->cells + x) = 0;
	for (int x = 0; x < (grid->columns) * (grid->lines + 1); ++x) *(grid->h_walls + x) = 1;
	for (int x = 0; x < (grid->columns + 1) * (grid->lines); ++x) *(grid->v_walls + x) = 1;
}

int getCellAt(Grid grid, int x, int y) {
	return *(grid.cells + x * grid.lines + y);
}

void setCellAt(Grid* grid, int x, int y, int value) {
	*(grid->cells + x * grid->lines + y) = value;
}

int getWallAt(int isHorizontal, Grid grid, int x, int y) {
	return *((isHorizontal ? grid.h_walls : grid.v_walls) + x * grid.lines + y);
}

void destroyWallAt(int isHorizontal, Grid* grid, int x, int y) {
	*((isHorizontal ? grid->h_walls : grid->v_walls) + x * grid->lines + y) = 0;
}

int isCellVisited(Grid grid, int x, int y) {
	return getCellAt(grid, x, y) == 1;
}

int isWallDestroyed(int isHorizontal, Grid grid, int x, int y) {
	return getWallAt(isHorizontal, grid, x, y) == 0;
}

void drawGrid(sf::RenderWindow* window, Grid grid) {
	drawGridCells(window, grid);
	drawGridWalls(window, grid);
}

void drawGridCells(sf::RenderWindow* window, Grid grid) {
	using namespace sf;

	for (int x = 0; x < grid.columns; ++x) {
		for (int y = 0; y < grid.lines; ++y) {
			RectangleShape cell(Vector2f(CELL_SIZE, CELL_SIZE));
			cell.setFillColor(isCellVisited(grid, x, y) ? Color::Red : Color::Black);
			cell.setPosition(Vector2f(x * CELL_SIZE, y * CELL_SIZE));

			window->draw(cell);
		}
	}
}

void drawGridWalls(sf::RenderWindow* window, Grid grid) {
	using namespace sf;

	// Draw horizontal walls
	for (int x = 0; x < grid.columns; ++x) {
		for (int y = 0; y < grid.lines + 1; ++y) {
			RectangleShape wall(Vector2f(CELL_SIZE, WALL_SIZE));
			wall.setFillColor(isWallDestroyed(1, grid, x, y) ? Color::Black : Color::White);
			wall.setPosition(Vector2f(x * CELL_SIZE, y * CELL_SIZE));

			window->draw(wall);
		}
	}

	// Draw vertical walls
	for (int x = 0; x < grid.columns + 1; ++x) {
		for (int y = 0; y < grid.lines; ++y) {
			RectangleShape wall(Vector2f(WALL_SIZE, CELL_SIZE));
			wall.setFillColor(isWallDestroyed(1, grid, x, y) ? Color::Black : Color::White);
			wall.setPosition(Vector2f(x * CELL_SIZE, y * CELL_SIZE));

			window->draw(wall);
		}
	}
}

void DEBUG_displayGrid(Grid grid) {
	for (int x = 0; x < grid.columns; ++x)
		for (int y = 0; y < grid.lines; ++y)
			std::cout << "Grid [" << x << "][" << y << "]: " << getCellAt(grid, x, y) << std::endl;
}
