#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaT)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaT);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.emplace_back(scene);
	return *scene;
}
