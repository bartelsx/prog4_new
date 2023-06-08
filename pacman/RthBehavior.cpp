#include "RthBehavior.h"

using namespace dae;

std::shared_ptr<RthBehavior> RthBehavior::Create(const std::shared_ptr<GameBoardModel>& pBoardModel, const std::shared_ptr<GameObject>& pGhostObj, const glm::vec2& homeLocation)
{
	return std::shared_ptr<RthBehavior>(new RthBehavior(pBoardModel, pGhostObj, homeLocation));
}

RthBehavior::RthBehavior(const std::shared_ptr<GameBoardModel>& pBoardModel, const std::shared_ptr<GameObject>& pGhostObj, const glm::vec2& homeLocation)
	: m_pBoardModel{ pBoardModel }
	, m_pGhostObj{ pGhostObj }
	, m_HomeLocation{ homeLocation }
{

	m_pPathFinder = std::make_unique<PathFinder>(m_pBoardModel);
}

glm::vec2 RthBehavior::GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime)
{
	if (m_CalculatedPath.empty())
	{
		const auto startIdx = m_pBoardModel->GetIdx(currentGhostLoc, true);
		const auto targetIdx = m_pBoardModel->GetIdx(m_HomeLocation, false);

		m_CalculatedPath = m_pPathFinder->FindPath(startIdx, targetIdx, {});

		if (m_CalculatedPath.empty())
		{
			if (!m_pGhostObj.expired())
			{
				EventManager::Publish(EventType::REACHED_HOME, m_pGhostObj.lock());

			}
			m_CalculatedPath.clear();
			return m_HomeLocation;
		}

		m_TraveledDistance = 0;
	}

	m_TraveledDistance += 100 * m_Speed * deltaTime;
	const int tileSize = m_pBoardModel->GetTileSize();

	int idx = int(m_TraveledDistance) / tileSize;

	const int pathSize = int(m_CalculatedPath.size());
	idx = std::min(idx, pathSize - 2);

	const float remaining = (pathSize - 1 - idx) * static_cast<float>(tileSize);
	float distance = m_TraveledDistance - static_cast<float>(idx * tileSize);

	distance = std::min(remaining, distance);

	const auto nextCellLoc = m_pBoardModel->GetOffset(m_CalculatedPath[idx + 1]);
	const auto prevCellLoc = m_pBoardModel->GetOffset(m_CalculatedPath[idx + 1]);

	const auto newX = prevCellLoc.x + (nextCellLoc.x < prevCellLoc.x ? -distance : nextCellLoc.x > prevCellLoc.x ? distance : 0);
	const auto newY = prevCellLoc.y + (nextCellLoc.y < prevCellLoc.y ? -distance : nextCellLoc.y > prevCellLoc.y ? distance : 0);

	if (abs(newX - m_HomeLocation.x) + abs(newY - m_HomeLocation.y) < 4)
	{
		if (!m_pGhostObj.expired())
		{
			EventManager::Publish(EventType::REACHED_HOME, m_pGhostObj.lock());

		}
		m_CalculatedPath.clear();
		return m_HomeLocation;
	}

	return glm::vec2{ newX,newY };


}


