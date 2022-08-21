#pragma once
#include <string>
#include "Texture.h"
#include "Object.h"
#include <iostream>
#include <SDL.h>
#include "Text.h"
class ObjectBuilder
{
public:
	
	static Object* CreateObject(const std::string& path, const SDL_Point& pos, const SDL_BlendMode& bm);
	static Object* CreateTextObject(const Text& text, const SDL_Point& pos, const SDL_BlendMode& bm);
	static Object* CreateTextObject(const Text& text, const SDL_Point& pos, const SDL_BlendMode& bm, int width);
};

