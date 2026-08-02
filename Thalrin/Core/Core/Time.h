#pragma once
#include <chrono>
#include "Core/API.h"

namespace Core
{
	class CORE_API Time
	{
	private:
		using Clock = std::chrono::steady_clock;
		Clock::time_point previousTime;
		float deltaTime;
		double totalTime;
		float maxDeltaTime = 0.1f; // clamp to avoid huge dt after alt-tab/breakpoints

		uint32_t frameCounter;
		float fpsTimer;
		float fps;
		float msPerFrame;

	public:
		Time();
		~Time();

		void Update();

		inline float GetDeltaTime() const { return deltaTime; }
		inline float GetTotalTime() const { return totalTime; }
		inline float GetFPS() const { return fps; }
		inline float GetMSPerFrame() const { return msPerFrame; }
	};
}