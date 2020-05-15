#include "../include/GameHandler.h"
#include "../include/Menu.h"
#include "../include/Game.h"

void gameHandler(sf::RenderWindow* window) {
	OptionType optionChosen = menu(window);
	option(window, optionChosen);
}

void option(sf::RenderWindow* window, OptionType optionChosen) {
	if (optionChosen == OptionType::PLAY) {
		int lines = DEFAULT_MAZE_H;
		int columns = DEFAULT_MAZE_W;
		settingsMenu(window, &lines, &columns);
		game(window, lines, columns);
		gameHandler(window);
	}
	else if (optionChosen == OptionType::QUIT) window->close();
}