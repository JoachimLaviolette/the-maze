#include "../include/GameHandler.h"
#include "../include/MainMenu.h"
#include "../include/SettingsMenu.h"
#include "../include/Game.h"

void gameHandler(sf::RenderWindow* window, GameParams* params) {
	OptionType optionChosen = mainMenu(window);
	option(window, optionChosen, params);
}

void option(sf::RenderWindow* window, OptionType optionChosen, GameParams* params) {
	if (optionChosen == OptionType::PLAY) {
		game(window, *params);
		gameHandler(window, params);
	}
	else if (optionChosen == OptionType::LOAD_GAME) {
		// TODO
	}
	else if (optionChosen == OptionType::SETTINGS) {
		settingsMenu(window, params);
		gameHandler(window, params);
	}
	else window->close();
}