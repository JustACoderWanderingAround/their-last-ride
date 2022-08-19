#include "BoxCollider.h"

BoxCollider::BoxCollider()
{

}

BoxCollider::BoxCollider(const SDL_Rect& box)
	: hitbox(box)
{
}

BoxCollider::BoxCollider(const SDL_Point& topleft, const SDL_Point& bottomright)
{
	int width = abs(topleft.x - bottomright.x);
	int height = abs(topleft.y - bottomright.y);
	int centrex = topleft.x + width / 2;
	int centrey = topleft.y - height / 2;
	hitbox = { centrex, centrey, width, height };
}

bool BoxCollider::isColliding(BoxCollider* victim)
{
	int leftA = hitbox.x;
	int rightA = hitbox.x + hitbox.w;
	int topA = hitbox.y;
	int bottomA = hitbox.y + hitbox.h;

	int leftB = victim->hitbox.x;
	int rightB = victim->hitbox.x + victim->hitbox.w;
	int topB = victim->hitbox.y;
	int bottomB = victim->hitbox.y + victim->hitbox.h;

    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    return true;
}

void BoxCollider::moveCollider(const SDL_Point& pos)
{
	hitbox.x = pos.x;
	hitbox.y = pos.y;
}
