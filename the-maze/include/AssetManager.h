#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include "Constants.h"

const int MADE_FONT = 0;
const int MAZE_FONT = 1;
const int DARK_SEED_FONT = 2;

void loadAssets();
sf::Font* getFont(int);

#endif