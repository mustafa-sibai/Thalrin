#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <Thalrin/API.h>

namespace Thalrin::Graphics::API::Vulkan
{
	class THALRIN_API Pipeline
	{
	private:
		VkDevice device;
		VkPipeline pipeline;
		VkPipelineLayout pipelineLayout;

	public:
		Pipeline();
		~Pipeline();

		void Create(VkDevice device, VkRenderPass renderPass, VkExtent2D extent,
			const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		VkShaderModule CreateShaderModule(const std::vector<char>& code);

		VkPipeline GetPipeline() const { return pipeline; }
	};
}