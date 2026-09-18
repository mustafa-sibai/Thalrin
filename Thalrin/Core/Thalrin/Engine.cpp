#include "Engine.h"
#include <Thalrin/Debug.h>
#include "miniaudio/miniaudio.h"

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
		ma_result result;
		ma_engine engine;

		result = ma_engine_init(NULL, &engine);
		if (result != MA_SUCCESS) {
			return;
		}

		result = ma_engine_play_sound(&engine, "Assets/Music/test_music.mp3", NULL);

		if (result != MA_SUCCESS) {
			Debug::LogError("Failed to play sound: %d", result);
		}
		//ma_engine_uninit(&engine);

		//-----------


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