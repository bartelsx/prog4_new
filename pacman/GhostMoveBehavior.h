#pragma once
#include <glm/vec2.hpp>
#include "ActorComponent.h"


struct PathNode;

namespace dae
{
	class GameBoardModel;
	class GameObject;

	class GhostMoveBehavior
	{
	public:
		GhostMoveBehavior() = default;
		virtual ~GhostMoveBehavior() = default;
		GhostMoveBehavior(const GhostMoveBehavior& other) = delete;
		GhostMoveBehavior(GhostMoveBehavior&& other) = delete;
		GhostMoveBehavior& operator=(const GhostMoveBehavior& other) = delete;
		GhostMoveBehavior& operator=(GhostMoveBehavior&& other) = delete;

		virtual glm::vec2 GetNextLocation(glm::vec2 currentGhostLoc, float deltaTime) = 0;
	};

}

