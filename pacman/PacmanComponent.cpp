#include "PacmanComponent.h"
#include "EventType.h"

using namespace dae;

PacmanComponent::PacmanComponent(const std::shared_ptr<Texture2D>& pTexture, const std::shared_ptr<GameBoardModel>& pGameBoardModel)
	: TextureComponent(pTexture)
	, m_pGameBoardModel(pGameBoardModel)
{
}

void PacmanComponent::Update(float)
{
	const auto pOwner = GetOwner();
	const auto position = pOwner->GetPosition();

	if (position != m_previousPosition)
	{
		const auto centerOffset = m_pGameBoardModel->GetTileSize() / 2;
		const auto centerOfActor = glm::vec2{ position.x + centerOffset, position.y + centerOffset };

		switch (m_pGameBoardModel->GetTileValue(centerOfActor))
		{
		case TileValue::Pill:
			m_pGameBoardModel->ChangeTileValue(centerOfActor, TileValue::Path);
			EventManager::Publish(Event::Create(EventType::SMALL_PICKUP, pOwner));
			break;
		case TileValue::Boost:
			m_pGameBoardModel->ChangeTileValue(centerOfActor, TileValue::Path);
			EventManager::Publish(Event::Create(EventType::POWER_UP, pOwner));
			break;
		}
		m_previousPosition = position;
	}
}

