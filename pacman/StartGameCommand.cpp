#include "StartGameCommand.h"

#include "EventType.h"
#include "SceneId.h"
#include "SceneManager.h"

dae::StartGameCommand::StartGameCommand(GameMode )
{

}

void dae::StartGameCommand::Execute()
{
	SceneManager::GetInstance().SetCurrentScene(SceneId::GAMEBOARD);
	EventManager::Publish(EventType::GAME_START);
}

void dae::StartGameCommand::Release()
{
}
