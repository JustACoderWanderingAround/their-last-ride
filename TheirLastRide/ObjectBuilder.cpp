#include "ObjectBuilder.h"

/// <summary>
/// Create the texture and create an object with that texture with the provided position.
/// </summary>
/// <param name="path">The file path</param>
/// <param name="pos">The position for the rendering.</param>
/// <param name="bm">The blend mode. (Look in Texture::setBlendMode() for more details)</param>
/// <returns>The pointer to the object created.</returns>
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

/// <summary>
/// Create the texture for the text and create an object with that texture with the provided position.
/// </summary>
/// <param name="text">The text to be written (Text is a struct containing the string, font and colour of the text)</param>
/// <param name="pos">The position for the rendering.</param>
/// <param name="bm">The blend mode. (Look in Texture::setBlendMode() for more details)</param>
/// <returns>The pointer to the object created.</returns>
Object* ObjectBuilder::CreateTextObject(const Text& text, const SDL_Point& pos, const SDL_BlendMode& bm)
{
    Texture _temptxt;
    if (!_temptxt.loadText(text)) {
        std::cout << "Failed to load text.\n";
        return nullptr;
    }
    _temptxt.setBlendMode(bm);
    return new Object(_temptxt, pos);
}

/// <summary>
/// Create the texture for the text and create an object with that texture with the provided position.
/// </summary>
/// <param name="text">The text to be written (Text is a struct containing the string, font and colour of the text)</param>
/// <param name="pos">The position for the rendering.</param>
/// <param name="bm">The blend mode. (Look in Texture::setBlendMode() for more details)</param>
/// <param name = "width> The index for the width of the text before a newline wrap. </param>
/// <returns>The pointer to the object created.</returns>
Object* ObjectBuilder::CreateTextObject(const Text& text, const SDL_Point& pos, const SDL_BlendMode& bm, int width)
{
    Texture _temptxt;
    if (!_temptxt.loadText(text, width)) {
        std::cout << "Failed to load text.\n";
        return nullptr;
    }
    _temptxt.setBlendMode(bm);
    return new Object(_temptxt, pos);
}
