#include "TrainScene.h"
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
TrainScene::TrainScene()
{

}
void TrainScene::Init()
{
	_cabins.push_back(TrainCabin());

    Texture background;
    if (!createImage("Sprites//trainCarBG.png", background)) {
        std::cout << "Image not imported.\n";
    }     
    background.setBlendMode(SDL_BLENDMODE_NONE);
    _objList[OBJECT_BACKGROUND1] = Object(background, { 0, 0 });
    _renderQueue.push_back(_objList[OBJECT_BACKGROUND1]);


    Texture player;
    if (!createImage("Sprites//tmStand.png", player)) {
        std::cout << "Image not imported.\n";
    }
    player.setBlendMode(SDL_BLENDMODE_BLEND);
    player.setScale(1.1);
    _objList[OBJECT_PLAYER] = Object(player, { 700, 300 });
    _renderQueue.push_back(_objList[OBJECT_PLAYER]);

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
        _renderQueue.push_back(chair_object);
        chair_object.setCoords({ chair_object.getCoords().x + x_offset, y_level});
    }
    chair_object.setCoords({ chair_object.getCoords().x + 105, y_level });
    for (int i = 0; i < 3; i++)
    {
        _renderQueue.push_back(chair_object);
        chair_object.setCoords({ chair_object.getCoords().x + x_offset, y_level });
    }
    Texture text;
    if (!createText("among us sussy morbing ye",White, TextManager::GetInstance()->getFonts()[FONT_REDENSEK], text)) {
        std::cout << "Text not imported.\n";
    }
    text.setBlendMode(SDL_BLENDMODE_BLEND);
    _objList[OBJECT_TEXT] = Object(text, {1280 / 2, 720 / 2});
    _renderQueue.push_back(_objList[OBJECT_TEXT]);
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
    for (auto i : _renderQueue) {
        i.getTexture().Render(i.getCoords().x, i.getCoords().y);
    }
    /*tm->RenderText("Fortnite", tm->getFonts()[FONT_REDENSEK], { 0, 0, 100, 100 }, White);*/

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

bool TrainScene::createText(const std::string& message, SDL_Color textcolor, TTF_Font* font, Texture& _txt)
{
    if (!_txt.loadText(message, font, textcolor)) {
        std::cout << "Failed to load text.\n";
        return false;
    }
    return true;
}
