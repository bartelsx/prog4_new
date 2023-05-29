#include "FleeBehavior.h"

using namespace dae;

FleeBehavior::FleeBehavior(const std::shared_ptr<GameBoardModel>& pBoardModel)
	: m_pBoardModel{ pBoardModel }
{}

glm::vec2 FleeBehavior::GetNextLocation(glm::vec2 currentGhostLoc, float /*deltaTime*/)
{
	return currentGhostLoc;
}