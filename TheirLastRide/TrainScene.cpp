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
    showImage("Sprites//chair.png");
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
    _txt.Render(500, 25);
    SDL_RenderPresent(m_Renderer);
}

bool TrainScene::showImage(std::string path)
{
    if (!_txt.loadImage(path)) {
        std::cout << "Failed to load image.\n";
        return false;
    }
    else {
        if (!_txt.lockTexture()) {
            std::cout << "Unable to lock texture\n";
            _txt.free();
            return false;
        }
        else {
            auto fmt = SDL_GetWindowPixelFormat(Application::GetInstance()->getWindow());
            SDL_PixelFormat* mpfmt = SDL_AllocFormat(fmt);
            Uint32* pixels = static_cast<Uint32*>(_txt.getPixels());
            int pixelCount = (_txt.getPitch() / 4) * _txt.getHeight();
            Uint32 colorKey = SDL_MapRGB(mpfmt, 255, 255, 0);
            Uint32 transparent = SDL_MapRGBA(mpfmt, 255, 255, 255, 0);
            for (int i = 0; i < pixelCount; i++)
            {
                if (pixels[i] == colorKey)
                    pixels[i] = transparent;
            }
            _txt.unlockTexture();
            SDL_FreeFormat(mpfmt);
        }
    }
    return true;
}