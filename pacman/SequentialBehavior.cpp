#include "SequentialBehavior.h"

using namespace dae;

std::shared_ptr<SequentialBehavior> SequentialBehavior::Create()
{
	return std::shared_ptr<SequentialBehavior>(new SequentialBehavior());
}

void SequentialBehavior::Add(const std::shared_ptr<GhostMoveBehavior>& pBehavior, float duration)
{
	std::pair<std::shared_ptr<GhostMoveBehavior>, float> item = std::make_pair(pBehavior, duration);
	m_Behaviors.emplace_back(item);
}

glm::vec2 SequentialBehavior::GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime)
{
	if (!m_Behaviors.empty())
	{
		if (m_RemainingTime <= 0.f)
		{
			++m_BehaviorIdx;
			if (m_BehaviorIdx >= m_Behaviors.size())
			{
				m_BehaviorIdx = 0;
			}
			m_RemainingTime = m_Behaviors[m_BehaviorIdx].second;
		}

		m_RemainingTime -= deltaTime;
		return m_Behaviors[m_BehaviorIdx].first->GetNextLocation(currentGhostLoc, deltaTime);
	}
	return currentGhostLoc;
}
