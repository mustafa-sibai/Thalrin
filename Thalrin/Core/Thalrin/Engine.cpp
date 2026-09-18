#include "Engine.h"
#include <Thalrin/Debug.h>

namespace Thalrin
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
		std::string request = "";
		std::vector<std::string> headers;

		http.Initialize();
		http.Get("https://httpbin.org/get", request, headers);
		Debug::LogInfo("%s", request.c_str());

		udpServer.Initialize();
		udpClient.Initialize();

		window.Create("Engine", 1280, 720);
		sceneManager.LoadScene(0);
		renderer.Initialize();

		while (window.IsOpen())
		{
			time.Update();

			window.Update();
			mouse.Update();
			keyboard.Update();
			sceneManager.Update(time.GetDeltaTime());

			udpServer.Update();

			if (keyboard.IsKeyPressed(Keyboard::KeyCode::Space))
			{
				udpClient.Update();
				Debug::LogInfo("Space key pressed");
			}

			renderer.Render();
			sceneManager.Render();
		}
	}
}