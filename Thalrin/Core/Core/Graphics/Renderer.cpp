#include "Renderer.h"
#include <Core/Debug.h>
#include <Core/Engine.h>

namespace Core::Graphics
{
	Renderer::Renderer() :
		vulkanDevice(),
		vulkanSurface(),
		swapchain(),
		renderPass(),
		pipeline(),
		commandBuffers(),
		imageAvailableSemaphores(),
		renderFinishedSemaphores(),
		inFlightFences(),
		currentFrame(0)
	{}

	Renderer::~Renderer()
	{}

	void Renderer::Initialize()
	{
		vulkanDevice.CreateInstance();
		vulkanSurface.Create(vulkanDevice.GetInstance(), Engine::GetInstance()->GetWindow().GetInstance(), Engine::GetInstance()->GetWindow().GetHWND());
		vulkanDevice.CreatePhysicalDevice(vulkanSurface.GetSurface());
		vulkanDevice.CreateLogicalDevice();
		swapchain.CreateSwapchain(vulkanDevice.GetPhysicalDevice(), vulkanDevice.GetLogicalDevice(), vulkanSurface.GetSurface(), Engine::GetInstance()->GetWindow().GetWidth(), Engine::GetInstance()->GetWindow().GetHeight());
		renderPass.Create(vulkanDevice.GetLogicalDevice(), swapchain.GetSwapchainFormat());
		swapchain.CreateFramebuffers(renderPass.GetRenderPass());
		vulkanDevice.CreateCommandPool();
		CreateCommandBuffers(swapchain.GetImageCount());
		CreateSyncObjects(swapchain.GetImageCount());
		pipeline.Create(vulkanDevice.GetLogicalDevice(), renderPass.GetRenderPass(), swapchain.GetExtent(),
			"Shaders/triangle-shader.vert.spv", "Shaders/triangle-shader.frag.spv");
	}

	void Renderer::CreateCommandBuffers(uint32_t count)
	{
		commandBuffers.resize(count);

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = vulkanDevice.GetCommandPool();
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = count;

		VkResult result = vkAllocateCommandBuffers(vulkanDevice.GetLogicalDevice(), &allocInfo, commandBuffers.data());
		if (result != VK_SUCCESS)
		{
			Debug::LogFatal("Failed to allocate command buffers!");
		}
		Debug::LogInfo("%u command buffers allocated successfully", count);
	}

	void Renderer::CreateSyncObjects(uint32_t frameCount)
	{
		imageAvailableSemaphores.resize(frameCount);
		renderFinishedSemaphores.resize(frameCount);
		inFlightFences.resize(frameCount);

		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo{};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (uint32_t i = 0; i < frameCount; i++)
		{
			VkResult result = vkCreateSemaphore(vulkanDevice.GetLogicalDevice(), &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]);
			if (result != VK_SUCCESS)
			{
				Debug::LogFatal("Failed to create image available semaphore!");
			}
			Debug::LogInfo("Image available semaphore %d created successfully", i);

			result = vkCreateSemaphore(vulkanDevice.GetLogicalDevice(), &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]);
			if (result != VK_SUCCESS)
			{
				Debug::LogFatal("Failed to create render finished semaphore!");
			}
			Debug::LogInfo("Render finished semaphore %d created successfully", i);

			result = vkCreateFence(vulkanDevice.GetLogicalDevice(), &fenceInfo, nullptr, &inFlightFences[i]);
			if (result != VK_SUCCESS)
			{
				Debug::LogFatal("Failed to create in-flight fence!");
			}
			Debug::LogInfo("In-flight fence %d created successfully", i);
		}
	}

	void Renderer::Render()
	{
		// 1. Wait for previous frame
		vkWaitForFences(vulkanDevice.GetLogicalDevice(), 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
		vkResetFences(vulkanDevice.GetLogicalDevice(), 1, &inFlightFences[currentFrame]);

		// 2. Acquire next image
		uint32_t imageIndex;
		vkAcquireNextImageKHR(vulkanDevice.GetLogicalDevice(), swapchain.GetSwapchain(), UINT64_MAX,
			imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

		// 3. Record command buffer
		VkCommandBuffer cmd = commandBuffers[currentFrame];
		vkResetCommandBuffer(cmd, 0);

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		vkBeginCommandBuffer(cmd, &beginInfo);

		VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = renderPass.GetRenderPass();
		renderPassInfo.framebuffer = swapchain.GetFramebuffers()[imageIndex];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = swapchain.GetExtent();
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(cmd, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		//Draw here
		vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.GetPipeline());
		vkCmdDraw(cmd, 3, 1, 0, 0);

		vkCmdEndRenderPass(cmd);

		vkEndCommandBuffer(cmd);

		// 4. Submit
		VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &cmd;
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		vkQueueSubmit(vulkanDevice.GetGraphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]);

		VkSwapchainKHR sc = swapchain.GetSwapchain();

		// 5. Present
		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &sc;
		presentInfo.pImageIndices = &imageIndex;

		vkQueuePresentKHR(vulkanDevice.GetGraphicsQueue(), &presentInfo);

		currentFrame = (currentFrame + 1) % commandBuffers.size();
	}
}