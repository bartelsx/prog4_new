#include "ActorMoveComponent.h"

#include <iostream>

#include "EventType.h"

using namespace dae;


ActorMoveComponent::ActorMoveComponent( std::shared_ptr<GameBoardModel> pModel)
	: m_pBoardModel(pModel)
{
}

void ActorMoveComponent::Update(float deltaTime)
{
	auto pOwner = GetOwner();
	auto currentPos = pOwner->GetPosition();

	auto currentCellIdx = m_pBoardModel->GetIdx(currentPos, true);

	auto newPos = CalculateNewPos(pOwner->GetPosition(), deltaTime);
	auto tileSize = m_pBoardModel->GetTileSize();

	auto newCellIdx = m_pBoardModel->GetIdx(newPos, true);

	//Teleport?
	if (m_pBoardModel->IsTeleport(newCellIdx) && !m_pBoardModel->IsTeleport(currentCellIdx))
	{
		auto teleportedCell = m_pBoardModel->GetPairedTeleport(newCellIdx);
		pOwner->SetPosition(m_pBoardModel->GetOffset(teleportedCell));
		return;
	}

	//Keep player on path
	glm::vec2 centerOfPlayer{ newPos.x + tileSize / 2, newPos.y + tileSize / 2 };

	if (! m_pBoardModel->IsTileAccessible(glm::vec2{centerOfPlayer.x-tileSize, centerOfPlayer.y}))//left
	{
		newPos.x = std::max(newPos.x, static_cast<float> (static_cast<int>(centerOfPlayer.x / tileSize) * tileSize ));
	}

	if (!m_pBoardModel->IsTileAccessible(glm::vec2{ centerOfPlayer.x + tileSize, centerOfPlayer.y }))//right
	{
		newPos.x = std::min(newPos.x, static_cast<float> (static_cast<int>(centerOfPlayer.x / tileSize) * tileSize));
	}

	if (!m_pBoardModel->IsTileAccessible(glm::vec2{ centerOfPlayer.x , centerOfPlayer.y - tileSize }))//up
	{
		newPos.y = std::max(newPos.y, static_cast<float> (static_cast<int>(centerOfPlayer.y / tileSize) * tileSize));
	}

	if (!m_pBoardModel->IsTileAccessible(glm::vec2{ centerOfPlayer.x , centerOfPlayer.y + tileSize }))//down
	{
		newPos.y = std::min(newPos.y, static_cast<float> (static_cast<int>(centerOfPlayer.y / tileSize) * tileSize));
	}

	if (newPos != currentPos)
	{
		pOwner->SetPosition(newPos);
	}
}
