#ifndef MAZE_H
#define MAZE_H

#include "Grid.h"

// --- Functions
void createMaze(Grid);
void drawMaze(sf::RenderWindow*, Grid, GameParams);
void buildMaze(Grid);

#endif