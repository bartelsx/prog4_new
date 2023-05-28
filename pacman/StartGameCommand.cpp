#include "StartGameCommand.h"

#include "SceneManager.h"

dae::StartGameCommand::StartGameCommand(GameModes )
{

}

void dae::StartGameCommand::Execute()
{
	SceneManager::GetInstance().SetCurrentScene(1);
}

void dae::StartGameCommand::Release()
{
}
