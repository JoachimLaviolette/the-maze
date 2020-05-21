#include "../include/Menu.h"
#include <iostream>

sf::Font madeFont;
sf::Font mazeFont;
sf::Font darkSeedFont;
sf::Text playText, loadText, quitText;
sf::Text textLogo;
sf::Text mazeWidthLabel;
sf::Text mazeWidthInput;
sf::String mazeWidthValue = "";
sf::Text mazeHeightLabel;
sf::Text mazeHeightInput;
sf::String mazeHeightValue = "";
sf::Text submitText;
int isWidthInputFocused = 1;

int isKeyDown = 0;

void loadAssets() {
	if (!mazeFont.loadFromFile("assets\\fonts\\maze.ttf")) { /* error... */ }
	if (!madeFont.loadFromFile("assets\\fonts\\made.otf")) { /* error... */ }
	if (!darkSeedFont.loadFromFile("assets\\fonts\\dark_seed.otf")) { /* error... */ }
}

void initMenu() {
	loadAssets();
}

OptionType menu(sf::RenderWindow* window) {
	using namespace sf;
	initMenu();
	OptionType optionChosen = OptionType::NONE;

	while (optionChosen == OptionType::NONE && window->isOpen())
	{
		Event event;
		while (window->pollEvent(event)) if (event.type == Event::Closed) window->close();

		window->clear(Color(0, 0, 0));

		drawMainMenu(window);
		optionChosen = handleMenuInputs(window);

		window->display();
	}

	return optionChosen;
}

void settingsMenu(sf::RenderWindow* window, int* lines, int* columns) {
	using namespace sf;
	int isSubmitted = false;

	while (!isSubmitted && window->isOpen())
	{
		Event event;
		while (window->pollEvent(event)) if (event.type == Event::Closed) window->close();

		window->clear(Color(0, 0, 0));

		drawSettingsMenu(window);
		isSubmitted = handleSettingsMenuInputs(window, event);

		window->display();
	}


	*lines = std::atoi(mazeWidthValue.toAnsiString().c_str());
	*columns = std::atoi(mazeHeightValue.toAnsiString().c_str());

	mazeWidthValue.clear();
	mazeHeightValue.clear();

	std::cout << "Maze height: " << *lines << std::endl;
	std::cout << "Maze width: " << *columns << std::endl;
}

void drawMainMenu(sf::RenderWindow* window) {
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

void drawSettingsMenu(sf::RenderWindow* window) {
	using namespace sf;

	const int padding = 70;

	mazeWidthLabel.setFont(madeFont);
	mazeWidthLabel.setString("Choose the maze's width:");
	mazeWidthLabel.setFillColor(Color::White);
	mazeWidthLabel.setCharacterSize(30);
	mazeWidthLabel.setPosition(Vector2f(
		WINDOW_W / 2 - mazeWidthLabel.getLocalBounds().width / 2,
		WINDOW_H / 2 - 200
	));
	
	mazeWidthInput.setFont(madeFont);
	mazeWidthInput.setString(mazeWidthValue);
	mazeWidthInput.setFillColor(Color::Blue);
	mazeWidthInput.setCharacterSize(30);
	mazeWidthInput.setPosition(Vector2f(
		WINDOW_W / 2 - mazeWidthInput.getLocalBounds().width / 2,
		mazeWidthLabel.getPosition().y + padding
	));

	RectangleShape mazeWidthInputBackground(Vector2f(200, 50));
	mazeWidthInputBackground.setFillColor(Color::White);
	mazeWidthInputBackground.setPosition(
		WINDOW_W / 2 - mazeWidthInputBackground.getLocalBounds().width / 2,
		mazeWidthInput.getPosition().y - 5
	);

	mazeHeightLabel.setFont(madeFont);
	mazeHeightLabel.setString("Choose the maze's height:");
	mazeHeightLabel.setFillColor(Color::White);
	mazeHeightLabel.setCharacterSize(30);
	mazeHeightLabel.setPosition(Vector2f(
		WINDOW_W / 2 - mazeHeightLabel.getLocalBounds().width / 2,
		mazeWidthInputBackground.getPosition().y + padding * 1.5
	));

	mazeHeightInput.setFont(madeFont);
	mazeHeightInput.setString(mazeHeightValue);
	mazeHeightInput.setFillColor(Color::Blue);
	mazeHeightInput.setCharacterSize(30);
	mazeHeightInput.setPosition(Vector2f(
		WINDOW_W / 2 - mazeHeightInput.getLocalBounds().width / 2,
		mazeHeightLabel.getPosition().y + padding
	));

	RectangleShape mazeHeightInputBackground(Vector2f(200, 50));
	mazeHeightInputBackground.setFillColor(Color::White);
	mazeHeightInputBackground.setPosition(
		WINDOW_W / 2 - mazeHeightInputBackground.getLocalBounds().width / 2,
		mazeHeightInput.getPosition().y - 5
	);

	submitText.setFont(madeFont);
	submitText.setString("SUBMIT");
	submitText.setFillColor(Color::White);
	submitText.setCharacterSize(45);
	submitText.setPosition(Vector2f(
		WINDOW_W / 2 - submitText.getLocalBounds().width / 2,
		mazeHeightInputBackground.getPosition().y + padding * 2
	));

	RectangleShape submitBackground(Vector2f(250, 70));
	submitBackground.setFillColor(Color::Red);
	submitBackground.setPosition(
		WINDOW_W / 2 - submitBackground.getLocalBounds().width / 2,
		submitText.getPosition().y - 5
	);

	window->draw(mazeWidthLabel);
	window->draw(mazeWidthInputBackground);
	window->draw(mazeWidthInput);
	window->draw(mazeHeightLabel);
	window->draw(mazeHeightInputBackground);
	window->draw(mazeHeightInput);
	window->draw(submitBackground);
	window->draw(submitText);
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
		case OptionType::SUBMIT:
			optionText = submitText; break;
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

int handleSettingsMenuInputs(sf::RenderWindow* window, sf::Event event) {
	using namespace sf;

	if (event.type == Event::TextEntered) {
		if (!isKeyDown) {
			if (Keyboard::isKeyPressed(Keyboard::Tab)) isWidthInputFocused = !isWidthInputFocused;
			else if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
				if (isWidthInputFocused) {
					if (!mazeWidthValue.isEmpty()) 
						mazeWidthValue = mazeWidthValue.substring(0, mazeWidthValue.getSize() - 1);
				}
				else {
					if (!mazeHeightValue.isEmpty()) 
						mazeHeightValue = mazeHeightValue.substring(0, mazeHeightValue.getSize() - 1);					
				}
			}
			else {
				int keyCode = isNumKeyPressed();
				String value = getStringFromKeyCode(keyCode);
				
				if (isWidthInputFocused) {
					if (mazeWidthValue.getSize() < 2) {
						mazeWidthValue += value;
						mazeWidthInput.setString(mazeWidthValue);
					}
				}
				else {
					if (mazeHeightValue.getSize() < 2) {
						mazeHeightValue += value;
						mazeHeightInput.setString(mazeHeightValue);
					}
				}
			}
		}

		isKeyDown = 1;
	} else isKeyDown = 0;

	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (isCursorOver(window, OptionType::SUBMIT))
			if (!mazeWidthValue.isEmpty() && !mazeHeightValue.isEmpty()) return true;
	}

	return false;
}

int isNumKeyPressed() {
	using namespace sf;
	
	if (Keyboard::isKeyPressed(Keyboard::Num0)) return Keyboard::Num0;
	if (Keyboard::isKeyPressed(Keyboard::Numpad0)) return Keyboard::Numpad0;
	if (Keyboard::isKeyPressed(Keyboard::Num1)) return Keyboard::Num1;
	if (Keyboard::isKeyPressed(Keyboard::Numpad1)) return Keyboard::Numpad1;
	if (Keyboard::isKeyPressed(Keyboard::Num2)) return Keyboard::Num2;
	if (Keyboard::isKeyPressed(Keyboard::Numpad2)) return Keyboard::Numpad2;
	if (Keyboard::isKeyPressed(Keyboard::Num3)) return Keyboard::Num3;
	if (Keyboard::isKeyPressed(Keyboard::Numpad3)) return Keyboard::Numpad3;
	if (Keyboard::isKeyPressed(Keyboard::Num4)) return Keyboard::Num4;
	if (Keyboard::isKeyPressed(Keyboard::Numpad4)) return Keyboard::Numpad4;
	if (Keyboard::isKeyPressed(Keyboard::Num5)) return Keyboard::Num5;
	if (Keyboard::isKeyPressed(Keyboard::Numpad5)) return Keyboard::Numpad5;
	if (Keyboard::isKeyPressed(Keyboard::Num6)) return Keyboard::Num6;
	if (Keyboard::isKeyPressed(Keyboard::Numpad6)) return Keyboard::Numpad6;
	if (Keyboard::isKeyPressed(Keyboard::Num7)) return Keyboard::Num7;
	if (Keyboard::isKeyPressed(Keyboard::Numpad7)) return Keyboard::Numpad7;
	if (Keyboard::isKeyPressed(Keyboard::Num8)) return Keyboard::Num8;
	if (Keyboard::isKeyPressed(Keyboard::Numpad8)) return Keyboard::Numpad8;
	if (Keyboard::isKeyPressed(Keyboard::Num9)) return Keyboard::Num9;
	if (Keyboard::isKeyPressed(Keyboard::Numpad9)) return Keyboard::Numpad9;

	return -1;
}

sf::String getStringFromKeyCode(int keyCode) {
	using namespace sf;

	switch (keyCode) {
		case Keyboard::Num0:
		case Keyboard::Numpad0:
			return "0";

		case Keyboard::Num1:
		case Keyboard::Numpad1:
			return "1";

		case Keyboard::Num2:
		case Keyboard::Numpad2:
			return "2";

		case Keyboard::Num3:
		case Keyboard::Numpad3:
			return "3";

		case Keyboard::Num4:
		case Keyboard::Numpad4:
			return "4";

		case Keyboard::Num5:
		case Keyboard::Numpad5:
			return "5";

		case Keyboard::Num6:
		case Keyboard::Numpad6:
			return "6";

		case Keyboard::Num7:
		case Keyboard::Numpad7:
			return "7";

		case Keyboard::Num8:
		case Keyboard::Numpad8:
			return "8";

		case Keyboard::Num9:
		case Keyboard::Numpad9:
			return "9";

		default: return "";
	}
}