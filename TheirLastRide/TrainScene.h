#pragma once
#include "Texture.h"
#include "Object.h"
#include "Scene.h"
#include "TrainCabin.h"
#include <vector>
#include <string>
#include <array>
#include "TextManager.h"
#include "ObjectBuilder.h"
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
	NUM_OBJECT
};

class TrainScene : public Scene
{
private:
	std::array<Object*, NUM_OBJECT> _objList;
	std::vector<Object*> _renderQueue; //maybe change to deque/priority queue?
	std::vector<TrainCabin> _cabins;
	std::vector<Text> _textQueue;
	std::string _displayText;
public:
	bool writingText;
	TrainScene();
	void Init();
	void Exit();
	void Update(double dt);
	void Render();
	void HandleKeyPress();
	int offSetX;
	int offSetY;
	void WriteText(const Text& text, const SDL_Point& pos);
};

