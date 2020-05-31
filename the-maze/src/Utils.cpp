#include "../include/Utils.h"

int isCursorOver(sf::RenderWindow* window, sf::Text optionText) {
	using namespace sf;

	FloatRect rect = optionText.getGlobalBounds();
	rect.top -= 20;
	rect.height += 40;

	return rect.contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y);
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