#include "VertexBuffer.h"

namespace Core::Graphics::API::Vulkan
{
	VertexBuffer::VertexBuffer() :
		device(nullptr), buffer(nullptr), memory(nullptr), vertexCount(0)
	{}

	VertexBuffer::~VertexBuffer()
	{
		if (buffer != nullptr)
		{
			//vkDestroyBuffer(device, buffer, nullptr);
		}
		if (memory != nullptr)
		{
			//vkFreeMemory(device, memory, nullptr);
		}
	}

	void VertexBuffer::Create(VkPhysicalDevice physicalDevice, VkDevice device, const std::vector<Vertex>& vertices)
	{}
}