#include <SFML/Graphics.hpp>
#include "Constants.h"

#ifndef MENU_H
#define MENU_H

// --- Functions
void loadAssets();
void initMenu();
void drawMenu(sf::RenderWindow*);
void drawLogo(sf::RenderWindow*);
void drawOptions(sf::RenderWindow*);
int isCursorOver(sf::RenderWindow*, OptionType);
OptionType handleMenuInputs(sf::RenderWindow*);

#endif