#include "VulkanDevice.h"
#include <Core/Debug.h>

namespace Core::Graphics::API::Vulkan
{
	VulkanDevice::VulkanDevice() :
		instance(nullptr),
		physicalDevice(nullptr), graphicsQueueFamily(UINT32_MAX),
		device(nullptr), graphicsQueue(nullptr),
		commandPool(nullptr), currentFrame(0)
	{}

	VulkanDevice::~VulkanDevice()
	{
		//vkDestroyDevice(device, nullptr);
		vkDestroyInstance(instance, nullptr);
	}

	void VulkanDevice::CreateInstance()
	{
		uint32_t version;
		VkResult result = vkEnumerateInstanceVersion(&version);
		if (result != VK_SUCCESS)
		{
			Debug::LogFatal("Failed to enumerate Vulkan instance version!");
		}
		Debug::LogInfo("Vulkan Instance Version: %u.%u.%u", VK_VERSION_MAJOR(version), VK_VERSION_MINOR(version), VK_VERSION_PATCH(version));

		std::vector<const char*> extensions = {
			"VK_KHR_surface",
			"VK_KHR_win32_surface"
		};

		std::vector<const char*> layers = {
#ifdef _DEBUG
			"VK_LAYER_KHRONOS_validation"
#endif
		};

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Thalrin Engine";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Thalrin Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_4;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();
		createInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
		createInfo.ppEnabledLayerNames = layers.data();

		result = vkCreateInstance(&createInfo, nullptr, &instance);
		if (result != VK_SUCCESS)
		{
			Debug::LogFatal("Failed to create Vulkan instance!");
		}
	}

	void VulkanDevice::CreatePhysicalDevice(VkSurfaceKHR surface)
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
		if (deviceCount == 0)
		{
			Debug::LogFatal("No Vulkan-capable GPU found!");
		}
		Debug::LogInfo("Number of Vulkan-capable GPUs found: %u", deviceCount);

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

		VkPhysicalDevice capableDevice = VK_NULL_HANDLE;
		uint32_t capableQueueFamily = UINT32_MAX;

		for (int i = 0; i < deviceCount; ++i)
		{
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(devices[i], &deviceProperties);
			Debug::LogInfo("GPU %d: %s", i, deviceProperties.deviceName);

			uint32_t queueFamilyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(devices[i], &queueFamilyCount, nullptr);
			Debug::LogInfo("Number of queue families for GPU %d: %u", i, queueFamilyCount);

			std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(devices[i], &queueFamilyCount, queueFamilies.data());

			for (int j = 0; j < queueFamilyCount; ++j)
			{
				bool supportsGraphics = queueFamilies[j].queueFlags & VK_QUEUE_GRAPHICS_BIT;
				bool isDiscreteGPU = deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;

				VkBool32 supportsPresent = false;
				vkGetPhysicalDeviceSurfaceSupportKHR(devices[i], j, surface, &supportsPresent);

				if (supportsGraphics && supportsPresent)
				{
					Debug::LogInfo("GPU %d supports graphics and presentation on queue family %d", i, j);
					capableDevice = devices[i];
					capableQueueFamily = j;

					if (isDiscreteGPU)
					{
						physicalDevice = devices[i];
						graphicsQueueFamily = j;
						Debug::LogInfo("GPU %d is a discrete GPU", i);
					}
				}
			}
		}

		if (physicalDevice == VK_NULL_HANDLE)
		{
			if (capableDevice != VK_NULL_HANDLE)
			{
				physicalDevice = capableDevice;
				graphicsQueueFamily = capableQueueFamily;
				Debug::LogInfo("No discrete GPU found, using capable GPU instead");
			}
			else
			{
				Debug::LogFatal("No suitable GPU found!");
			}
		}

		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
		Debug::LogInfo("-----------");
		Debug::LogInfo("Selected GPU: %s with queue family %d", deviceProperties.deviceName, graphicsQueueFamily);
		Debug::LogInfo("-----------");
	}

	void VulkanDevice::CreateLogicalDevice()
	{
		float queuePriority = 1.0f;
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = graphicsQueueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		VkPhysicalDeviceFeatures deviceFeatures{};
		const char* deviceExtensions[] = { "VK_KHR_swapchain" };

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;
		createInfo.ppEnabledExtensionNames = deviceExtensions;
		createInfo.enabledExtensionCount = 1;
		createInfo.pEnabledFeatures = &deviceFeatures;

		VkResult result = vkCreateDevice(physicalDevice, &createInfo, nullptr, &device);
		if (result != VK_SUCCESS)
		{
			Debug::LogFatal("Failed to create logical device!");
		}

		vkGetDeviceQueue(device, graphicsQueueFamily, 0, &graphicsQueue);
		Debug::LogInfo("Logical device created successfully with graphics queue");
	}

	void VulkanDevice::CreateCommandPool()
	{
		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		poolInfo.queueFamilyIndex = graphicsQueueFamily;

		VkResult result = vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool);
		if (result != VK_SUCCESS)
		{
			Debug::LogFatal("Failed to create command pool!");
		}
		Debug::LogInfo("Command pool created successfully for graphics queue family %d", graphicsQueueFamily);
	}

	void VulkanDevice::CreateCommandBuffers(uint32_t count)
	{
		commandBuffers.resize(count);

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = count;

		VkResult result = vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data());
		if (result != VK_SUCCESS)
		{
			Debug::LogFatal("Failed to allocate command buffers!");
		}
		Debug::LogInfo("%u command buffers allocated successfully", count);
	}

	void VulkanDevice::CreateSyncObjects(uint32_t frameCount)
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
			VkResult result = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]);
			if (result != VK_SUCCESS)
			{
				Debug::LogFatal("Failed to create image available semaphore!");
			}
			Debug::LogInfo("Image available semaphore %d created successfully", i);

			result = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]);
			if (result != VK_SUCCESS)
			{
				Debug::LogFatal("Failed to create render finished semaphore!");
			}
			Debug::LogInfo("Render finished semaphore %d created successfully", i);

			result = vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]);
			if (result != VK_SUCCESS)
			{
				Debug::LogFatal("Failed to create in-flight fence!");
			}
			Debug::LogInfo("In-flight fence %d created successfully", i);
		}
	}

	void VulkanDevice::DrawFrame(VkSwapchainKHR swapchain, VkRenderPass renderPass,
		std::vector<VkFramebuffer>& framebuffers, VkExtent2D extent, VkPipeline pipeline)
	{
		// 1. Wait for previous frame
		vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
		vkResetFences(device, 1, &inFlightFences[currentFrame]);

		// 2. Acquire next image
		uint32_t imageIndex;
		vkAcquireNextImageKHR(device, swapchain, UINT64_MAX,
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
		renderPassInfo.renderPass = renderPass;
		renderPassInfo.framebuffer = framebuffers[imageIndex];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = extent;
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(cmd, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		
		//Draw here
		vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
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

		vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]);

		// 5. Present
		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &swapchain;
		presentInfo.pImageIndices = &imageIndex;

		vkQueuePresentKHR(graphicsQueue, &presentInfo);

		currentFrame = (currentFrame + 1) % commandBuffers.size();
	}
}