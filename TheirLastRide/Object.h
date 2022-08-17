#pragma once
#include <SDL.h>
#include "Texture.h"
class Object
{
private:
	Texture _txt;
	SDL_Point _coords;
public:
	Object(const Texture& t, const SDL_Point& c);
	Texture getTexture() const;
	SDL_Point getCoords() const;
	void setCoords(const SDL_Point& coords);
	void setTexture(const Texture& txt);
};

