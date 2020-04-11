#include <SFML/Graphics.hpp>

#ifndef GRID_H
#define GRID_H

// --- Struct
typedef struct Grid {
	int columns;
	int lines;
	int *cells;
	int *h_walls;
	int *v_walls;
};

// --- Functions
void initializeGrid(Grid*);
int getCellAt(Grid, int, int);
void setCellAt(Grid*, int, int, int);
int getWallAt(int, Grid, int, int);
void destroyWallAt(int, Grid*, int, int);
int isCellVisited(Grid, int, int);
int isWallDestroyed(int, Grid, int, int);
void drawGrid(sf::RenderWindow*, Grid);
void drawGridCells(sf::RenderWindow*, Grid);
void drawGridWalls(sf::RenderWindow*, Grid);

// ---  DEBUG
void DEBUG_displayGrid(Grid);

#endif