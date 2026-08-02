#include "Engine.h"

namespace Core
{
	Engine Engine::instance;

	Engine* Engine::GetInstance()
	{
		return &instance;
	}

	Engine::Engine() :
		mouse(window)
	{}

	void Engine::Run()
	{
		window.Create("Engine", 1280, 720);
		sceneManager.LoadScene(0);

		while (window.IsOpen())
		{
			time.Update();

			window.Update();
			mouse.Update();
			keyboard.Update();
			sceneManager.Update(time.GetDeltaTime());
			sceneManager.Render();
		}
	}
}