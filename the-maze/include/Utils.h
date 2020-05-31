#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include "Constants.h"

// --- Functions
int isCursorOver(sf::RenderWindow*, sf::FloatRect);
int isNumKeyPressed();
sf::String getStringFromKeyCode(int);
int colorEquals(Color, Color);
sf::Color colorToSfColor(Color);

#endif