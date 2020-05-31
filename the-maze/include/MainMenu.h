#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SFML/Graphics.hpp>
#include "Constants.h"

// --- Functions
OptionType mainMenu(sf::RenderWindow*);
void initMainMenu(sf::RenderWindow*);
void drawMainMenu(sf::RenderWindow*);
OptionType handleMainMenuInputs(sf::RenderWindow*);

#endif