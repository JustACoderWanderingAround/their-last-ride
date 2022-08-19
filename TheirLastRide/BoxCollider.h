#pragma once
#include <SDL.h>
class BoxCollider
{
public:
	SDL_Rect hitbox;
	BoxCollider();
	BoxCollider(const SDL_Rect& box);
	BoxCollider(const SDL_Point& topleft, const SDL_Point& bottomright);
	bool isColliding(BoxCollider* victim);
	void moveCollider(const SDL_Point& pos);
};

