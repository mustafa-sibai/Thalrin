#pragma once
#include <vector>
#include <Thalrin/Scene/Scene.h>
#include <Thalrin/API.h>

namespace Thalrin::SceneManagement
{
	class THALRIN_API SceneManager
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