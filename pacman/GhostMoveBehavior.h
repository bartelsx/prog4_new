#pragma once
#include <glm/vec2.hpp>
#include "ActorComponent.h"


struct PathNode;

namespace dae
{
	class GameBoardModel;
	class GameObject;

	class GhostMoveBehavior : std::enable_shared_from_this<GhostMoveBehavior>
	{
	public:
		virtual ~GhostMoveBehavior() = default;
		GhostMoveBehavior(const GhostMoveBehavior& other) = delete;
		GhostMoveBehavior(GhostMoveBehavior&& other) = delete;
		GhostMoveBehavior& operator=(const GhostMoveBehavior& other) = delete;
		GhostMoveBehavior& operator=(GhostMoveBehavior&& other) = delete;

		virtual glm::vec2 GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime) = 0;

	protected:
		GhostMoveBehavior() = default;
	};

}

