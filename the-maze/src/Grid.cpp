#include "../include/Constants.h"
#include "../include/Grid.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void initializeGrid(Grid* grid) {
	for (int x = 0; x < grid->columns; ++x) 
		for (int y = 0; y < grid->lines; ++y) 
			initializeCellAt(*grid, x, y);	

	for (int x = 0; x < (grid->columns) * (grid->lines + 1); ++x) *(grid->h_walls + x) = 1;
	for (int x = 0; x < (grid->columns + 1) * (grid->lines); ++x) *(grid->v_walls + x) = 1;
}

void initializeCellAt(Grid grid, int x, int y) {
	(*(grid.cells + x * grid.lines + y)).x = x;
	(*(grid.cells + x * grid.lines + y)).y = y;
	(*(grid.cells + x * grid.lines + y)).value = 0;
	(*(grid.cells + x * grid.lines + y)).formerCell_x = -1;
	(*(grid.cells + x * grid.lines + y)).formerCell_y = -1;
}

Cell getCellAt(Grid grid, int x, int y) {
	return *(grid.cells + x * grid.lines + y);
}

void setCellValue(Grid grid, Cell cell, int value) {
	(*(grid.cells + cell.x * grid.lines + cell.y)).value = value;
}

void setCellFormerCell(Grid grid, Cell cell, Cell formerCell) {
	(*(grid.cells + cell.x * grid.lines + cell.y)).formerCell_x = formerCell.x;
	(*(grid.cells + cell.x * grid.lines + cell.y)).formerCell_y = formerCell.y;
}

int getWallAt(int isHorizontal, Grid grid, int x, int y) {
	return *((isHorizontal ? grid.h_walls : grid.v_walls) + x * (isHorizontal ? grid.lines + 1 : grid.lines) + y);
}

void destroyWallAt(int isHorizontal, Grid* grid, int x, int y) {
	*((isHorizontal ? grid->h_walls : grid->v_walls) + x * (isHorizontal ? grid->lines + 1 : grid->lines) + y) = 0;
}

int isCellVisited(Grid grid, int x, int y) {
	return getCellAt(grid, x, y).value == 1;
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
			cell.setFillColor(/*isCellVisited(grid, x, y) ? Color::Red : */Color::Black);
			cell.setPosition(Vector2f(x * CELL_SIZE, y * CELL_SIZE));
			window->draw(cell);
		}
	}
}

void drawGridWalls(sf::RenderWindow* window, Grid grid) {
	using namespace sf;

	// Draw vertical walls
	for (int x = 0; x < grid.columns + 1; ++x) {
		for (int y = 0; y < grid.lines; ++y) {
			sf::Color wallColor = x == 0 || y == grid.columns ? sf::Color::White 
				: isWallDestroyed(0, grid, x, y) ? Color::Black : Color::White;

			RectangleShape wall(Vector2f(WALL_SIZE, CELL_SIZE));
			wall.setFillColor(wallColor);
			wall.setPosition(Vector2f(x * CELL_SIZE, y * CELL_SIZE));
			window->draw(wall);
		}
	}
	
	// Draw horizontal walls
	for (int x = 0; x < grid.columns; ++x) {
		for (int y = 0; y < grid.lines + 1; ++y) {
			sf::Color wallColor = y == 0 || y == grid.lines ? sf::Color::White
			: isWallDestroyed(1, grid, x, y) ? Color::Black : Color::White;

			RectangleShape wall(Vector2f(CELL_SIZE, WALL_SIZE));
			wall.setFillColor(wallColor);
			wall.setPosition(Vector2f(x * CELL_SIZE, y * CELL_SIZE));
			window->draw(wall);
		}
	}
}

int isAllCellsVisited(Grid* grid) {
	for (int x = 0; x < grid->columns; ++x) 
		for (int y = 0; y < grid->lines; ++y) 
			if (!isCellVisited(*grid, x, y)) return 0;

	return 1;
}

void tryGetNeighborCell(Grid grid, Cell currentCell, Cell* neighborCell, int dir) {
	// First, handle special cases
	if (dir == UP && currentCell.y == 0) return;
	if (dir == DOWN && currentCell.y == grid.lines - 1) return;
	if (dir == LEFT && currentCell.x == 0) return;
	if (dir == RIGHT && currentCell.x == grid.columns - 1) return;

	// Now, handle normal cases
	neighborCell->x = currentCell.x;
	neighborCell->y = currentCell.y;

	if (dir == UP) --neighborCell->y;
	else if (dir == DOWN) ++neighborCell->y;
	else if (dir == LEFT) --neighborCell->x;
	else ++neighborCell->x;

	neighborCell = &getCellAt(grid, neighborCell->x, neighborCell->y);
}

void DEBUG_displayGrid(Grid grid) {
	for (int x = 0; x < grid.columns; ++x)
		for (int y = 0; y < grid.lines; ++y)
			std::cout << "Grid [" << x << "][" << y << "]: " << getCellAt(grid, x, y).value << std::endl;
}
