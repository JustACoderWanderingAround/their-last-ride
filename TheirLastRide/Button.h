#pragma once
#include "Object.h"
#include "Texture.h"
#include <array>
enum BUTTON_ANIM {
    BUTTON_STATIC,
    BUTTON_MOUSE_ON,
    NUM_BUTTON_ANIM
};
class Button :
    public Object
{
private:
    unsigned int ID;
    std::array<Texture*, NUM_BUTTON_ANIM> _buttonAnimList;
public:
    Button(unsigned int id);
    int handleEvent(SDL_Event* e);
};

