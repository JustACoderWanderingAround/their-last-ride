#include "TrainScene.h"
#include <SDL_image.h>
#include <iostream>
SDL_Surface* chair;
const SDL_Color DARK_LIME = { 153, 203, 14 };
TrainScene::TrainScene(SDL_Window* w, SDL_Surface* s)
	: Scene(w, s)
{
}
void TrainScene::Init()
{
	_cabins.push_back(TrainCabin());
    chair = loadImage("Sprites//chair.png");
}

void TrainScene::Exit()
{
}

void TrainScene::Update(double dt)
{
}

void TrainScene::Render()
{
    SDL_FillRect(m_Surface, NULL, SDL_MapRGB(m_Surface->format, DARK_LIME.r, DARK_LIME.g, DARK_LIME.b));
    SDL_BlitSurface(chair, NULL, m_Surface, NULL);

}

SDL_Surface* TrainScene::loadImage(std::string path)
{
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedImage = IMG_Load(path.c_str());
    if (loadedImage == NULL)  
        std::cout << "Unable to load image %s! SDL_image Error:"<< path.c_str() << IMG_GetError() << std::endl;
    else
    {
        optimizedSurface = SDL_ConvertSurface(loadedImage, m_Surface->format, 0);
        if (optimizedSurface == NULL)
            std::cout << "Unable to optimize image %s! SDL Error" << path.c_str() << SDL_GetError() << std::endl;
        SDL_FreeSurface(loadedImage);
    }
    return optimizedSurface;
}