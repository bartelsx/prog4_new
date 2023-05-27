#include "GameState.h"

#include "GameObject.h"


void dae::GameState::SetPacmanObj(std::shared_ptr<dae::GameObject>& obj)
{
	m_pPacmanObj = obj;
}

std::shared_ptr<dae::GameObject>& dae::GameState::GetPacmanObj()
{
	return m_pPacmanObj;
}
glm::vec2 dae::GameState::GetPacmanLocation()
{
	return m_pPacmanObj->GetPosition();
}
