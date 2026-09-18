#pragma once
#include <Thalrin/Scene/Scene.h>

using namespace Thalrin;
using namespace Thalrin::SceneManagement;

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene() override;

	void Initialize() override;
	void Load() override;
	void Setup() override;
	void Update(float deltaTime) override;
	void Render() override;
};
