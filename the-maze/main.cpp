#include "include/Constants.h"
#include "include/GameHandler.h"
#include "include/AssetManager.h"
#include <stdlib.h>
#include <time.h>
#include "include/Grid.h"

int main() {
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), WINDOW_TITLE);

	loadAssets();

	GameParams params;
	Color defaultMazeColor;

	defaultMazeColor.r = DEFAULT_MAZE_COLOR_R;
	defaultMazeColor.g = DEFAULT_MAZE_COLOR_G;
	defaultMazeColor.b = DEFAULT_MAZE_COLOR_B;

	params.mazeWidth = DEFAULT_MAZE_W;
	params.mazeHeight = DEFAULT_MAZE_H;
	params.mazeColor = defaultMazeColor;
	
	gameHandler(&window, &params);

	return EXIT_SUCCESS;
}