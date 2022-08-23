#include "TrainScene.h"
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include "BoxCollider.h"
#include "Player.h"
#include "InteractablePerson.h"
#include "Texture.h"
#include <math.h>
#include <string>
#include <algorithm>
#include <functional>

const int x_level = 35;
const int y_level = 480;
const int x_offset = 190;
const float player_speed = 1.0f;
const float text_type_speed = 25;
bool isTransitioning = false;
bool isInteracting = false;
bool ticketFront = false;
bool ticketStamp = false;
bool ticketReturn = false;
bool moveDirectionRight = false;
bool renderAnnoucement = false;
double iterator = 0;
int frame_count = 0;
int last_dir = 0;
int pageChanger = 0;
int keyTimer = 0;
int blackScreenAlpha = 0;
std::string _dT;

bool inBoundsUp(int y)
{
    if (y <= 220)
    return false;
}

bool inBoundsDown(int y)
{
    if (y >= 320)
    return false;
}

/// <summary>
/// Constructor, used to initialize values.
/// </summary>
TrainScene::TrainScene()
    : writingText(false), _displayText(" "), _currentCabin(0), level(1)
{
    /*_mainRide->loadAttributes(level);
    for (auto stopLst : _mainRide->stops)
    {
        std::cout << stopLst << std::endl;
    }*/
}

/// <summary>
/// Checks if there is person that was clicked (checked by using the mouse's collider and checking through all the
/// seats for collision)
/// </summary>
/// <returns>The pointer to the person if found, if not, returns nullptr</returns>
Person* TrainScene::getPersonClick()
{
    auto seats = _cabins[_currentCabin]->getSeats();
    for (int i = 0; i < seats.size(); i++)
    {
        if (seats[i] == nullptr) continue;
        if (seats[i]->getCollider() == nullptr) continue;
        if (seats[i]->getCollider()->isColliding(_mouseCollider)) {
            //std::cout << seats[i];
            return seats[i];
        }
    }
    return nullptr;
}

/// <summary>
/// Create the interactive people objects and adds them to the render queue.
/// WARNING: The top row and bottom row are added to queue in sequence. Make sure that the player is rendered in between.
/// </summary>
void TrainScene::renderCabins()
{
    int x_offset, y_offset;
    int initialX = 0, initialY = 45;
    x_offset = 190;
    y_offset = 180;
    auto seats = _cabins[_currentCabin]->getSeats();
    for (int row = 0; row < 6; row++) {
        if (seats[TrainCabin::ConvertToPosition({ 0, row })] != NULL) {
            if (row < 3) {
                seats[TrainCabin::ConvertToPosition({ 0, row })]->setCoords({ (x_offset * row) + initialX, initialY + 100 });
            }
            else
                seats[TrainCabin::ConvertToPosition({ 0, row })]->setCoords({ (x_offset * row) + initialX + 100, initialY + 100 });
             

            RenderAtCoords(seats[TrainCabin::ConvertToPosition({ 0, row })]);
        }
        
    }
    for (int column = 1; column < 3; column++) {
        {
            if (column == 2) {
                RenderAtCoords(_objList[OBJECT_PLAYER]);
                RenderAtCoords(_objList[OBJECT_CHAIR_ROW]);
            }
            for (int row = 0; row < 6; row++)
            {
                if (row < 3) {
                    if (seats[TrainCabin::ConvertToPosition({ column, row })] != NULL) {
                        seats[TrainCabin::ConvertToPosition({ column, row })]->setCoords({ (x_offset * row) + initialX, (y_offset * column) + initialY });
                        /*std::cout << "Collider:(" << (x_offset * row) + initialX << "," << (y_offset * column) + initialY << ")\n";*/
                        if (seats[TrainCabin::ConvertToPosition({ column, row })]->getCollider() == nullptr) {
                            seats[TrainCabin::ConvertToPosition({ column, row })]->getCollider() = new BoxCollider({ (x_offset * row) + initialX + seats[TrainCabin::ConvertToPosition({column, row})]->getTexture().getWidth() / 3, (y_offset * column) + initialY + seats[TrainCabin::ConvertToPosition({column, row})]->getTexture().getHeight() / 4, 60, 100 });
                        }
                        if (static_cast<InteractablePerson*>(seats[TrainCabin::ConvertToPosition({ column, row })])->getTicket() == nullptr) {
                            static_cast<InteractablePerson*>(seats[TrainCabin::ConvertToPosition({ column, row })])->setTicket(new Ticket(_mainRide->getStops(), _mainRide->getInvalidStops(), _mainRide->getDate()));
                        }
                        if (static_cast<InteractablePerson*>(seats[TrainCabin::ConvertToPosition({ column, row })])->getRailPass() == nullptr) {
                            static_cast<InteractablePerson*>(seats[TrainCabin::ConvertToPosition({ column, row })])->setRailPass(new RailPass(static_cast<InteractablePerson*>(seats[TrainCabin::ConvertToPosition({ column, row })])->getName(), static_cast<InteractablePerson*>(seats[TrainCabin::ConvertToPosition({ column, row })])->getPassType(), rand() % 30 + 1));
                        }

                        RenderAtCoords(seats[TrainCabin::ConvertToPosition({ column, row })]);
                    }
                }
                else {

                    if (seats[TrainCabin::ConvertToPosition({ column, row })] != NULL) {
                        seats[TrainCabin::ConvertToPosition({ column, row })]->setCoords({ (x_offset * row) + 100 + initialX,(y_offset * column) + initialY });
                        /*std::cout << "Collider:(" << (x_offset * row) + 100 + initialX << "," << (y_offset * column) + initialY << ")\n";*/
                        if (seats[TrainCabin::ConvertToPosition({ column, row })]->getCollider() == nullptr) {
                            seats[TrainCabin::ConvertToPosition({ column, row })]->getCollider() = new BoxCollider({ (x_offset * row) + 100 + initialX + seats[TrainCabin::ConvertToPosition({column, row})]->getTexture().getWidth() / 3, (y_offset * column) + initialY + seats[TrainCabin::ConvertToPosition({column, row})]->getTexture().getHeight() / 4, 60, 100 });
                        }


                        if (static_cast<InteractablePerson*>(seats[TrainCabin::ConvertToPosition({ column, row })])->getTicket() == nullptr) {
                            static_cast<InteractablePerson*>(seats[TrainCabin::ConvertToPosition({ column, row })])->setTicket(new Ticket(_mainRide->getStops(), _mainRide->getInvalidStops(), _mainRide->getDate()));
                        }
                        if (static_cast<InteractablePerson*>(seats[TrainCabin::ConvertToPosition({ column, row })])->getRailPass() == nullptr) {
                            static_cast<InteractablePerson*>(seats[TrainCabin::ConvertToPosition({ column, row })])->setRailPass(new RailPass(static_cast<InteractablePerson*>(seats[TrainCabin::ConvertToPosition({ column, row })])->getName(), static_cast<InteractablePerson*>(seats[TrainCabin::ConvertToPosition({ column, row })])->getPassType(), rand() % 30 + 1));
                        }
                        RenderAtCoords(seats[TrainCabin::ConvertToPosition({ column, row })]);
                    }

                }
            }
        }
    }
    for (int row = 0; row < 6; row++) {
        if (seats[TrainCabin::ConvertToPosition({ 3, row })] != NULL) {
            if (row < 3) {
                seats[TrainCabin::ConvertToPosition({ 3, row })]->setCoords({ (x_offset * row) + initialX, (y_offset * 2) + initialY + 55 });
            }
            else
                seats[TrainCabin::ConvertToPosition({ 3, row })]->setCoords({ (x_offset * row) + initialX + 100, (y_offset * 2) + initialY + 55 });


            RenderAtCoords(seats[TrainCabin::ConvertToPosition({ 3, row })]);
        }
    }
}

/// <summary>
/// Initialise everything needed for the scene:
/// textures, objects, colliders.
/// </summary>
void TrainScene::Init()
{
    _currentCabin = 0;
    renderAnnoucement = false;
    _currentAnimState = FADE_ANIM::FADE_ANIM_OFF;
    _mouseCollider = new BoxCollider({ _mouse_coords.x, _mouse_coords.y, 4, 4 });
    for (int i = 0; i < _mainRide->getCarriageNum(); i++) {
        _cabins.push_back(new TrainCabin());
    }
    blackScreenAlpha = 0;

    _objList[OBJECT_BLACK_SCREEN] = ObjectBuilder::CreateObject("Sprites//blackScreen.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_BLACK_SCREEN]->setToAlpha(blackScreenAlpha);
    _objList[OBJECT_BACKGROUND1] = ObjectBuilder::CreateObject("Sprites//trainCarBG.png", {0, 0}, SDL_BLENDMODE_NONE);
    _objList[OBJECT_PLAYER] = ObjectBuilder::CreateObject("Sprites//TicketMaster//tmLeftStand.png", { 700, 300 }, new BoxCollider({ (playerX) + 700 / 3, (playerY) + 300 / 4, 100, 100 }), SDL_BLENDMODE_BLEND);
    _objList[OBJECT_PLAYER]->setToScale(1.2);
    _objList[OBJECT_TEXT] = ObjectBuilder::CreateTextObject({ _displayText, TextManager::GetInstance()->getFonts()[FONT_REDENSEK], White }, { 1280 / 2, 720 / 2 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_CHAIR_ROW] = ObjectBuilder::CreateObject("Sprites//chairRow.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_TEXTBOX] = ObjectBuilder::CreateObject("Sprites//UI//dialogueBox.PNG", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_NOTEBOOK_PAGE] = ObjectBuilder::CreateObject("Sprites//Items//notebook//notebookPage1Txt.png", { 0, 200 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_NOTEBOOK] = ObjectBuilder::CreateObject("Sprites//Items//notebook//notebookClosed.png", { 0, 600 }, new BoxCollider({0, 600, 150, 300}), SDL_BLENDMODE_BLEND);
    _objList[OBJECT_NOTEBOOK]->setToScale(0.5);
    _objList[OBJECT_RETURN] = ObjectBuilder::CreateObject("Sprites//UI//returnTicketBox.PNG", { 930, 90 }, new BoxCollider({ 930 + 85, 90 + 85, 342, 85 }), SDL_BLENDMODE_BLEND);
    //_objList[OBJECT_CHOICE] = ObjectBuilder::CreateObject("Sprites//UI//optionBox.PNG", { 0, 0 }, SDL_BLENDMODE_BLEND);
    //_objList[OBJECT_GEORGE]
    //_objList[OBJECT_SASHA]
  /*  _objList[OBJECT_GEORGE] = ObjectBuilder::CreateObject("Sprites//Passengers//George.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_SASHA] = ObjectBuilder::CreateObject("Sprites//Passengers//Sasha.png", { 0, 0 }, SDL_BLENDMODE_BLEND);*/
    _objList[OBJECT_TICKET] = ObjectBuilder::CreateObject("Sprites//Items//ticket.png", { 384, 0 }, new BoxCollider({414, 120, 452, 272}), SDL_BLENDMODE_BLEND);
    _objList[OBJECT_RAILPASS] = ObjectBuilder::CreateObject("Sprites//Items//adultPass.png", { 420, 36 }, new BoxCollider({ 456, 156, 452, 272 }), SDL_BLENDMODE_BLEND);
    _objList[OBJECT_TICKET_FROM] = ObjectBuilder::CreateTextObject({ "girl help", TextManager::GetInstance()->getFonts()[FONT_REDENSEK], Grey}, {600, 192}, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_TICKET_TO] = ObjectBuilder::CreateTextObject({ "owa owa", TextManager::GetInstance()->getFonts()[FONT_REDENSEK], Grey }, { 600, 228 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_TICKET_DOI] = ObjectBuilder::CreateTextObject({ "pain", TextManager::GetInstance()->getFonts()[FONT_REDENSEK], Grey }, { 600, 264 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_RAILPASS_NAME] = ObjectBuilder::CreateTextObject({ "girl help", TextManager::GetInstance()->getFonts()[FONT_REDENSEK], Pink }, { 636, 244 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_RAILPASS_EXPIRY] = ObjectBuilder::CreateTextObject({ "aaaaaaaa", TextManager::GetInstance()->getFonts()[FONT_REDENSEK], Pink }, { 636, 280 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_HEAD] = ObjectBuilder::CreateObject("Sprites//Passengers//SashaHead.png", { 165, 435 }, SDL_BLENDMODE_BLEND);

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
        _tmAnimList[i]->setScale(1.2);
    }

    for (int j = 0; j < NUM_NOTEBOOK; j++) {
        _nbSprites[j] = new Texture();
    }
    _nbSprites[NOTEBOOK_C]->loadImage("Sprites//Items//notebook//notebookClosed.png");
    _nbSprites[NOTEBOOK_O]->loadImage("Sprites//Items//notebook//notebookOpenBlank.png");
    _nbSprites[NOTEBOOK_P1]->loadImage("Sprites//Items//notebook//notebookPage1Txt.png");
    _nbSprites[NOTEBOOK_P2]->loadImage("Sprites//Items//notebook//notebookPage2.png");
    _nbSprites[NOTEBOOK_P3]->loadImage("Sprites//Items//notebook//notebookPage3Txt.png");
    _nbSprites[NOTEBOOK_P4]->loadImage("Sprites//Items//notebook//notebookPage4Txt.png");
    for (int i = 0; i < NUM_NOTEBOOK; i++)
    {
        _nbSprites[i]->setBlendMode(SDL_BLENDMODE_BLEND);
    }
    _nbSprites[NOTEBOOK_C]->setScale(0.5);
    _nbSprites[NOTEBOOK_P1]->setScale(1);
    _nbSprites[NOTEBOOK_P2]->setScale(1);
    _nbSprites[NOTEBOOK_P3]->setScale(1);
    _nbSprites[NOTEBOOK_P4]->setScale(1);


    for (int i = 0; i < NUM_PASS_TXTR; i++)
    {
       _passTextureList[i] = new Texture();
    }

    _passTextureList[CHILD_PASS]->loadImage("Sprites//Items//childPass.png");
    _passTextureList[ADULT_PASS]->loadImage("Sprites//Items//adultPass.png");
    _passTextureList[TICKET]->loadImage("Sprites//Items//ticket.png");
    _passTextureList[TICKET_PUNCH]->loadImage("Sprites//Items//ticketPunch.png");
   
    for (int i = 0; i < NUM_PASS_TXTR; i++)
    {
        _passTextureList[i]->setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    _objList[OBJECT_STAMPER] = ObjectBuilder::CreateObject("Sprites//Items//deathStamp.png", { 0, 0 }, new BoxCollider({0 + 50, 0 + 50, 150, 150}), SDL_BLENDMODE_BLEND);
    _objList[OBJECT_STAMPER]->setToScale(0.5);
    _objList[OBJECT_STAMP_MARK] = ObjectBuilder::CreateObject("Sprites//Items//deathStampMark.png", _objList[OBJECT_TICKET]->getCoords() , SDL_BLENDMODE_BLEND);
    _objList[OBJECT_PUNCHER] = ObjectBuilder::CreateObject("Sprites//Items//punchOpen.png", {150, 20}, new BoxCollider({ 150 + 50, 20 + 50, 100, 100 }), SDL_BLENDMODE_BLEND);
    _objList[OBJECT_PUNCHER]->setToScale(0.4);
    _objList[OBJECT_RETURN] = ObjectBuilder::CreateObject("Sprites//UI//returnTicketBox.png", { 850, 90 }, new BoxCollider({850 + 85, 90 + 85, 342, 85 }), SDL_BLENDMODE_BLEND);
    _objList[OBJECT_RETURN]->setToScale(0.75);
    _objList[OBJECT_ANNOUCEMENT] = ObjectBuilder::CreateTextObject({ "Press anywhere to whistle!", TextManager::GetInstance()->getFonts()[FONT_REDENSEK], White }, { 1280 / 2 - 150, 0 }, SDL_BLENDMODE_BLEND);
    // Render queue
    _renderQueue.push_back(_objList[OBJECT_BACKGROUND1]);

    
    //createBottomRowChairs();
    Player* testPlayer = new Player(_mainRide->getStops());
    setPlayer(testPlayer);
    date = _mainPlayer->getDay();
    playerX = 700;
    playerY = 300;
    notebookOpen = false;
    fillCabins();
}
/// <summary>
/// Called on scene exit. Used to prevent memory leaks.
/// </summary>
void TrainScene::Exit()
{
    for (auto cabin : _cabins) {
        for (auto seat : cabin->getSeats()) {
            if (seat != nullptr) {
                delete seat;
                seat = nullptr;
            }
        }
    }
    for (auto i : _objList) {
        if (i != nullptr) {
            delete i;
            i = nullptr;
        }
    }
    for (auto i : _tmAnimList) {
        if (i != nullptr) {
            delete i;
            i = nullptr;
        }
    }
    for (auto i : _nbSprites) {
        if (i != nullptr) {
            delete i;
            i = nullptr;
        }
    }
    for (auto i : _passTextureList) {
        if (i != nullptr) {
            delete i;
            i = nullptr;
        }
    }
    _renderQueue.clear();
    _textQueue.clear();
    _cabins.clear();
    _displayText = " ";
}

/// <summary>
/// Called every frame. Use this for polling (checking for key input and processing)
/// </summary>
/// <param name="dt">Delta time(time inbetween frames)</param>
void TrainScene::Update(double dt)
{
   /* if (!isTransitioning) {*/
        if (_mainRide != nullptr && _mainRide->getInteractablePeople().size() == 0) {
            renderAnnoucement = true;
            /*Application::GetInstance()->changeScene(Application::GetInstance()->getScenes()[SCENE_OVERVIEW]);*/
            std::cout << "Done.\n";
        }
        
        //HandleInput();
        ///*_objList[OBJECT_TICKET]->setTexture((_interactingPerson != nullptr && static_cast<InteractablePerson*>(_interactingPerson)->getTicket().getClippedState()) ? *_passTextureList[TICKET_PUNCH] : *_passTextureList[TICKET]);*/
        //_mouseCollider->moveCollider(_mouse_coords);
        //if (_textQueue.size() > 0) {
        //    iterator += dt * text_type_speed;
        //    if ((_displayText.length() - 1) == _textQueue.front().msg.length()) {
        //        _textQueue.erase(_textQueue.begin());
        //        writingText = false;
        //    }
        //    else {
        //        if (iterator > 1.0) {
        //            _displayText += _textQueue.front().msg[_displayText.length() - 1];
        //            iterator = 0;
        //        }
        //    }

        //    _dT = _displayText;
        //    _dT.erase(0, 1);
        //    _objList[OBJECT_TEXT]->updateText(_dT, White, TextManager::GetInstance()->getFonts()[FONT_REDENSEK], SDL_BLENDMODE_BLEND);
        //}
        //_objList[OBJECT_PLAYER]->setCoords({ playerX, playerY });
    /*}*/
    //else {
    //    /*if (isTransitioning) {*/
    //    if (_fadeQueue.size() > 0) {
    //        isTransitioning = true;
    //        if (frame_count % 3 == 0) {
    //            //frame_count = 0;
    //            if (!_fadeQueue.front())
    //                ++blackScreenAlpha;
    //            else
    //                --blackScreenAlpha;
    //            std::cout << blackScreenAlpha;
    //            _objList[OBJECT_BLACK_SCREEN]->setToAlpha(blackScreenAlpha);
    //            if (!fadeDirection && blackScreenAlpha == 255) {
    //                _fadeQueue.erase(_fadeQueue.begin());
    //                // Do your action here.

    //                if (_fadeQueue.size() == 0)
    //                    isTransitioning = false;
    //            }
    //            else {
    //                if (fadeDirection && blackScreenAlpha == 0)
    //                {
    //                    _fadeQueue.erase(_fadeQueue.begin());
    //                    if (_fadeQueue.size() == 0)
    //                        isTransitioning = false;
    //                }
    //            }
    //        }
    //    }
    //   /* }*/
    //}
    switch (_currentAnimState) {
    case FADE_ANIM_OFF:
        HandleInput();
        /*_objList[OBJECT_TICKET]->setTexture((_interactingPerson != nullptr && static_cast<InteractablePerson*>(_interactingPerson)->getTicket().getClippedState()) ? *_passTextureList[TICKET_PUNCH] : *_passTextureList[TICKET]);*/
        _mouseCollider->moveCollider(_mouse_coords);
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
        _objList[OBJECT_PLAYER]->setCoords({ playerX, playerY });
        break;
    case FADE_ANIM_START:
        if (frame_count % 2 == 0) {
            ++blackScreenAlpha;
            _objList[OBJECT_BLACK_SCREEN]->setToAlpha(blackScreenAlpha);
        }
        if (blackScreenAlpha == 255) {
            _currentAnimState = FADE_ANIM::FADE_ANIM_MIDDLE;
        }
        break;
    case FADE_ANIM_MIDDLE:
        _currentCabin = (moveDirectionRight) ? _currentCabin + 1 : _currentCabin - 1;
        playerX = (moveDirectionRight) ? 30 : 980;
        _objList[OBJECT_PLAYER]->setCoords({ playerX, playerY });
        _currentAnimState = FADE_ANIM::FADE_ANIM_END;
        break;
    case FADE_ANIM_END:
        if (frame_count % 2 == 0) {
            --blackScreenAlpha;
            _objList[OBJECT_BLACK_SCREEN]->setToAlpha(blackScreenAlpha);
        }
        if (blackScreenAlpha == 0) {
            _currentAnimState = FADE_ANIM::FADE_ANIM_OFF;
        }
        break;
    default:
        break;
    }
    frame_count += 1;
    /*std::cout << isTransitioning << "\n";*/
}

/// <summary>
/// Function to render everything out into the surface on the window.
/// </summary>
void TrainScene::Render()
{
    SDL_RenderClear(Application::GetInstance()->getRenderer()); // Clear the screen.
    // Object rendering inside here
    for (int i = 0; i < _renderQueue.size(); i++)
    {
        RenderAtCoords(_renderQueue[i]);
        if (i == 0) {
            renderCabins();
        }

    }

    
    // UI Rendering
    InteractablePerson* person = static_cast<InteractablePerson*>(_interactingPerson);

    if (isInteracting && _mainRide->checkInteractable(person->getName())){
        
        RenderAtCoords(_objList[OBJECT_TEXTBOX]);
        RenderAtCoords(_objList[OBJECT_TEXT]);
        RenderAtCoords(_objList[OBJECT_HEAD]);

        if (!ticketFront)
        {
            RenderAtCoords(_objList[OBJECT_TICKET]);
            RenderAtCoords(_objList[OBJECT_TICKET_FROM]);
            RenderAtCoords(_objList[OBJECT_TICKET_TO]);
            RenderAtCoords(_objList[OBJECT_TICKET_DOI]);

            if (ticketStamp) {
                RenderAtCoords(_objList[OBJECT_STAMP_MARK]);
            }
        }
       
        bool isRailpass = _interactingPerson; //attach to getRailpass
        if (isRailpass)
        {
            RenderAtCoords(_objList[OBJECT_RAILPASS]);
            RenderAtCoords(_objList[OBJECT_RAILPASS_NAME]);
            RenderAtCoords(_objList[OBJECT_RAILPASS_EXPIRY]);
        }

        if (ticketFront && isRailpass)
        {
            RenderAtCoords(_objList[OBJECT_TICKET]);
            RenderAtCoords(_objList[OBJECT_TICKET_FROM]);
            RenderAtCoords(_objList[OBJECT_TICKET_TO]);
            RenderAtCoords(_objList[OBJECT_TICKET_DOI]);
           
            if (ticketStamp) {
                RenderAtCoords(_objList[OBJECT_STAMP_MARK]);
            }
        }
        RenderAtCoords(_objList[OBJECT_STAMPER]);
        RenderAtCoords(_objList[OBJECT_PUNCHER]);
        if (ticketStamp && ticketFront) {
            RenderAtCoords(_objList[OBJECT_STAMP_MARK]);
        }
       
        RenderAtCoords(_objList[OBJECT_RETURN]);
    }
    RenderAtCoords(_objList[OBJECT_NOTEBOOK]);
    if (notebookOpen) {
        RenderAtCoords(_objList[OBJECT_NOTEBOOK_PAGE]);
    }

    RenderAtCoords(_objList[OBJECT_BLACK_SCREEN]);
    if (renderAnnoucement) {
        RenderAtCoords(_objList[OBJECT_ANNOUCEMENT]);
    }
    SDL_RenderPresent(Application::GetInstance()->getRenderer()); // Render everything on the screen. 
}

/// <summary>
/// Handle key input inside this function. Logic is to be in this function.
/// </summary>
void TrainScene::HandleInput()
{
    // SDL_KEYDOWN is used for key presses.
    // IsKeyPressed is used for key holds.
    _mouse_coords = Application::GetInstance()->getMouseCoords();
    //_event = *Application::GetInstance()->getEvent();
    auto& events = Application::GetInstance()->GetFrameEvents();
    int option = NULL;
    for (auto& event : events) {
        for (auto button : _buttons)
        {
            int temp = button->handleEvent(&event);
            if (temp != 0) {
                option = temp;
                break;
            }
        } 
        switch (event.type) {
        case SDL_MOUSEBUTTONDOWN: {
            std::cout << "Mouse down at\n" << _mouse_coords.x << "," << _mouse_coords.y << "\n";
            if (renderAnnoucement) {
                Application::GetInstance()->changeScene(Application::GetInstance()->getScenes()[SCENE_OVERVIEW]);
                return;
            }
            if (isInteracting)
            {

                if (!static_cast<InteractablePerson*>(_interactingPerson)->getTicket()->getClippedState() && ticketFront && _objList[OBJECT_PUNCHER]->getCollider()->isColliding(_mouseCollider))
                {
                    static_cast<InteractablePerson*>(_interactingPerson)->getTicket()->setClippedState(true);
                    _objList[OBJECT_TICKET]->setTexture(*_passTextureList[TICKET_PUNCH]);
                    break;
                }

                if (ticketFront && _objList[OBJECT_STAMPER]->getCollider()->isColliding(_mouseCollider))
                {
                    ticketStamp = true;
                }
               
                if (!ticketFront && _objList[OBJECT_TICKET]->getCollider()->isColliding(_mouseCollider))
                {
                    ticketFront = true;
                    break;
                }

                else
                {
                    if (ticketFront && _objList[OBJECT_RAILPASS]->getCollider()->isColliding(_mouseCollider))
                    {
                        ticketFront = false;
                        break;
                    }
                }

                if (_objList[OBJECT_RETURN]->getCollider()->isColliding(_mouseCollider))
                {
                    std::cout << "LOLLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOLOOLOLOLOLOLOLOLOLOLOLOLOLOLOLOL" << std::endl;
                    _objList[OBJECT_TICKET]->setTexture(*_passTextureList[TICKET]);
                    ticketReturn = true;
                }

            }
            
            if (_objList[OBJECT_NOTEBOOK]->getCollider()->isColliding(_mouseCollider)) {
                if (!notebookOpen) {
                    _objList[OBJECT_NOTEBOOK]->setTexture(*(_nbSprites[NOTEBOOK_O]));
                    /*_renderQueue.push_back(_objList[OBJECT_NOTEBOOK_PAGE]);*/
                    _objList[OBJECT_NOTEBOOK]->setCoords({ 0, 200 });
                    _objList[OBJECT_NOTEBOOK]->getCollider()->moveCollider({ 0, 200 });
                    notebookOpen = true;
                }
                else
                {
                    _objList[OBJECT_NOTEBOOK]->setTexture(*(_nbSprites[NOTEBOOK_C]));
                   /* _renderQueue.pop_back();*/
                    _objList[OBJECT_NOTEBOOK]->setCoords({ 0, 600 });
                    _objList[OBJECT_NOTEBOOK]->getCollider()->moveCollider({ 0, 600 });
                    notebookOpen = false;
                }
            }
            else if (!isInteracting && !writingText) {
                _interactingPerson = getPersonClick();
                if (_interactingPerson != nullptr && getDistance({ _objList[OBJECT_PLAYER]->getCoords().x, _objList[OBJECT_PLAYER]->getCoords().y }, { _interactingPerson->getCoords().x, _interactingPerson->getCoords().y}) <= 150) {
                    isInteracting = true;
                    ticketReturn = false;
                    ticketStamp = false;
                    playerInteraction();
                }
            }
            else {
                if (!writingText)         
                    playerInteraction(option);               
            }
            break;
        }
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_DOWN:
                break;

            case SDLK_RIGHT:
                pageChanger = (pageChanger + 1 <= 4) ? pageChanger + 1:pageChanger;
                break;

            case SDLK_LEFT:
                pageChanger = (pageChanger - 1 >= 1) ? pageChanger - 1 : pageChanger;
                break;

            case SDLK_UP:
                break;
            }
        }
    }
    
    switch (pageChanger)
    {
    case 1:
        _objList[OBJECT_NOTEBOOK_PAGE]->setTexture(*(_nbSprites[NOTEBOOK_P1]));
        break;

    case 2:
        _objList[OBJECT_NOTEBOOK_PAGE]->setTexture(*(_nbSprites[NOTEBOOK_P2]));
        break;

    case 3:
        _objList[OBJECT_NOTEBOOK_PAGE]->setTexture(*(_nbSprites[NOTEBOOK_P3]));
        break;

    case 4:
        _objList[OBJECT_NOTEBOOK_PAGE]->setTexture(*(_nbSprites[NOTEBOOK_P4]));
        break;
    }

    

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

    if (Application::IsKeyPressed('W'))
    {
        if (frame_count % 3 == 0 && inBoundsUp(playerY) != false)
        {
            playerY -= player_speed;
        }
       
        if (frame_count < 180)
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
            playerX -= player_speed;
        }
       // offSetX -= player_speed;

        if (frame_count < 180)
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

        if (_currentCabin - 1 >= 0 && playerX <= -45 && _currentAnimState == FADE_ANIM::FADE_ANIM_OFF)
        {
            /*fade(false);*/
            _currentAnimState = FADE_ANIM::FADE_ANIM_START;
            moveDirectionRight = false;
            /*_currentCabin -= 1;
            playerX = 980;*/
            std::cout << "hehexd" << _currentCabin << std::endl;
        }

        last_dir = 2; 
    }

    if (Application::IsKeyPressed('S'))
    {
        if (frame_count % 3 == 0 && inBoundsDown(playerY) != false) 
        {
            playerY += player_speed;
        }

        if (frame_count < 180)
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
            playerX += player_speed;
        }

        if (frame_count < 180)
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

        if (_currentCabin + 1 < _cabins.size() && playerX >= 1050 && _currentAnimState == FADE_ANIM::FADE_ANIM_OFF)
        {
            _currentAnimState = FADE_ANIM::FADE_ANIM_START;
            moveDirectionRight = true;
            std::cout << "pogchamp ?!" << std::endl;
        }

            last_dir = 4;
    }
   
}

/// <summary>
/// Called after player input.
/// </summary>
void TrainScene::playerInteraction(int option)
{
    InteractablePerson* person = static_cast<InteractablePerson*>(_interactingPerson);
    Ticket* comparisonTicket = person->getTicket();
    RailPass* comparisonRailpass = person->getRailPass();
    std::string filepath = "Sprites//Passengers//" + person->getName() + "Head.png";
    Texture headTexture;
    headTexture.loadImage(filepath);
    headTexture.setBlendMode(SDL_BLENDMODE_BLEND);
    _objList[OBJECT_HEAD]->setTexture(headTexture);
    _objList[OBJECT_HEAD]->setToScale(0.9);

    _objList[OBJECT_TICKET_DOI]->updateText("June " + std::to_string(person->getTicket()->getIssueDate()), Grey, TextManager::GetInstance()->getFonts()[FONT_REDENSEK], SDL_BLENDMODE_BLEND);
    _objList[OBJECT_TICKET_TO]->updateText(person->getTicket()->getDestination(), Grey, TextManager::GetInstance()->getFonts()[FONT_REDENSEK], SDL_BLENDMODE_BLEND);
    _objList[OBJECT_TICKET_FROM]->updateText(_mainRide->getStart(), Grey, TextManager::GetInstance()->getFonts()[FONT_REDENSEK], SDL_BLENDMODE_BLEND);
    
    
    if (!person->getPassType())
    {
        _objList[OBJECT_RAILPASS]->setTexture(*(_passTextureList[ADULT_PASS]));
        _objList[OBJECT_RAILPASS_NAME]->updateText(person->getRailPass()->getName(), Teal, TextManager::GetInstance()->getFonts()[FONT_REDENSEK], SDL_BLENDMODE_BLEND);
        _objList[OBJECT_RAILPASS_EXPIRY]->updateText("June " + std::to_string(person->getRailPass()->getExpiry() + 1), Teal, TextManager::GetInstance()->getFonts()[FONT_REDENSEK], SDL_BLENDMODE_BLEND);
    }

    if (person->getPassType())
    {
        _objList[OBJECT_RAILPASS]->setTexture(*(_passTextureList[CHILD_PASS]));
        _objList[OBJECT_RAILPASS_NAME]->updateText(person->getRailPass()->getName(), Pink, TextManager::GetInstance()->getFonts()[FONT_REDENSEK], SDL_BLENDMODE_BLEND);
        _objList[OBJECT_RAILPASS_EXPIRY]->updateText("June " + std::to_string(person->getRailPass()->getExpiry() + 1), Pink, TextManager::GetInstance()->getFonts()[FONT_REDENSEK], SDL_BLENDMODE_BLEND);
    }
   
    if (_buttons.size() != 0) {
        for (int i = 0; i < person->getCurrentNode()->results.size() * 2; i++)
        {
            if (_renderQueue.back() != nullptr)
                delete _renderQueue.back();
            _renderQueue.pop_back();
        }
    }
    _buttons.clear();
    std::vector<Node*> nodes = person->getNodes();
    Node* currentNode;
    if (option != NULL) {
        person->getCurrentNode() = nodes[person->getCurrentNode()->results[option - 1]];
    }
    currentNode = person->getCurrentNode();
    const int button_x = 300;
    const int button_y = 115;
    const int y_offset = -65;
    const int button_text_offset_x = 625;
    const int button_text_offset_y = 270;
    // Before or after a conversation, _currentNode should be nullptr.
    if (nodes.size() == 0) {
    	std::cout << "No nodes to interact" << std::endl;
    	return;
    }
    if (currentNode == nullptr)
        currentNode = nodes.front();
    if (ticketReturn) {
        /*for (int i = 0; i < 2; i++)
        {
            _renderQueue.pop_back();
        }*/
        /*if (person->verdictChecker(ticketStamp) == false)
        {
            _mainRide->setWrongVerdict(_mainRide->getWrongVerdict() + 1);
        }*/
        auto ppl = _mainRide->getInteractablePeople();
        ppl.erase(std::remove(ppl.begin(), ppl.end(), static_cast<InteractablePerson*>(_interactingPerson)->getName()), ppl.end());
        _mainRide->setInteractablePeople(ppl);
        person->getCurrentNode() = nullptr;
        _interactingPerson = nullptr;
        isInteracting = false;
        return;
    }
    if (_dT == currentNode->npcText && currentNode->results.size() == 0) {
        if (person->getTicket()->getClippedState() && _mainRide->checkInteractable(person->getName())) {
            /*for (int i = 0; i < 2; i++)
            {
                _renderQueue.pop_back();
            }*/
            if (person->verdictChecker(ticketStamp) == false)
            {
                _mainRide->setWrongVerdict(_mainRide->getWrongVerdict() + 1);
            }
            auto ppl = _mainRide->getInteractablePeople();
            ppl.erase(std::remove(ppl.begin(), ppl.end(), static_cast<InteractablePerson*>(_interactingPerson)->getName()), ppl.end());
            _mainRide->setInteractablePeople(ppl);
            person->getCurrentNode() = nullptr;
            _interactingPerson = nullptr;
            isInteracting = false;
        }
        else {
            return;
        }
    }

   
    if (currentNode == nodes.front()) {
        //write player text
        WriteText({ currentNode->playerText, TextManager::GetInstance()->getFonts()[FONT_REDENSEK] }, { 480, 500 });
        //_renderQueue.push_back(_objList[OBJECT_TEXT]);
        person->getCurrentNode() = nodes[currentNode->results.front()];
    }
    else {
        //write npc 
        WriteText({ currentNode->npcText, TextManager::GetInstance()->getFonts()[FONT_REDENSEK] }, { 480, 500 });
        for (int i = 0; i < currentNode->results.size(); i++)
        {
            _buttons.push_back(new Button(i + 1));
            _buttons.back()->setCoords({ button_x, button_y + y_offset * i });
            _buttons.back()->getCollider() = new BoxCollider({ button_x + 600, button_y + y_offset * i + 250, 300, 60 });
            _renderQueue.push_back(_buttons.back());
            //create the text on the button
            _renderQueue.push_back(ObjectBuilder::CreateTextObject({ nodes[currentNode->results[i]]->playerText,  TextManager::GetInstance()->getFonts()[FONT_REDENSEK_SMALL], White }, { _buttons[i]->getCoords().x + button_text_offset_x, _buttons[i]->getCoords().y + button_text_offset_y }, SDL_BLENDMODE_BLEND, 200));
        }
    }
    
    
    return;

}

/// <summary>
/// Adds text to the text queue for rendering. This function is to be called once to write the message once.
/// (Don't call this every frame)
/// </summary>
/// <param name="text">The text to be written (Text is a struct containing the string, font and colour of the text)</param>
/// <param name="pos">The position of the text on the surface (SDL_Point, a integer Vector2)</param>
void TrainScene::WriteText(const Text& text, const SDL_Point& pos)
{
    iterator = 0;
    _displayText = " ";
    _textQueue.push_back(text);
    _objList[OBJECT_TEXT]->setCoords(pos);
    writingText = true;
}

void TrainScene::RenderAtCoords(Object* obj)
{
    obj->getTexture().Render(obj->getCoords().x, obj->getCoords().y);
}

float TrainScene::getDistance(const SDL_Point& first, const SDL_Point& second)
{
    return sqrt(pow(second.x - first.x, 2) + pow(second.y - first.y, 2));
}

void TrainScene::fillCabins()
{
    std::vector<int> positions;
    std::vector < std::string> names = _mainRide->getInteractablePeople();
    int newPosition;
    TrainCabin* cabin;
    for (int i = 0; i < number_of_seats; i++)
    {
        if (TrainCabin::ConvertToPoint(i).x == 0 || TrainCabin::ConvertToPoint(i).x == 3)
            positions.push_back(i);
    }
    size_t no_of_positions = positions.size();
    for (int i = 0; i < _mainRide->getNonInteractable(); i++)
    {
        newPosition = positions[rand() % no_of_positions];
        cabin = _cabins[rand() % _cabins.size()];
        if (cabin->getSeats()[newPosition] == nullptr)
            cabin->getSeats()[newPosition] = new NonInteractivePerson();
        else
            i--;
    }
    positions.clear();
    for (int i = 0; i < number_of_seats; i++)
    {
        if (TrainCabin::ConvertToPoint(i).x == 1 || TrainCabin::ConvertToPoint(i).x == 2)
            positions.push_back(i);
    }
    no_of_positions = positions.size();
    int nameIndex;
    for (int i = 0; i < _mainRide->getInteractable(); i++)
    {
        newPosition = positions[rand() % no_of_positions];
        cabin = _cabins[rand() % _cabins.size()];
        nameIndex = rand() % names.size();
        if (cabin->getSeats()[newPosition] == nullptr) {
            cabin->getSeats()[newPosition] = new InteractablePerson(names[nameIndex]);
            names.erase(names.begin() + nameIndex);
        }
        else
            i--;
    }
}

void TrainScene::setPlayer(Player* p)
{
    _mainPlayer = p;
}

void TrainScene::setRide(Ride* r)
{
    _mainRide = r;
}

Ride* TrainScene::getMainRide()
{
    return _mainRide;
}

void TrainScene::fade(bool dir)
{
    isTransitioning = true;
    moveDirectionRight = dir;
}

void TrainScene::setMainRide(Ride* ride)
{
    _mainRide = ride;
}

/// <summary>
/// Get the list of train cabins(logic)
/// </summary>
/// <returns>Vector of TrainCabin pointers</returns>
std::vector<TrainCabin*> TrainScene::getCabins()
{
    return _cabins;
}



