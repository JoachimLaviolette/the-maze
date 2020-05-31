#ifndef MENU_SETTINGS_H
#define MENU_SETTINGS_H

#include <SFML/Graphics.hpp>
#include "Constants.h"

const int MAX_SELECTABLE_COLORS = 12;

// --- Functions
void settingsMenu(sf::RenderWindow*, GameParams*);
void initSettingsMenu(sf::RenderWindow*, GameParams);
void drawSettingsMenu(sf::RenderWindow*, GameParams);
int handleSettingsMenuInputs(sf::RenderWindow*, sf::Event);
void saveParams(GameParams*);

#endif