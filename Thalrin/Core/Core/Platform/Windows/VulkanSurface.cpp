#include "VulkanSurface.h"
#include <Core/Debug.h>

namespace Core::Platform::Windows
{
	VulkanSurface::VulkanSurface() :
		instance(VK_NULL_HANDLE), surface(VK_NULL_HANDLE)
	{}

	VulkanSurface::~VulkanSurface()
	{
		if (this->instance != VK_NULL_HANDLE && this->surface != VK_NULL_HANDLE)
		{
			vkDestroySurfaceKHR(this->instance, surface, nullptr);
		}
	}

	void VulkanSurface::Create(VkInstance instance, HINSTANCE hInstance, HWND hWnd)
	{
		VkWin32SurfaceCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		createInfo.hinstance = hInstance;
		createInfo.hwnd = hWnd;

		VkResult result = vkCreateWin32SurfaceKHR(instance, &createInfo, nullptr, &this->surface);
		if (result != VK_SUCCESS)
		{
			Debug::LogFatal("Failed to create Vulkan Win32 surface!");
		}
		Debug::LogInfo("Vulkan Win32 surface created successfully");
	}
}