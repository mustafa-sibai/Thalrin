#include "Pipeline.h"
#include <Core/IO/FileReader.h>
#include <Core/Debug.h>

namespace Core::Graphics::API::Vulkan
{
	using namespace Core::IO;

	Pipeline::Pipeline() :
		device(VK_NULL_HANDLE), pipeline(VK_NULL_HANDLE), pipelineLayout(VK_NULL_HANDLE)
	{}

	Pipeline::~Pipeline()
	{
		if (pipeline != VK_NULL_HANDLE)
		{
			//vkDestroyPipeline(device, pipeline, nullptr);
		}

		if (pipelineLayout != VK_NULL_HANDLE)
		{
			//vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
		}
	}

	void Pipeline::Create(VkDevice device, VkRenderPass renderPass, VkExtent2D extent,
		const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		this->device = device;

		std::vector<char> vertexShaderCode = FileReader::ReadBinaryFile(vertexShaderPath);
		std::vector<char> fragmentShaderCode = FileReader::ReadBinaryFile(fragmentShaderPath);

		Debug::LogInfo("Vertex shader size: %zu bytes", vertexShaderCode.size());
		Debug::LogInfo("Fragment shader size: %zu bytes", fragmentShaderCode.size());

		VkShaderModule vertexShaderModule = CreateShaderModule(vertexShaderCode);
		VkShaderModule fragmentShaderModule = CreateShaderModule(fragmentShaderCode);

		Debug::LogInfo("Shader modules created successfully");

		// --- Shader stages ---
		VkPipelineShaderStageCreateInfo vertStage{};
		vertStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vertStage.module = vertexShaderModule;
		vertStage.pName = "main";

		VkPipelineShaderStageCreateInfo fragStage{};
		fragStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		fragStage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		fragStage.module = fragmentShaderModule;
		fragStage.pName = "main";

		VkPipelineShaderStageCreateInfo shaderStages[] = { vertStage, fragStage };

		// --- Vertex input (empty, triangle is hardcoded in shader) ---
		VkPipelineVertexInputStateCreateInfo vertexInput{};
		vertexInput.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInput.vertexBindingDescriptionCount = 0;
		vertexInput.vertexAttributeDescriptionCount = 0;

		// --- Input assembly ---
		VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		// --- Viewport and scissor ---
		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)extent.width;
		viewport.height = (float)extent.height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = extent;

		VkPipelineViewportStateCreateInfo viewportState{};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.pViewports = &viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = &scissor;

		// --- Rasterizer ---
		VkPipelineRasterizationStateCreateInfo rasterizer{};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;

		// --- Multisampling (disabled) ---
		VkPipelineMultisampleStateCreateInfo multisampling{};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		// --- Color blending ---
		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
			VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_FALSE;

		VkPipelineColorBlendStateCreateInfo colorBlending{};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;

		// --- Pipeline layout (no uniforms/push constants) ---
		VkPipelineLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		layoutInfo.setLayoutCount = 0;
		layoutInfo.pushConstantRangeCount = 0;

		VkResult layoutResult = vkCreatePipelineLayout(device, &layoutInfo, nullptr, &pipelineLayout);
		if (layoutResult != VK_SUCCESS)
		{
			Debug::LogFatal("Failed to create pipeline layout!");
		}

		// --- Final assembly ---
		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = shaderStages;
		pipelineInfo.pVertexInputState = &vertexInput;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.layout = pipelineLayout;
		pipelineInfo.renderPass = renderPass;
		pipelineInfo.subpass = 0;

		VkResult result = vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline);
		if (result != VK_SUCCESS)
		{
			Debug::LogFatal("Failed to create graphics pipeline!");
		}

		Debug::LogInfo("Graphics pipeline created successfully");

		// Shader modules only needed during pipeline creation
		vkDestroyShaderModule(device, vertexShaderModule, nullptr);
		vkDestroyShaderModule(device, fragmentShaderModule, nullptr);
	}

	VkShaderModule Pipeline::CreateShaderModule(const std::vector<char>& code)
	{
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		VkShaderModule shaderModule;
		VkResult result = vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule);
		if (result != VK_SUCCESS)
		{
			Debug::LogFatal("Failed to create shader module!");
		}

		return shaderModule;
	}
}