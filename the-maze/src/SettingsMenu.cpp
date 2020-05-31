#include "../include/AssetManager.h"
#include "../include/SettingsMenu.h"
#include "../include/Utils.h"
#include <iostream>

sf::Text mazeWidthLabel;
sf::Text mazeWidthInput;
sf::Text mazeHeightLabel;
sf::Text mazeHeightInput;
sf::Text mazeColorLabel;
sf::Text saveButtonLabel;

sf::String mazeWidthValue;
sf::String mazeHeightValue;

sf::RectangleShape mazeWidthInputBackground;
sf::RectangleShape mazeHeightInputBackground;
sf::RectangleShape saveButtonBackground;

Color selectableColors[MAX_SELECTABLE_COLORS];
sf::RectangleShape selectableColorShapes[MAX_SELECTABLE_COLORS];
int colorComponents[MAX_SELECTABLE_COLORS][3] = {
	{252, 103, 73},
	{252, 151, 73},
	{252, 207, 73},
	{249, 252, 73},
	{168, 252, 73},
	{73, 252, 121},
	{73, 252, 210},
	{73, 219, 252},
	{73, 154, 252},
	{138, 122, 255},
	{206, 122, 255},
	{255, 122, 231},
};
Color selectedColor;

int isWidthInputFocused = 0;
int isHeightInputFocused = 0;
int isKeyDown = 0;

void initSettingsMenu(sf::RenderWindow* window, GameParams params) {
	mazeWidthValue = "";
	mazeHeightValue = "";
	mazeWidthLabel.setString("Choose maze's width");
	mazeHeightLabel.setString("Choose maze's height");
	mazeColorLabel.setString("Choose maze's color");
	saveButtonLabel.setString("Save");
	
	mazeWidthLabel.setFillColor(sf::Color::White);
	mazeHeightLabel.setFillColor(sf::Color::White);
	mazeColorLabel.setFillColor(sf::Color::White);
	mazeWidthInputBackground.setFillColor(sf::Color::White);
	mazeHeightInputBackground.setFillColor(sf::Color::White);
	saveButtonLabel.setFillColor(sf::Color::White);

	mazeWidthLabel.setCharacterSize(30);
	mazeHeightLabel.setCharacterSize(30);
	mazeColorLabel.setCharacterSize(30);
	saveButtonLabel.setCharacterSize(30);
	mazeWidthInput.setCharacterSize(30);
	mazeHeightInput.setCharacterSize(30);

	mazeWidthInputBackground.setSize(sf::Vector2f(200, 50));
	mazeHeightInputBackground.setSize(sf::Vector2f(200, 50));
	saveButtonBackground.setSize(sf::Vector2f(140, 50));

	// Init the selectable colors and their shape
	for (int i = 0; i < MAX_SELECTABLE_COLORS; ++i) {
		// Init the color
		Color c;
		c.r = colorComponents[i][0];
		c.g = colorComponents[i][1];
		c.b = colorComponents[i][2];

		selectableColors[i] = c;

		// Init the colors shapes' fill colors
		sf::RectangleShape colorShape;
		colorShape.setFillColor(sf::Color(selectableColors[i].r, selectableColors[i].g, selectableColors[i].b));
		colorShape.setOutlineThickness(5);
		colorShape.setOutlineColor(sf::Color::White);
		selectableColorShapes[i] = colorShape;
	}

	selectedColor = params.mazeColor;
}

void settingsMenu(sf::RenderWindow* window, GameParams* params) {
	using namespace sf;
	initSettingsMenu(window, *params);
	int isSubmitted = false;

	while (!isSubmitted && window->isOpen())
	{
		Event event;
		while (window->pollEvent(event)) if (event.type == Event::Closed) window->close();

		window->clear(sf::Color(0, 0, 0));

		drawSettingsMenu(window, *params);
		isSubmitted = handleSettingsMenuInputs(window, event);

		window->display();
	}

	saveParams(params);

	mazeWidthValue.clear();
	mazeHeightValue.clear();

	std::cout << "Maze height: " << params->mazeHeight << std::endl;
	std::cout << "Maze width: " << params->mazeWidth << std::endl;
}

void drawSettingsMenu(sf::RenderWindow* window, GameParams params) {
	using namespace sf;

	const int padding = 70;

	mazeWidthInputBackground.setOutlineThickness(
		isWidthInputFocused || isCursorOver(window, mazeWidthInputBackground.getGlobalBounds()) ?
		10 : 5
	);
	mazeHeightInputBackground.setOutlineThickness(
		isHeightInputFocused || isCursorOver(window, mazeHeightInputBackground.getGlobalBounds()) ?
		10 : 5
	);

	mazeWidthInputBackground.setOutlineColor(
		isWidthInputFocused || isCursorOver(window, mazeWidthInputBackground.getGlobalBounds()) ? 
		sf::Color(255, 177, 43) : sf::Color(209, 46, 46)
	);
	mazeHeightInputBackground.setOutlineColor(
		isHeightInputFocused || isCursorOver(window, mazeHeightInputBackground.getGlobalBounds()) ?
		sf::Color(255, 177, 43) : sf::Color(209, 46, 46)
	);

	mazeWidthInput.setFillColor(isWidthInputFocused ? sf::Color(255, 177, 43) : sf::Color(209, 46, 46));
	mazeHeightInput.setFillColor(isHeightInputFocused ? sf::Color(255, 177, 43) : sf::Color(209, 46, 46));

	saveButtonBackground.setFillColor(isCursorOver(window, saveButtonBackground.getGlobalBounds()) ? sf::Color(247, 104, 104) : sf::Color(209, 46, 46));

	mazeWidthLabel.setFont(*getFont(MADE_FONT));
	mazeWidthInput.setFont(*getFont(MADE_FONT));
	mazeHeightLabel.setFont(*getFont(MADE_FONT));
	mazeHeightInput.setFont(*getFont(MADE_FONT));
	mazeColorLabel.setFont(*getFont(MADE_FONT));
	saveButtonLabel.setFont(*getFont(MADE_FONT));

	mazeWidthInput.setString(mazeWidthValue);
	mazeHeightInput.setString(mazeHeightValue);

	mazeWidthLabel.setPosition(Vector2f(
		WINDOW_W / 2 - mazeWidthLabel.getLocalBounds().width / 2,
		WINDOW_H / 2 - 330
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
	mazeColorLabel.setPosition(Vector2f(
		WINDOW_W / 2 - mazeColorLabel.getLocalBounds().width / 2,
		mazeHeightInputBackground.getPosition().y + padding * 1.5
	));
	saveButtonLabel.setPosition(Vector2f(
		WINDOW_W / 2 - saveButtonLabel.getLocalBounds().width / 2,
		WINDOW_H - 80
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
	window->draw(mazeColorLabel);
	window->draw(mazeHeightInput);
	window->draw(saveButtonBackground);
	window->draw(saveButtonLabel);

	int maxColumns = 6;
	int currentColumn = 0;
	int line = 0;
	int linePadding = 90;
	int columnPadding = 90;

	for (int i = 0; i < MAX_SELECTABLE_COLORS; ++i) {
		int colorShapeSize = 
			isCursorOver(window, selectableColorShapes[i].getGlobalBounds()) || colorEquals(selectedColor, selectableColors[i]) ? 
			70 : 50;

		selectableColorShapes[i].setSize(sf::Vector2f(colorShapeSize, colorShapeSize));
		selectableColorShapes[i].setPosition(
			sf::Vector2f(
				0 + columnPadding * currentColumn + WINDOW_W / 2 - (((float)(maxColumns - 1) * columnPadding) + colorShapeSize) / 2,
				mazeColorLabel.getPosition().y + 100 + line * linePadding - colorShapeSize / 2
			)
		);

		++currentColumn;

		if (currentColumn == maxColumns) {
			++line;
			currentColumn = 0;
		}

		window->draw(selectableColorShapes[i]);	
	}
}

int wasClicked = 0;

int handleSettingsMenuInputs(sf::RenderWindow* window, sf::Event event) {
	if (event.type == sf::Event::TextEntered) {
		using namespace sf;
		if (!isKeyDown) {
			if (Keyboard::isKeyPressed(Keyboard::Tab)) {
				if (isWidthInputFocused) {
					isWidthInputFocused = false;
					isHeightInputFocused = true;
				}
				else {
					isWidthInputFocused = true;
					isHeightInputFocused = false;
				}
			}
			else if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
				if (isWidthInputFocused) {
					if (!mazeWidthValue.isEmpty())
						mazeWidthValue = mazeWidthValue.substring(0, mazeWidthValue.getSize() - 1);
				}
				else if (isHeightInputFocused) {
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
				else if (isHeightInputFocused) {
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (!wasClicked) {
			if (isCursorOver(window, saveButtonLabel.getGlobalBounds()))
				return true;

			isWidthInputFocused = isCursorOver(window, mazeWidthInputBackground.getGlobalBounds());
			isHeightInputFocused = isCursorOver(window, mazeHeightInputBackground.getGlobalBounds());

			Color defaultMazeColor;
			defaultMazeColor.r = DEFAULT_MAZE_COLOR_R;
			defaultMazeColor.g = DEFAULT_MAZE_COLOR_G;
			defaultMazeColor.b = DEFAULT_MAZE_COLOR_B;

			for (int i = 0; i < MAX_SELECTABLE_COLORS; ++i) {
				if (isCursorOver(window, selectableColorShapes[i].getGlobalBounds())) 
					selectedColor = colorEquals(selectedColor, selectableColors[i]) ? defaultMazeColor : selectableColors[i];
			}

			wasClicked = 1;
		}
	}
	else wasClicked = 0;

	return false;
}

void saveParams(GameParams* params) {
	// Save maze's width and height if both fields are filled
	if (!mazeWidthValue.isEmpty() && !mazeHeightValue.isEmpty()) {
		params->mazeHeight = std::atoi(mazeWidthValue.toAnsiString().c_str());
		params->mazeWidth = std::atoi(mazeHeightValue.toAnsiString().c_str());
	}

	// Save maze's color if any selected
	params->mazeColor = selectedColor;
}