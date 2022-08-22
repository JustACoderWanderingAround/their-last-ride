#pragma once
#include "Button.h"
#include "Texture.h"
#include "Object.h"
#include "Scene.h"
#include "TrainCabin.h"
#include <vector>
#include <string>
#include <array>
#include "TextManager.h"
#include "ObjectBuilder.h"
#include "BoxCollider.h"
#include "Text.h"

enum OBJECT {
	OBJECT_BACKGROUND1,
	OBJECT_PLAYER,
	OBJECT_CHAIR_ROW,
	OBJECT_TEXT,
	OBJECT_GEORGE,
	OBJECT_SASHA,
	OBJECT_TICKET,
	OBJECT_RAILPASS,
	OBJECT_STAMP_MARK,
	OBJECT_STAMP,
	OBJECT_PUNCH,
	OBJECT_NOTEBOOK_CLOSED,
	OBJECT_NOTEBOOK_OPEN,
	OBJECT_NOTEBOOK_PAGE,
	OBJECT_TEXTBOX,
	OBJECT_CHOICE,
	NUM_OBJECT
};

enum TM_ANIM {

	TM_ANIM_STAND_L,
	TM_ANIM_STAND_R,
	TM_ANIM_WALK_L_1,
	TM_ANIM_WALK_L_2,
	TM_ANIM_WALK_R_1,
	TM_ANIM_WALK_R_2,
	TM_ANIM_FRONT,
	TM_ANIM_BACK,
	TM_ANIM_FRONT_WALK_1,
	TM_ANIM_FRONT_WALK_2,
	TM_ANIM_BACK_WALK_1,
	TM_ANIM_BACK_WALK_2,
	NUM_TM_ANIM
};

class Person;
class Scene;
class TrainScene : public Scene
{
private:
	int level;
	unsigned int _currentCabin;
	BoxCollider* _mouseCollider;
	std::array<Object*, NUM_OBJECT> _objList;
	std::array<Texture*, NUM_TM_ANIM> _tmAnimList;
	std::vector<Button*> _buttons;
	std::vector<Object*> _renderQueue; //maybe change to deque/priority queue?
	std::vector<TrainCabin*> _cabins;
	std::vector<Text> _textQueue;
	std::string _displayText;
	SDL_Point _mouse_coords;
	SDL_Event _event;
	Person* _interactingPerson;
	int offSetX;
	int offSetY;
public:
	bool writingText;
	TrainScene();
	Person* getPersonClick();
	void renderCabins();
	void Init();
	void Exit();
	void Update(double dt);
	void Render();
	void HandleInput();
	void playerInteraction(int option = NULL);
	void WriteText(const Text& text, const SDL_Point& pos);
	std::vector<TrainCabin*> getCabins();
	bool renderTextBox;
	int date;
};

