#include "Window.h"
#include "WindowsUtils.h"

namespace Core::Platform::Windows
{
	Window::Window() :
		hWnd(nullptr), hInstance(nullptr), Width(0), Height(0), isWindowOpen(false)
	{}

	Window::~Window()
	{
		if (hWnd)
		{
			DestroyWindow(hWnd);
			hWnd = nullptr;
		}
	}

	void Window::Create(std::string InTitle, int InWidth, int InHeight)
	{
		const wchar_t CLASS_NAME[] = L"CoreClass";

		WNDCLASSEXW wc = { 0 };
		wc.cbSize = sizeof(WNDCLASSEXW);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = Window::WndProc;
		wc.hInstance = hInstance;
		wc.lpszClassName = CLASS_NAME;
		wc.hIcon = LoadIconW(0, IDI_APPLICATION);
		wc.hIconSm = LoadIconW(0, IDI_APPLICATION);
		wc.hCursor = LoadCursorW(0, IDC_ARROW);

		if (!RegisterClassExW(&wc))
		{
			MessageBox(nullptr, L"Window Registration Failed!", L"Error", MB_ICONERROR);
			return;
		}

		Width = InWidth;
		Height = InHeight;

		std::wstring wTitle = ToWideString(InTitle);

		hWnd = CreateWindowExW(
			0,
			CLASS_NAME,
			wTitle.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			InWidth, InHeight,
			nullptr,
			nullptr,
			hInstance,
			this
		);

		if (!hWnd)
		{
			MessageBox(nullptr, L"Window Creation Failed!", L"Error", MB_ICONERROR);
			return;
		}

		ShowWindow(hWnd, SW_NORMAL);
		UpdateWindow(hWnd);

		isWindowOpen = true;
	}

	void Window::Update()
	{
		MSG msg = { 0 };

		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				isWindowOpen = false;
				break;
			}
		}
	}

	LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		switch (message) {
		case WM_CREATE: {
			CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
			window = reinterpret_cast<Window*>(cs->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
			break;
		}

		case WM_DESTROY: {
			if (window) window->isWindowOpen = false;
			PostQuitMessage(0);
			return 0;
		}

		case WM_SIZE: {
			if (window) {
				window->Width = LOWORD(lParam);
				window->Height = HIWORD(lParam);
			}
			break;
		}
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}