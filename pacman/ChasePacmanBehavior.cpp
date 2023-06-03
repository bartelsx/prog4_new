
#include "ChasePacmanBehavior.h"
#include <vector>
#include "GameBoardModel.h"
#include "TargetSelector.h"

struct PathNode;

using namespace dae;

ChasePacmanBehavior::ChasePacmanBehavior(const std::shared_ptr<GameObject>& pPacmanObj, const std::shared_ptr<GameBoardModel>& pBoardModel, const std::shared_ptr<TargetSelector>& pTargetSelector)
	: GhostMoveBehavior()
	, m_pPacmanObj(pPacmanObj)
	, m_pBoardModel(pBoardModel)
	, m_pTargetSelector(pTargetSelector)

{
	m_pathFinder = std::make_shared<PathFinder>(pBoardModel);
}

glm::vec2 ChasePacmanBehavior::GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime)
{
	const float centerOffset = m_pBoardModel->GetTileSize()/2.f;
	auto ghostCenter= glm::vec2{ currentGhostLoc.x + centerOffset, currentGhostLoc.y + centerOffset };
	auto pacmanCenter{ m_pPacmanObj->GetPosition() };
	pacmanCenter = glm::vec2{ pacmanCenter.x + centerOffset, pacmanCenter.y + centerOffset };

	auto startIdx = m_pBoardModel->GetIdx(ghostCenter);
	int pacmanIdx = m_pBoardModel->GetIdx(pacmanCenter);
	auto targetIdx = m_pTargetSelector->GetTarget(pacmanIdx, m_pBoardModel);

	auto startIt = std::ranges::find(m_PrevPath, startIdx);
	auto targetIt = std::ranges::find(m_PrevPath, targetIdx);

	//If both target and ghost are on the previous calculated path, reuse the previous calculated path
	if (startIt == m_PrevPath.end() || targetIt == m_PrevPath.end())
	{
		if (pacmanIdx == targetIdx)
		{
			m_PrevPath = m_pathFinder->FindPath(startIdx, targetIdx, {});
		}
		else
		{
			m_PrevPath = m_pathFinder->FindPath(startIdx, targetIdx, {pacmanIdx});
		}

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

	auto nextCell = *(startIt+1);
	auto distance = deltaTime * 100 * m_Speed;
	auto nextCellLoc = m_pBoardModel->GetOffset(nextCell);

	auto newX = currentGhostLoc.x + (nextCellLoc.x < currentGhostLoc.x ? -distance : nextCellLoc.x > currentGhostLoc.x ? distance : 0);
	auto newY = currentGhostLoc.y + (nextCellLoc.y < currentGhostLoc.y ? -distance : nextCellLoc.y > currentGhostLoc.y ? distance : 0);

	return glm::vec2{ newX,newY };
}
