#include "IntroScene.h"
#include "MenuScene.h"
#include "Application.h"
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include "BoxCollider.h"
#include "Texture.h"

int iterator2 = 0;
int frame_count2 = 0;
bool isFading = false;

IntroScene::IntroScene()
{

}

void IntroScene::Init()
{
    sceneClicks = 0;
    _objList[OBJECT_BACKGROUND2] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//transitionBG.png", { 0, 0 }, SDL_BLENDMODE_NONE);
    _objList[OBJECT_NORMAL_NOTE] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//transitionNormalNote.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_REAPER_NOTE] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//transitionReaperNote.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_NORMAL_NOTE]->setToAlpha(0); //make it transparent
    _objList[OBJECT_REAPER_NOTE]->setToAlpha(0); //make it transparent
    /*_fadeQueue.push_back(_objList[OBJECT_NORMAL_NOTE]);
    _fadeQueue.push_back(_objList[OBJECT_REAPER_NOTE]);*/

    // Render queue
    _renderQueue.push_back(_objList[OBJECT_BACKGROUND2]);
    _renderQueue.push_back(_objList[OBJECT_REAPER_NOTE]);
    _renderQueue.push_back(_objList[OBJECT_NORMAL_NOTE]);
}

void IntroScene::Exit()
{
    for (auto i : _renderQueue) {
        if (i != nullptr) {
            delete i;
        }
    }
}

void IntroScene::Update(double dt)
{
    HandleInput();
    frame_count2++;
    if (_fadeQueue.size() > 0) {
        isFading = true;
        if (frame_count2 % 3 == 0) {
            iterator2++;
            frame_count2 = 0;
        }
        if (iterator2 != 255) {
            _fadeQueue.front()->setToAlpha(iterator2);
        }
        else {
            _fadeQueue.erase(_fadeQueue.begin());
            iterator2 = 0;
        }
    }
}

void IntroScene::Render()
{
    SDL_RenderClear(Application::GetInstance()->getRenderer()); // Clear the screen.
    //rendering inside here
    for (auto i : _renderQueue) {
        i->getTexture().Render(i->getCoords().x, i->getCoords().y);
    }
    SDL_RenderPresent(Application::GetInstance()->getRenderer()); // Render everything on the screen. 
}

void IntroScene::HandleInput()
{
    auto events = Application::GetInstance()->GetFrameEvents();
    for (auto event : events) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                if (sceneClicks == 2) {
                    sceneClicks++;
                    return;
                }
                _fadeQueue.push_back(_objList[sceneClicks + 1]);
                sceneClicks++;
            }
        }
    }
}
