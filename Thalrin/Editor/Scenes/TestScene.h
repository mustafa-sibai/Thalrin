#pragma once
#include <Core/Scene/Scene.h>

using namespace Core;
using namespace Core::SceneManagement;

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