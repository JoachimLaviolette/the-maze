#include "../include/Menu.h"

sf::Font madeFont;
sf::Font mazeFont;
sf::Font darkSeedFont;
sf::Text playText, loadText, quitText;
sf::Text textLogo;

void loadAssets() {
	if (!mazeFont.loadFromFile("assets\\fonts\\maze.ttf")) { /* error... */ }
	if (!madeFont.loadFromFile("assets\\fonts\\made.otf")) { /* error... */ }
	if (!darkSeedFont.loadFromFile("assets\\fonts\\dark_seed.otf")) { /* error... */ }
}

void initMenu() {
	loadAssets();
}

void drawMenu(sf::RenderWindow* window) {
	drawLogo(window);
	drawOptions(window);
}

void drawLogo(sf::RenderWindow* window) {
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
	using namespace sf;

	const float spacing = 90;

	playText.setFont(madeFont);
	loadText.setFont(madeFont);
	quitText.setFont(madeFont);

	playText.setString("Play");
	loadText.setString("Load game");
	quitText.setString("Quit");

	playText.setFillColor(isCursorOver(window, OptionType::PLAY) ? sf::Color::Yellow : sf::Color::White);
	loadText.setFillColor(isCursorOver(window, OptionType::LOAD) ? sf::Color::Red : sf::Color::White);
	quitText.setFillColor(isCursorOver(window, OptionType::QUIT) ? sf::Color::Cyan : sf::Color::White);
	
	playText.setCharacterSize(isCursorOver(window, OptionType::PLAY) ? 50 : 40);
	loadText.setCharacterSize(isCursorOver(window, OptionType::LOAD) ? 50 : 40);
	quitText.setCharacterSize(isCursorOver(window, OptionType::QUIT) ? 50 : 40);

	playText.setPosition(sf::Vector2f(
		WINDOW_W / 2 - playText.getLocalBounds().width / 2,
		WINDOW_H / 2
	));
	loadText.setPosition(sf::Vector2f(
		WINDOW_W / 2 - loadText.getLocalBounds().width / 2,
		WINDOW_H / 2 + spacing
	));
	quitText.setPosition(sf::Vector2f(
		WINDOW_W / 2 - quitText.getLocalBounds().width / 2,
		WINDOW_H / 2 + spacing * 2
	));

	window->draw(playText);
	window->draw(loadText);
	window->draw(quitText);
}

int isCursorOver(sf::RenderWindow* window, OptionType option) {
	using namespace sf;

	Text optionText;

	switch (option) {
		case OptionType::PLAY:
			optionText = playText; break;
		case OptionType::LOAD:
			optionText = loadText; break;
		case OptionType::QUIT:
			optionText = quitText; break;
		default: return false;
	}
	   
	FloatRect rect = optionText.getGlobalBounds();
	rect.top -= 20;
	rect.height += 40;

	return rect.contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y);	
}

OptionType handleMenuInputs(sf::RenderWindow* window) {
	using namespace sf;

	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (isCursorOver(window, OptionType::PLAY)) return OptionType::PLAY;
		else if (isCursorOver(window, OptionType::LOAD)) return OptionType::LOAD;
		else if (isCursorOver(window, OptionType::QUIT)) return OptionType::QUIT;
	}

	return OptionType::NONE;
}