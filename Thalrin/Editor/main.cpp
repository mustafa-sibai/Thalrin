#include <Core/Engine.h>
#include "Scenes/TestScene.h"

using namespace Core;

int main()
{
	Engine::GetInstance()->GetSceneManager().AddScene(new TestScene());
	Engine::GetInstance()->Run();

	return 0;
}