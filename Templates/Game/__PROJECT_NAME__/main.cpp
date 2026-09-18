#include <Thalrin/Engine.h>
#include "Scenes/GameScene.h"

using namespace Thalrin;

int main()
{
	Engine::GetInstance()->GetSceneManager().AddScene(new GameScene());
	Engine::GetInstance()->Run();
	return 0;
}
