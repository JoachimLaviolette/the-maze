#ifndef PLAYER_H
#define PLAYER_H

#include "../include/Grid.h"
#include <SFML/Graphics.hpp>

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
int isMoveKeyPressed();

#endif PLAYER_H