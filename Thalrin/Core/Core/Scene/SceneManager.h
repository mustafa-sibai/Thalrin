#pragma once
#include <vector>
#include "Core/Scene/Scene.h"
#include "Core/API.h"

namespace Core::SceneManagement
{
	class CORE_API SceneManager
	{
	private:
		std::vector<Scene*> m_scenes;
		int m_currentSceneIndex;

	public:
		SceneManager();
		~SceneManager();

		void AddScene(Scene* scene);
		void RemoveScene(int sceneIndex);
		void LoadScene(int sceneIndex);

		void Update(float deltaTime);
		void Render();

		inline const Scene* GetCurrentScene() const { return m_scenes[m_currentSceneIndex]; }
	};
}