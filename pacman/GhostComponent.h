#pragma once
#include "ActorComponent.h"
#include "GameState.h"

namespace dae
{

	class GhostComponent : public ActorComponent
	{
	public:
		static std::shared_ptr<GhostComponent> Create(const std::shared_ptr<Texture2D>& pTexture, const std::shared_ptr<GameState>& pGameState) 
		{
			auto ptr = std::shared_ptr<GhostComponent>(new GhostComponent(pTexture, pGameState));
			EventManager::Subscribe(EventType::RESET_LEVEL, ptr);
			EventManager::Subscribe(EventType::BOOST_PICKUP, ptr);
			EventManager::Subscribe(EventType::END_BOOST, ptr);
			return ptr;
		}

		void Update(float deltaTime) override;
		void HandleEvent(const Event& event) override;

	private:
		GhostComponent(const std::shared_ptr<Texture2D>& pTexture, const std::shared_ptr<GameState>& pGameState)
		: ActorComponent(ActorType::Ghost, pTexture)
		, m_pGameState(pGameState)
		{}

		std::shared_ptr<GameState> m_pGameState;

		bool m_wasColliding{};
	};
}
