#include "Swapchain.h"
#include <Core/Math/Mathf.h>
#include <Core/Debug.h>

namespace Core::Graphics::API::Vulkan
{
	using namespace Core::Math;

	Swapchain::Swapchain() :
		device(VK_NULL_HANDLE),
		swapchain(VK_NULL_HANDLE),
		swapchainFormat(VK_FORMAT_UNDEFINED),
		swapchainExtent{ 0, 0 },
		imageCount(3) //Tripple buffering
	{}

	Swapchain::~Swapchain()
	{
		if (device != VK_NULL_HANDLE && swapchain != VK_NULL_HANDLE)
		{
			//vkDestroySwapchainKHR(device, swapchain, nullptr);
		}
	}

	void Swapchain::CreateSwapchain(VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface, uint32_t width, uint32_t height)
	{
		this->device = device;

		VkSurfaceCapabilitiesKHR capabilities;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &capabilities);

		uint32_t formatCount = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);
		std::vector<VkSurfaceFormatKHR> formats(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, formats.data());

		uint32_t presentModeCount = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);
		std::vector<VkPresentModeKHR> presentModes(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, presentModes.data());

		VkSurfaceFormatKHR chosenFormat = formats[0];
		for (int i = 0; i < formats.size(); ++i)
		{
			if (formats[i].format == VK_FORMAT_B8G8R8A8_SRGB && formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				chosenFormat = formats[i];
				Debug::LogInfo("Chosen surface format: format=%d, colorSpace=%d", chosenFormat.format, chosenFormat.colorSpace);
				break;
			}
		}
		swapchainFormat = chosenFormat.format;

		VkPresentModeKHR chosenPresentMode = VK_PRESENT_MODE_FIFO_KHR;
		for (int i = 0; i < presentModes.size(); ++i)
		{
			if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				chosenPresentMode = presentModes[i];
				Debug::LogInfo("Chosen present mode: VK_PRESENT_MODE_MAILBOX_KHR");
				break;
			}
		}

		swapchainExtent.width = Mathf::Clamp(width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		swapchainExtent.height = Mathf::Clamp(height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

		uint32_t imageCount = 3; //Tripple buffering
		if (capabilities.maxImageCount > 0)
		{
			imageCount = Mathf::Clamp(imageCount, capabilities.minImageCount, capabilities.maxImageCount);
		}
		else
		{
			imageCount = Mathf::Max(imageCount, capabilities.minImageCount);
		}

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = surface;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = chosenFormat.format;
		createInfo.imageColorSpace = chosenFormat.colorSpace;
		createInfo.imageExtent.width = swapchainExtent.width;
		createInfo.imageExtent.height = swapchainExtent.height;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.preTransform = capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = chosenPresentMode;
		createInfo.clipped = VK_TRUE;

		VkResult result = vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapchain);
		if (result != VK_SUCCESS)
		{
			Debug::LogFatal("Failed to create Vulkan swapchain!");
		}
		Debug::LogInfo("Vulkan swapchain created successfully: imageCount=%d, format=%d, colorSpace=%d, extent=(%d,%d), presentMode=%d",
			imageCount, chosenFormat.format, chosenFormat.colorSpace, swapchainExtent.width, swapchainExtent.height, chosenPresentMode);

		vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr);
		swapchainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(device, swapchain, &imageCount, swapchainImages.data());

		swapchainImageViews.resize(imageCount);
		for (uint32_t i = 0; i < imageCount; i++)
		{
			VkImageViewCreateInfo viewInfo{};
			viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			viewInfo.image = swapchainImages[i];
			viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			viewInfo.format = chosenFormat.format;
			viewInfo.components = { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
									VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY };
			viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			viewInfo.subresourceRange.baseMipLevel = 0;
			viewInfo.subresourceRange.levelCount = 1;
			viewInfo.subresourceRange.baseArrayLayer = 0;
			viewInfo.subresourceRange.layerCount = 1;

			vkCreateImageView(device, &viewInfo, nullptr, &swapchainImageViews[i]);
			Debug::LogInfo("Created image view for swapchain image %d", i);
		}
	}

	void Swapchain::CreateFramebuffers(VkRenderPass renderPass)
	{
		framebuffers.resize(swapchainImageViews.size());

		for (size_t i = 0; i < swapchainImageViews.size(); i++)
		{
			VkImageView attachments[] = { swapchainImageViews[i] };

			VkFramebufferCreateInfo framebufferInfo{};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = renderPass;
			framebufferInfo.attachmentCount = 1;
			framebufferInfo.pAttachments = attachments;
			framebufferInfo.width = swapchainExtent.width;
			framebufferInfo.height = swapchainExtent.height;
			framebufferInfo.layers = 1;

			VkResult result = vkCreateFramebuffer(device, &framebufferInfo, nullptr, &framebuffers[i]);
			if (result != VK_SUCCESS)
			{
				Debug::LogFatal("Failed to create framebuffer for swapchain image %zu!", i);
			}
			Debug::LogInfo("Created framebuffer for swapchain image %zu", i);
		}
	}
}