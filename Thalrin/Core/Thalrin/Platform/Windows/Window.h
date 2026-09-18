#pragma once
#include <string>
#include <Windows.h>
#include <Thalrin/API.h>

namespace Thalrin::Platform::Windows
{
	class THALRIN_API Window
	{
	private:
		HWND hWnd;
		HINSTANCE hInstance;

		int Width;
		int Height;

		bool isWindowOpen;

	public:
		Window();
		~Window();

		void Create(std::string InTitle, int InWidth, int InHeight);
		void Update();

		inline bool IsOpen() { return isWindowOpen; }
		HWND GetHWND() const { return hWnd; }
		HINSTANCE GetInstance() const { return hInstance; }
		int GetWidth() const { return Width; }
		int GetHeight() const { return Height; }
		float GetAspectRatio() const { return (float)Width / (float)Height; }

	private:
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}