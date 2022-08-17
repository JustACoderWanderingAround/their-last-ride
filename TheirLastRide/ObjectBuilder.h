#pragma once
#include <string>
#include "Texture.h"
#include "Object.h"
#include <iostream>
#include <SDL.h>
class ObjectBuilder
{
public:
	static Object* CreateObject(const std::string& path, const SDL_Point& pos, const SDL_BlendMode& bm);
	static Object* CreateTextObject(const std::string& message, SDL_Color textcolor, TTF_Font* font, const SDL_Point& pos, const SDL_BlendMode& bm);
};

