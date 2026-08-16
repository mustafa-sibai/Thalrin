#include "VulkanDevice.h"
#include <Core/Debug.h>

namespace Core::Graphics::API::Vulkan
{
	VulkanDevice::VulkanDevice() :
		instance(nullptr),
		physicalDevice(nullptr), graphicsQueueFamily(UINT32_MAX),
		device(nullptr), graphicsQueue(nullptr),
		commandPool(nullptr)
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
}