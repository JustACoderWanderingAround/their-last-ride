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
	//OBJECT_GEORGE,
	//OBJECT_SASHA,
	OBJECT_TICKET,
	OBJECT_RAILPASS,
	OBJECT_STAMP_MARK,
	OBJECT_STAMP,
	OBJECT_PUNCH,
	OBJECT_NOTEBOOK,
	OBJECT_NOTEBOOK_PAGE,
	OBJECT_TEXTBOX,
	OBJECT_CHOICE,
	OBJECT_TICKET_FROM,
	OBJECT_TICKET_TO,
	OBJECT_TICKET_DOI,
	OBJECT_RAILPASS_NAME,
	OBJECT_RAILPASS_EXPIRY,
	OBJECT_STAMPER,
	OBJECT_RETURN,
	OBJECT_PUNCHER,
	OBJECT_HEAD,
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

enum PASS_TXTR {
	
	CHILD_PASS,
	ADULT_PASS,
	TICKET,
	TICKET_PUNCH,
	NUM_PASS_TXTR
};

enum NOTEBOOK {
	NOTEBOOK_O,
	NOTEBOOK_C,
	NOTEBOOK_P1,
	NOTEBOOK_P2,
	NOTEBOOK_P3,
	NOTEBOOK_P4,
	NUM_NOTEBOOK
};

class Person;
class Scene;
class TrainScene : public Scene
{
private:
	int level;
	int _currentCabin;
	BoxCollider* _mouseCollider;
	std::array<Object*, NUM_OBJECT> _objList;
	std::array<Texture*, NUM_TM_ANIM> _tmAnimList;
	std::array<Texture*, NUM_NOTEBOOK> _nbSprites;
	std::array<Texture*, NUM_PASS_TXTR> _passTextureList;
	std::vector<Button*> _buttons;
	std::vector<Object*> _renderQueue; //maybe change to deque/priority queue?
	std::vector<TrainCabin*> _cabins;
	std::vector<Text> _textQueue;
	std::string _displayText;
	SDL_Point _mouse_coords;
	SDL_Event _event;
	Person* _interactingPerson;
	int playerX;
	int playerY;
	Player* _mainPlayer;
	Ride* _mainRide;
public:
	bool writingText;
	TrainScene();
	Person* getPersonClick();
	void renderCabins();
	void RenderAtCoords(Object* obj);
	void Init();
	void Exit();
	void Update(double dt);
	void Render();
	void HandleInput();
	void playerInteraction(int option = NULL);
	void WriteText(const Text& text, const SDL_Point& pos);
	float getDistance(const SDL_Point& first, const SDL_Point& second);
	std::vector<TrainCabin*> getCabins();
	void fillCabins();
	bool renderTextBox;
	bool notebookOpen;
	void setPlayer(Player* p);
	void setRide(Ride* r);
	int date;
	Ride* getMainRide();
	void setMainRide(Ride* ride);
};

