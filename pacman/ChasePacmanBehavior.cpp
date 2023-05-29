
#include "ChasePacmanBehavior.h"

#include <iostream>
#include <ostream>
#include <vector>

#include "GameBoardModel.h"

struct PathNode;

using namespace dae;

ChasePacmanBehavior::ChasePacmanBehavior(const std::shared_ptr<GameObject>& pPacmanObj, const std::shared_ptr<GameBoardModel>& pBoardModel)
	: GhostMoveBehavior()
	, m_pPacmanObj(pPacmanObj)
	, m_pBoardModel(pBoardModel)

{
	m_pathFinder = std::make_shared<PathFinder>(pBoardModel);
}

glm::vec2 ChasePacmanBehavior::GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime)
{
	const float centerOffset = m_pBoardModel->GetTileSize()/2.f;
	auto ghostCenter= glm::vec2{ currentGhostLoc.x + centerOffset, currentGhostLoc.y + centerOffset };
	auto pacmanCenter{ m_pPacmanObj->GetPosition() };
	pacmanCenter = glm::vec2{ pacmanCenter.x + centerOffset, pacmanCenter.y + centerOffset };

	auto startId = m_pBoardModel->GetIdx(ghostCenter);
	auto targetId = m_pBoardModel->GetIdx(pacmanCenter);

	auto startIt = std::ranges::find(m_PrevPath, startId);
	auto targetIt = std::ranges::find(m_PrevPath, targetId);

	//If both pacman and ghost are on the previous calculated path, reuse the previous calculated path
	if (startIt == m_PrevPath.end() || targetIt == m_PrevPath.end())
	{
		m_PrevPath = m_pathFinder->FindPath(startId, targetId);
		if (m_PrevPath.empty())
		{
			return currentGhostLoc;
		}

		startIt = m_PrevPath.begin();
	}

	if (startIt+1 >= m_PrevPath.end())
	{
		return currentGhostLoc;
	}

	auto target = *(startIt+1);
	auto distance = deltaTime * 100 * m_Speed;
	auto targetLoc = m_pBoardModel->GetOffset(target);
	auto newX = currentGhostLoc.x + (targetLoc.x < currentGhostLoc.x ? -distance : targetLoc.x > currentGhostLoc.x ? +distance : 0);
	auto newY = currentGhostLoc.y + (targetLoc.y < currentGhostLoc.y ? -distance : targetLoc.y > currentGhostLoc.y ? +distance : 0);
	return glm::vec2{ newX,newY };
}
