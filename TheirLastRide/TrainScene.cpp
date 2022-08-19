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
int last_dir = 0;
std::string _dT;

TrainScene::TrainScene()
    : writingText(false), _displayText(" "), _mouseCollider({ Application::GetInstance()->getMouseCoords().x, Application::GetInstance()->getMouseCoords().y, 4, 4 }), _currentCabin(0)
{
    
}

void TrainScene::renderCabins()
{
    /*for (int i = 0; i < _cabins.size(); i++)
    {
       
    }*/
    int x_offset, y_offset;
    int initialX = 0, initialY = 45;
    x_offset = 190;
    y_offset = 180;
    auto seats = _cabins[_currentCabin]->getSeats();
    for (int column = 1; column < 3; column++)
    {
        //for (int column = 0; column < 2; column++)
        //{
        //    if (row < 2) {
        //        if (seats[TrainCabin::ConvertToPosition({ row, column })] != NULL) {
        //            seats[TrainCabin::ConvertToPosition({ row, column })]->setCoords({ x_offset * row + initialX, y_offset * column + initialY});
        //            _renderQueue.push_back(seats[TrainCabin::ConvertToPosition({ row, column })]);
        //        }
        //    }
        //    else {
        //        if (seats[TrainCabin::ConvertToPosition({ row, column })] != NULL) {
        //            seats[TrainCabin::ConvertToPosition({ row, column })]->setCoords({ x_offset * row + 175 + initialX, y_offset * column + initialY });
        //            _renderQueue.push_back(seats[TrainCabin::ConvertToPosition({ row, column })]);
        //        }
        //    }
        //    //seats[TrainCabin::ConvertToPosition({ column, row })]->getTexture().Render(x_offset * row, y_offset * column);
        //}
        //for (int column = 2; column < 4; column++)
        //{
        //    if (row < 2) {
        //        if (seats[TrainCabin::ConvertToPosition({ row, column })] != NULL) {
        //            seats[TrainCabin::ConvertToPosition({ row, column })]->setCoords({ x_offset * row + initialX, y_offset * column + 200 + initialY});
        //            _renderQueue.push_back(seats[TrainCabin::ConvertToPosition({ row, column })]);
        //        }
        //    }
        //    else {
        //        if (seats[TrainCabin::ConvertToPosition({ row, column })] != NULL) {
        //            seats[TrainCabin::ConvertToPosition({ row, column })]->setCoords({ x_offset * row + 175 + initialX, y_offset * column + 200 + initialY});
        //            _renderQueue.push_back(seats[TrainCabin::ConvertToPosition({ row, column })]);
        //        }
        //    }
        for (int row = 0; row < 6; row++)
        {
            if (row < 3) {
                if (seats[TrainCabin::ConvertToPosition({ column, row })] != NULL) {
                    seats[TrainCabin::ConvertToPosition({ column, row })]->setCoords({ (x_offset * row) + initialX, (y_offset * column) + initialY });
                    _renderQueue.push_back(seats[TrainCabin::ConvertToPosition({ column, row })]);
                }
            }
            else {
                if (seats[TrainCabin::ConvertToPosition({ column, row })] != NULL) {
                    seats[TrainCabin::ConvertToPosition({ column, row })]->setCoords({ (x_offset * row) + 100 + initialX,(y_offset * column) + initialY });
                    _renderQueue.push_back(seats[TrainCabin::ConvertToPosition({ column, row })]);
                }
            }
        }
        
    }
}

void TrainScene::Init()
{
	_cabins.push_back(new TrainCabin());

    _objList[OBJECT_BACKGROUND1] = ObjectBuilder::CreateObject("Sprites//trainCarBG.png", {0, 0}, SDL_BLENDMODE_NONE);
    _objList[OBJECT_PLAYER] = ObjectBuilder::CreateObject("Sprites//TicketMaster//tmLeftStand.png", { 700, 300 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_PLAYER]->setToScale(1.3);
    _objList[OBJECT_TEXT] = ObjectBuilder::CreateTextObject({ _displayText, TextManager::GetInstance()->getFonts()[FONT_REDENSEK], White }, { 1280 / 2, 720 / 2 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_CHAIR_ROW] = ObjectBuilder::CreateObject("Sprites//chairRow.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_TEXTBOX] = ObjectBuilder::CreateObject("Sprites//UI//dialogueBox.PNG", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_CHOICE] = ObjectBuilder::CreateObject("Sprites//UI//optionBox.PNG", { 0, 0 }, SDL_BLENDMODE_BLEND);
    //_objList[OBJECT_GEORGE]
    //_objList[OBJECT_SASHA]
  /*  _objList[OBJECT_GEORGE] = ObjectBuilder::CreateObject("Sprites//Passengers//George.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_SASHA] = ObjectBuilder::CreateObject("Sprites//Passengers//Sasha.png", { 0, 0 }, SDL_BLENDMODE_BLEND);*/
    

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
    _tmAnimList[TM_ANIM_FRONT_WALK_1]->loadImage("Sprites//TicketMaster//tmFrontWalk1.png");
    _tmAnimList[TM_ANIM_FRONT_WALK_2]->loadImage("Sprites//TicketMaster//tmFrontWalk2.png");
    _tmAnimList[TM_ANIM_BACK_WALK_1]->loadImage("Sprites//TicketMaster//tmBackWalk1.png");
    _tmAnimList[TM_ANIM_BACK_WALK_2]->loadImage("Sprites//TicketMaster//tmBackWalk2.png");
    for (int i = 0; i < NUM_TM_ANIM; i++)
    {
        _tmAnimList[i]->setBlendMode(SDL_BLENDMODE_BLEND);
        _tmAnimList[i]->setScale(1.3);
    }
    // Render queue
    _renderQueue.push_back(_objList[OBJECT_BACKGROUND1]);
    _renderQueue.push_back(_objList[OBJECT_PLAYER]);
    _renderQueue.push_back(_objList[OBJECT_CHAIR_ROW]);
    renderCabins();
    _renderQueue.push_back(_objList[OBJECT_TEXTBOX]);
    _renderQueue.push_back(_objList[OBJECT_CHOICE]);
    
    //createBottomRowChairs();
    _renderQueue.push_back(_objList[OBJECT_TEXT]);
   


    offSetX = 700;
    offSetY = 300;
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
            writingText = false;
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
       
        if (frame_count < 180);
        {
            _objList[OBJECT_PLAYER]->setTexture(*(_tmAnimList[TM_ANIM_BACK_WALK_1]));
        }

        if (frame_count >= 180)
        {
            _objList[OBJECT_PLAYER]->setTexture(*(_tmAnimList[TM_ANIM_BACK_WALK_2]));

            if (frame_count >= 360)
            {
                frame_count = 0;
            }
        }

        last_dir = 1; 

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

        last_dir = 2; 
    }

    if (Application::IsKeyPressed('S'))
    {
        if (frame_count % 3 == 0)
        {
            offSetY += player_speed;
        }

        if (frame_count < 180);
        {
            _objList[OBJECT_PLAYER]->setTexture(*(_tmAnimList[TM_ANIM_FRONT_WALK_1]));
        }

        if (frame_count >= 180)
        {
            _objList[OBJECT_PLAYER]->setTexture(*(_tmAnimList[TM_ANIM_FRONT_WALK_2]));

            if (frame_count >= 360)
            {
                frame_count = 0;
            }
        }

        last_dir = 3;
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
            last_dir = 4;
    }

    if (Application::IsKeyPressed('W') == false && Application::IsKeyPressed('A') == false && Application::IsKeyPressed('S') == false && Application::IsKeyPressed('D') == false)
    {
        switch (last_dir)
        {
        case 1:
            _objList[OBJECT_PLAYER]->setTexture(*(_tmAnimList[TM_ANIM_BACK]));
            break;

        case 2:
            _objList[OBJECT_PLAYER]->setTexture(*(_tmAnimList[TM_ANIM_STAND_L]));
            break;

        case 3:
            _objList[OBJECT_PLAYER]->setTexture(*(_tmAnimList[TM_ANIM_FRONT]));
            break;

        case 4:
            _objList[OBJECT_PLAYER]->setTexture(*(_tmAnimList[TM_ANIM_STAND_R]));
            break;
        }
    }
    if (Application::IsKeyPressed) {
        renderTextBox = true;
    }
   
}
void TrainScene::WriteText(const Text& text, const SDL_Point& pos)
{
    iterator = 0;
    _displayText = " ";
    _textQueue.push_back(text);
    _objList[OBJECT_TEXT]->setCoords(pos);
    writingText = true;
}

std::vector<TrainCabin*> TrainScene::getCabins()
{
    return _cabins;
}

