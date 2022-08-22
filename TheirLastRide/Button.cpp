#include "Button.h"
#include "Application.h"
/// <summary>
/// Initialise textures.
/// </summary>
Button::Button(unsigned int id)
	: ID(id)
{
	for (int i = 0; i < _buttonAnimList.size(); i++)
	{
		_buttonAnimList[i] = new Texture();
	}
	_buttonAnimList[BUTTON_STATIC]->loadImage("Sprites//UI/optionBox.png");
	_buttonAnimList[BUTTON_STATIC]->setScale(0.75);
	_buttonAnimList[BUTTON_STATIC]->setBlendMode(SDL_BLENDMODE_BLEND);
	_buttonAnimList[BUTTON_MOUSE_ON]->loadImage("Sprites//UI/optionBox.png");
	_buttonAnimList[BUTTON_MOUSE_ON]->setBlendMode(SDL_BLENDMODE_BLEND);
	_buttonAnimList[BUTTON_MOUSE_ON]->setColor(230, 230, 230);
	_buttonAnimList[BUTTON_MOUSE_ON]->setScale(0.75);

	_txt = *_buttonAnimList[BUTTON_STATIC];
}

/// <summary>
/// Handle events like key press or mouse button in this function. 
/// </summary>
/// <param name="e">Pointer to SDL_Event</param>
int Button::handleEvent(SDL_Event* e)
{
	bool insideButton = false;
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		SDL_Point mouseCoords = Application::GetInstance()->getMouseCoords();
		BoxCollider* m_collider =  new BoxCollider({ mouseCoords.x, mouseCoords.y, 4, 4 });
		if (_collider != nullptr && _collider->isColliding(m_collider)) {
			insideButton = true;
		}
		else {
			insideButton = false;
		}
		if (!insideButton) {
			_txt = *_buttonAnimList[BUTTON_STATIC];
			return 0;
		}
		else {
			switch (e->type) {
			case SDL_MOUSEMOTION:
				_txt = *_buttonAnimList[BUTTON_MOUSE_ON];
				break;
			case SDL_MOUSEBUTTONDOWN:
				return ID;
			}


		}
		return 0;
		delete m_collider;
	}
}
