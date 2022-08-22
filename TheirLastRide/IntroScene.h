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

enum OBJECT2
{
	OBJECT_BACKGROUND2,
	NUM_OBJECT2
};

enum TM_ANIM2 
{
	NUM_BG_ANIM2
};


class Scene;
class IntroScene :public Scene
{
private:
	unsigned int _currentCabin;
	BoxCollider* _mouseCollider;
	std::array<Object*, NUM_OBJECT2> _objList;
	std::array<Texture*, NUM_BG_ANIM2> _tmAnimList;
	std::vector<Button*> _buttons;
	std::vector<Object*> _renderQueue;
	SDL_Event _event;
	Person* _interactingPerson;
	int offSetX;
	int offSetY;
public:
	bool writingText;
	IntroScene();
	void Init();
	void Exit();
	void Update(double dt);
	void Render();
	void HandleInput();
};

