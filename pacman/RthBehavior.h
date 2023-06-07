#pragma once
#include "GhostMoveBehavior.h"
#include "PathFinder.h"

namespace dae
{
	class RthBehavior : public GhostMoveBehavior
	{
	public:
		~RthBehavior() override = default;
		RthBehavior(const RthBehavior& other) = delete;
		RthBehavior(RthBehavior&& other) = delete;
		RthBehavior& operator=(const RthBehavior& other) = delete;
		RthBehavior& operator=(RthBehavior&& other) = delete;

		static std::shared_ptr<RthBehavior> Create(const std::shared_ptr<GameBoardModel> pBoardModel, const std::shared_ptr<GameObject>pGhostObj, const glm::vec2& homeLocation);
		glm::vec2 GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime) override;
		
	private:
		RthBehavior(const std::shared_ptr<GameBoardModel> pBoardModel, const std::shared_ptr<GameObject>pGhostObj, const glm::vec2& homeLocation);

		const std::shared_ptr<GameBoardModel>& m_pBoardModel;
		const std::shared_ptr<GameObject>& m_pGhostObj;
		glm::vec2 m_HomeLocation;

		std::unique_ptr<PathFinder> m_pPathFinder;
		std::vector<int> m_CalculatedPath{};
		float m_TraveledDistance{};

		const float m_Speed{2.5f};

	};
}
