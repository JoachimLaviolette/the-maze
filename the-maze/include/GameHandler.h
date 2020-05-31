#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H

#include <SFML/Graphics.hpp>
#include "Constants.h"

void gameHandler(sf::RenderWindow*, GameParams*);
void option(sf::RenderWindow*, OptionType, GameParams*);

#endif