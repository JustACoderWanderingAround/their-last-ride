#include "TrainScene.h"
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>

const int x_level = 35;
const int y_level = 480;
const int x_offset = 190;
const float player_speed = 1.0f;
const float text_type_speed = 25;
double iterator = 0;
int frame_count = 0;
std::string _dT;

TrainScene::TrainScene()
    : writingText(false), _displayText(" ")
{

}

void TrainScene::Init()
{
	_cabins.push_back(TrainCabin());

    _objList[OBJECT_BACKGROUND1] = ObjectBuilder::CreateObject("Sprites//trainCarBG.png", {0, 0}, SDL_BLENDMODE_NONE);
    _objList[OBJECT_PLAYER] = ObjectBuilder::CreateObject("Sprites//TicketMaster//tmStand.png", { 700, 300 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_PLAYER]->setToScale(1.3);
    _objList[OBJECT_TEXT] = ObjectBuilder::CreateTextObject({ _displayText, TextManager::GetInstance()->getFonts()[FONT_REDENSEK], White }, { 1280 / 2, 720 / 2 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_CHAIR_ROW] = ObjectBuilder::CreateObject("Sprites//chairRow.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    /*_objList[OBJECT_CHAIR]->setToScale(0.35);*/

    for (int i = 0; i < NUM_TM_ANIM; i++)
    {
        _tmAnimList[i] = new Texture();
    }
    _tmAnimList[TM_ANIM_STAND_L]->loadImage("Sprites//TicketMaster//tmLeftStand.png");
    _tmAnimList[TM_ANIM_STAND_R]->loadImage("Sprites//TicketMaster//tmRightStand.png");
    _tmAnimList[TM_ANIM_WALK_L_1]->loadImage("Sprites//TicketMaster//tmLeftWalk1.png");
    _tmAnimList[TM_ANIM_WALK_L_2]->loadImage("Sprites//TicketMaster//tmLeftWalk2.png");
    _tmAnimList[TM_ANIM_WALK_R_1]->loadImage("Sprites//TicketMaster//tmRightWalk1.png");
    _tmAnimList[TM_ANIM_WALK_R_2]->loadImage("Sprites//TicketMaster//tmRightWalk2.png");
    _tmAnimList[TM_ANIM_FRONT]->loadImage("Sprites//TicketMaster//tmFront.png");
    _tmAnimList[TM_ANIM_BACK]->loadImage("Sprites//TicketMaster//tmBack.png");

    for (int i = 0; i < NUM_TM_ANIM; i++)
    {
        _tmAnimList[i]->setBlendMode(SDL_BLENDMODE_BLEND);
        _tmAnimList[i]->setScale(1.3);
    }
    // Render queue
    _renderQueue.push_back(_objList[OBJECT_BACKGROUND1]);
    _renderQueue.push_back(_objList[OBJECT_PLAYER]);
    _renderQueue.push_back(_objList[OBJECT_CHAIR_ROW]);
    //createBottomRowChairs();
    _renderQueue.push_back(_objList[OBJECT_TEXT]);

    offSetX = 0;
    offSetY = 0;

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
   
    HandleKeyPress();
    if (_textQueue.size() > 0) {
        iterator += dt * text_type_speed;
        if ((_displayText.length() - 1) == _textQueue.front().msg.length()) {
            _textQueue.erase(_textQueue.begin());
        }  
        else {
            if (iterator > 1.0) {
                _displayText += _textQueue.front().msg[_displayText.length() - 1];
                iterator = 0;
            }
        }
        _dT = _displayText;
        _dT.erase(0, 1);
        _objList[OBJECT_TEXT]->updateText(_dT, White, TextManager::GetInstance()->getFonts()[FONT_REDENSEK], SDL_BLENDMODE_BLEND);
    }
    frame_count += 1;
    _objList[OBJECT_PLAYER]->setCoords({ offSetX, offSetY });
}

void TrainScene::Render()
{
    SDL_RenderClear(Application::GetInstance()->getRenderer());
    //rendering inside here
    for (auto i : _renderQueue) {
        i->getTexture().Render(i->getCoords().x, i->getCoords().y);
    }

    SDL_RenderPresent(Application::GetInstance()->getRenderer());
}

void TrainScene::HandleKeyPress()
{
    if (Application::IsKeyPressed('W'))
    {
        if (frame_count % 3 == 0)
        {
            offSetY -= player_speed;
        }
       
        _objList[OBJECT_PLAYER]->setTexture(*(_tmAnimList[TM_ANIM_BACK]));

    }

    if (Application::IsKeyPressed('A'))
    {
        if (frame_count % 3 == 0)
        {
            offSetX -= player_speed;
        }
       // offSetX -= player_speed;

        if (frame_count < 180);
        {
            _objList[OBJECT_PLAYER]->setTexture(*(_tmAnimList[TM_ANIM_WALK_L_1]));
        }
        
        if (frame_count >= 180)
        {
            _objList[OBJECT_PLAYER]->setTexture(*(_tmAnimList[TM_ANIM_WALK_L_2]));
            
            if (frame_count >= 360)
            {
                frame_count = 0;
            }
        }

    }

    if (Application::IsKeyPressed('S'))
    {
        if (frame_count % 3 == 0)
        {
            offSetY += player_speed;
        }

        _objList[OBJECT_PLAYER]->setTexture(*(_tmAnimList[TM_ANIM_FRONT]));
    }

    if (Application::IsKeyPressed('D'))
    {
        if (frame_count % 3 == 0)
        {
            offSetX += player_speed;
        }

        if (frame_count < 180);
        {
            _objList[OBJECT_PLAYER]->setTexture(*(_tmAnimList[TM_ANIM_WALK_R_1]));
        }

        if (frame_count >= 180)
        {
            _objList[OBJECT_PLAYER]->setTexture(*(_tmAnimList[TM_ANIM_WALK_R_2]));

            if (frame_count >= 360)
            {
                frame_count = 0;
            }
        }
    }
}
void TrainScene::WriteText(const Text& text, const SDL_Point& pos)
{
    iterator = 0;
    _displayText = " ";
    _textQueue.push_back(text);
}

