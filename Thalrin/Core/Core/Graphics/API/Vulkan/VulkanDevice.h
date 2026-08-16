#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <Core/API.h>

namespace Core::Graphics::API::Vulkan
{
	class CORE_API VulkanDevice
	{
	private:
		VkInstance instance;

		VkPhysicalDevice physicalDevice;
		uint32_t graphicsQueueFamily;

		VkDevice device;
		VkQueue graphicsQueue;
		VkCommandPool commandPool;

	public:
		VulkanDevice();
		~VulkanDevice();

		void CreateInstance();
		void CreatePhysicalDevice(VkSurfaceKHR surface);
		void CreateLogicalDevice();
		void CreateCommandPool();

		VkInstance GetInstance() const { return instance; }
		VkPhysicalDevice GetPhysicalDevice() const { return physicalDevice; }
		VkDevice GetLogicalDevice() const { return device; }
		VkQueue GetGraphicsQueue() const { return graphicsQueue; }
		VkCommandPool GetCommandPool() const { return commandPool; }

		uint32_t GetGraphicsQueueFamily() const { return graphicsQueueFamily; }
	};
}