#include "MoveToPacmanComponent.h"

#include "ActorComponent.h"

using namespace dae;

glm::vec2 MoveToPacmanComponent::CalculateNewPos(glm::vec2 currentPos, float /*deltaTime*/) const
{
	//glm::vec2 vectorToPacman{ m_PacmanPosition.x - currentPos.x, m_PacmanPosition.y - currentPos.y };
	//auto factor = 100.f * deltaTime / std::sqrtf(vectorToPacman.x * vectorToPacman.x + vectorToPacman.y * vectorToPacman.y);

	//glm::vec2 newPosition{vectorToPacman.x * factor, vectorToPacman.y * factor};
	//return newPosition;

	return currentPos;
}

void MoveToPacmanComponent::Notify(const Event& , const Subject& )
{
	//auto ev = dynamic_cast<EventWithPayload<std::shared_ptr<ActorComponent>>&>(event);

	//const auto pOtherActor = ev.GetData();

	//if (pOtherActor->GetType() == ActorType::Pacman)
	//{
	//	m_PacmanPosition = pOtherActor->GetPosition();
	//}
}
