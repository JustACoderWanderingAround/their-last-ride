#include "TextManager.h"
#include "Application.h"
#include <iostream>

TextManager::TextManager()
	: maxWidth(600), _textWrapWidths(std::array<int, 2>({ 600, 200 }))// To change
{
	
	if (TTF_OpenFont("Fonts//REDENSEK.ttf", 32) == NULL) {
		std::cout << "Cannot open font." << TTF_GetError();
	}
	else {
		_fonts[FONT_REDENSEK] = TTF_OpenFont("Fonts//REDENSEK.ttf", 32);
	}
	if (TTF_OpenFont("Fonts//REDENSEK.ttf", 18) == NULL) {
		std::cout << "Cannot open font." << TTF_GetError();
	}
	else {
		_fonts[FONT_REDENSEK_SMALL] = TTF_OpenFont("Fonts//REDENSEK.ttf", 18);
	}
}

std::array<TTF_Font*, NUM_FONT> TextManager::getFonts() const
{
	return _fonts;
}

std::array<int, 2> TextManager::getTextWrapWidths()
{
	return _textWrapWidths;
}
