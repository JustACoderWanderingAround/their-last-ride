#include "EndScene.h"
#include "MenuScene.h"
#include "Application.h"
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include "BoxCollider.h"
#include "Texture.h"

int iterator5 = 0;
int frame_count5 = 0;

EndScene::EndScene()
{

}

void EndScene::Init()
{
    sceneClicks = 0;
    _objList[OBJECT_END_BLACK_BACKGROUND] = ObjectBuilder::CreateObject("Sprites//blackScreen.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_END_BLACK_BACKGROUND]->setToAlpha(0);
    _objList[OBJECT_BACKGROUND5] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//transitionBG.png", { 0, 0 }, SDL_BLENDMODE_NONE);
    _objList[OBJECT_END_NORMAL_NOTE] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//neutralNormalNote.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_END_REAPER_NOTE] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//neutralReaperNote.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_END_CHEQUE] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//goodCheque.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_END_NORMAL_NOTE]->setToAlpha(0); //make it transparent
    _objList[OBJECT_END_REAPER_NOTE]->setToAlpha(0); //make it transparent
    _objList[OBJECT_END_CHEQUE]->setToAlpha(0);//make it transparent

    Texture rNote;
    Texture nNote;

    // Render queue
    _renderQueue.push_back(_objList[OBJECT_BACKGROUND5]);
    _renderQueue.push_back(_objList[OBJECT_END_REAPER_NOTE]);
    _renderQueue.push_back(_objList[OBJECT_END_NORMAL_NOTE]);
    _renderQueue.push_back(_objList[OBJECT_END_BLACK_BACKGROUND]);


    auto rides = Application::GetInstance()->getRides();

    int numWrong = 0;

    for (auto ride : rides)
    {
        numWrong += ride->getWrongVerdict();
    }

    if (numWrong < 5)
    {
        rNote.loadImage("Sprites\\LoadingScreen\\goodReaperNote.png");
        nNote.loadImage("Sprites\\LoadingScreen\\goodNormalNote.png");
        rNote.setBlendMode(SDL_BLENDMODE_BLEND);
        nNote.setBlendMode(SDL_BLENDMODE_BLEND);
        _objList[OBJECT_END_NORMAL_NOTE]->setTexture(rNote);
        _objList[OBJECT_END_REAPER_NOTE]->setTexture(nNote);
        _renderQueue.push_back(_objList[OBJECT_END_CHEQUE]);
    }

    if (numWrong > 12)
    {
        rNote.loadImage("Sprites\\LoadingScreen\\badReaperNote.png");
        nNote.loadImage("Sprites\\LoadingScreen\\badNormalNote.png");
        rNote.setBlendMode(SDL_BLENDMODE_BLEND);
        nNote.setBlendMode(SDL_BLENDMODE_BLEND);
        _objList[OBJECT_END_NORMAL_NOTE]->setTexture(rNote);
        _objList[OBJECT_END_REAPER_NOTE]->setTexture(nNote);
    }

}

void EndScene::Exit()
{
    for (auto i : _renderQueue) {
        if (i != nullptr) {
            delete i;
        }
    }
}

void EndScene::Update(double dt)
{
    HandleInput();
    frame_count5++;
    if (_fadeQueue.size() > 0) {
        if (frame_count5 % 3 == 0) {
            iterator5++;
            frame_count5 = 0;
        }
        if (iterator5 != 255) {
            _fadeQueue.front()->setToAlpha(iterator5);
        }
        else {
            _fadeQueue.erase(_fadeQueue.begin());
            iterator5 = 0;
        }
    }
}

void EndScene::Render()
{
    SDL_RenderClear(Application::GetInstance()->getRenderer()); // Clear the screen.
    //rendering inside here
    for (auto i : _renderQueue) {
        i->getTexture().Render(i->getCoords().x, i->getCoords().y);
    }
    SDL_RenderPresent(Application::GetInstance()->getRenderer()); // Render everything on the screen. 
}

void EndScene::HandleInput()
{
    auto events = Application::GetInstance()->GetFrameEvents();
    for (auto event : events) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                if (sceneClicks == 2) {
                    _fadeQueue.push_back(_objList[OBJECT_END_BLACK_BACKGROUND]);
                    return;
                }
                _fadeQueue.push_back(_objList[sceneClicks + 1]);
                sceneClicks++;
            }
        }
    }
}

