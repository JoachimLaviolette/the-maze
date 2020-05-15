#include <SFML/Graphics.hpp>
#include "Maze.h"
#include "Player.h"

#ifndef GAME_H
#define GAME_H

void game(sf::RenderWindow*, int, int);
int isGameOver(Player, int, int);

#endif