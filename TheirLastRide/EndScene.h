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

enum OBJECT5
{
	OBJECT_BACKGROUND5,
	OBJECT_END_REAPER_NOTE,
	OBJECT_END_NORMAL_NOTE,
	OBJECT_END_BLACK_BACKGROUND,
	OBJECT_END_CHEQUE,
	NUM_OBJECT5
};

class Scene;
class EndScene :public Scene
{
private:
	std::array<Object*, NUM_OBJECT5> _objList;
	std::vector<Object*> _renderQueue;
	std::vector<Object*> _fadeQueue;
public:
	int sceneClicks;
	EndScene();
	void Init();
	void Exit();
	void Update(double dt);
	void Render();
	void HandleInput();
};
