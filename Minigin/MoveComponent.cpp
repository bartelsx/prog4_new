#include "MoveComponent.h"

void dae::MoveComponent::Update(float deltaTime)
{
	const auto& owner = GetOwner();
	const auto direction = glm::vec2{ m_Direction.x, -m_Direction.y };
	const auto currentPos = owner->GetPosition();

	glm::vec2 newPosition = glm::vec2{
		std::min(640.f-28, std::max(0.f, currentPos.x + 100 * deltaTime * m_Speed * direction.x)),
		std::min(480.f-28, std::max(0.f, currentPos.y + 100 * deltaTime * m_Speed * direction.y))
	};
	owner->SetPosition(newPosition);
}
