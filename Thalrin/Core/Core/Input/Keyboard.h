#pragma once
#include <Windows.h>
#include <unordered_map>
#include <Core/API.h>

namespace Core
{
	class Engine;
}

namespace Core::Input
{
	class CORE_API Keyboard
	{
		friend class Core::Engine;

	public:
		enum class KeyCode : int {
			Unknown = 0,

			Backspace = VK_BACK,
			Tab = VK_TAB,
			Enter = VK_RETURN,
			Shift = VK_SHIFT,
			Control = VK_CONTROL,
			Alt = VK_MENU,
			Pause = VK_PAUSE,
			CapsLock = VK_CAPITAL,
			Escape = VK_ESCAPE,
			Space = VK_SPACE,
			PageUp = VK_PRIOR,
			PageDown = VK_NEXT,
			End = VK_END,
			Home = VK_HOME,
			LeftArrow = VK_LEFT,
			UpArrow = VK_UP,
			RightArrow = VK_RIGHT,
			DownArrow = VK_DOWN,
			PrintScreen = VK_SNAPSHOT,
			Insert = VK_INSERT,
			Delete = VK_DELETE,

			// Number keys (0-9)
			D0 = 0x30,
			D1 = 0x31,
			D2 = 0x32,
			D3 = 0x33,
			D4 = 0x34,
			D5 = 0x35,
			D6 = 0x36,
			D7 = 0x37,
			D8 = 0x38,
			D9 = 0x39,

			// Letter keys (A-Z)
			A = 0x41,
			B = 0x42,
			C = 0x43,
			D = 0x44,
			E = 0x45,
			F = 0x46,
			G = 0x47,
			H = 0x48,
			I = 0x49,
			J = 0x4A,
			K = 0x4B,
			L = 0x4C,
			M = 0x4D,
			N = 0x4E,
			O = 0x4F,
			P = 0x50,
			Q = 0x51,
			R = 0x52,
			S = 0x53,
			T = 0x54,
			U = 0x55,
			V = 0x56,
			W = 0x57,
			X = 0x58,
			Y = 0x59,
			Z = 0x5A,

			// Function keys
			F1 = VK_F1,
			F2 = VK_F2,
			F3 = VK_F3,
			F4 = VK_F4,
			F5 = VK_F5,
			F6 = VK_F6,
			F7 = VK_F7,
			F8 = VK_F8,
			F9 = VK_F9,
			F10 = VK_F10,
			F11 = VK_F11,
			F12 = VK_F12
		};

	private:
		std::unordered_map<KeyCode, bool> currentKeyState;
		std::unordered_map<KeyCode, bool> previousKeyState;
		std::vector<KeyCode> keys;

	private:
		Keyboard();
		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;
		~Keyboard() = default;

		void Update();

	public:
		bool IsKeyPressed(KeyCode key);
		bool IsKeyReleased(KeyCode key);
		bool IsKeyHeld(KeyCode key);
	};
}