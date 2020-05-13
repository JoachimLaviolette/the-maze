#include "../include/Menu.h"

sf::Font madeFont;
sf::Font mazeFont;
sf::Font darkSeedFont;

void loadAssets() {
	if (!mazeFont.loadFromFile("assets\\fonts\\maze.ttf")) { /* error... */ }
	if (!madeFont.loadFromFile("assets\\fonts\\made.otf")) { /* error... */ }
	if (!darkSeedFont.loadFromFile("assets\\fonts\\dark_seed.otf")) { /* error... */ }
}

void createMenu() {
	loadAssets();
}

void drawMenu(sf::RenderWindow* window) {
	drawLogo(window);
	drawOptions(window);
}

void drawLogo(sf::RenderWindow* window) {
	sf::Text textLogo;
	textLogo.setFont(mazeFont);
	textLogo.setString("The Maze");
	textLogo.setFillColor(sf::Color::White);
	textLogo.setCharacterSize(150);
	textLogo.setPosition(sf::Vector2f(
		WINDOW_W / 2 - textLogo.getLocalBounds().width / 2, 
		WINDOW_H / 2 - 270
	));
	window->draw(textLogo);
}

void drawOptions(sf::RenderWindow* window) {
	sf::Text play, load, exit;
	play.setFont(madeFont);
	load.setFont(madeFont);
	exit.setFont(madeFont);

	play.setString("Play");
	load.setString("Load game");
	exit.setString("Exit");

	play.setFillColor(sf::Color::White);
	load.setFillColor(sf::Color::White);
	exit.setFillColor(sf::Color::White);
	
	play.setCharacterSize(40);
	load.setCharacterSize(40);
	exit.setCharacterSize(40);

	play.setPosition(sf::Vector2f(
		WINDOW_W / 2 - play.getLocalBounds().width / 2,
		WINDOW_H / 2
	));
	load.setPosition(sf::Vector2f(
		WINDOW_W / 2 - load.getLocalBounds().width / 2,
		WINDOW_H / 2 + 80
	));
	exit.setPosition(sf::Vector2f(
		WINDOW_W / 2 - exit.getLocalBounds().width / 2,
		WINDOW_H / 2 + 160
	));

	window->draw(play);
	window->draw(load);
	window->draw(exit);
}
