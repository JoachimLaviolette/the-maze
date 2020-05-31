#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include "Constants.h"

// --- Struct
typedef struct Cell {
	int x;
	int y;
	int isVisited;
	int isStart;
	int isEnd;
};

typedef struct Grid {
	int columns;
	int lines;
	Cell* cells;
	Cell* formerCells;
	int *h_walls;
	int *v_walls;
};

// --- Functions
void initializeGrid(Grid);
void initializeCellAt(Grid, int, int);
Cell* getCellAt(Grid, int, int);
void setCellVisited(Cell*, int); 
void setCellStart(Cell*, int);
void setCellEnd(Cell*, int);
Cell* getFormerCellOf(Grid, Cell);
void setFormerCellOf(Grid, Cell, Cell*);
int getWallAt(int, Grid, int, int);
void destroyWallAt(int, Grid, int, int);
int isCellVisited(Cell);
int isStartCell(Cell);
int isEndCell(Cell);
int isWallDestroyed(int, Grid, int, int);
void drawGrid(sf::RenderWindow*, Grid, GameParams);
void drawGridCells(sf::RenderWindow*, Grid);
void drawGridWalls(sf::RenderWindow*, Grid, GameParams);
int isAllCellsVisited(Grid);
void tryGetNeighborCell(Grid, Cell, Cell**, int);
int isAllDirectionsTested(int[4]);
int isDirectionTested(int[4], int);
int isCellEquals(Cell, Cell);

// ---  DEBUG
void DEBUG_displayGrid(Grid);
void DEBUG_displayWalls(Grid);

#endif