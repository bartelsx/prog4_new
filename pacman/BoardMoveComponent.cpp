#include "BoardMoveComponent.h"

using namespace dae;


BoardMoveComponent::BoardMoveComponent(std::shared_ptr<GameBoardModel> pModel) : m_pModel(pModel)
{
}

void BoardMoveComponent::Update(float deltaTime)
{
	auto pOwner = GetOwner();
	auto newPos = CalculateNewPos(pOwner->GetPosition(), deltaTime);
	auto tileSize = m_pModel->GetTileSize();

	glm::vec2 centerOfPlayer{ newPos.x + m_pModel->GetTileSize() / 2, newPos.y + m_pModel->GetTileSize() / 2 };

	if (! m_pModel->IsTileAtLocationAccessible(glm::vec2{centerOfPlayer.x-m_pModel->GetTileSize(), centerOfPlayer.y}))//left
	{
		newPos.x = static_cast<float> (std::max(static_cast<int>(newPos.x), static_cast<int>(centerOfPlayer.x / tileSize) * tileSize ));
	}


	if (!m_pModel->IsTileAtLocationAccessible(glm::vec2{ centerOfPlayer.x + m_pModel->GetTileSize(), centerOfPlayer.y }))//right
	{
		newPos.x = static_cast<float> (std::min(static_cast<int>(newPos.x), static_cast<int>(centerOfPlayer.x / tileSize) * tileSize));
	}

	if (!m_pModel->IsTileAtLocationAccessible(glm::vec2{ centerOfPlayer.x , centerOfPlayer.y - m_pModel->GetTileSize() }))//up
	{
		newPos.y = static_cast<float> (std::max(static_cast<int>(newPos.y), static_cast<int>(centerOfPlayer.y / tileSize) * tileSize));
	}

	if (!m_pModel->IsTileAtLocationAccessible(glm::vec2{ centerOfPlayer.x , centerOfPlayer.y + m_pModel->GetTileSize() }))//down
	{
		newPos.y = static_cast<float> (std::min(static_cast<int>(newPos.y), static_cast<int>(centerOfPlayer.y / tileSize) * tileSize));
	}

		//if (m_pModel->IsPlayerAllowedAtLocation(newPos))
	{
		pOwner->SetPosition(newPos);
	}

}
