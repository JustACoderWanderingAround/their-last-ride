#include "Object.h"

Object::Object(const Texture& t, const SDL_Point& c)
    :_txt(t), _coords(c)
{
}

Texture Object::getTexture() const
{
    return _txt;
}

SDL_Point Object::getCoords() const
{
    return _coords;
}

void Object::setCoords(const SDL_Point& coords)
{
    _coords = coords;
}

void Object::setTexture(const Texture& txt)
{
    _txt = txt;
}
