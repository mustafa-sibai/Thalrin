#pragma once
#include <chrono>
#include <Core/Networking/Http.h>
#include <Core/Time.h>
#include <Core/Platform/Windows/Window.h>
#include <Core/Graphics/Renderer.h>
#include <Core/Scene/SceneManager.h>
#include <Core/Input/Keyboard.h>
#include <Core/Input/Mouse.h>
#include <Core/API.h>

namespace Core
{
	using namespace Core::Platform::Windows;
	using namespace Core::Input;
	using namespace Core::SceneManagement;
	using namespace Core::Graphics;
	using namespace Core::Networking;

	class CORE_API Engine
	{
	private:
		Http http;
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