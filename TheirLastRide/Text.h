#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
struct Text
{
	std::string msg;
	TTF_Font* font;
	SDL_Color textcolor;
};

