#pragma once
#include "Core/API.h"

namespace Core::SceneManagement
{
	class CORE_API Scene
	{
	public:
		Scene() = default;
		virtual ~Scene() = default;

		virtual void Initialize() = 0;
		virtual void Load() = 0;
		virtual void Setup() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;
	};
}