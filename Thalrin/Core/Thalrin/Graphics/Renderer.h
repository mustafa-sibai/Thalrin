#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <Thalrin/Platform/Windows/VulkanSurface.h>
#include <Thalrin/Graphics/API/Vulkan/VulkanDevice.h>
#include <Thalrin/Graphics/API/Vulkan/Swapchain.h>
#include <Thalrin/Graphics/API/Vulkan/RenderPass.h>
#include <Thalrin/Graphics/API/Vulkan/Pipeline.h>
#include <Thalrin/API.h>

namespace Thalrin::Graphics
{
	using namespace Thalrin::Platform::Windows;
	using namespace Thalrin::Graphics::API::Vulkan;

	class THALRIN_API Renderer
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
