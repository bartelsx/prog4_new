#include "DelayedBehavior.h"

using namespace dae;

DelayedBehavior::DelayedBehavior(float delay, const std::shared_ptr<GhostMoveBehavior>& pBaseBehavior)
	: GhostMoveBehavior()
	, m_Delay(delay)
	, m_RemainingTime(delay)
	, m_pBaseBehavior(pBaseBehavior)
{
}

glm::vec2 DelayedBehavior::GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime)
{
	if (m_RemainingTime < 0)
	{
		return m_pBaseBehavior->GetNextLocation(currentGhostLoc, deltaTime);
	}
	m_RemainingTime -= deltaTime;
	return currentGhostLoc;
}

void DelayedBehavior::HandleEvent(const Event& event)
{
	if (event.Is(EventType::GAME_START))
	{
		m_RemainingTime = m_Delay;
	}

}