#pragma once
#include <array>

#include "BaseComponent.h"
#include "GameBoardModel.h"
#include "MoveCommand.h"
#include "rapidjson/document.h"

namespace dae
{
	class TextureManager;

	class GameBoardComponent : public dae::BaseComponent
	{
	public:
		GameBoardComponent(const std::shared_ptr<GameBoardModel>& pModel, const std::shared_ptr<TextureManager>& pTextureManager);
		~GameBoardComponent() override = default;
		GameBoardComponent(const GameBoardComponent& other) = delete;
		GameBoardComponent(GameBoardComponent&& other) = delete;
		GameBoardComponent& operator=(const GameBoardComponent& other) = delete;
		GameBoardComponent& operator=(GameBoardComponent&& other) = delete;

		void Render(bool isDirty) override;

	private:
		std::shared_ptr<GameBoardModel> m_pModel;
		std::array<std::shared_ptr<Texture2D>, 4> m_pTextures{};
	};
}

