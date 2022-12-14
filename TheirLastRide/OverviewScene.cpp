#include "OverviewScene.h"
#include "ObjectBuilder.h"
#include "TextManager.h"
int iterator3 = 0;
int iterator4 = 255;
int frame_count3 = 0;
bool isFading_overview = false;
bool changeToScene = false;
bool changeToEnd = false;

void OverviewScene::setExpected(int expA, int expD)
{
    expectedAlive = expA;
    expectedDead = expD;
}
void OverviewScene::setActual(int actA, int actD)
{
    actualAlive = actA;
    actualDead = actD;
}
OverviewScene::OverviewScene()
    : rideNumber(-1)
{

}

void OverviewScene::Init()
{
    rideNumber++;
    iterator3 = 0;
    iterator4 = 255;
    sceneClicks = 0;
    isFading_overview = false;
    changeToScene = false;
    changeToEnd = false;
    _objList[OBJECT_OVERVIEW_BLACK_SCREEN] = ObjectBuilder::CreateObject("Sprites//blackScreen.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_OVERVIEW_NEWS] = ObjectBuilder::CreateObject("Sprites//blackScreen.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
	_objList[OBJECT_OVERVIEW_BACKGROUND] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//transitionBG.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
	_objList[OBJECT_OVERVIEW_BLANK_NORMAL_NOTE] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//transitionNormalNoteBlank.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_OVERVIEW_NORMAL_NOTE] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//transitionNormalSummary.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
	_objList[OBJECT_OVERVIEW_BLANK_REAPER_NOTE] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//transitionReaperNoteBlank.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_OVERVIEW_REAPER_NOTE] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//transitionReaperSummary.png", { 0, 0 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_RIDE_NUMBER] = ObjectBuilder::CreateTextObject({ std::to_string(rideNumber), TextManager::GetInstance()->getFonts()[FONT_REDENSEK], ReaperGrey }, { 700, 217 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_RIDE_NUMBER]->setToScale(1.35);
    _objList[OBJECT_REPORTED_ALIVE] = ObjectBuilder::CreateTextObject({ std::to_string(actualAlive), TextManager::GetInstance()->getFonts()[FONT_REDENSEK],ReaperGrey }, { 765, 408 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_REPORTED_DEAD] = ObjectBuilder::CreateTextObject({ std::to_string(actualDead), TextManager::GetInstance()->getFonts()[FONT_REDENSEK],ReaperGrey }, { 755, 369 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_EXPECTED_ALIVE] = ObjectBuilder::CreateTextObject({ std::to_string(expectedAlive), TextManager::GetInstance()->getFonts()[FONT_REDENSEK],ReaperGrey}, { 720, 527 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_EXPECTED_DEAD] = ObjectBuilder::CreateTextObject({ std::to_string(expectedDead), TextManager::GetInstance()->getFonts()[FONT_REDENSEK],ReaperGrey }, { 700, 488 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_DISPARITY_ALIVE] = ObjectBuilder::CreateTextObject({ std::to_string(abs(expectedAlive - actualAlive)), TextManager::GetInstance()->getFonts()[FONT_REDENSEK],ReaperGrey }, { 652, 605 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_DISPARITY_DEAD] = ObjectBuilder::CreateTextObject({ std::to_string(abs(expectedDead -  actualDead)), TextManager::GetInstance()->getFonts()[FONT_REDENSEK],ReaperGrey }, { 652, 645}, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_EXPECTED_PASS] = ObjectBuilder::CreateTextObject({ std::to_string(expectedAlive + expectedDead) , TextManager::GetInstance()->getFonts()[FONT_REDENSEK],Grey }, { 980, 350 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_REPORTED_PASS] = ObjectBuilder::CreateTextObject({ std::to_string(actualDead + actualAlive), TextManager::GetInstance()->getFonts()[FONT_REDENSEK],Grey }, { 980,  390 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_DISPARITY] = ObjectBuilder::CreateTextObject({std::to_string(abs((expectedAlive + expectedDead) - (actualDead + actualAlive))), TextManager::GetInstance()->getFonts()[FONT_REDENSEK],Grey }, {795,  415}, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_LOST_REV] = ObjectBuilder::CreateTextObject({ std::to_string(abs((expectedAlive + expectedDead) - (actualDead + actualAlive)) * 35), TextManager::GetInstance()->getFonts()[FONT_REDENSEK],Grey }, { 850, 500 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_RIDE_NUMBER_2] = ObjectBuilder::CreateTextObject({ std::to_string(rideNumber), TextManager::GetInstance()->getFonts()[FONT_REDENSEK], Grey }, { 923, 193 }, SDL_BLENDMODE_BLEND);
    _objList[OBJECT_RIDE_NUMBER_2]->setToScale(1.35);
    _objList[OBJECT_OVERVIEW_BACKGROUND2] = ObjectBuilder::CreateObject("Sprites//LoadingScreen//transitionBG.png", { 0, 0 }, SDL_BLENDMODE_BLEND);

    for (int i = 1; i < NUM_OBJECT_OVERVIEW; i++)
    {
        _objList[i]->setToAlpha(0);
    }
    _renderQueue.insert(std::end(_renderQueue), std::begin(_objList), std::end(_objList));
    _objList[OBJECT_OVERVIEW_BLACK_SCREEN]->setToAlpha(255);
    _unfadeQueue.push_back(_objList[OBJECT_OVERVIEW_BLACK_SCREEN]);
    
    std::cout << rideNumber;
    if (rideNumber == 2 || rideNumber == 3) {
        Texture news;
        news.loadImage("Sprites\\LoadingScreen\\transitionNews" + std::to_string(rideNumber - 1) + ".png");
        news.setBlendMode(SDL_BLENDMODE_BLEND);
        news.setAlpha(0);
        _objList[OBJECT_OVERVIEW_NEWS]->setTexture(news);
    }
    else {
        Texture news;
        news.createBlank(1, 1);
        _objList[OBJECT_OVERVIEW_NEWS]->setTexture(news);
    }
}

void OverviewScene::Update(double dt)
{
    HandleInput();
    frame_count3++;
    if (_fadeQueue.size() > 0) {
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
            if (changeToEnd) {
                Application::GetInstance()->changeScene(Application::GetInstance()->getScenes()[SCENE_END]);
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
                    if (sceneClicks >= _objList.size() - (3 + (rideNumber == 1))) {
                        if (Application::GetInstance()->getCurrentRide() + 1 < Application::GetInstance()->getRides().size())
                            Application::GetInstance()->setCurrentRide(Application::GetInstance()->getCurrentRide() + 1);

                        else {                           
                            _fadeQueue.push_back(_objList[OBJECT_OVERVIEW_BACKGROUND2]);
                            changeToEnd = true;
                            return;
                        }
                        Application::GetInstance()->updateCurrentRide();
                        Application::GetInstance()->getScenes()[SCENE_TRAIN]->Init();
                        _fadeQueue.push_back(_objList[OBJECT_OVERVIEW_BLACK_SCREEN]);
                        changeToScene = true;
                        /*Application::GetInstance()->changeScene(Application::GetInstance()->getScenes()[SCENE_TRAIN]);*/
                        return;
                    }
                    /*if (sceneClicks != 0)*/
                    if (rideNumber == 1)
                        _fadeQueue.push_back(_objList[sceneClicks + 2]);
                    else
                        _fadeQueue.push_back(_objList[sceneClicks + 1]);
                    /*else
                        _unfadeQueue.push_back(_objList[OBJECT_OVERVIEW_BLACK_SCREEN]);*/
                    sceneClicks++;
                }
            }
        }
    }
}
