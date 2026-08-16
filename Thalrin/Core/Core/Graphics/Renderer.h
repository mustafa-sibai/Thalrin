#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <Core/Platform/Windows/VulkanSurface.h>
#include <Core/Graphics/API/Vulkan/VulkanDevice.h>
#include <Core/Graphics/API/Vulkan/Swapchain.h>
#include <Core/Graphics/API/Vulkan/RenderPass.h>
#include <Core/Graphics/API/Vulkan/Pipeline.h>
#include <Core/API.h>

namespace Core::Graphics
{
	using namespace Core::Platform::Windows;
	using namespace Core::Graphics::API::Vulkan;

	class CORE_API Renderer
	{
	private:
		VulkanDevice vulkanDevice;
		VulkanSurface vulkanSurface;
		Swapchain swapchain;
		RenderPass renderPass;
		Pipeline pipeline;

		std::vector<VkCommandBuffer> commandBuffers;

		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;

		uint32_t currentFrame;

	public:
		Renderer();
		~Renderer();

		void CreateCommandBuffers(uint32_t count);
		void CreateSyncObjects(uint32_t frameCount);

		void Initialize();
		void Render();
	};
}
