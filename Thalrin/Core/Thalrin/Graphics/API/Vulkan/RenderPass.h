#pragma once
#include <vulkan/vulkan.h>
#include <Thalrin/API.h>

namespace Thalrin::Graphics::API::Vulkan
{
	class THALRIN_API RenderPass
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