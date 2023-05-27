#pragma once
#include <memory>
#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;

	class GameState
	{
	public:
		GameState() = default;
		~GameState() = default;
		GameState(const GameState& other) = delete;
		GameState(GameState&& other) = delete;
		GameState& operator=(const GameState& other) = delete;
		GameState& operator=(GameState&& other) = delete;

		glm::vec2 GetPacmanLocation();

		void SetPacmanObj(std::shared_ptr<dae::GameObject>& obj);
		std::shared_ptr<dae::GameObject>& GetPacmanObj();
	private:
		std::shared_ptr<dae::GameObject> m_pPacmanObj{};
	};
}

