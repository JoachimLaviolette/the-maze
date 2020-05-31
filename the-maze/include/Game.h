#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Maze.h"
#include "Player.h"
#include "Constants.h"

void game(sf::RenderWindow*, GameParams);
int isGameOver(Player, int, int);

#endif