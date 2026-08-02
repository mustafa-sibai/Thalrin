#include "Mouse.h"

namespace Core::Input
{
	Mouse::Mouse(const Window& window) :
		window(window)
	{
	}

	bool Mouse::IsButtonPressed(ButtonCode button)
	{
		int index = static_cast<int>(button);
		return (!prev[index] && current[index]);
	}

	bool Mouse::IsButtonReleased(ButtonCode button)
	{
		int index = static_cast<int>(button);
		return (prev[index] && !current[index]);
	}

	bool Mouse::IsButtonHeld(ButtonCode button)
	{
		int index = static_cast<int>(button);
		return current[index];
	}

	void Mouse::Update()
	{
		for (int i = 0; i < totalMouseButtons; ++i)
			prev[i] = current[i];

		for (size_t i = 0; i < totalMouseButtons; i++)
			current[i] = (GetAsyncKeyState(GetVirtualKey(static_cast<ButtonCode>(i))) & 0x8000) != 0;
	}

	Vector2f Mouse::GetPosition(bool relativeToWindow) const
	{
		POINT pos;
		GetCursorPos(&pos);

		if (relativeToWindow)
		{
			ScreenToClient(window.GetHWND(), &pos);
		}

		return Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y));
	}

	int Mouse::GetVirtualKey(ButtonCode button) const
	{
		switch (button)
		{
		case ButtonCode::LeftButton:
			return VK_LBUTTON;
		case ButtonCode::RightButton:
			return VK_RBUTTON;
		case ButtonCode::MiddleButton:
			return VK_MBUTTON;
		case ButtonCode::XButton1:
			return VK_XBUTTON1;
		case ButtonCode::XButton2:
			return VK_XBUTTON2;
		default:
			return 0;
		}
	}
}