#pragma once
#include <vulkan/vulkan.h>
#include <Core/API.h>

namespace Core::Graphics::API::Vulkan
{
	class CORE_API RenderPass
	{
	private:
		VkDevice device;
		VkRenderPass renderPass;

	public:
		RenderPass();
		~RenderPass();

		void Create(VkDevice device, VkFormat swapchainFormat);

		VkRenderPass GetRenderPass() const { return renderPass; }
	};
}