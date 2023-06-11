#include "StartGameCommand.h"

#include "EventType.h"
#include "KeyboardInputHandler.h"
#include "ControllerInputHandler.h"
#include "SceneFactory.h"
#include "SceneManager.h"
#include "Settings.h"

dae::StartGameCommand::StartGameCommand(GameMode gameMode, int level)
	: m_GameMode(gameMode)
	, m_Level(level)
{}

void dae::StartGameCommand::Execute()
{
	KeyboardInputHandler::GetInstance().Clear();
	ControllerInputHandler::GetInstance().Clear();
	SceneManager::GetInstance().Clear();
	SceneFactory::GetInstance().LoadGameScene(m_GameMode, m_Level);
	EventManager::Publish(EventType::GAME_START);
}

void dae::StartGameCommand::Release()
{
}

void dae::MainMenuCommand::Execute()
{
	KeyboardInputHandler::GetInstance().Clear();
	ControllerInputHandler::GetInstance().Clear();
	SceneManager::GetInstance().Clear();
	SceneFactory::GetInstance().LoadMainMenuScene();

}

void dae::HallOfFameCommand::Execute()
{
	KeyboardInputHandler::GetInstance().Clear();
	ControllerInputHandler::GetInstance().Clear();
	SceneManager::GetInstance().Clear();
	SceneFactory::GetInstance().LoadHighScoreScene();
}
