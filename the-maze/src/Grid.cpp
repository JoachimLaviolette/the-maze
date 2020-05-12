#include "../include/Constants.h"
#include "../include/Grid.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void initializeGrid(Grid grid) {
	for (int x = 0; x < grid.columns; ++x) 
		for (int y = 0; y < grid.lines; ++y) 
			initializeCellAt(grid, x, y);	

	for (int x = 0; x < (grid.columns) * (grid.lines + 1); ++x) *(grid.h_walls + x) = 1;
	for (int x = 0; x < (grid.columns + 1) * (grid.lines); ++x) *(grid.v_walls + x) = 1;
}

void initializeCellAt(Grid grid, int x, int y) {
	(*(grid.cells + x * grid.lines + y)).x = x;
	(*(grid.cells + x * grid.lines + y)).y = y;
	(*(grid.cells + x * grid.lines + y)).value = 0;
	(*(grid.formerCells + x * grid.lines + y)).x = -1;
	(*(grid.formerCells + x * grid.lines + y)).y = -1;
}

Cell* getCellAt(Grid grid, int x, int y) {
	return grid.cells + x * grid.lines + y;
}

void setCellVisited(Cell* cell, int value) {
	cell->value = value;
}

Cell* getFormerCellOf(Grid grid, Cell cell) {
	return grid.formerCells + cell.x * grid.lines + cell.y;
}

void setFormerCellOf(Grid grid, Cell cell, Cell* formerCell) {
	*(grid.formerCells + cell.x * grid.lines + cell.y) = *formerCell;
}

int getWallAt(int isHorizontal, Grid grid, int x, int y) {
	return *((isHorizontal ? grid.h_walls : grid.v_walls) + x * (isHorizontal ? grid.lines + 1 : grid.lines) + y);
}

void destroyWallAt(int isHorizontal, Grid grid, int x, int y) {
	*((isHorizontal ? grid.h_walls : grid.v_walls) + x * (isHorizontal ? grid.lines + 1 : grid.lines) + y) = 0;
}

int isCellVisited(Cell cell) {
	return cell.value == 1;
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
			cell.setFillColor(isCellVisited(*getCellAt(grid, x, y)) ? Color::Yellow : Color::Red);
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
			sf::Color wallColor = sf::Color::Red;

			if (!(x == 0 || x == grid.columns)) {
				if (isWallDestroyed(0, grid, x, y)) continue;
			}

			RectangleShape wall(Vector2f(WALL_SIZE, CELL_SIZE));
			wall.setFillColor(wallColor);
			wall.setPosition(Vector2f(x * CELL_SIZE, y * CELL_SIZE));
			window->draw(wall);
		}
	}
	
	// Draw horizontal walls
	for (int x = 0; x < grid.columns; ++x) {
		for (int y = 0; y < grid.lines + 1; ++y) {
			sf::Color wallColor = sf::Color::Red;

			if (!(y == 0 || y == grid.lines)) {
				if (isWallDestroyed(1, grid, x, y)) continue;
			}

			RectangleShape wall(Vector2f(CELL_SIZE, WALL_SIZE));
			wall.setFillColor(wallColor);
			wall.setPosition(Vector2f(x * CELL_SIZE, y * CELL_SIZE));
			window->draw(wall);
		}
	}
}

int isAllCellsVisited(Grid grid) {
	for (int x = 0; x < grid.columns; ++x) 
		for (int y = 0; y < grid.lines; ++y) 
			if (!isCellVisited(*getCellAt(grid, x, y))) return 0;

	return 1;
}

void tryGetNeighborCell(Grid grid, Cell currentCell, Cell** neighborCell, int dir) {
	// First, handle special cases
	if (dir == UP && currentCell.y == 0) return;
	if (dir == DOWN && currentCell.y == grid.lines - 1) return;
	if (dir == LEFT && currentCell.x == 0) return;
	if (dir == RIGHT && currentCell.x == grid.columns - 1) return;

	// Now, handle normal cases
	int xOut = currentCell.x;
	int yOut = currentCell.y;

	if (dir == UP) --yOut;
	else if (dir == DOWN) ++yOut;
	else if (dir == LEFT) --xOut;
	else ++xOut;

	if (!isCellVisited(*getCellAt(grid, xOut, yOut))) *neighborCell = getCellAt(grid, xOut, yOut);
}

int isCellEquals(Cell c0, Cell c1) {
	return c0.x == c1.x && c0.y == c1.y;
}

void DEBUG_displayGrid(Grid grid) {
	for (int x = 0; x < grid.columns; ++x)
		for (int y = 0; y < grid.lines; ++y)
			std::cout << "Grid [" << x << "][" << y << "]: " << getCellAt(grid, x, y)->value << std::endl;
}

void DEBUG_displayWalls(Grid grid) {
	printf("::::::::::::: HORIZONTAL WALLS :::::::::::::\n");
	for (int x = 0; x < grid.columns; ++x)
		for (int y = 0; y < grid.lines + 1; ++y)
			std::cout << "Wall [" << x << "][" << y << "]: " << getWallAt(1, grid, x, y) << std::endl;

	printf("::::::::::::: VERTICAL WALLS :::::::::::::\n");
	for (int x = 0; x < grid.columns + 1; ++x)
		for (int y = 0; y < grid.lines; ++y)
			std::cout << "Wall [" << x << "][" << y << "]: " << getWallAt(0, grid, x, y) << std::endl;

}
