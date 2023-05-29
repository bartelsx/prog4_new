#pragma once
#include "ActorComponent.h"
#include "GameState.h"

namespace dae
{

	class GhostComponent : public ActorComponent
	{
	public:
		static std::shared_ptr<GhostComponent> Create(const std::shared_ptr<Texture2D>& pNormalTexture, const std::shared_ptr<Texture2D>& pScaredTexture, const std::shared_ptr<GameState>& pGameState) 
		{
			auto ptr = std::shared_ptr<GhostComponent>(new GhostComponent(pNormalTexture, pScaredTexture, pGameState));
			EventManager::Subscribe(EventType::RESET_LEVEL, ptr);
			EventManager::Subscribe(EventType::BOOST_PICKUP, ptr);
			EventManager::Subscribe(EventType::END_BOOST, ptr);
			EventManager::Subscribe(EventType::ENEMY_DIED, ptr);
			return ptr;
		}

		void Update(float deltaTime) override;
		void HandleEvent(const Event& event) override;

	protected:
		std::shared_ptr<dae::Texture2D> GetTexture() override;

	private:
		GhostComponent(const std::shared_ptr<Texture2D>& pNormalTexture, const std::shared_ptr<Texture2D>& pScaredTexture,  const std::shared_ptr<GameState>& pGameState)
		: ActorComponent(ActorType::Ghost, pNormalTexture)
		, m_pScaredTexture(pScaredTexture)
		, m_pGameState(pGameState)
		{}

		std::shared_ptr<Texture2D> m_pScaredTexture;
		std::shared_ptr<GameState> m_pGameState;
		bool m_IsScared{};
		bool m_WasColliding{};
	};
}
