#include "TrainScene.h"
#include <SDL_image.h>
#include <iostream>
SDL_Texture* chair;
SDL_Rect dest;
const SDL_Color DARK_LIME = { 153, 203, 14 };
TrainScene::TrainScene(SDL_Window* w, SDL_Surface* s, SDL_Renderer* r)
	: Scene(w, s, r)
{
}
void TrainScene::Init()
{
	_cabins.push_back(TrainCabin());
    chair = loadImage("Sprites//chair.png");
    dest.x = 1280 / 2;
    dest.y = 720 / 2;
    dest.w = 100;
    dest.h = 100;
   
}

void TrainScene::Exit()
{
    SDL_DestroyTexture(chair);
}

void TrainScene::Update(double dt)
{
}

void TrainScene::Render()
{
    SDL_RenderClear(m_Renderer);
    SDL_SetTextureBlendMode(chair, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(m_Renderer, NULL);
    SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 0);
    SDL_RenderFillRect(m_Renderer, &dest);
    SDL_RenderCopy(m_Renderer, chair, NULL, &dest);
    SDL_RenderPresent(m_Renderer);
}

SDL_Texture* TrainScene::loadImage(std::string path)
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
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, optimizedSurface);
    SDL_FreeSurface(optimizedSurface);
    return texture;
}