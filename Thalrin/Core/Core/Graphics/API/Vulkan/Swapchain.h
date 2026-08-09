#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <Core/API.h>

namespace Core::Graphics::API::Vulkan
{
	class CORE_API Swapchain
	{
	private:
		VkDevice device;
		VkSwapchainKHR swapchain;

		VkFormat swapchainFormat;
		VkExtent2D swapchainExtent;

		std::vector<VkImage> swapchainImages;
		std::vector<VkImageView> swapchainImageViews;
		std::vector<VkFramebuffer> framebuffers;
		uint32_t imageCount;

	public:
		Swapchain();
		~Swapchain();

		void CreateSwapchain(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface, uint32_t width, uint32_t height);
		void CreateFramebuffers(VkRenderPass renderPass);

		VkSwapchainKHR GetSwapchain() const { return swapchain; }
		VkExtent2D GetExtent() const { return swapchainExtent; }
		VkFormat GetSwapchainFormat() const { return swapchainFormat; }
		std::vector<VkFramebuffer>& GetFramebuffers() { return framebuffers; }

		uint32_t GetImageCount() const { return imageCount; }
	};
}