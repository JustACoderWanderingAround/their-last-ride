#include "TextManager.h"
#include "Application.h"
#include <iostream>

TextManager::TextManager()
	: maxWidth(600)
{
	if (TTF_OpenFont("Fonts//REDENSEK.ttf", 24) == NULL) {
		std::cout << "Cannot open font." << TTF_GetError();
	}
	else {
		_fonts[FONT_REDENSEK] = TTF_OpenFont("Fonts//REDENSEK.ttf", 24);
	}	
}

std::array<TTF_Font*, NUM_FONT> TextManager::getFonts() const
{
	return _fonts;
}

