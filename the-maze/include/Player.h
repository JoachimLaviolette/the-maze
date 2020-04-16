#include "../include/Grid.h"
#include <SFML/Graphics.hpp>

#ifndef PLAYER_H
#define PLAYER_H

// --- Struct
typedef struct Player {
	int id;
	int x;
	int y;
};

// --- Functions
void movePlayer(Grid, Player*, int);
void drawPlayer(sf::RenderWindow*, Player);
void handlePlayerInputs(Grid, Player*);

#endif PLAYER_H