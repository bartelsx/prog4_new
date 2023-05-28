#pragma once
#include "ActorComponent.h"
#include "GameBoardModel.h"
#include "TextureComponent.h"

namespace dae
{

	class PacmanComponent :	public ActorComponent
	{
	public:
		~PacmanComponent() = default;
		PacmanComponent(const PacmanComponent& other) = delete;
		PacmanComponent(PacmanComponent&& other) = delete;
		PacmanComponent& operator=(const PacmanComponent& other) = delete;
		PacmanComponent& operator=(PacmanComponent&& other) = delete;

		static std::shared_ptr<PacmanComponent> Create(const std::shared_ptr<dae::Texture2D>& pTexture, const std::shared_ptr<GameBoardModel>& pGameBoardModel)
		{
			auto ptr = std::shared_ptr<PacmanComponent>(new PacmanComponent(pTexture, pGameBoardModel));

			EventManager::Subscribe(EventType::BOOST_PICKUP, ptr);
			EventManager::Subscribe(EventType::FRUIT_PICKUP, ptr);
			EventManager::Subscribe(EventType::RESET_LEVEL, ptr);

			return ptr;
		}

		void Update(float deltaTime) override;

	private:
		PacmanComponent(const std::shared_ptr<dae::Texture2D>& pTexture, const std::shared_ptr<GameBoardModel>& pGameBoardModel);
		std::shared_ptr<GameBoardModel> m_pGameBoardModel;
		glm::vec2 m_previousPosition{};
		std::shared_ptr<PacmanComponent> GetPtr();
	};
}

