#pragma once
#include <chrono>
#include <Thalrin/Networking/Http.h>
#include <Thalrin/Networking/UDPServer.h>
#include <Thalrin/Networking/UDPClient.h>
#include <Thalrin/Time.h>
#include <Thalrin/Platform/Windows/Window.h>
#include <Thalrin/Graphics/Renderer.h>
#include <Thalrin/Scene/SceneManager.h>
#include <Thalrin/Input/Keyboard.h>
#include <Thalrin/Input/Mouse.h>
#include <Thalrin/API.h>

namespace Thalrin
{
	using namespace Thalrin::Platform::Windows;
	using namespace Thalrin::Input;
	using namespace Thalrin::SceneManagement;
	using namespace Thalrin::Graphics;
	using namespace Thalrin::Networking;

	class THALRIN_API Engine
	{
	private:
		Http http;
		UDPServer udpServer;
		UDPClient udpClient;
		Window window;
		Renderer renderer;
		SceneManager sceneManager;
		Keyboard keyboard;
		Mouse mouse;
		Time time;

		static Engine instance;

	public:
		static Engine* GetInstance();

	private:
		Engine();
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator=(const Engine&) = delete;

	public:
		~Engine() = default;

		void Run();

		inline Window& GetWindow() { return window; }
		inline SceneManager& GetSceneManager() { return sceneManager; }
		inline Keyboard& GetKeyboard() { return keyboard; }
		inline Mouse& GetMouse() { return mouse; }
		inline const Time& GetTime() const { return time; }
	};
}