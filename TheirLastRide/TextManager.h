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

class TextManager : public Singleton<TextManager>
{
private:
	std::array<TTF_Font*, NUM_FONT> _fonts;
public:
	int maxWidth;
	TextManager();
	std::array<TTF_Font*, NUM_FONT> getFonts() const;
};

