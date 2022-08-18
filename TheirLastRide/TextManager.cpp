#include "TextManager.h"
#include "Application.h"
#include <iostream>

TextManager::TextManager()
{
	if (TTF_OpenFont("Fonts//REDENSEK.ttf", 24) == NULL) {
		std::cout << "Cannot open font." << TTF_GetError();
	}
	else {
		_fonts[FONT_REDENSEK] = TTF_OpenFont("Fonts//REDENSEK.ttf", 24);
	}
	std::cout << _fonts[FONT_REDENSEK];
}

std::array<TTF_Font*, NUM_FONT> TextManager::getFonts() const
{
	return _fonts;
}

