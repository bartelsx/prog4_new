#pragma once
#include "GhostMoveBehavior.h"

namespace dae
{
	class FleeBehavior : public GhostMoveBehavior
	{
	public:
		~FleeBehavior() override = default;
		FleeBehavior(const FleeBehavior& other) = delete;
		FleeBehavior(FleeBehavior&& other) = delete;
		FleeBehavior& operator=(const FleeBehavior& other) = delete;
		FleeBehavior& operator=(FleeBehavior&& other) = delete;

		static std::shared_ptr<FleeBehavior> Create(const std::shared_ptr<GameBoardModel>& pBoardModel)
		{
			return std::shared_ptr<FleeBehavior>(new FleeBehavior(pBoardModel));
		}

		glm::vec2 GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime) override;

	private:
		FleeBehavior(const std::shared_ptr<GameBoardModel>& pBoardModel);
		std::shared_ptr<GameBoardModel> m_pBoardModel;
	};
}
