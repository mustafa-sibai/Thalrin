#pragma once
#include <Thalrin/Platform/Windows/Window.h>
#include <Thalrin/Math/Vector2.h>
#include <Thalrin/API.h>

namespace Thalrin::Input
{
	using namespace Thalrin::Platform::Windows;
	using namespace Thalrin::Math;

	class THALRIN_API Mouse
	{
		friend class Engine;

	private:
		const Window& window;

		static constexpr int totalMouseButtons = 5;

		bool current[totalMouseButtons] = { false };
		bool prev[totalMouseButtons] = { false };

	public:
		enum class ButtonCode
		{
			LeftButton,
			RightButton,
			MiddleButton,
			XButton1,
			XButton2
		};

	public:

		bool IsButtonPressed(ButtonCode button);
		bool IsButtonReleased(ButtonCode button);
		bool IsButtonHeld(ButtonCode button);

		Vector2f GetPosition(bool relativeToWindow = false) const;

	private:
		Mouse(const Window& window);
		Mouse(const Mouse&) = delete;
		Mouse(Mouse&&) = delete;
		Mouse& operator=(const Mouse&) = delete;
		~Mouse() = default;

		int GetVirtualKey(ButtonCode button) const;
		void Update();
	};
}