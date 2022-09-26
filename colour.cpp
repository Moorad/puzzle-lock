#include <string>
#include "colour.h"

std::string colourise(std::string text, Colour colour, bool isBackground = false) {
	std::string colourCode = "\033[";

	if (isBackground) {
		colourCode += std::to_string(colour + 10);
	} else {
		colourCode += std::to_string(colour);
	}

	colourCode += "m";

	return colourCode + text + "\033[0m";
}