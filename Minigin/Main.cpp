#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif


#include "EllipticalMoveComponent.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Scene.h"
#include "FPSCalcComponent.h"
#include "TextureComponent.h"
#include "ControllerInputHandler.h"
#include "InputManager.h"
#include "moveCommand.h"
#include "command.h"
dae::Scene* pScene;

#define PACMAN_CONTROLLER_ID 0
#define GHOST_CONTROLLER_ID 1


MoveParameters GetLeftThumbValuesFromController(unsigned int controllerID)
{
	const auto& cih{ ControllerInputHandler::GetInstance() };
	const auto& value = MoveParameters(cih.GetDirection(controllerID), cih.GetSpeed(controllerID), cih.GetAcceleration(controllerID));
	return value;
}

MoveParameters GetLeftThumbValuesFromPacmanController()
{
	return GetLeftThumbValuesFromController(PACMAN_CONTROLLER_ID);
 }
MoveParameters GetLeftThumbValuesFromGhostController()
{
	return GetLeftThumbValuesFromController(GHOST_CONTROLLER_ID);
 }

MoveParameters GetKeyUpMoveParameters()
{
	return {{0.f,1.f}, 1.f, 0.f};
}

void load()
{
	pScene = &dae::SceneManager::GetInstance().CreateScene("Demo");
	auto titleObj{ dae::GameObject::Create() };
	auto backgroundObj {dae::GameObject::Create()};
	auto logoObj{ dae::GameObject::Create() };
	auto pacmanObj{ dae::GameObject::Create() };
	auto ghostObj{ dae::GameObject::Create() };
	auto fpsObj{ dae::GameObject::Create() };

	auto& cih = ControllerInputHandler::GetInstance();


	const auto pacmanMoveComp = std::make_shared<dae::MoveComponent>();
	pacmanObj->AddComponent(pacmanMoveComp);
	std::shared_ptr<Command>  pLeftJoystickCommandPacMan = std::make_shared<moveCommand>(pacmanMoveComp, GetLeftThumbValuesFromPacmanController);
	std::shared_ptr<Command> pMoveUpCommand = std::make_shared<moveCommand>(pacmanMoveComp, []() {return MoveParameters{ {0.f,1.f}, 1.f, 0.f }; });
	std::shared_ptr<Command> pMoveDownCommand = std::make_shared<moveCommand>(pacmanMoveComp, []() {return MoveParameters{ {0.f,-1.f}, 1.f, 0.f }; });

	const auto ghostMoveComp = std::make_shared<dae::MoveComponent>();
	ghostObj->AddComponent(ghostMoveComp);
	std::shared_ptr<Command> pLeftJoystickCommandGhost = std::make_shared<moveCommand>(ghostMoveComp, GetLeftThumbValuesFromGhostController);

	//Bind Pacman controls
	cih.AddCommand(PACMAN_CONTROLLER_ID, ControllerButton::LeftJoystick, pLeftJoystickCommandPacMan);
	cih.AddCommand(PACMAN_CONTROLLER_ID, ControllerButton::ButtonY, pMoveUpCommand);
	cih.AddCommand(PACMAN_CONTROLLER_ID, ControllerButton::ButtonA, pMoveDownCommand);

	//Bind Ghost controls
	cih.AddCommand(GHOST_CONTROLLER_ID, ControllerButton::LeftJoystick, pLeftJoystickCommandGhost);

	const auto background = std::make_shared<TextureComponent>();
	background->SetTexture("background.tga");
	backgroundObj->AddComponent(background);

	const auto logo = std::make_shared<TextureComponent>();
	logo->SetTexture("logo.tga");
	logoObj->AddComponent(logo);
	logoObj->SetPosition( 216, 180);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	const auto textComponent = std::make_shared<dae::TextComponent>( "Programming 4 Assignment", font);
	titleObj->AddComponent(textComponent);
	titleObj->SetPosition( 80, 20);

	auto fontFPS = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto fpsCounter = std::make_shared<dae::FPSCalcComponent>();
	fpsObj->AddComponent(fpsCounter);
	const auto fpsText = std::make_shared<dae::TextComponent>(fpsCounter, fontFPS);
	fpsObj->SetPosition( 10, 15);
	fpsText->SetColor({ 255,255,0 });
	fpsObj->AddComponent(fpsText);


	const auto pacmanComp = std::make_shared<TextureComponent>();
	pacmanComp->SetTexture("pacman.png");
	pacmanObj->AddComponent(pacmanComp);
	pacmanObj->SetPosition({ 264,250 });

	const auto ghostTextureComp = std::make_shared<TextureComponent>();
	ghostTextureComp->SetTexture("ghost-pink.png");
	ghostObj->AddComponent(ghostTextureComp);
	ghostObj->SetPosition({ 348,250 });
	//ghostObj->SetParent(pacmanObj);

	pScene->Add(backgroundObj);
	pScene->Add(titleObj);
	pScene->Add(logoObj);
	pScene->Add(pacmanObj);
	pScene->Add(ghostObj);
	pScene->Add(fpsObj);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}