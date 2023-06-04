#pragma once
#include "ActorComponent.h"
#include "GameState.h"

namespace dae
{

	class GhostComponent : public ActorComponent
	{
	public:
		static std::shared_ptr<GhostComponent> Create(const std::shared_ptr<GameState>& pGameState) 
		{
			auto ptr = std::shared_ptr<GhostComponent>(new GhostComponent(pGameState));
			return ptr;
		}

		void Update(float deltaTime) override;

	private:
		GhostComponent(const std::shared_ptr<GameState>& pGameState)
		: ActorComponent(ActorType::Ghost)
		, m_pGameState(pGameState)
		{}

		std::shared_ptr<Texture2D> m_pScaredTexture;
		std::shared_ptr<GameState> m_pGameState;
		bool m_IsScared{};
		bool m_WasColliding{};
	};
}
