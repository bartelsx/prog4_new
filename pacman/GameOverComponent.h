#pragma once
#include "TextComponent.h"

namespace dae
{
	class GameOverComponent : BaseComponent
	{
	public:
		~GameOverComponent() override = default;
		GameOverComponent(const GameOverComponent& other) = delete;
		GameOverComponent(GameOverComponent&& other) = delete;
		GameOverComponent& operator=(const GameOverComponent& other) = delete;
		GameOverComponent& operator=(GameOverComponent&& other) = delete;

	private :
		GameOverComponent() = default;
	};
}
