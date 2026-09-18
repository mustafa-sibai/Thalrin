#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <Thalrin/Graphics/Vertex.h>
#include <Thalrin/API.h>

namespace Thalrin::Graphics::API::Vulkan
{
	class THALRIN_API VertexBuffer
	{
	private:
		VkDevice device;
		VkBuffer buffer;
		VkDeviceMemory memory;
		uint32_t vertexCount;

	public:
		VertexBuffer();
		~VertexBuffer();

		void Create(VkPhysicalDevice physicalDevice, VkDevice device, const std::vector<Vertex>& vertices);
	};
}