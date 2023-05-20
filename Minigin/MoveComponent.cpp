#include "MoveComponent.h"

using namespace dae;

glm::vec2 MoveComponent::CalculateNewPos(glm::vec2 currentPos, float deltaTime) const
{
	const auto direction = glm::vec2{ m_Direction.x, -m_Direction.y };

	const glm::vec2 newPosition = glm::vec2{
		std::min(1024.f-28, std::max(0.f, currentPos.x + 100 * deltaTime * m_Speed * direction.x)),
		std::min(768.f-28, std::max(0.f, currentPos.y + 100 * deltaTime * m_Speed * direction.y))
	};

	return newPosition;
}
void MoveComponent::Update(float deltaTime)
{
	const auto& owner = GetOwner();
	owner->SetPosition(CalculateNewPos(owner->GetPosition(), deltaTime));
}
