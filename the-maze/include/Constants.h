#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>

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
const int DEFAULT_MAZE_COLOR_R = 255;
const int DEFAULT_MAZE_COLOR_G = 255;
const int DEFAULT_MAZE_COLOR_B = 255;

// --- Grid
const int CELL_SIZE = 50;
const int WALL_SIZE = 3;

// --- Enum
enum OptionType {
	NONE,
	PLAY,
	LOAD_GAME,
	SETTINGS,
	QUIT,
	SUBMIT,
};

// --- Struct
typedef struct {
	int r;
	int g;
	int b;
} Color;

typedef struct {
	int mazeWidth;
	int mazeHeight;
	Color mazeColor;
} GameParams;

#endif