#include "Object.h"

Object::Object()
{
}

Object::Object(const Texture& t, const SDL_Point& c)
    :_txt(t), _coords(c)
{
}

Object::~Object()
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

void Object::setToScale(float scalar)
{
    _txt.setScale(scalar);
}

void Object::setToScale(float x, float y)
{
    _txt.setScale(x, y);
}
