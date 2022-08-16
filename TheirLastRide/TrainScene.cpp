#include "TrainScene.h"
const SDL_Color DARK_LIME = { 153, 203, 14 };
TrainScene::TrainScene(SDL_Window* w, SDL_Surface* s)
	: Scene(w, s)
{

}
void TrainScene::Init()
{
}

void TrainScene::Exit()
{
}

void TrainScene::Update(double dt)
{

}

void TrainScene::Render()
{
	SDL_FillRect(m_Surface, NULL, SDL_MapRGB(m_Surface->format, DARK_LIME.r, DARK_LIME.g, DARK_LIME.b));
}
