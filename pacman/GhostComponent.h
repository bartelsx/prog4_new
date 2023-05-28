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
			return std::shared_ptr<GhostComponent>(new GhostComponent(pTexture, pGameState));
		}

		void Update(float deltaTime) override;

	private:
		GhostComponent(const std::shared_ptr<Texture2D>& pTexture, const std::shared_ptr<GameState>& pGameState)
		: ActorComponent(ActorType::Ghost, pTexture)
		, m_pGameState(pGameState)
		{}

		std::shared_ptr<GhostComponent> GetPtr() { return std::dynamic_pointer_cast<GhostComponent>(shared_from_this()); }
		std::shared_ptr<GameState> m_pGameState;

		bool m_wasColliding{};
	};
}
