#include "../include/AssetManager.h"
#include "../include/MainMenu.h"
#include "../include/Utils.h"
#include <iostream>

sf::Text logoText;
sf::Text playText;
sf::Text settingsText;
sf::Text loadGameText;
sf::Text quitText;

void initMainMenu(sf::RenderWindow* window) {
	using namespace sf;

	logoText.setString("The Maze");
	playText.setString("Play");
	loadGameText.setString("Load game");
	settingsText.setString("Settings");
	quitText.setString("Quit");
}

OptionType mainMenu(sf::RenderWindow* window) {
	using namespace sf;
	initMainMenu(window);
	OptionType optionChosen = OptionType::NONE;

	while (optionChosen == OptionType::NONE && window->isOpen())
	{
		Event event;
		while (window->pollEvent(event)) if (event.type == Event::Closed) window->close();

		window->clear(sf::Color(0, 0, 0));

		drawMainMenu(window);
		optionChosen = handleMainMenuInputs(window);

		window->display();
	}

	return optionChosen;
}

void drawMainMenu(sf::RenderWindow* window) {
	const float spacing = 70;

	logoText.setFont(*getFont(MAZE_FONT)); 
	playText.setFont(*getFont(MADE_FONT));
	loadGameText.setFont(*getFont(MADE_FONT));
	settingsText.setFont(*getFont(MADE_FONT));
	quitText.setFont(*getFont(MADE_FONT));

	logoText.setFillColor(sf::Color::White);
	playText.setFillColor(isCursorOver(window, playText) ? sf::Color(235, 183, 73) : sf::Color::White);
	loadGameText.setFillColor(isCursorOver(window, loadGameText) ? sf::Color(60, 135, 214) : sf::Color::White);
	settingsText.setFillColor(isCursorOver(window, settingsText) ? sf::Color(209, 46, 46) : sf::Color::White);
	quitText.setFillColor(isCursorOver(window, quitText) ? sf::Color(153, 69, 181) : sf::Color::White);

	logoText.setCharacterSize(150);
	playText.setCharacterSize(isCursorOver(window, playText) ? 50 : 40);
	loadGameText.setCharacterSize(isCursorOver(window, loadGameText) ? 50 : 40);
	settingsText.setCharacterSize(isCursorOver(window, settingsText) ? 50 : 40);
	quitText.setCharacterSize(isCursorOver(window, quitText) ? 50 : 40);
	
	logoText.setPosition(sf::Vector2f(
		WINDOW_W / 2 - logoText.getLocalBounds().width / 2,
		WINDOW_H / 2 - 330
	));
	playText.setPosition(sf::Vector2f(
		WINDOW_W / 2 - playText.getLocalBounds().width / 2,
		WINDOW_H / 2 - 60
	));
	loadGameText.setPosition(sf::Vector2f(
		WINDOW_W / 2 - loadGameText.getLocalBounds().width / 2,
		playText.getGlobalBounds().top + spacing
	));
	settingsText.setPosition(sf::Vector2f(
		WINDOW_W / 2 - settingsText.getLocalBounds().width / 2,
		loadGameText.getGlobalBounds().top + spacing
	));
	quitText.setPosition(sf::Vector2f(
		WINDOW_W / 2 - quitText.getLocalBounds().width / 2,
		settingsText.getGlobalBounds().top + spacing
	));

	window->draw(logoText);
	window->draw(playText);
	window->draw(loadGameText);
	window->draw(settingsText);
	window->draw(quitText);
}

OptionType handleMainMenuInputs(sf::RenderWindow* window) {
	using namespace sf;

	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (isCursorOver(window, playText)) return OptionType::PLAY;
		else if (isCursorOver(window, loadGameText)) return OptionType::LOAD_GAME;
		else if (isCursorOver(window, settingsText)) return OptionType::SETTINGS;
		else if (isCursorOver(window, quitText)) return OptionType::QUIT;
	}

	return OptionType::NONE;
}

