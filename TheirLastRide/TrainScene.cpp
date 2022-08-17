#include "TrainScene.h"
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>

const int x_level = 35;
const int y_level = 480;
const int x_offset = 190;

TrainScene::TrainScene()
    : writingText(false), _displayText(" ")
{

}

void TrainScene::Init()
{
	_cabins.push_back(TrainCabin());

    _objList[OBJECT_BACKGROUND1] = ObjectBuilder::CreateObject("Sprites//trainCarBG.png", {0, 0}, SDL_BLENDMODE_NONE);
    _objList[OBJECT_PLAYER] = ObjectBuilder::CreateObject("Sprites//tmStand.png", { 700, 300 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_PLAYER]->setToScale(1.1);
    _objList[OBJECT_TEXT] = ObjectBuilder::CreateTextObject(_displayText, White, TextManager::GetInstance()->getFonts()[FONT_REDENSEK], { 1280 / 2, 720 / 2 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_CHAIR_ROW] = ObjectBuilder::CreateObject("Sprites//chairRow.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    /*_objList[OBJECT_CHAIR]->setToScale(0.35);*/

    // Render queue
    _renderQueue.push_back(_objList[OBJECT_BACKGROUND1]);
    _renderQueue.push_back(_objList[OBJECT_PLAYER]);
    _renderQueue.push_back(_objList[OBJECT_CHAIR_ROW]);
    //createBottomRowChairs();
    _renderQueue.push_back(_objList[OBJECT_TEXT]);

}

void TrainScene::Exit()
{
    for (auto i : _renderQueue) {
        if (i != nullptr) {
            delete i;
        }
    }
}

void TrainScene::Update(double dt)
{
    
}

void TrainScene::Render()
{
    SDL_RenderClear(Application::GetInstance()->getRenderer());
    //rendering inside here
    for (auto i : _renderQueue) {
        i->getTexture().Render(i->getCoords().x, i->getCoords().y);
        //if (i->getCoords().x == _objList[OBJECT_TEXT]->getCoords().x) {
        //    std::cout << i->getTexture().getWidth() << std::endl;
        //}
    }

    SDL_RenderPresent(Application::GetInstance()->getRenderer());
}



void TrainScene::WriteText(const std::string& msg, const SDL_Color& color, TTF_Font* font, const SDL_Point& pos)
{
    if (!writingText) {
        _displayText = " ";
        writingText = true;
    }
    else {
        Texture temp_text;
        if (_displayText.length() - 1 == msg.length()) {
            writingText = false;
        }
        else {
            //std::cout << _displayText << std::endl;
            _displayText += msg[_displayText.length() - 1];
            _objList[OBJECT_TEXT]->updateText(_displayText, color, font, SDL_BLENDMODE_BLEND);
        }
        /*_objList[OBJECT_TEXT] = ObjectBuilder::CreateTextObject(_displayText, White, TextManager::GetInstance()->getFonts()[FONT_REDENSEK], { 1280 / 2, 720 / 2 }, SDL_BLENDMODE_BLEND);*/
        /*_objList[OBJECT_TEXT].setTexture(temp_text);*/
    }
}

