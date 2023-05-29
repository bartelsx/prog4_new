#include "GhostMoveComponent.h"

#include "GhostMoveBehavior.h"

using namespace dae;

GhostMoveComponent::GhostMoveComponent(const std::shared_ptr<GhostMoveBehavior>& chaseBehavior, const std::shared_ptr<GhostMoveBehavior>& fleeBehavior, const std::shared_ptr<GameBoardModel>& pModel)
	:ActorMoveComponent(pModel)
	, m_pChaseBehavior{ chaseBehavior }
	, m_pFleeBehavior{fleeBehavior}
	, m_pCurrentBehavior{ chaseBehavior }
{

}

glm::vec2 GhostMoveComponent::CalculateNewPos(glm::vec2 currentPos, float deltaTime) const
{
	auto pos = m_pCurrentBehavior->GetNextLocation(currentPos, deltaTime);

	return pos;
}

void GhostMoveComponent::HandleEvent(const Event& event)
{
	switch (event.GetType())
	{
	case EventType::BOOST_PICKUP:
		m_pCurrentBehavior = m_pFleeBehavior;
		break;
	case EventType::END_BOOST:
		m_pCurrentBehavior = m_pChaseBehavior;
		break;
	case EventType::ENEMY_DIED:
		auto e = dynamic_cast<const EventWithPayload<std::shared_ptr<GameObject>>&>(event);
		if (e.GetData() == GetOwner())
		{
			m_pCurrentBehavior = m_pChaseBehavior;
		}
		//break;
	}
}
