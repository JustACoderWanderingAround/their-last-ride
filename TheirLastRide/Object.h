#pragma once
#include <SDL.h>
#include "Texture.h"
#include "BoxCollider.h"
class Object
{
protected:
	Texture _txt;
	SDL_Point _coords;
	BoxCollider* _collider;
public:
	Object();
	Object(const Texture& t, const SDL_Point& c);
	Object(const Texture& t, const SDL_Point& c, BoxCollider* bc);
	virtual ~Object();
	Texture getTexture() const;
	SDL_Point getCoords() const;
	BoxCollider*& getCollider();
	void setCoords(const SDL_Point& coords);
	void setTexture(const Texture& txt);
	void setToScale(float scalar);
	void setToScale(float x, float y);
	void updateText(const std::string& msg, const SDL_Color& color, TTF_Font* font, const SDL_BlendMode& bm);
	void updateText(const std::string& msg, const SDL_Color& color, TTF_Font* font, const SDL_BlendMode& bm, int width);
};

