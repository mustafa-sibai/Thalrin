#include "SceneManager.h"
#include "Core/Engine.h"
#include "Core/Debug.h"

namespace Core::SceneManagement
{
	SceneManager::SceneManager()
		: m_currentSceneIndex(0)
	{}

	SceneManager::~SceneManager()
	{}

	void SceneManager::AddScene(Scene* scene)
	{
		m_scenes.emplace_back(scene);
	}

	void SceneManager::RemoveScene(int sceneIndex)
	{
		if (sceneIndex < 0 || sceneIndex >= static_cast<int>(m_scenes.size()))
		{
			Debug::LogFatal("Scene index out of range: {}", sceneIndex);
		}

		delete m_scenes[sceneIndex];
		m_scenes.erase(m_scenes.begin() + sceneIndex);
	}

	void SceneManager::LoadScene(int sceneIndex)
	{
		if (sceneIndex < 0 || sceneIndex >= static_cast<int>(m_scenes.size()))
		{
			Debug::LogFatal("Scene index out of range: {}", sceneIndex);
		}

		m_currentSceneIndex = sceneIndex;

		m_scenes[m_currentSceneIndex]->Initialize();
		m_scenes[m_currentSceneIndex]->Load();
		m_scenes[m_currentSceneIndex]->Setup();
	}

	void SceneManager::Update(float deltaTime)
	{
		m_scenes[m_currentSceneIndex]->Update(deltaTime);
	}

	void SceneManager::Render()
	{
		m_scenes[m_currentSceneIndex]->Render();
	}
}