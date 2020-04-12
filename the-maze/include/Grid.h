#include <SFML/Graphics.hpp>

#ifndef GRID_H
#define GRID_H

// --- Struct
typedef struct Cell {
	int x;
	int y;
	int value;
	int formerCell_x;
	int formerCell_y;
};

typedef struct Grid {
	int columns;
	int lines;
	Cell *cells;
	int *h_walls;
	int *v_walls;
};

// --- Functions
void initializeGrid(Grid*);
void initializeCellAt(Grid, int, int);
Cell getCellAt(Grid, int, int);
void setCellValue(Grid, Cell, int); 
void setCellFormerCell(Grid, Cell, Cell);
int getWallAt(int, Grid, int, int);
void destroyWallAt(int, Grid*, int, int);
int isCellVisited(Grid, int, int);
int isWallDestroyed(int, Grid, int, int);
void drawGrid(sf::RenderWindow*, Grid);
void drawGridCells(sf::RenderWindow*, Grid);
void drawGridWalls(sf::RenderWindow*, Grid);
int isAllCellsVisited(Grid*);
void tryGetNeighborCell(Grid, Cell, Cell*, int);
int isAllDirectionsTested(int[4]);
int isDirectionTested(int[4], int);

// ---  DEBUG
void DEBUG_displayGrid(Grid);

#endif