#include "Keyboard.h"

namespace Core::Input
{
	Keyboard::Keyboard()
	{
		keys =
		{
			KeyCode::Backspace, KeyCode::Tab, KeyCode::Enter, KeyCode::Shift,
			KeyCode::Control, KeyCode::Alt, KeyCode::Pause, KeyCode::CapsLock,
			KeyCode::Escape, KeyCode::Space, KeyCode::PageUp, KeyCode::PageDown,
			KeyCode::End, KeyCode::Home, KeyCode::LeftArrow, KeyCode::UpArrow,
			KeyCode::RightArrow, KeyCode::DownArrow, KeyCode::PrintScreen,
			KeyCode::Insert, KeyCode::Delete,
			// Number keys
			KeyCode::D0, KeyCode::D1, KeyCode::D2, KeyCode::D3, KeyCode::D4,
			KeyCode::D5, KeyCode::D6, KeyCode::D7, KeyCode::D8, KeyCode::D9,
			// Letter keys
			KeyCode::A, KeyCode::B, KeyCode::C, KeyCode::D, KeyCode::E, KeyCode::F,
			KeyCode::G, KeyCode::H, KeyCode::I, KeyCode::J, KeyCode::K, KeyCode::L,
			KeyCode::M, KeyCode::N, KeyCode::O, KeyCode::P, KeyCode::Q, KeyCode::R,
			KeyCode::S, KeyCode::T, KeyCode::U, KeyCode::V, KeyCode::W, KeyCode::X,
			KeyCode::Y, KeyCode::Z,
			// Function keys
			KeyCode::F1, KeyCode::F2, KeyCode::F3, KeyCode::F4, KeyCode::F5,
			KeyCode::F6, KeyCode::F7, KeyCode::F8, KeyCode::F9, KeyCode::F10,
			KeyCode::F11, KeyCode::F12
		};
	}

	bool Keyboard::IsKeyPressed(KeyCode key)
	{
		return currentKeyState[key] && !previousKeyState[key];
	}

	bool Keyboard::IsKeyReleased(KeyCode key)
	{
		return !currentKeyState[key] && previousKeyState[key];
	}

	bool Keyboard::IsKeyHeld(KeyCode key)
	{
		return currentKeyState[key];
	}

	void Keyboard::Update()
	{
		previousKeyState = currentKeyState;

		for (KeyCode code : keys)
		{
			currentKeyState[code] = ((GetAsyncKeyState(static_cast<int>(code)) & 0x8000) != 0);
		}
	}
}