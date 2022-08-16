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
        optimizedSurface = SDL_ConvertSurface(loadedImage, Application::GetInstance()->getWindowSurface()->format, 0);
        if (optimizedSurface == NULL) {
            std::cout << "Unable to optimize image %s! SDL Error" << path.c_str() << SDL_GetError() << std::endl;
            return false;
        }
        texture = SDL_CreateTexture(Application::GetInstance()->getRenderer(), SDL_GetWindowPixelFormat(Application::GetInstance()->getWindow()), SDL_TEXTUREACCESS_STREAMING, optimizedSurface->w, optimizedSurface->h);
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
