#pragma once
#include "ActorMoveComponent.h"
#include "GameBoardModel.h"
#include "GameState.h"
#include "MoveCommand.h"
#include "StartGameCommand.h"

class SceneFactory : public dae::Singleton<SceneFactory>
{
public:
	SceneFactory();

	std::shared_ptr<dae::GameObject> BuildGhost(int index, dae::Textures textureId,
	                                            const std::shared_ptr<dae::GhostMoveBehavior>& chaseBehavior,
	                                            const std::shared_ptr<dae::GameObject>& pacmanObj,
	                                            const std::shared_ptr<dae::GameBoardModel>& pBoardModel,
	                                            const std::shared_ptr<dae::GameState>& pGameState, 
												const std::shared_ptr<dae::ActorMoveComponent>& pMoveComponent = nullptr);

	void LoadGameScene(dae::GameMode gameMode);
	void LoadMainMenuScene();
};

