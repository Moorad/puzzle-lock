#include <string>

enum Colour {
	black = 30,
	red,
	green,
	yellow,
	blue,
	magenta,
	cyan,
	white
};

std::string colourise(std::string text, Colour colour, bool isBackground);