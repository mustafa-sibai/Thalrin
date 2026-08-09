#include "Engine.h"

namespace Core
{
	Engine Engine::instance;

	Engine* Engine::GetInstance()
	{
		return &instance;
	}

	Engine::Engine() :
		mouse(window)
	{}

	void Engine::Run()
	{
		window.Create("Engine", 1280, 720);
		vulkanDevice.CreateInstance();
		vulkanSurface.Create(vulkanDevice.GetInstance(), window.GetInstance(), window.GetHWND());
		vulkanDevice.CreatePhysicalDevice(vulkanSurface.GetSurface());
		vulkanDevice.CreateLogicalDevice();
		swapchain.CreateSwapchain(vulkanDevice.GetPhysicalDevice(), vulkanDevice.GetLogicalDevice(), vulkanSurface.GetSurface(), window.GetWidth(), window.GetHeight());
		renderPass.Create(vulkanDevice.GetLogicalDevice(), swapchain.GetSwapchainFormat());
		swapchain.CreateFramebuffers(renderPass.GetRenderPass());
		vulkanDevice.CreateCommandPool();
		vulkanDevice.CreateCommandBuffers(swapchain.GetImageCount());
		vulkanDevice.CreateSyncObjects(swapchain.GetImageCount());

		sceneManager.LoadScene(0);

		while (window.IsOpen())
		{
			time.Update();

			window.Update();
			mouse.Update();
			keyboard.Update();
			sceneManager.Update(time.GetDeltaTime());

			vulkanDevice.DrawFrame(
				swapchain.GetSwapchain(),
				renderPass.GetRenderPass(),
				swapchain.GetFramebuffers(),
				swapchain.GetExtent());

			sceneManager.Render();
		}
	}
}