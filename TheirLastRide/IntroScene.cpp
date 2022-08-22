#include "IntroScene.h"
#include "MenuScene.h"
#include "Application.h"
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include "BoxCollider.h"
#include "Texture.h"

const int x_level = 35;
const int y_level = 480;
int iterator1 = 0;
int frame_count2 = 0;

IntroScene::IntroScene()
{

}

void IntroScene::Init()
{
    _objList[OBJECT_BACKGROUND2] = ObjectBuilder::CreateObject("Sprites//trainCarBG.png", { 0, 0 }, SDL_BLENDMODE_NONE);

    // Render queue
    _renderQueue.push_back(_objList[OBJECT_BACKGROUND2]);
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
    if (Application::IsKeyPressed(VK_SPACE))
    {
        Application* app = Application::GetInstance();
        app->Init();
        app->Run();
        app->Exit();
    }
}
