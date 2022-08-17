#include "TrainScene.h"
#include <SDL_image.h>
#include <iostream>
SDL_Texture* chair;
SDL_Rect dest;
const SDL_Color DARK_LIME = { 153, 203, 14 };
TrainScene::TrainScene(SDL_Window* w, SDL_Surface* s, SDL_Renderer* r)
	: Scene(w, s, r)
{
}
void TrainScene::Init()
{
	_cabins.push_back(TrainCabin());

    Texture background;
    if (!createImage("Sprites//trainCarBG.png", background)) {
        std::cout << "Image not imported.\n";
    }     
    background.setBlendMode(SDL_BLENDMODE_NONE);
    _objs.push_back(Object(background, {0, 0}));

    Texture player;
    if (!createImage("Sprites//tmStand.png", player)) {
        std::cout << "Image not imported.\n";
    }
    player.setBlendMode(SDL_BLENDMODE_BLEND);
    player.setScale(1.1);
    _objs.push_back(Object(player, { 700, 300 }));

    Texture chair;
    if (!createImage("Sprites//chair.png", chair)) {
        std::cout << "Image not imported.\n";
    }
    chair.setScale(.35);
    chair.setBlendMode(SDL_BLENDMODE_BLEND);

    const int y_level = 480;
    const int x_offset = 190;
    Object chair_object = Object(chair, { 35, y_level });
    for (int i = 0; i < 3; i++)
    {
        _objs.push_back(chair_object);
        chair_object.setCoords({ chair_object.getCoords().x + x_offset, y_level});
    }
    chair_object.setCoords({ chair_object.getCoords().x + 105, y_level });
    for (int i = 0; i < 3; i++)
    {
        _objs.push_back(chair_object);
        chair_object.setCoords({ chair_object.getCoords().x + x_offset, y_level });
    }

    dest.x = 1280 / 2;
    dest.y = 720 / 2;
    dest.w = 100;
    dest.h = 100;
   
}

void TrainScene::Exit()
{
    SDL_DestroyTexture(chair);
}

void TrainScene::Update(double dt)
{
}

void TrainScene::Render()
{
   /* SDL_Rect clip = { 300, 300, 100, 100 };*/
    SDL_RenderClear(m_Renderer);
    for (auto i : _objs) {
        i.getTexture().Render(i.getCoords().x, i.getCoords().y);
    }
    SDL_RenderPresent(m_Renderer);
}

bool TrainScene::createImage(std::string path, Texture& _txt)
{
    if (!_txt.loadImage(path)) {
        std::cout << "Failed to load image.\n";
        return false;
    }
    else {
        //if (!_txt.lockTexture()) {
        //    std::cout << "Unable to lock texture\n";
        //    _txt.free();
        //    return false;
        //}
        //else {
        //    /*auto fmt = SDL_GetWindowPixelFormat(Application::GetInstance()->getWindow());
        //    SDL_PixelFormat* mpfmt = SDL_AllocFormat(fmt);
        //    Uint32* pixels = static_cast<Uint32*>(_txt.getPixels());
        //    int pixelCount = (_txt.getPitch() / 4) * _txt.getHeight();
        //    Uint32 colorKey = SDL_MapRGB(mpfmt, 0, 0, 0);
        //    Uint32 transparent = SDL_MapRGBA(mpfmt, 255, 255, 255, 0);
        //    for (int i = 0; i < pixelCount; i++)
        //    {
        //        if (pixels[i] == colorKey)
        //            pixels[i] = transparent;
        //    }
        //    _txt.unlockTexture();
        //    SDL_FreeFormat(mpfmt);*/
        //}
    }
    return true;
}