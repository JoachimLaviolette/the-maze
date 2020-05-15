#include "include/Constants.h"
#include "include/GameHandler.h"
#include <stdlib.h>
#include <time.h>

int main() {
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), WINDOW_TITLE);

	gameHandler(&window);

	return EXIT_SUCCESS;
}