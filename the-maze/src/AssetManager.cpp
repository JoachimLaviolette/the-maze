#include "../include/AssetManager.h"

sf::Font* madeFont = new sf::Font();
sf::Font* mazeFont = new sf::Font();
sf::Font* darkSeedFont = new sf::Font();

void loadAssets() {
	if (!mazeFont->loadFromFile("assets\\fonts\\maze.ttf")) puts("Error when loading maze font.");
	if (!madeFont->loadFromFile("assets\\fonts\\made.otf")) puts("Error when loading made font.");
	if (!darkSeedFont->loadFromFile("assets\\fonts\\dark_seed.otf")) puts("Error when loading dark seed font.");
}

sf::Font* getFont(int font) {
	switch (font) {
		case MADE_FONT: return madeFont;
		case MAZE_FONT: return mazeFont;
		default: return darkSeedFont;
	}
}