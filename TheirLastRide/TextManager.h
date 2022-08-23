#pragma once
#include "Singleton.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <array>
#include <string>
#include "Texture.h"
#include "Node.h"
enum FONT
{
	FONT_REDENSEK,
	FONT_REDENSEK_SMALL,
	NUM_FONT
};



const SDL_Color White = { 255, 255 ,255 };
const SDL_Color Grey = { 94, 92, 87 };
const SDL_Color Pink = { 201, 112, 106 };
const SDL_Color Teal = { 87, 165, 171 };
const SDL_Color ReaperGrey = { 147, 154, 177 };

class TextManager : public Singleton<TextManager>
{
private:
	std::array<int, 2> _textWrapWidths;
	std::array<TTF_Font*, NUM_FONT> _fonts;
public:
	int maxWidth;
	TextManager();
	std::array<TTF_Font*, NUM_FONT> getFonts() const;
	std::array<int, 2> getTextWrapWidths();
};

