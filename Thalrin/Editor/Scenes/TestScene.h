#pragma once
#include <Thalrin/Scene/Scene.h>

using namespace Thalrin;
using namespace Thalrin::SceneManagement;

class TestScene : public Scene
{
public:
	TestScene();
	virtual ~TestScene() override;

	void Initialize() override;
	void Load() override;
	void Setup() override;
	void Update(float deltaTime) override;
	void Render() override;
};