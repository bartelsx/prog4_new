#include "SceneManager.h"
#include "Scene.h"
using namespace dae;

void dae::SceneManager::Update(float deltaT)
{
	for (auto& pScene : m_scenes )
	{
		pScene->Update(deltaT);
	}
}

void dae::SceneManager::Render()
{
	for (auto& pScene : m_scenes)
	{
		pScene->Render();
	}
}

void SceneManager::Clear()
{
	m_scenes.clear();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.emplace_back(scene);
	return *scene;
}
