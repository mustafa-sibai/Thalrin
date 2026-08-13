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

		std::vector<VkCommandBuffer> commandBuffers;

		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;

		uint32_t currentFrame;

	public:
		VulkanDevice();
		~VulkanDevice();

		void CreateInstance();
		void CreatePhysicalDevice(VkSurfaceKHR surface);
		void CreateLogicalDevice();
		void CreateCommandPool();
		void CreateCommandBuffers(uint32_t count);
		void CreateSyncObjects(uint32_t frameCount);
		void DrawFrame(VkSwapchainKHR swapchain, VkRenderPass renderPass, std::vector<VkFramebuffer>& framebuffers, VkExtent2D extent, VkPipeline pipeline);

		VkInstance GetInstance() const { return instance; }
		VkPhysicalDevice GetPhysicalDevice() const { return physicalDevice; }
		VkDevice GetLogicalDevice() const { return device; }

		uint32_t GetGraphicsQueueFamily() const { return graphicsQueueFamily; }
	};
}