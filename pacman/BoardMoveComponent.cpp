#include "BoardMoveComponent.h"

using namespace dae;


BoardMoveComponent::BoardMoveComponent(std::shared_ptr<GameBoardModel> pModel) : m_pModel(pModel)
{
}

void BoardMoveComponent::Update(float deltaTime)
{
	auto pOwner = GetOwner();
	auto newPos = CalculateNewPos(pOwner->GetPosition(), deltaTime);

	if (m_pModel->IsPlayerAllowedAtLocation(newPos))
	{
		pOwner->SetPosition(newPos);
	}

}
