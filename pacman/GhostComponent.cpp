#include "GhostComponent.h"
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
		if (!m_WasColliding)
		{
			if(m_IsScared)
			{
				EventManager::Publish(EventType::ENEMY_DIED, GetOwner());
				GetOwner()->SetPosition(m_SpawnLocation);
				m_IsScared = false;
			}
			else
			{
				EventManager::Publish(EventType::ACTOR_DIED);
			}
		}
		m_WasColliding = true;
	}
	else
	{
		m_WasColliding = false;
	}
}
//
//void GhostComponent::HandleEvent(const Event& event)
//{
//	ActorComponent::HandleEvent(event);
//
//	switch (event.GetType())
//	{
//	case EventType::BOOST_PICKUP:
//		m_IsScared = true;
//		break;
//	case EventType::END_BOOST:
//		m_IsScared = false;
//		break;
//	}
//}

