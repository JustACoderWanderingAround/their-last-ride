#include "MenuScene.h"
#include "Application.h"
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include "BoxCollider.h"
#include "Texture.h"

const int x_level = 35;
const int y_level = 480;
int iterator = 0;
int frame_count1 = 0;
int iteratorAlpha = 0;
bool goIntro = false;

/// <summary>
/// Constructor, used to initialize values.
/// </summary>
MenuScene::MenuScene()
{

}

void MenuScene::Init()
{
    goIntro = false;
    _objList[OBJECT_MAIN_BLACK_BACKGROUND] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//transitionBG.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_MAIN_BLACK_BACKGROUND]->setToAlpha(0);
    _objList[OBJECT_BACKGROUND] = ObjectBuilder::CreateObject("Sprites//trainCarBG.png", { 0, 0 }, SDL_BLENDMODE_NONE);
    _objList[OBJECT_TITLE_CARD] = ObjectBuilder::CreateObject("Sprites//TitleScreen//titleCard.png", { 50, 50 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_TITLE_CARD]->setToScale(0.5);

    for (int i = 0; i < NUM_BG_ANIM1; i++)
    {
        _tmAnimList[i] = new Texture();
    }
    _tmAnimList[BG_ANIM_MOVE1]->loadImage("Sprites//TitleScreen//titleScreen1.png");
    _tmAnimList[BG_ANIM_MOVE2]->loadImage("Sprites//TitleScreen//titleScreen2.png");
    _tmAnimList[BG_ANIM_MOVE3]->loadImage("Sprites//TitleScreen//titleScreen3.png");
    for (int i = 0; i < NUM_BG_ANIM1; i++)
    {
        _tmAnimList[i]->setBlendMode(SDL_BLENDMODE_BLEND);
        _tmAnimList[i]->setScale(1.3);
    }

    // Render queue
    _renderQueue.push_back(_objList[OBJECT_BACKGROUND]);
    _renderQueue.push_back(_objList[OBJECT_TITLE_CARD]);
    _renderQueue.push_back(_objList[OBJECT_MAIN_BLACK_BACKGROUND]);
}

void MenuScene::Exit()
{
    for (auto i : _renderQueue) {
        if (i != nullptr) {
            delete i;
        }
    }
}

void MenuScene::HandleInput()
{
    auto events = Application::GetInstance()->GetFrameEvents();
    for (auto event : events) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                goIntro = true;
                _fadeQueue.push_back(_objList[OBJECT_MAIN_BLACK_BACKGROUND]);              
            }
        }
    }
}

void MenuScene::Update(double dt)
{
    HandleInput();

    _objList[OBJECT_BACKGROUND]->setTexture(*_tmAnimList[iterator]);
    _objList[OBJECT_BACKGROUND]->setToScale( .77, .77 );
   
    frame_count1++;
   
    if (frame_count1 >= 200)
    {
        iterator++;
        frame_count1 = 0;

        if (iterator > 2)
        {
            iterator = 0;
        }
    }
    if (_fadeQueue.size() > 0) {
        if (frame_count1 % 3 == 0) {
            iteratorAlpha++;
            frame_count1 = 0;
        }
        if (iteratorAlpha != 255) {
            _fadeQueue.front()->setToAlpha(iteratorAlpha);
        }
        else {
            _fadeQueue.erase(_fadeQueue.begin());
            if (goIntro) {
                Application::GetInstance()->changeScene(Application::GetInstance()->getScenes()[SCENE_INTRO]);
            }
            iteratorAlpha = 0;
        }
    }
}

/// <summary>
/// Function to render everything out into the surface on the window.
/// </summary>
void MenuScene::Render()
{
    SDL_RenderClear(Application::GetInstance()->getRenderer()); // Clear the screen.
    //rendering inside here
    for (auto i : _renderQueue) {
        i->getTexture().Render(i->getCoords().x, i->getCoords().y);
    }
    SDL_RenderPresent(Application::GetInstance()->getRenderer()); // Render everything on the screen. 
}