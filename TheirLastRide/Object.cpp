#include "Object.h"

Object::Object()
    : _collider(nullptr)
{
}

Object::Object(const Texture& t, const SDL_Point& c)
    :_txt(t), _coords(c), _collider(nullptr)
{
}

Object::Object(const Texture& t, const SDL_Point& c, BoxCollider* bc)
    : _txt(t), _coords(c), _collider(bc)
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

/// <summary>
/// Get the collider to change it or get info.
/// </summary>
/// <returns>A reference to the box collider pointer inside this object.</returns>
BoxCollider*& Object::getCollider()
{
    return _collider;
}

void Object::setCoords(const SDL_Point& coords)
{
    _coords = coords;
}

/// <summary>
/// Set the texture of the object. Be careful with this.
/// </summary>
/// <param name="txt">Texture</param>
void Object::setTexture(const Texture& txt)
{
    _txt = txt;
}

/// <summary>
/// Scales the texture with a uniform aspect ratio respective to its own.
/// </summary>
/// <param name="scalar">Scalar value</param>
void Object::setToScale(float scalar)
{
    _txt.setScale(scalar);
}

/// <summary>
/// Scales the texture with x and y values.
/// </summary>
/// <param name="x">x scalar</param>
/// <param name="y">y scalar</param>
void Object::setToScale(float x, float y)
{
    _txt.setScale(x, y);
}

/// <summary>
/// Update the object's texture with a Texture of text.
/// </summary>
/// <param name="msg">The string of the text</param>
/// <param name="color">The colour of the text</param>
/// <param name="font">The font of the text</param>
/// <param name="bm">The blend mode of the new texture.</param>
///  <param name="width">Max width before text wraps to a new line</param>
void Object::updateText(const std::string& msg, const SDL_Color& color, TTF_Font* font, const SDL_BlendMode& bm)
{
    _txt.free();
    _txt.loadText(msg, font, color);
    _txt.setBlendMode(bm);
}
void Object::updateText(const std::string& msg, const SDL_Color& color, TTF_Font* font, const SDL_BlendMode& bm, int width)
{
    _txt.free();
    _txt.loadText(msg, font, color, width);
    _txt.setBlendMode(bm);
}
