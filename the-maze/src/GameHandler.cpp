#include "../include/GameHandler.h"
#include "../include/Menu.h"
#include "../include/Game.h"

void gameHandler(sf::RenderWindow* window) {
	OptionType optionChosen = menu(window);
	option(window, optionChosen);
}

OptionType menu(sf::RenderWindow* window) {
	initMenu();
	OptionType optionChosen = OptionType::NONE;

	while (optionChosen == OptionType::NONE && window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event)) if (event.type == sf::Event::Closed) window->close();

		window->clear(sf::Color(0, 0, 0));

		drawMenu(window);
		optionChosen = handleMenuInputs(window);

		window->display();
	}

	return optionChosen;
}

void option(sf::RenderWindow* window, OptionType optionChosen) {
	printf("YAAAAAAAAAAAAAAAA");
	if (optionChosen == OptionType::PLAY) game(window);
	else if (optionChosen == OptionType::QUIT) window->close();
}