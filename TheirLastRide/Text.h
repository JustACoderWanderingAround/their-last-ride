#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
/// <summary>
/// Struct for formatting string, font and colour into one whole type to be passed as a function.
/// </summary>
struct Text
{
	std::string msg;
	TTF_Font* font;
	SDL_Color textcolor;
};

