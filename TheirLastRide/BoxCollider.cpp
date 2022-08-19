#include "BoxCollider.h"

BoxCollider::BoxCollider()
{

}

/// <summary>
/// Initialise the box collider with the rect as its collider. (Remember that the SDL_Rect's x and y is at the top left of the collider)
/// </summary>
/// <param name="box">{x coordinate, y coordinate, width, height}</param>
BoxCollider::BoxCollider(const SDL_Rect& box)
	: hitbox(box)
{
}

/// <summary>
/// Initialise the box collider with two coordinates.
/// </summary>
/// <param name="topleft">Top left coordinate of the box</param>
/// <param name="bottomright">Bottom right coordinate of the box</param>
BoxCollider::BoxCollider(const SDL_Point& topleft, const SDL_Point& bottomright)
{
	int width = abs(topleft.x - bottomright.x);
	int height = abs(topleft.y - bottomright.y);
	int centrex = topleft.x + width / 2;
	int centrey = topleft.y - height / 2;
	hitbox = { centrex, centrey, width, height };
}

/// <summary>
/// Check if this collider is colliding with another specific collider.
/// </summary>
/// <param name="victim">That specific collider.</param>
/// <returns>True if colliding, else false.</returns>
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

/// <summary>
/// Move the collider to another position.
/// </summary>
/// <param name="pos">SDL_Point</param>
void BoxCollider::moveCollider(const SDL_Point& pos)
{
	hitbox.x = pos.x;
	hitbox.y = pos.y;
}
