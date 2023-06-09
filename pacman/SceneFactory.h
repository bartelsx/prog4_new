#pragma once
#include "ActorMoveComponent.h"
#include "GameBoardModel.h"
#include "MoveCommand.h"
#include "StartGameCommand.h"

class SceneFactory : public dae::Singleton<SceneFactory>
{
public:
	SceneFactory();

	std::shared_ptr<dae::GameObject> BuildGhost(dae::GameMode gameMode, dae::Textures textureId,
		int index,
		const std::shared_ptr<dae::GhostMoveBehavior>& chaseBehavior,
		const std::shared_ptr<dae::GameObject>& pacmanObj,
		std::shared_ptr<dae::GameObject>& pacWomanObj,
		const std::shared_ptr<dae::GameBoardModel>& pBoardModel,
		const std::shared_ptr<dae::ActorMoveComponent>& pMoveComponent = nullptr) const;

	void LoadGameScene(dae::GameMode gameMode);
	void LoadMainMenuScene();
private:
	int m_PacmanControllerId{ -1 };
};

