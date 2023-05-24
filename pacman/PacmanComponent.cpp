#include "PacmanComponent.h"
#include "EventType.h"

using namespace dae;

PacmanComponent::PacmanComponent(const std::shared_ptr<Texture2D>& pTexture, const std::shared_ptr<GameBoardModel>& pGameBoardModel)
	: ActorComponent(ActorType::Pacman, pTexture)
	, m_pGameBoardModel(pGameBoardModel)
{
}

std::shared_ptr<PacmanComponent> PacmanComponent::GetPtr()
{
	return std::dynamic_pointer_cast<PacmanComponent>(shared_from_this());
}

void PacmanComponent::Update(float)
{
	const auto pOwner = GetOwner();
	const auto position = pOwner->GetPosition();

	if (position != m_previousPosition)
	{
		const auto centerOffset = m_pGameBoardModel->GetTileSize() / 2;
		const auto centerOfActor = glm::vec2{ position.x + centerOffset, position.y + centerOffset };
		const std::shared_ptr<PacmanComponent> ptr = GetPtr();

		switch (m_pGameBoardModel->GetTileValue(centerOfActor))
		{
		case TileValue::Pill:
			m_pGameBoardModel->ChangeTileValue(centerOfActor, TileValue::Path);
			Notify(Event(EventType::PILL_PICKUP));
			break;
		case TileValue::Boost:
			m_pGameBoardModel->ChangeTileValue(centerOfActor, TileValue::Path);
			Notify(Event(EventType::BOOST_PICKUP));
			break;
		}
		m_previousPosition = position;
	}
}

