#include "StartGameCommand.h"

#include "EventType.h"
#include "SceneFactory.h"
#include "SceneId.h"
#include "SceneManager.h"

dae::StartGameCommand::StartGameCommand(GameMode gameMode)
	: m_GameMode(gameMode)
{}

void dae::StartGameCommand::Execute()
{
	SceneFactory::GetInstance().LoadGameScene(m_GameMode);
	SceneManager::GetInstance().SetCurrentScene(SceneId::GAMEBOARD);
	EventManager::Publish(EventType::GAME_START);
}

void dae::StartGameCommand::Release()
{
}
