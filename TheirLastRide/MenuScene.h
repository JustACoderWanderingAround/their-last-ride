#pragma once
#include "Button.h"
#include "Texture.h"
#include "Object.h"
#include "Scene.h"
#include <vector>
#include <string>
#include <array>
#include "TextManager.h"
#include "ObjectBuilder.h"
#include "BoxCollider.h"
#include "Text.h"

enum OBJECT1
{
	OBJECT_BACKGROUND,
	NUM_OBJECT1
};

enum TM_ANIM1 {

	BG_ANIM_MOVE1,
	BG_ANIM_MOVE2,
	BG_ANIM_MOVE3,
	NUM_BG_ANIM1
};


class Scene;
class MenuScene:public Scene
{
private:
	unsigned int _currentCabin;
	BoxCollider* _mouseCollider;
	std::array<Object*, NUM_OBJECT1> _objList;
	std::array<Texture*, NUM_BG_ANIM1> _tmAnimList;
	std::vector<Button*> _buttons;
	std::vector<Object*> _renderQueue;
	SDL_Event _event;
	Person* _interactingPerson;
	int offSetX;
	int offSetY;
public:
	bool writingText;
	MenuScene();
	void Init();
	void Exit();
	void Update(double dt);
	void Render();
	void HandleInput();
};