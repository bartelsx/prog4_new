#include "GhostComponent.h"

#include <iostream>

#include "EventType.h"

using namespace dae;

void GhostComponent::Update(float deltaTime)
{
	ActorComponent::Update(deltaTime);

	//Check collision with Pacman
	auto myLocation = GetOwner()->GetPosition();
	auto pacmanLoc = m_pGameState->GetPacmanLocation();

	if (std::abs(myLocation.x - pacmanLoc.x) < 8 && std::abs(myLocation.y - pacmanLoc.y) < 8)
	{
		// COLLISION !!!
		if (!m_wasColliding)
		{
			std::cout << "COLLISION !!!\n";
			EventManager::Publish(EventType::ACTOR_DIED);
		}
		m_wasColliding = true;
	}
	else
	{
		m_wasColliding = false;
	}
}

void GhostComponent::HandleEvent(const Event& event)
{
	ActorComponent::HandleEvent(event);

	switch (event.GetType())
	{
	case EventType::BOOST_PICKUP:
		std::cout << "BOOST_PICKUP\n";
		break;
	case EventType::END_BOOST:
		std::cout << "END_BOOST\n";
		break;
	}
}

