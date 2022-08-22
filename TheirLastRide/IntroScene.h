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
	OBJECT_NORMAL_NOTE,
	OBJECT_REAPER_NOTE,
	NUM_OBJECT2
};

class Scene;
class IntroScene :public Scene
{
private:
	unsigned int _currentCabin;
	BoxCollider* _mouseCollider;
	std::array<Object*, NUM_OBJECT2> _objList;
	std::vector<Object*> _renderQueue;
	SDL_Event _event;
public:
	bool writingText;
	IntroScene();
	void Init();
	void Exit();
	void Update(double dt);
	void Render();
	void HandleInput();
};

