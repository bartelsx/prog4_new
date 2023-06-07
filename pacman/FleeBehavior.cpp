#include "FleeBehavior.h"

#include "GameBoardModel.h"
#include "GameState.h"

using namespace dae;

FleeBehavior::FleeBehavior(const std::shared_ptr<GameBoardModel>& pBoardModel, const std::shared_ptr<GameState>& pGameState)
	: m_pBoardModel{ pBoardModel }
	, m_pGameState { pGameState }
{}

int FleeBehavior::CalcDistance(int candidateCol, int candidateRow, int pacmanCol, int pacmanRow) const
{
	if (candidateRow < 0 || candidateCol >= m_pBoardModel->GetColumns() || candidateRow<0 || candidateCol >= m_pBoardModel->GetRows())
	{
		return 0;
	}

	if (m_pBoardModel->GetTileValue(candidateCol, candidateRow) == TileValue::Wall)
	{
		return 0;
	}

	auto cellIdx = m_pBoardModel->GetIdx(candidateCol, candidateRow);
	if (m_pBoardModel->IsTeleport(cellIdx))
	{
		auto crOtherTeleport = m_pBoardModel->GetColumnRow(m_pBoardModel->GetPairedTeleport(cellIdx));
		return abs(pacmanCol - crOtherTeleport.x) + abs(pacmanRow - crOtherTeleport.y);
	}

	return abs(pacmanCol - candidateCol) + abs(pacmanRow - candidateRow);
}

glm::vec2 FleeBehavior::GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime)
{
	auto crGhost = m_pBoardModel->GetColumnRow(glm::vec2{currentGhostLoc.x+8, currentGhostLoc.y+8});
	auto crPacman = m_pBoardModel->GetColumnRow(glm::vec2{ m_pGameState->GetPacmanLocation().x + 8, m_pGameState->GetPacmanLocation().y + 8 });

	int maxDist = 0;
	int dist;
	glm::vec2 direction{};

	//Try the four neighbors of the ghost's current cell
	if ((dist = CalcDistance(crGhost.x-1, crGhost.y, crPacman.x, crPacman.y)) > maxDist)
	{
		maxDist = dist;
		direction = glm::ivec2(-1,0);
	}

	if ((dist = CalcDistance(crGhost.x+1, crGhost.y, crPacman.x, crPacman.y)) > maxDist)
	{
		maxDist = dist;
		direction = glm::ivec2(1,0);
	}

	if ((dist = CalcDistance(crGhost.x, crGhost.y-1, crPacman.x, crPacman.y)) > maxDist)
	{
		maxDist = dist;
		direction = glm::ivec2(0,-1);
	}

	if ((dist = CalcDistance(crGhost.x, crGhost.y+1, crPacman.x, crPacman.y)) > maxDist)
	{
		maxDist = dist;
		direction = glm::ivec2(0,1);
	}

	//auto ghostCell = m_pBoardModel->GetIdx(currentGhostLoc, true);
	//if (m_pBoardModel->IsTeleport(ghostCell))
	//{
	//	auto crTeleport = m_pBoardModel->GetColumnRow(m_pBoardModel->GetPairedTeleport(ghostCell));
	//	if (CalcDistance(crTeleport.x, crTeleport.y, crPacman.x, crPacman.y) > maxDist)
	//	{
	//		return m_pBoardModel->GetOffset(crTeleport.x, crTeleport.y);
	//	}
	//}

	const float distance = m_speed * 100 * deltaTime;

	return glm::vec2{currentGhostLoc.x + distance * direction.x, currentGhostLoc.y + distance * direction.y};
}