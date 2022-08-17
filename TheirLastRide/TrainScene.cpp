#include "TrainScene.h"
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
TrainScene::TrainScene()
{

}
void TrainScene::Init()
{
    TTF_Font* Redensek = TTF_OpenFont("Fonts//REDENSEK.TTF",24);
	_cabins.push_back(TrainCabin());

    Texture background;
    if (!createImage("Sprites//trainCarBG.png", background)) {
        std::cout << "Image not imported.\n";
    }     
    background.setBlendMode(SDL_BLENDMODE_NONE);
    _objs.push_back(Object(background, {0, 0}));

    Texture player;
    if (!createImage("Sprites//tmStand.png", player)) {
        std::cout << "Image not imported.\n";
    }
    player.setBlendMode(SDL_BLENDMODE_BLEND);
    player.setScale(1.1);
    _objs.push_back(Object(player, { 700, 300 }));

    Texture chair;
    if (!createImage("Sprites//chair.png", chair)) {
        std::cout << "Image not imported.\n";
    }
    chair.setScale(.35);
    chair.setBlendMode(SDL_BLENDMODE_BLEND);

    const int y_level = 480;
    const int x_offset = 190;
    Object chair_object = Object(chair, { 35, y_level });
    for (int i = 0; i < 3; i++)
    {
        _objs.push_back(chair_object);
        chair_object.setCoords({ chair_object.getCoords().x + x_offset, y_level});
    }
    chair_object.setCoords({ chair_object.getCoords().x + 105, y_level });
    for (int i = 0; i < 3; i++)
    {
        _objs.push_back(chair_object);
        chair_object.setCoords({ chair_object.getCoords().x + x_offset, y_level });
    }

    
   
}

void TrainScene::Exit()
{
    
}

void TrainScene::Update(double dt)
{
}

void TrainScene::Render()
{
    SDL_RenderClear(Application::GetInstance()->getRenderer());
    //rendering inside here
    for (auto i : _objs) {
        i.getTexture().Render(i.getCoords().x, i.getCoords().y);
    }

    SDL_RenderPresent(Application::GetInstance()->getRenderer());
}

bool TrainScene::createImage(std::string path, Texture& _txt)
{
    if (!_txt.loadImage(path)) {
        std::cout << "Failed to load image.\n";
        return false;
    }
    return true;
}