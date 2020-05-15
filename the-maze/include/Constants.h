#include <SFML/Graphics.hpp>

#ifndef CONSTANTS_H
#define CONSTANTS_H

// --- Main
const int WINDOW_W = 1280;
const int WINDOW_H = 720;
const sf::String WINDOW_TITLE = "The Maze";

// --- Maze
const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;
const int DEFAULT_MAZE_W = 5;
const int DEFAULT_MAZE_H = 7;

// --- Grid
const int CELL_SIZE = 50;
const int WALL_SIZE = 1;

enum OptionType {
	NONE,
	PLAY,
	LOAD,
	QUIT,
	SUBMIT,
};

#endif