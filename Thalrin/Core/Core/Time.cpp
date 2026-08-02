#include "Time.h"
#include "Core/Math/Mathf.h"

namespace Core
{
	using namespace Core::Math;

	Time::Time() :
		previousTime(Clock::now()),
		deltaTime(0.0f),
		totalTime(0.0),
		frameCounter(0),
		fpsTimer(0.0f),
		fps(0.0f),
		msPerFrame(0.0f)
	{
	}

	Time::~Time()
	{
	}

	void Time::Update()
	{
		const auto now = Clock::now();
		std::chrono::duration<float> dt = now - previousTime;
		previousTime = now;

		deltaTime = dt.count();
		if (maxDeltaTime > 0.0f)
			deltaTime = Mathf::Min(deltaTime, maxDeltaTime);

		totalTime += deltaTime;

		// --- FPS measurement ---
		frameCounter++;
		fpsTimer += deltaTime;

		if (fpsTimer >= 1.0f)
		{
			fps = (float)frameCounter / fpsTimer;
			msPerFrame = 1000.0f / fps;

			frameCounter = 0;
			fpsTimer = 0.0f;
		}
	}
}