#include "Object.h"

Object::Object()
    : _collider(nullptr)
{
}

Object::Object(const Texture& t, const SDL_Point& c)
    :_txt(t), _coords(c), _collider(nullptr)
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

BoxCollider*& Object::getCollider()
{
    return _collider;
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

void Object::updateText(const std::string& msg, const SDL_Color& color, TTF_Font* font, const SDL_BlendMode& bm)
{
    _txt.free();
    _txt.loadText(msg, font, color);
    _txt.setBlendMode(bm);
}
