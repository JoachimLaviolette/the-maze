#include "../include/AssetManager.h"
#include "../include/SettingsMenu.h"
#include "../include/Utils.h"
#include <iostream>

sf::Text mazeWidthLabel;
sf::Text mazeWidthInput;
sf::Text mazeHeightLabel;
sf::Text mazeHeightInput;
sf::Text saveButtonLabel;

sf::String mazeWidthValue;
sf::String mazeHeightValue;

sf::RectangleShape mazeWidthInputBackground;
sf::RectangleShape mazeHeightInputBackground;
sf::RectangleShape saveButtonBackground;

int isWidthInputFocused = 1;
int isKeyDown = 0;

void initSettingsMenu(sf::RenderWindow* window) {
	using namespace sf;

	mazeWidthValue = "";
	mazeHeightValue = "";
	mazeWidthLabel.setString("Choose maze's width");
	mazeHeightLabel.setString("Choose maze's height");
	saveButtonLabel.setString("Save");
	
	mazeWidthInput.setFillColor(sf::Color(209, 46, 46));
	mazeHeightInput.setFillColor(sf::Color(209, 46, 46));
	mazeWidthLabel.setFillColor(sf::Color::White);
	mazeHeightLabel.setFillColor(sf::Color::White);
	mazeWidthInputBackground.setFillColor(sf::Color::White);
	mazeHeightInputBackground.setFillColor(sf::Color::White);
	saveButtonLabel.setFillColor(sf::Color::White);
	saveButtonBackground.setFillColor(sf::Color(209, 46, 46));

	mazeWidthLabel.setCharacterSize(30);
	mazeHeightLabel.setCharacterSize(30);
	saveButtonLabel.setCharacterSize(35);
	mazeWidthInput.setCharacterSize(30);
	mazeHeightInput.setCharacterSize(30);

	mazeWidthInputBackground.setSize(sf::Vector2f(200, 50));
	mazeHeightInputBackground.setSize(sf::Vector2f(200, 50));
	saveButtonBackground.setSize(sf::Vector2f(200, 60));
}

void settingsMenu(sf::RenderWindow* window, GameParams* params) {
	using namespace sf;
	initSettingsMenu(window);
	int isSubmitted = false;

	while (!isSubmitted && window->isOpen())
	{
		Event event;
		while (window->pollEvent(event)) if (event.type == Event::Closed) window->close();

		window->clear(sf::Color(0, 0, 0));

		drawSettingsMenu(window);
		isSubmitted = handleSettingsMenuInputs(window, event);

		window->display();
	}

	saveParams(params);

	mazeWidthValue.clear();
	mazeHeightValue.clear();

	std::cout << "Maze height: " << params->mazeHeight << std::endl;
	std::cout << "Maze width: " << params->mazeWidth << std::endl;
}

void drawSettingsMenu(sf::RenderWindow* window) {
	using namespace sf;

	const int padding = 70;

	mazeWidthLabel.setFont(*getFont(MADE_FONT));
	mazeWidthInput.setFont(*getFont(MADE_FONT));
	mazeHeightLabel.setFont(*getFont(MADE_FONT));
	mazeHeightInput.setFont(*getFont(MADE_FONT));
	saveButtonLabel.setFont(*getFont(MADE_FONT));

	mazeWidthInput.setString(mazeWidthValue);
	mazeHeightInput.setString(mazeHeightValue);

	mazeWidthLabel.setPosition(Vector2f(
		WINDOW_W / 2 - mazeWidthLabel.getLocalBounds().width / 2,
		WINDOW_H / 2 - 200
	));
	mazeWidthInput.setPosition(Vector2f(
		WINDOW_W / 2 - mazeWidthInput.getLocalBounds().width / 2,
		mazeWidthLabel.getPosition().y + padding
	));
	mazeWidthInputBackground.setPosition(Vector2f(
		WINDOW_W / 2 - mazeWidthInputBackground.getLocalBounds().width / 2,
		mazeWidthInput.getPosition().y - 5
	));
	mazeHeightLabel.setPosition(Vector2f(
		WINDOW_W / 2 - mazeHeightLabel.getLocalBounds().width / 2,
		mazeWidthInputBackground.getPosition().y + padding * 1.5
	));
	mazeHeightInput.setPosition(Vector2f(
		WINDOW_W / 2 - mazeHeightInput.getLocalBounds().width / 2,
		mazeHeightLabel.getPosition().y + padding
	));
	mazeHeightInputBackground.setPosition(Vector2f(
		WINDOW_W / 2 - mazeHeightInputBackground.getLocalBounds().width / 2,
		mazeHeightInput.getPosition().y - 5
	));
	saveButtonLabel.setPosition(Vector2f(
		WINDOW_W / 2 - saveButtonLabel.getLocalBounds().width / 2,
		mazeHeightInputBackground.getPosition().y + padding * 2
	));
	saveButtonBackground.setPosition(Vector2f(
		WINDOW_W / 2 - saveButtonBackground.getLocalBounds().width / 2,
		saveButtonLabel.getPosition().y - 5
	));

	window->draw(mazeWidthLabel);
	window->draw(mazeWidthInputBackground);
	window->draw(mazeWidthInput);
	window->draw(mazeHeightLabel);
	window->draw(mazeHeightInputBackground);
	window->draw(mazeHeightInput);
	window->draw(saveButtonBackground);
	window->draw(saveButtonLabel);
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
	}
	else isKeyDown = 0;

	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (isCursorOver(window, saveButtonLabel))
			return true;
	}

	return false;
}

void saveParams(GameParams* params) {
	// Save maze's width and height if both fields are filled
	if (!mazeWidthValue.isEmpty() && !mazeHeightValue.isEmpty()) {
		params->mazeHeight = std::atoi(mazeWidthValue.toAnsiString().c_str());
		params->mazeWidth = std::atoi(mazeHeightValue.toAnsiString().c_str());
	}

	// Save maze's color if any selected
	// Todo
}