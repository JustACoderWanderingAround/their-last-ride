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
	OBJECT_REAPER_NOTE,
	OBJECT_NORMAL_NOTE,
	OBJECT_INTRO_BLACK_BACKGROUND,
	NUM_OBJECT2
};

class Scene;
class IntroScene :public Scene
{
private:
	std::array<Object*, NUM_OBJECT2> _objList;
	std::vector<Object*> _renderQueue;
	std::vector<Object*> _fadeQueue;
public:
	int sceneClicks;
	IntroScene();
	void Init();
	void Exit();
	void Update(double dt);
	void Render();
	void HandleInput();
};

