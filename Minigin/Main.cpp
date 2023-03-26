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
#include "KeyboardInputHandler.h"
#include "MoveCommand.h"
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

	auto& kih = dae::KeyboardInputHandler::GetInstance();
	auto& cih = ControllerInputHandler::GetInstance();

	//Commands that control Pacman
	const auto pacmanMoveComp = std::make_shared<dae::MoveComponent>();
	pacmanObj->AddComponent(pacmanMoveComp);
	std::shared_ptr<Command>  pLeftJoystickCommandPacMan = std::make_shared<MoveCommand>(pacmanMoveComp, GetLeftThumbValuesFromPacmanController);
	std::shared_ptr<Command> pMoveUpCommandPacman = std::make_shared<MoveCommand>(pacmanMoveComp, []() {return MoveParameters{ {0.f,1.f}, 1.f, 0.f }; });
	std::shared_ptr<Command> pMoveDownCommandPacman = std::make_shared<MoveCommand>(pacmanMoveComp, []() {return MoveParameters{ {0.f,-1.f}, 1.f, 0.f }; });
	std::shared_ptr<Command> pMoveLeftCommandPacman = std::make_shared<MoveCommand>(pacmanMoveComp, []() {return MoveParameters{ {-1.f,0.f}, 1.f, 0.f }; });
	std::shared_ptr<Command> pMoveRightCommandPacman = std::make_shared<MoveCommand>(pacmanMoveComp, []() {return MoveParameters{ {1.f,0.f}, 1.f, 0.f }; });

	//Commands that control Ghost
	const auto ghostMoveComp = std::make_shared<dae::MoveComponent>();
	ghostObj->AddComponent(ghostMoveComp);
	std::shared_ptr<Command> pLeftJoystickCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, GetLeftThumbValuesFromGhostController);
	std::shared_ptr<Command> pMoveUpCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, []() {return MoveParameters{ {0.f,1.f}, 2.f, 0.f }; });
	std::shared_ptr<Command> pMoveDownCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, []() {return MoveParameters{ {0.f,-1.f}, 2.f, 0.f }; });
	std::shared_ptr<Command> pMoveLeftCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, []() {return MoveParameters{ {-1.f,0.f}, 2.f, 0.f }; });
	std::shared_ptr<Command> pMoveRightCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, []() {return MoveParameters{ {1.f,0.f}, 2.f, 0.f }; });

	//Bind Pacman controls
	//  Joystick
	cih.AddCommand(PACMAN_CONTROLLER_ID, ControllerButton::LeftJoystick, pLeftJoystickCommandPacMan);

	//  Controller buttons
	cih.AddCommand(PACMAN_CONTROLLER_ID, ControllerButton::ButtonY, pMoveUpCommandPacman);
	cih.AddCommand(PACMAN_CONTROLLER_ID, ControllerButton::ButtonA, pMoveDownCommandPacman);
	cih.AddCommand(PACMAN_CONTROLLER_ID, ControllerButton::ButtonX, pMoveLeftCommandPacman);
	cih.AddCommand(PACMAN_CONTROLLER_ID, ControllerButton::ButtonB, pMoveRightCommandPacman);

	//  Keyboard
	kih.AddCommand(SDL_SCANCODE_UP, pMoveUpCommandPacman);
	kih.AddCommand(SDL_SCANCODE_DOWN, pMoveDownCommandPacman);
	kih.AddCommand(SDL_SCANCODE_LEFT, pMoveLeftCommandPacman);
	kih.AddCommand(SDL_SCANCODE_RIGHT, pMoveRightCommandPacman);

	//Bind Ghost controls
	//  Joystick
	cih.AddCommand(GHOST_CONTROLLER_ID, ControllerButton::LeftJoystick, pLeftJoystickCommandGhost);

	//  Controller buttons
	cih.AddCommand(GHOST_CONTROLLER_ID, ControllerButton::ButtonY, pMoveUpCommandGhost);
	cih.AddCommand(GHOST_CONTROLLER_ID, ControllerButton::ButtonA, pMoveDownCommandGhost);
	cih.AddCommand(GHOST_CONTROLLER_ID, ControllerButton::ButtonX, pMoveLeftCommandGhost);
	cih.AddCommand(GHOST_CONTROLLER_ID, ControllerButton::ButtonB, pMoveRightCommandGhost);
	
	//
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