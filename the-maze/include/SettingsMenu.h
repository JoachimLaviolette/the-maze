#ifndef MENU_SETTINGS_H
#define MENU_SETTINGS_H

#include <SFML/Graphics.hpp>
#include "Constants.h"

void settingsMenu(sf::RenderWindow*, GameParams*);
void drawSettingsMenu(sf::RenderWindow*);
int handleSettingsMenuInputs(sf::RenderWindow*, sf::Event);
void saveParams(GameParams*);

#endif