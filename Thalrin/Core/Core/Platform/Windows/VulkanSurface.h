#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include <Windows.h>
#include <Core/API.h>

namespace Core::Platform::Windows
{
	class CORE_API VulkanSurface
	{
	private:
		VkInstance instance;
		VkSurfaceKHR surface;

	public:
		VulkanSurface();
		~VulkanSurface();

		void Create(VkInstance instance, HINSTANCE hInstance, HWND hWnd);

		VkSurfaceKHR GetSurface() const { return surface; }
	};
}