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

    _objList[OBJECT_BACKGROUND1] = ObjectBuilder::CreateObject("Sprites//trainCarBG.png", {0, 0}, SDL_BLENDMODE_NONE);
    _objList[OBJECT_PLAYER] = ObjectBuilder::CreateObject("Sprites//tmStand.png", { 700, 300 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_PLAYER].setToScale(1.1);
    _objList[OBJECT_TEXT] = ObjectBuilder::CreateTextObject("This is a objectbuilder test", White, TextManager::GetInstance()->getFonts()[FONT_REDENSEK], { 1280 / 2, 720 / 2 }, SDL_BLENDMODE_BLEND);

    // Render queue
    _renderQueue.push_back(_objList[OBJECT_BACKGROUND1]);
    _renderQueue.push_back(_objList[OBJECT_PLAYER]);
    createBottomRowChairs();
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

    SDL_RenderPresent(Application::GetInstance()->getRenderer());
}

void TrainScene::createBottomRowChairs()
{
    const int x_level = 35;
    const int y_level = 480;
    const int x_offset = 190;
    Object chair_object = ObjectBuilder::CreateObject("Sprites//chair.png", { x_level, y_level }, SDL_BLENDMODE_BLEND);
    chair_object.setToScale(0.35);
    for (int i = 0; i < 3; i++)
    {
        _renderQueue.push_back(chair_object);
        chair_object.setCoords({ chair_object.getCoords().x + x_offset, y_level });
    }
    chair_object.setCoords({ chair_object.getCoords().x + 105, y_level });
    for (int i = 0; i < 3; i++)
    {
        _renderQueue.push_back(chair_object);
        chair_object.setCoords({ chair_object.getCoords().x + x_offset, y_level });
    }

}

