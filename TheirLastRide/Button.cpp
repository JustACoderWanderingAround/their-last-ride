#include "Button.h"
#include "Application.h"
/// <summary>
/// Initialise textures.
/// </summary>
Button::Button()
{
	for (int i = 0; i < _buttonAnimList.size(); i++)
	{
		_buttonAnimList[i] = new Texture();
	}
	_buttonAnimList[BUTTON_STATIC]->loadImage("Sprites//UI/optionBox.png");
	_buttonAnimList[BUTTON_STATIC]->setScale(0.5);
	_buttonAnimList[BUTTON_STATIC]->setBlendMode(SDL_BLENDMODE_BLEND);
	_buttonAnimList[BUTTON_MOUSE_ON]->loadImage("Sprites//UI/optionBox.png");
	_buttonAnimList[BUTTON_MOUSE_ON]->setBlendMode(SDL_BLENDMODE_BLEND);
	_buttonAnimList[BUTTON_MOUSE_ON]->setColor(5, 5, 5);
	_buttonAnimList[BUTTON_STATIC]->setScale(0.5);
	_buttonAnimList[BUTTON_MOUSE_ON]->setScale(1.05);

	_txt = *_buttonAnimList[BUTTON_STATIC];
}

/// <summary>
/// Handle events like key press or mouse button in this function. 
/// </summary>
/// <param name="e">Pointer to SDL_Event</param>
void Button::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		SDL_Point mouseCoords = Application::GetInstance()->getMouseCoords();
		BoxCollider* m_collider =  new BoxCollider({ mouseCoords.x, mouseCoords.y, 4, 4 });
		if (_collider->isColliding(m_collider)) {
			_txt = *_buttonAnimList[BUTTON_MOUSE_ON];
		}
		else {
			_txt = *_buttonAnimList[BUTTON_STATIC];
		}
		delete m_collider;
	}
}
