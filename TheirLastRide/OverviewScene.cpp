#include "OverviewScene.h"
#include "ObjectBuilder.h"
#include "TextManager.h"
#include "TrainScene.h"
int iterator3 = 0;
int iterator4 = 255;
int frame_count3 = 0;
bool isFading_overview = false;
bool changeToScene = false;
OverviewScene::OverviewScene()
    : rideNumber(1)
{

}

void OverviewScene::Init()
{
    iterator3 = 0;
    iterator4 = 255;
    sceneClicks = 0;
    isFading_overview = false;
    changeToScene = false;
    _objList[OBJECT_OVERVIEW_BLACK_SCREEN] = ObjectBuilder::CreateObject("Sprites//blackScreen.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
	_objList[OBJECT_OVERVIEW_BACKGROUND] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//transitionBG.png", { 0, 0 }, SDL_BLENDMODE_NONE);
	_objList[OBJECT_OVERVIEW_BLANK_NORMAL_NOTE] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//transitionNormalNoteBlank.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_OVERVIEW_NORMAL_NOTE] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//transitionNormalSummary.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
	_objList[OBJECT_OVERVIEW_BLANK_REAPER_NOTE] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//transitionReaperNoteBlank.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_OVERVIEW_REAPER_NOTE] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//transitionReaperSummary.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_RIDE_NUMBER] = ObjectBuilder::CreateTextObject({ std::to_string(rideNumber), TextManager::GetInstance()->getFonts()[FONT_REDENSEK], ReaperGrey }, { 700, 217 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_RIDE_NUMBER]->setToScale(1.35);

    for (int i = 1; i < NUM_OBJECT_OVERVIEW; i++)
    {
        _objList[i]->setToAlpha(0);
    }
    _renderQueue.insert(std::end(_renderQueue), std::begin(_objList), std::end(_objList));
    _objList[OBJECT_OVERVIEW_BLACK_SCREEN]->setToAlpha(255);
    _unfadeQueue.push_back(_objList[OBJECT_OVERVIEW_BLACK_SCREEN]);
    
}

void OverviewScene::Update(double dt)
{
    HandleInput();
    frame_count3++;
    if (_fadeQueue.size() > 0) {
        std::cout << changeToScene;
        isFading_overview = true;
        if (frame_count3 % 3 == 0) {
            iterator3++;
            frame_count3 = 0;
        }
        if (iterator3 != 255) {
            _fadeQueue.front()->setToAlpha(iterator3);
        }
        else {
            _fadeQueue.erase(_fadeQueue.begin());
            if (changeToScene) {
                Application::GetInstance()->changeScene(Application::GetInstance()->getScenes()[SCENE_TRAIN]);
            }
            iterator3 = 0;
        }
    }
    if (_unfadeQueue.size() > 0) {
        isFading_overview = true;
        if (frame_count3 % 3 == 0) {
            iterator4--;
            frame_count3 = 0;
        }
        if (iterator4 != 0) {
            _unfadeQueue.front()->setToAlpha(iterator4);
        }
        else {
            _unfadeQueue.erase(_unfadeQueue.begin());
            iterator4 = 255;
        }
    }
}

void OverviewScene::UpdateText(Ride* r)
{
    rideNumber++;
}

void OverviewScene::Render()
{
    SDL_RenderClear(Application::GetInstance()->getRenderer()); // Clear the screen.
    for (int i = 0; i < _renderQueue.size(); i++)
    {
        _renderQueue[i]->getTexture().Render(_renderQueue[i]->getCoords().x, _renderQueue[i]->getCoords().y);
    }
    SDL_RenderPresent(Application::GetInstance()->getRenderer()); // Render everything on the screen. 
}

void OverviewScene::Exit()
{
    for (auto i : _objList) {
        if (i != nullptr) {
            delete i;
            i = nullptr;
        }
    }
    _renderQueue.clear();
    _fadeQueue.clear();
    _unfadeQueue.clear();
}

void OverviewScene::HandleInput()
{
    auto events = Application::GetInstance()->GetFrameEvents();
    for (auto event : events) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                if (!changeToScene) {
                    if (sceneClicks >= _objList.size() - 2) {
                        if (Application::GetInstance()->getCurrentRide() + 1 <= Application::GetInstance()->getRides().size())
                            Application::GetInstance()->setCurrentRide(Application::GetInstance()->getCurrentRide() + 1);
                        Application::GetInstance()->updateCurrentRide();
                        Application::GetInstance()->getScenes()[SCENE_TRAIN]->Init();
                        _fadeQueue.push_back(_objList[OBJECT_OVERVIEW_BLACK_SCREEN]);
                        changeToScene = true;
                        /*Application::GetInstance()->changeScene(Application::GetInstance()->getScenes()[SCENE_TRAIN]);*/
                        return;
                    }
                    /*if (sceneClicks != 0)*/
                    _fadeQueue.push_back(_objList[sceneClicks + 1]);
                    /*else
                        _unfadeQueue.push_back(_objList[OBJECT_OVERVIEW_BLACK_SCREEN]);*/
                    sceneClicks++;
                }
            }
        }
    }
}
