#include "Texture.h"
#include "Application.h"
#include <iostream>

Texture::Texture()
	: _texture(NULL), _pixels(NULL), _pitch(0), _width(0), _height(0)
{
}

Texture::~Texture()
{

}
/// <summary>
/// Check if the texture exists
/// </summary>
/// <returns>True if texture exists, else false.</returns>
bool Texture::operator!()
{
    return (_texture == NULL);
}

/// <summary>
/// Loads an image(PNG) into this texture object.
/// </summary>
/// <param name="path">The filepath to the image.</param>
/// <returns>True if successful, false if not.</returns>
bool Texture::loadImage(std::string path)
{
    SDL_Texture* texture;
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedImage = IMG_Load(path.c_str());

    if (loadedImage == NULL) {
        std::cout << "Unable to load image! SDL_image Error:" << path.c_str() << IMG_GetError() << std::endl;
        return false;
    }
    else
    {
        optimizedSurface = SDL_ConvertSurfaceFormat(loadedImage, SDL_PIXELFORMAT_ARGB8888, 0);
        if (optimizedSurface == NULL) {
            std::cout << "Unable to optimize image %s! SDL Error" << path.c_str() << SDL_GetError() << std::endl;
            return false;
        }
        Uint32 colorkey = SDL_MapRGB(optimizedSurface->format, 0, 0, 0);
        SDL_SetColorKey(optimizedSurface, SDL_TRUE, colorkey);
        texture = SDL_CreateTexture(Application::GetInstance()->getRenderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, optimizedSurface->w, optimizedSurface->h);
        if (texture == NULL) {
            std::cout << "Unable to texturize image! SDL Error" << path.c_str() << SDL_GetError() << std::endl;
            return false;
        }
        else {
            SDL_LockTexture(texture, NULL, &_pixels, &_pitch);
            memcpy(_pixels, optimizedSurface->pixels, optimizedSurface->pitch * optimizedSurface->h);
            SDL_UnlockTexture(texture);
            _pixels = NULL;
            _width = optimizedSurface->w;
            _height = optimizedSurface->h;
        }
        SDL_FreeSurface(optimizedSurface);
        SDL_FreeSurface(loadedImage);
        _texture = texture;
        return true;
    }
}

/// <summary>
/// Creates the text texture with the input, and loads it into this texture.
/// </summary>
/// <param name="message">The actual string for the text. (Data)</param>
/// <param name="font">The font for the text.(TTF_Font)</param>
/// <param name="textcolor">The colour of the text. (SDL_Color, RGB)</param>
/// <returns>True if successful, false if not.</returns>
bool Texture::loadText(const std::string& message, TTF_Font* font, SDL_Color textcolor)
{
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, message.c_str(), textcolor, TextManager::GetInstance()->maxWidth);
    if (textSurface != NULL)
    {
        //Create texture from surface pixels
        _texture = SDL_CreateTextureFromSurface(Application::GetInstance()->getRenderer(), textSurface);
        if (_texture == NULL)
        {
            SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            _width = textSurface->w;
            _height = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
        return true;
    }
    else
    {
        /*std::cout << "Unable to render text surface! SDL_ttf Error:" << TTF_GetError() << std::endl;*/
        return false;
    }
}

/// <summary>
/// Creates a blank texture and loads into this texture.
/// </summary>
/// <param name="width">Width of the blank texture.</param>
/// <param name="height">Height of the blank texture.</param>
/// <param name="access">Texture access pattern (Don't input unless you know what you're doing)</param>
/// <returns>True if successful, false if not.</returns>
bool Texture::createBlank(int width, int height, SDL_TextureAccess access)
{
    _texture = SDL_CreateTexture(Application::GetInstance()->getRenderer(), SDL_PIXELFORMAT_RGBA8888, access, width, height);
    if (_texture == NULL)
    {
        std::cout << "Unable to create blank texture! SDL Error: " << SDL_GetError() << "\n";
    }
    else
    {
        _width = width;
        _height = height;
    }

    return (_texture != NULL);
}
/// <summary>
/// Creates the text texture with the input, and loads it into this texture.
/// </summary>
/// <param name="text">The text to be written (Text is a struct containing the string, font and colour of the text)</param>
/// <returns>True if successful, false if not.</returns>
bool Texture::loadText(const Text& text)
{
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(text.font, text.msg.c_str(), text.textcolor, TextManager::GetInstance()->maxWidth);
    if (textSurface != NULL)
    {
        //Create texture from surface pixels
        _texture = SDL_CreateTextureFromSurface(Application::GetInstance()->getRenderer(), textSurface);
        if (_texture == NULL)
        {
            SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            _width = textSurface->w;
            _height = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
        return true;
    }
    else
    {
        /*std::cout << "Unable to render text surface! SDL_ttf Error:" << TTF_GetError() << std::endl;*/
        return false;
    }
}
/// <summary>
/// Set color modulation
/// </summary>
/// <param name="r">Red value (0-255)</param>
/// <param name="g">Green value (0-255)</param>
/// <param name="b">Blue value (0-255)</param>
void Texture::setColor(unsigned int r, unsigned int g, unsigned int b)
{
    SDL_SetTextureColorMod(_texture, r, g, b);
}

/// <summary>
/// Set alpha modulation (transparency)
/// </summary>
/// <param name="a">Alpha value</param>
void Texture::setAlpha(unsigned int a)
{
    SDL_SetTextureAlphaMod(_texture, a);
}

/// <summary>
/// Set blend mode.
/// Blend modes:
/// SDL_BLENDMODE_BLEND - Blend the texture (Remove the black background of the PNG.)
/// SDL_BLENDMODE_NONE - Don't blend the texture (The black background will be there, use this for debugging the width and height)
/// </summary>
/// <param name="bm">Blend mode</param>
void Texture::setBlendMode(SDL_BlendMode bm)
{
    SDL_SetTextureBlendMode(_texture, bm);
}

/// <summary>
/// Scales the texture with x and y values.
/// </summary>
/// <param name="x">x scalar</param>
/// <param name="y">y scalar</param>
void Texture::setScale(float x, float y)
{
    _width *= x;
    _height *= y;
}

/// <summary>
/// Scales the texture with a uniform aspect ratio respective to its own.
/// </summary>
/// <param name="scalar">Scalar value</param>
void Texture::setScale(float scalar)
{
    _width *= scalar;
    _height *= scalar;
}

/// <summary>
/// Clears all the memory. Use this when reloading a new SDL_Texture onto the this Texture wrapper.
/// </summary>
void Texture::free()
{
    if (_texture != NULL) {
        SDL_DestroyTexture(_texture);
        _width = 0;
        _height = 0;
        _texture = NULL;
        _pixels = NULL;
        _pitch = 0;
    }
}

/// <summary>
/// Render this texture.
/// </summary>
/// <param name="x">The x coordinate to render at</param>
/// <param name="y">The y coordinate to render at</param>
/// <param name="clip">The specific crop of the texture to be rendered (Not necessary to input)</param>
/// <param name="angle">The angle to render the texture at. (Defaulted at 0 degrees)</param>
/// <param name="centre">The point at which the centre of the texture is (Not necessary to input)</param>
/// <param name="flip">Whether the renderer flips the image (Defaulted to no)</param>
void Texture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* centre, SDL_RendererFlip flip)
{
    SDL_Rect rendQuad = { x, y, _width, _height };
    if (clip != NULL) {
        rendQuad.w = clip->w;
        rendQuad.h = clip->h;
    }
    SDL_RenderCopyEx(Application::GetInstance()->getRenderer(), _texture, clip, &rendQuad, angle, centre, flip);
}

/// <summary>
/// Get width of texture
/// </summary>
/// <returns>Width (int)</returns>
int Texture::getWidth()
{
    return _width;
}

/// <summary>
/// Get height of texture
/// </summary>
/// <returns>Height (int)</returns>
int Texture::getHeight()
{
    return _height;
}

/// <summary>
/// Get pitch of texture
/// </summary>
/// <returns>Pitch (int)</returns>
int Texture::getPitch()
{
    return _pitch;
}

/// <summary>
/// Set width (TRY NOT TO USE THIS UNLESS YOU KNOW WHAT YOU'RE DOING)
/// </summary>
/// <param name="w">width</param>
void Texture::setWidth(int w)
{
    _width = w;
}

/// <summary>
/// Set height (TRY NOT TO USE THIS UNLESS YOU KNOW WHAT YOU'RE DOING)
/// </summary>
/// <param name="h">height</param>
void Texture::setHeight(int h)
{
    _height = h;
}

/// <summary>
/// (TRY NOT TO USE THIS VARIABLE AT ALL)
/// </summary>
/// <returns>void pointer</returns>
void* Texture::getPixels()
{
    return _pixels;
}

/// <summary>
/// Pixel manipulation (Try not to use this)
/// </summary>
/// <returns>True if succesful, false if not.</returns>
bool Texture::lockTexture()
{
    if (_pixels != NULL) {
        std::cout << "Textured is already locked!\n";
        return false;
    }
    else {
        if (SDL_LockTexture(_texture, NULL, &_pixels, &_pitch) != 0) {
            std::cout << "Unable to lock texture!\n" << SDL_GetError() << std::endl;
            return false;
        }
    }
    return true;
}

/// <summary>
/// Pixel manipulation (Try not to use this)
/// </summary>
/// <returns>True if succesful, false if not.</returns>
bool Texture::unlockTexture()
{
    if (_pixels == NULL)
    {
        std::cout << "Texture is not locked!\n";
        return false;
    }
    else
    {
        SDL_UnlockTexture(_texture);
        _pixels = NULL;
        _pitch = 0;
    }
}
