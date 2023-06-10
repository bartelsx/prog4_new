#include "StartGameCommand.h"

#include "EventType.h"
#include "KeyboardInputHandler.h"
#include "ControllerInputHandler.h"
#include "SceneFactory.h"
#include "SceneId.h"
#include "SceneManager.h"

dae::StartGameCommand::StartGameCommand(GameMode gameMode)
	: m_GameMode(gameMode)
{}

void dae::StartGameCommand::Execute()
{
	KeyboardInputHandler::GetInstance().Clear();
	ControllerInputHandler::GetInstance().Clear();
	SceneManager::GetInstance().Clear();
	SceneFactory::GetInstance().LoadGameScene(m_GameMode);
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
