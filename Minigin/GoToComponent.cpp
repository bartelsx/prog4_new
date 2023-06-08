#include "GoToComponent.h"

using namespace dae;

GoToComponent::GoToComponent(glm::vec2 position)
	: m_Position(position)
{}

std::shared_ptr<GoToComponent> GoToComponent::Create(glm::vec2 position)
{
	return std::shared_ptr<GoToComponent>(new GoToComponent(position));
}

void GoToComponent::Update(float )
{
	GetOwner()->SetPosition(m_Position);
}


