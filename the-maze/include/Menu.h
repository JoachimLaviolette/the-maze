#include <SFML/Graphics.hpp>
#include "Constants.h"

#ifndef MENU_H
#define MENU_H

// --- Functions
void loadAssets();
void initMenu();
OptionType menu(sf::RenderWindow*);
void settingsMenu(sf::RenderWindow*, int*, int*);
void drawMainMenu(sf::RenderWindow*);
void drawLogo(sf::RenderWindow*);
void drawOptions(sf::RenderWindow*);
void drawSettingsMenu(sf::RenderWindow*);
int isCursorOver(sf::RenderWindow*, OptionType);
OptionType handleMenuInputs(sf::RenderWindow*);
int handleSettingsMenuInputs(sf::RenderWindow*, sf::Event);
int isNumKeyPressed();
sf::String getStringFromKeyCode(int);

#endif