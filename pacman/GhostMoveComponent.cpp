#include "GhostMoveComponent.h"

#include "GhostMoveBehavior.h"

using namespace dae;

GhostMoveComponent::GhostMoveComponent(const std::shared_ptr<GhostMoveBehavior>& behavior, const std::shared_ptr<GameBoardModel>& pModel)
	:ActorMoveComponent(pModel)
	, m_pBehavior{ behavior }
{}

glm::vec2 GhostMoveComponent::CalculateNewPos(glm::vec2 currentPos, float deltaTime) const
{
	auto pos = m_pBehavior->GetNextLocation(currentPos, deltaTime);
	return pos;
}
