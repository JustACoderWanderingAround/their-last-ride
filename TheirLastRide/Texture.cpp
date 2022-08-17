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
        /*optimizedSurface = SDL_ConvertSurface(loadedImage, Application::GetInstance()->getWindowSurface()->format, 0);*/
        optimizedSurface = SDL_ConvertSurfaceFormat(loadedImage, SDL_PIXELFORMAT_ARGB8888, 0);
        if (optimizedSurface == NULL) {
            std::cout << "Unable to optimize image %s! SDL Error" << path.c_str() << SDL_GetError() << std::endl;
            return false;
        }
        Uint32 colorkey = SDL_MapRGB(optimizedSurface->format, 0, 0, 0);
        SDL_SetColorKey(optimizedSurface, SDL_TRUE, colorkey);
        texture = SDL_CreateTexture(Application::GetInstance()->getRenderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, optimizedSurface->w, optimizedSurface->h);
        /*texture = SDL_CreateTexture(Application::GetInstance()->getRenderer(), SDL_GetWindowPixelFormat(Application::GetInstance()->getWindow()), SDL_TEXTUREACCESS_STREAMING, optimizedSurface->w, optimizedSurface->h);*/
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

bool Texture::loadText(const std::string& message, TTF_Font* font, SDL_Color textcolor)
{
    const int maxWidth = 600; //to be determined, and put in TextManager class probably.
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, message.c_str(), textcolor, maxWidth);
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
        std::cout << "Unable to render text surface! SDL_ttf Error:" << TTF_GetError() << std::endl;
        return false;
    }
}

void Texture::setColor(unsigned int r, unsigned int g, unsigned int b)
{
    SDL_SetTextureColorMod(_texture, r, g, b);
}

void Texture::setAlpha(unsigned int a)
{
    SDL_SetTextureAlphaMod(_texture, a);
}

void Texture::setBlendMode(SDL_BlendMode bm)
{
    SDL_SetTextureBlendMode(_texture, bm);
}

void Texture::setScale(float x, float y)
{
    _width *= x;
    _height *= y;
}

void Texture::setScale(float scalar)
{
    _width *= scalar;
    _height *= scalar;
}

bool Texture::importSurface(SDL_Surface* sf)
{
    SDL_Surface* optimizedSurface = NULL;
    SDL_Texture* texture;
    if (sf == NULL) {
        std::cout << "Surface is null.\n";
        return false;
    }
    else
    {
        /*optimizedSurface = SDL_ConvertSurface(loadedImage, Application::GetInstance()->getWindowSurface()->format, 0);*/
        optimizedSurface = SDL_ConvertSurfaceFormat(sf, SDL_PIXELFORMAT_ARGB8888, 0);
        if (optimizedSurface == NULL) {
            std::cout << "Failed to optimize.\n";
            return false;
        }
        Uint32 colorkey = SDL_MapRGB(optimizedSurface->format, 0, 0, 0);
        SDL_SetColorKey(optimizedSurface, SDL_TRUE, colorkey);
        texture = SDL_CreateTexture(Application::GetInstance()->getRenderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, optimizedSurface->w, optimizedSurface->h);
        /*texture = SDL_CreateTexture(Application::GetInstance()->getRenderer(), SDL_GetWindowPixelFormat(Application::GetInstance()->getWindow()), SDL_TEXTUREACCESS_STREAMING, optimizedSurface->w, optimizedSurface->h);*/
        if (texture == NULL) {
            std::cout << "Texture could not be created.\n";
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
        _texture = texture;
        return true;
    }
}

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

void Texture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* centre, SDL_RendererFlip flip)
{
    SDL_Rect rendQuad = { x, y, _width, _height };
    if (clip != NULL) {
        rendQuad.w = clip->w;
        rendQuad.h = clip->h;
    }
    SDL_RenderCopyEx(Application::GetInstance()->getRenderer(), _texture, clip, &rendQuad, angle, centre, flip);
}

int Texture::getWidth()
{
    return _width;
}

int Texture::getHeight()
{
    return _height;
}

int Texture::getPitch()
{
    return _pitch;
}

void Texture::setWidth(int w)
{
    _width = w;
}

void Texture::setHeight(int h)
{
    _height = h;
}

void* Texture::getPixels()
{
    return _pixels;
}

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
