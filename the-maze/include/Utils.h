#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include "Constants.h"

// --- Functions
int isCursorOver(sf::RenderWindow*, sf::Text);
int isNumKeyPressed();
sf::String getStringFromKeyCode(int);

#endif