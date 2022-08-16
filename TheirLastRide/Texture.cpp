#include "Texture.h"

Texture::Texture()
	: _texture(NULL), _pixels(NULL), _pitch(0), _width(0), _height(0)
{
}

Texture::~Texture()
{
	
}

bool Texture::loadImage(std::string path)
{
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedImage = IMG_Load(path.c_str());
    if (loadedImage == NULL)
        std::cout << "Unable to load image %s! SDL_image Error:" << path.c_str() << IMG_GetError() << std::endl;
    else
    {
        optimizedSurface = SDL_ConvertSurface(loadedImage, m_Surface->format, 0);
        if (optimizedSurface == NULL)
            std::cout << "Unable to optimize image %s! SDL Error" << path.c_str() << SDL_GetError() << std::endl;
        SDL_FreeSurface(loadedImage);
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, optimizedSurface);
    SDL_FreeSurface(optimizedSurface);
    return texture;
}

