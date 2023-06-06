#pragma once
#include "GameBoardModel.h"
#include "GameState.h"
#include "MoveCommand.h"

class SceneFactory : public dae::Singleton<SceneFactory>
{
public:
	SceneFactory();

	std::shared_ptr<dae::GameObject> BuildGhost(int index, dae::Textures textureId,
		const std::shared_ptr<dae::GhostMoveBehavior>& chaseBehavior,
		const std::shared_ptr<dae::GameObject>& pacmanObj,
		const std::shared_ptr<dae::GameBoardModel>& pBoardModel,
		const std::shared_ptr<dae::GameState>& pGameState);

	void LoadGameScene();
	void LoadMainMenuScene();
};

