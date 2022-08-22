#include "TrainScene.h"
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include "BoxCollider.h"
#include "Player.h"
#include "Texture.h"
#include <math.h>
const int x_level = 35;
const int y_level = 480;
const int x_offset = 190;
const float player_speed = 1.0f;
const float text_type_speed = 25;
bool isInteracting = false;
bool ticketFront = false;
double iterator = 0;
int frame_count = 0;
int last_dir = 0;
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
    mainRide->loadAttributes(level);
    for (auto stopLst : mainRide->stops)
    {
        std::cout << stopLst << std::endl;
    }
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
    for (int column = 1; column < 3; column++)
    {
        if (column == 2) {
            _renderQueue.push_back(_objList[OBJECT_PLAYER]);
            _renderQueue.push_back(_objList[OBJECT_CHAIR_ROW]);
        }
        for (int row = 0; row < 6; row++)
        {
            if (row < 3) {
                if (seats[TrainCabin::ConvertToPosition({ column, row })] != NULL) {
                    //TODO: centre the box collider
                    seats[TrainCabin::ConvertToPosition({ column, row })]->setCoords({ (x_offset * row) + initialX, (y_offset * column) + initialY});
                    std::cout << "Collider:(" << (x_offset * row) + initialX << "," << (y_offset * column) + initialY << ")\n";
                    seats[TrainCabin::ConvertToPosition({ column, row })]->getCollider() = new BoxCollider({ (x_offset * row) + initialX + seats[TrainCabin::ConvertToPosition({column, row})]->getTexture().getWidth() / 3, (y_offset * column) + initialY + seats[TrainCabin::ConvertToPosition({column, row})]->getTexture().getHeight() / 4, 60, 100});
                    /*seats[TrainCabin::ConvertToPosition({ column, row })]->getCollider() = new BoxCollider({ (x_offset * row) + initialX, (y_offset * column) + initialY, 50, 50 });*/
                    static_cast<InteractablePerson*>(seats[TrainCabin::ConvertToPosition({ column, row })])->setTicket(new Ticket(mainRide->stops, mainRide->invalidStops, mainRide->getDate()));
                    _renderQueue.push_back(seats[TrainCabin::ConvertToPosition({ column, row })]);
                }
            }
            else {
                
                if (seats[TrainCabin::ConvertToPosition({ column, row })] != NULL) {
                    //TODO: centre the box collider
                    seats[TrainCabin::ConvertToPosition({ column, row })]->setCoords({ (x_offset * row) + 100 + initialX,(y_offset * column) + initialY });
                    std::cout << "Collider:(" << (x_offset * row) + 100 + initialX << "," << (y_offset * column) + initialY << ")\n";
                    seats[TrainCabin::ConvertToPosition({ column, row })]->getCollider() = new BoxCollider({ (x_offset * row) + 100 + initialX + seats[TrainCabin::ConvertToPosition({column, row})]->getTexture().getWidth() / 3, (y_offset * column) + initialY + seats[TrainCabin::ConvertToPosition({column, row})]->getTexture().getHeight() / 4, 60, 100 });
                    _renderQueue.push_back(seats[TrainCabin::ConvertToPosition({ column, row })]);
                }
                
            }
        }
    }
    
}

/// <summary>
/// Initialise everything needed for the scene:
/// textures, objects, colliders.
/// </summary>
void TrainScene::Init()
{
    _mouseCollider = new BoxCollider({ _mouse_coords.x, _mouse_coords.y, 4, 4 });
    /*for (int i = 0; i < mainRide->getCarriageNum(); i++) {*/
        _cabins.push_back(new TrainCabin());
    /*}*/
	

    _objList[OBJECT_BACKGROUND1] = ObjectBuilder::CreateObject("Sprites//trainCarBG.png", {0, 0}, SDL_BLENDMODE_NONE);
    _objList[OBJECT_PLAYER] = ObjectBuilder::CreateObject("Sprites//TicketMaster//tmLeftStand.png", { 700, 300 }, new BoxCollider({ (offSetX) + 700 / 3, (offSetY) + 300 / 4, 100, 100 }), SDL_BLENDMODE_BLEND);
    _objList[OBJECT_PLAYER]->setToScale(1.3);
    _objList[OBJECT_TEXT] = ObjectBuilder::CreateTextObject({ _displayText, TextManager::GetInstance()->getFonts()[FONT_REDENSEK], White }, { 1280 / 2, 720 / 2 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_CHAIR_ROW] = ObjectBuilder::CreateObject("Sprites//chairRow.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_TEXTBOX] = ObjectBuilder::CreateObject("Sprites//UI//dialogueBox.PNG", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_NOTEBOOK_PAGE] = ObjectBuilder::CreateObject("Sprites//Items//notebook//notebookPage1Txt.png", { 0, 200 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_NOTEBOOK] = ObjectBuilder::CreateObject("Sprites//Items//notebook//notebookClosed.png", { 0, 600 }, new BoxCollider({0, 600, 150, 300}), SDL_BLENDMODE_BLEND);
    _objList[OBJECT_NOTEBOOK]->setToScale(0.5);
    //_objList[OBJECT_CHOICE] = ObjectBuilder::CreateObject("Sprites//UI//optionBox.PNG", { 0, 0 }, SDL_BLENDMODE_BLEND);
    //_objList[OBJECT_GEORGE]
    //_objList[OBJECT_SASHA]
  /*  _objList[OBJECT_GEORGE] = ObjectBuilder::CreateObject("Sprites//Passengers//George.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_SASHA] = ObjectBuilder::CreateObject("Sprites//Passengers//Sasha.png", { 0, 0 }, SDL_BLENDMODE_BLEND);*/
    _objList[OBJECT_TICKET] = ObjectBuilder::CreateObject("Sprites//Items//ticket.png", { 384, 0 }, new BoxCollider({414, 120, 452, 272}), SDL_BLENDMODE_BLEND);
    _objList[OBJECT_RAILPASS] = ObjectBuilder::CreateObject("Sprites//Items//childPass.png", { 420, 36 }, new BoxCollider({ 456, 156, 452, 272 }), SDL_BLENDMODE_BLEND);
    _objList[OBJECT_TICKET_FROM] = ObjectBuilder::CreateTextObject({ "girl help", TextManager::GetInstance()->getFonts()[FONT_REDENSEK], Grey}, {600, 192}, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_TICKET_TO] = ObjectBuilder::CreateTextObject({ "owa owa", TextManager::GetInstance()->getFonts()[FONT_REDENSEK], Grey }, { 600, 228 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_TICKET_DOI] = ObjectBuilder::CreateTextObject({ "pain", TextManager::GetInstance()->getFonts()[FONT_REDENSEK], Grey }, { 600, 264 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_RAILPASS_NAME] = ObjectBuilder::CreateTextObject({ "girl help", TextManager::GetInstance()->getFonts()[FONT_REDENSEK], Pink }, { 636, 244 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_RAILPASS_EXPIRY] = ObjectBuilder::CreateTextObject({ "aaaaaaaa", TextManager::GetInstance()->getFonts()[FONT_REDENSEK], Pink }, { 636, 280 }, SDL_BLENDMODE_BLEND);

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

    for (int j = 0; j < NUM_NOTEBOOK; j++) {
        _nbSprites[j] = new Texture();
    }
    _nbSprites[NOTEBOOK_C]->loadImage("Sprites//Items//notebook//notebookClosed.png");
    _nbSprites[NOTEBOOK_O]->loadImage("Sprites//Items//notebook//notebookOpenBlank.png");
    _nbSprites[NOTEBOOK_P1]->loadImage("Sprites//Items//notebook//Page1Txt.png");
    _nbSprites[NOTEBOOK_P2]->loadImage("Sprites//Items//notebook//Page2.png");
    _nbSprites[NOTEBOOK_P3]->loadImage("Sprites//Items//notebook//Page3.png");
    for (int i = 0; i < NUM_NOTEBOOK; i++)
    {
        _nbSprites[i]->setBlendMode(SDL_BLENDMODE_BLEND);
    }
    _nbSprites[NOTEBOOK_C]->setScale(0.5);
    _nbSprites[NOTEBOOK_P1]->setScale(1);
    _nbSprites[NOTEBOOK_P2]->setScale(1);
    _nbSprites[NOTEBOOK_P3]->setScale(1);


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
    
    _objList[OBJECT_STAMPER] = ObjectBuilder::CreateObject("Sprites//Items//deathStamp.png", { 700, 0 }, new BoxCollider({700, 0, 50, 100}), SDL_BLENDMODE_BLEND);
    _objList[OBJECT_STAMPER]->setToScale(0.5);
    // Render queue
    _renderQueue.push_back(_objList[OBJECT_BACKGROUND1]);
    renderCabins();
    /*_renderQueue.push_back(_objList[OBJECT_NOTEBOOK]);*/
    //_renderQueue.push_back(_objList[OBJECT_TEXTBOX]);
    //_renderQueue.push_back(_objList[OBJECT_CHOICE]);
    
    //createBottomRowChairs();
    Player* testPlayer = new Player(mainRide->stops);
    setPlayer(testPlayer);
    date = mainPlayer->getDay();
    offSetX = 700;
    offSetY = 300;
    notebookOpen = false;
}

/// <summary>
/// Called on scene exit. Used to prevent memory leaks.
/// </summary>
void TrainScene::Exit()
{
    for (auto i : _renderQueue) {
        if (i != nullptr) {
            delete i;
        }
    }
}

/// <summary>
/// Called every frame. Use this for polling (checking for key input and processing)
/// </summary>
/// <param name="dt">Delta time(time inbetween frames)</param>
void TrainScene::Update(double dt)
{
    HandleInput();
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
    frame_count += 1;
    _objList[OBJECT_PLAYER]->setCoords({ offSetX, offSetY });
}

/// <summary>
/// Function to render everything out into the surface on the window.
/// </summary>
void TrainScene::Render()
{
    SDL_RenderClear(Application::GetInstance()->getRenderer()); // Clear the screen.
    // Object rendering inside here
    for (auto i : _renderQueue) {
        RenderAtCoords(i);
    }
    // UI Rendering
    if (isInteracting) {
        RenderAtCoords(_objList[OBJECT_TEXTBOX]);
        RenderAtCoords(_objList[OBJECT_TEXT]);
        RenderAtCoords(_objList[OBJECT_TICKET]);
        RenderAtCoords(_objList[OBJECT_TICKET_FROM]);
        RenderAtCoords(_objList[OBJECT_TICKET_TO]);
        RenderAtCoords(_objList[OBJECT_TICKET_DOI]);

        bool isRailpass = true; //attach to getRailpass
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
        }
        RenderAtCoords(_objList[OBJECT_STAMPER]);
    }
    RenderAtCoords(_objList[OBJECT_NOTEBOOK]);
    if (notebookOpen) {
        RenderAtCoords(_objList[OBJECT_NOTEBOOK_PAGE]);
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
            if (isInteracting)
            {
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

            case SDLK_UP:
                break;
            }
        }
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
        if (frame_count % 3 == 0 && inBoundsUp(offSetY) != false)
        {
            offSetY -= player_speed;
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
            offSetX -= player_speed;
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

        /*if (_cabins[_currentCabin + 1] != nullptr && offSetX < 180 )
        {
            _cabins[_currentCabin + 1];
        }*/

        last_dir = 2; 
    }

    if (Application::IsKeyPressed('S'))
    {
        if (frame_count % 3 == 0 && inBoundsDown(offSetY) != false) 
        {
            offSetY += player_speed;
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
            offSetX += player_speed;
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
            last_dir = 4;
    }
   
}

/// <summary>
/// Called after player input.
/// </summary>
void TrainScene::playerInteraction(int option)
{
    InteractablePerson* person = static_cast<InteractablePerson*>(_interactingPerson);
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
    if (_dT == currentNode->npcText && currentNode->results.size() == 0) {
        for (int i = 0; i < 2; i++)
        {
            _renderQueue.pop_back();
        }
        person->getCurrentNode() = nullptr;
        _interactingPerson = nullptr;
        isInteracting = false;
    }
    Ticket comparisonTicket =person->getTicket();
    RailPass comparisonRailpass = person->getRailPass();

    if (currentNode == nodes.front()) {
    	//write player text
        _renderQueue.push_back(_objList[OBJECT_TEXTBOX]);
    	WriteText({ currentNode->playerText, TextManager::GetInstance()->getFonts()[FONT_REDENSEK]}, {480, 500});
        _renderQueue.push_back(_objList[OBJECT_TEXT]);
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

/// <summary>
/// Get the list of train cabins(logic)
/// </summary>
/// <returns>Vector of TrainCabin pointers</returns>
std::vector<TrainCabin*> TrainScene::getCabins()
{
    return _cabins;
}



