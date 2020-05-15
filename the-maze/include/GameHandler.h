#include <SFML/Graphics.hpp>
#include "Constants.h"

#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H

void gameHandler(sf::RenderWindow*);
OptionType menu(sf::RenderWindow*);
void option(sf::RenderWindow*, OptionType);

#endif