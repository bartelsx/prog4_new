#include "ActorMoveComponent.h"

#include "EventType.h"

using namespace dae;


ActorMoveComponent::ActorMoveComponent( std::shared_ptr<GameBoardModel> pModel)
	: m_pModel(pModel)
{
}

void ActorMoveComponent::Update(float deltaTime)
{
	auto pOwner = GetOwner();
	auto currentPos = pOwner->GetPosition();
	auto newPos = CalculateNewPos(pOwner->GetPosition(), deltaTime);
	auto tileSize = m_pModel->GetTileSize();

	glm::vec2 centerOfPlayer{ newPos.x +tileSize / 2, newPos.y + tileSize / 2 };

	if (! m_pModel->IsTileAtLocationAccessible(glm::vec2{centerOfPlayer.x-tileSize, centerOfPlayer.y}))//left
	{
		newPos.x = std::max(newPos.x, static_cast<float> (static_cast<int>(centerOfPlayer.x / tileSize) * tileSize ));
	}


	if (!m_pModel->IsTileAtLocationAccessible(glm::vec2{ centerOfPlayer.x + tileSize, centerOfPlayer.y }))//right
	{
		newPos.x = std::min(newPos.x, static_cast<float> (static_cast<int>(centerOfPlayer.x / tileSize) * tileSize));
	}

	if (!m_pModel->IsTileAtLocationAccessible(glm::vec2{ centerOfPlayer.x , centerOfPlayer.y - tileSize }))//up
	{
		newPos.y = std::max(newPos.y, static_cast<float> (static_cast<int>(centerOfPlayer.y / tileSize) * tileSize));
	}

	if (!m_pModel->IsTileAtLocationAccessible(glm::vec2{ centerOfPlayer.x , centerOfPlayer.y + tileSize }))//down
	{
		newPos.y = std::min(newPos.y, static_cast<float> (static_cast<int>(centerOfPlayer.y / tileSize) * tileSize));
	}

	if (newPos != currentPos)
	{
		pOwner->SetPosition(newPos);
	}
}
