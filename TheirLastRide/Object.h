#pragma once
#include <SDL.h>
#include "Texture.h"
class Object
{
private:
	Texture _txt;
	SDL_Point _coords;
public:
	Object();
	Object(const Texture& t, const SDL_Point& c);
	virtual ~Object();
	Texture getTexture() const;
	SDL_Point getCoords() const;
	void setCoords(const SDL_Point& coords);
	void setTexture(const Texture& txt);
	void setToScale(float scalar);
	void setToScale(float x, float y);
	void updateText(const std::string& msg, const SDL_Color& color, TTF_Font* font, const SDL_BlendMode& bm);
};

