#include "ObjectBuilder.h"

Object* ObjectBuilder::CreateObject(const std::string& path, const SDL_Point& pos, const SDL_BlendMode& bm)
{
    Texture _temptxt;
    if (!_temptxt.loadImage(path)) {
        std::cout << "Failed to load image.\n";
        return nullptr;
    }
    _temptxt.setBlendMode(bm);
    return new Object(_temptxt, pos);
}

Object* ObjectBuilder::CreateTextObject(const std::string& message, SDL_Color textcolor, TTF_Font* font, const SDL_Point& pos, const SDL_BlendMode& bm)
{
    Texture _temptxt;
    if (!_temptxt.loadText(message, font, textcolor)) {
        std::cout << "Failed to load text.\n";
        return nullptr;
    }
    _temptxt.setBlendMode(bm);
    return new Object(_temptxt, pos);
}
