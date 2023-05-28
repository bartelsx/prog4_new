#include "SceneManager.h"
#include "Scene.h"
using namespace dae;

void SceneManager::SetCurrentScene(int idx)
{
	if(m_scenes.size()<= idx)
	{
		throw "invalid scene selected";
	}
	m_pCurrentScene = m_scenes[idx];
}
void dae::SceneManager::Update(float deltaT)
{
	m_pCurrentScene->Update(deltaT);
}

void dae::SceneManager::Render()
{
	m_pCurrentScene->Render();
	
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.emplace_back(scene);
	return *scene;
}
