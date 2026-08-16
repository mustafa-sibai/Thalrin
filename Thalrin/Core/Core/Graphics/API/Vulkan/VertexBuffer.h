#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <Core/Graphics/Vertex.h>
#include <Core/API.h>

namespace Core::Graphics::API::Vulkan
{
	class CORE_API VertexBuffer
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