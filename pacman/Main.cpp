
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <SDL.h>
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
#include "PointsComponent.h"


#include "Minigin.h"
#include "SoundSystem.h"
#include "TextureManager.h"
#include "GameBoardComponent.h"

dae::Scene* pScene;

#define PACMAN_CONTROLLER_ID 0
#define GHOST_CONTROLLER_ID 1
#define APP_WIDTH (1024)
#define APP_HEIGHT (768)

MoveParameters GetLeftThumbValuesFromController(unsigned int controllerID)
{
	const auto& cih{ ControllerInputHandler::GetInstance() };
	const auto& value = MoveParameters{ cih.GetDirection(controllerID), cih.GetSpeed(controllerID), cih.GetAcceleration(controllerID) };
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



void Load()
{
	TextureManager textureManager{};

	pScene = &dae::SceneManager::GetInstance().CreateScene("Demo");
	auto titleObj{ dae::GameObject::Create() };
	auto backgroundObj {dae::GameObject::Create()};
	auto logoObj{ dae::GameObject::Create() };
	auto pacmanObj{ dae::GameObject::Create() };
	auto ghos1tObj{ dae::GameObject::Create() };
	auto ghos2tObj{ dae::GameObject::Create() };
	auto ghos3tObj{ dae::GameObject::Create() };
	auto fpsObj{ dae::GameObject::Create() };
	auto pointsPacmanObj{ dae::GameObject::Create() };
	auto livesPacmanObj{ dae::GameObject::Create() };
	auto pointsGhostObj{ dae::GameObject::Create() };
	auto livesGhostObj{ dae::GameObject::Create() };
	auto mapObj{ dae::GameObject::Create() };

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

	std::shared_ptr<Command> pDiePacman = std::make_shared<DieCommand>(pacmanObj);
	std::shared_ptr<Command> pPickUpFruitPacman = std::make_shared<PickUpFruitCommand>(pacmanObj);
	std::shared_ptr<Command> pPickUpSmallPacman = std::make_shared<PickUpSmallCommand>(pacmanObj);
	std::shared_ptr<Command> pPickUpPowerUpPacman = std::make_shared<PickUpPowerUpCommand>(pacmanObj);
	std::shared_ptr<Command> pEnemyDeadPacman = std::make_shared<EnemyDeadCommand>(pacmanObj);

	//Commands that control Ghost
	const auto ghostMoveComp = std::make_shared<dae::MoveComponent>();
	ghos1tObj->AddComponent(ghostMoveComp);
	std::shared_ptr<Command> pLeftJoystickCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, GetLeftThumbValuesFromGhostController);
	std::shared_ptr<Command> pMoveUpCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, []() {return MoveParameters{ {0.f,1.f}, 2.f, 0.f }; });
	std::shared_ptr<Command> pMoveDownCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, []() {return MoveParameters{ {0.f,-1.f}, 2.f, 0.f }; });
	std::shared_ptr<Command> pMoveLeftCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, []() {return MoveParameters{ {-1.f,0.f}, 2.f, 0.f }; });
	std::shared_ptr<Command> pMoveRightCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, []() {return MoveParameters{ {1.f,0.f}, 2.f, 0.f }; });

	std::shared_ptr<Command> pDieGhost = std::make_shared<DieCommand>(ghos1tObj);
	std::shared_ptr<Command> pPickUpFruitGhost = std::make_shared<PickUpFruitCommand>(ghos1tObj);
	std::shared_ptr<Command> pPickUpSmallGhost = std::make_shared<PickUpSmallCommand>(ghos1tObj);
	std::shared_ptr<Command> pPickUpPowerUpGhost = std::make_shared<PickUpPowerUpCommand>(ghos1tObj);
	std::shared_ptr<Command> pEnemyDeadGhost = std::make_shared<EnemyDeadCommand>(ghos1tObj);

	//Bind Pacman controls
	//  Joystick
	cih.AddCommand(PACMAN_CONTROLLER_ID, ControllerButton::LeftJoystick, pLeftJoystickCommandPacMan);

	//  Controller buttons
	cih.AddCommand(PACMAN_CONTROLLER_ID, ControllerButton::ButtonY, pMoveUpCommandPacman);
	cih.AddCommand(PACMAN_CONTROLLER_ID, ControllerButton::ButtonA, pMoveDownCommandPacman);
	cih.AddCommand(PACMAN_CONTROLLER_ID, ControllerButton::ButtonX, pMoveLeftCommandPacman);
	cih.AddCommand(PACMAN_CONTROLLER_ID, ControllerButton::ButtonB, pMoveRightCommandPacman);

	//  Keyboard
	kih.AddCommand(SDL_SCANCODE_W, pMoveUpCommandPacman);
	kih.AddCommand(SDL_SCANCODE_S, pMoveDownCommandPacman);
	kih.AddCommand(SDL_SCANCODE_A, pMoveLeftCommandPacman);
	kih.AddCommand(SDL_SCANCODE_D, pMoveRightCommandPacman);

	kih.AddCommand(SDL_SCANCODE_Z, pDiePacman);
	kih.AddCommand(SDL_SCANCODE_X, pPickUpFruitPacman);
	kih.AddCommand(SDL_SCANCODE_C, pPickUpSmallPacman);
	kih.AddCommand(SDL_SCANCODE_V, pPickUpPowerUpPacman);
	kih.AddCommand(SDL_SCANCODE_B, pEnemyDeadPacman);

	//ghost
	kih.AddCommand(SDL_SCANCODE_Y, pDieGhost);
	kih.AddCommand(SDL_SCANCODE_U, pPickUpFruitGhost);
	kih.AddCommand(SDL_SCANCODE_I, pPickUpSmallGhost);
	kih.AddCommand(SDL_SCANCODE_O, pPickUpPowerUpGhost);
	kih.AddCommand(SDL_SCANCODE_P, pEnemyDeadGhost);

	std::cout << "\n\ncontrols \n\n";
	std::cout << "pacman: \n";
	std::cout << "movement: wasd to move \n";
	std::cout << "points: x , c ,v,b to add points \n";
	std::cout << "die: z to die, remove a life, play dead sound \n\n";

	std::cout << "ghost: \n";
	std::cout << "points: u , i ,o,p to add points \n";
	std::cout << "die: y to die, remove a life, play dead sound \n\n";

	std::cout << "arrow down plays startup sound and arrow up same sound other volume \n\n";


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
	background->SetTexture(textureManager.GetTexture(Textures::Background));
	backgroundObj->AddComponent(background);

	const auto logo = std::make_shared<TextureComponent>();
	logo->SetTexture(textureManager.GetTexture(Textures::Logo));
	logoObj->AddComponent(logo);
	logoObj->SetPosition( 80, 70);

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


	//points pacman
	auto fontPointsPacMan = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto pointsCounterPacMan = std::make_shared<dae::PointsComponent>();
	pointsPacmanObj->AddComponent(pointsCounterPacMan);
	auto tpointsPacman = [](std::shared_ptr<dae::PointsComponent> x) {return x->GetScore(); };
	auto lpointsPacman = std::make_shared<dae::LambdaTextProvider<std::shared_ptr<dae::PointsComponent>>>(pointsCounterPacMan, tpointsPacman);
	const auto pointsTextPacman = std::make_shared<dae::TextComponent>(lpointsPacman, fontPointsPacMan);
	pointsPacmanObj->SetPosition(10, 200);
	pointsTextPacman->SetColor({ 255,255,0 });
	pointsPacmanObj->AddComponent(pointsTextPacman);

	//lives pacman
	
	auto tLivesPacman = [](std::shared_ptr<dae::PointsComponent> x) {return x->GetLives(); };
	auto lLivesPacman = std::make_shared<dae::LambdaTextProvider<std::shared_ptr<dae::PointsComponent>>>(pointsCounterPacMan, tLivesPacman);
	const auto LivesTextPacman = std::make_shared<dae::TextComponent>(lLivesPacman, fontPointsPacMan);
	livesPacmanObj->SetPosition(10, 230);
	LivesTextPacman->SetColor({ 255,255,0 });
	livesPacmanObj->AddComponent(LivesTextPacman);


	//points ghost
	auto fontPointsGhost = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto pointsCounterGhost = std::make_shared<dae::PointsComponent>();
	pointsGhostObj->AddComponent(pointsCounterGhost);
	auto tpointsGhost = [](std::shared_ptr<dae::PointsComponent> x) {return x->GetScore(); };
	auto lpointsGhost = std::make_shared<dae::LambdaTextProvider<std::shared_ptr<dae::PointsComponent>>>(pointsCounterGhost, tpointsGhost);
	const auto pointsTextGhost = std::make_shared<dae::TextComponent>(lpointsGhost, fontPointsGhost);
	pointsGhostObj->SetPosition(10, 280);
	pointsTextGhost->SetColor({ 240,20,230 });
	pointsGhostObj->AddComponent(pointsTextGhost);
	// lives ghost
	auto tLivesGhost = [](std::shared_ptr<dae::PointsComponent> x) {return x->GetLives(); };
	auto lLivesGhost = std::make_shared<dae::LambdaTextProvider<std::shared_ptr<dae::PointsComponent>>>(pointsCounterGhost, tLivesGhost);
	const auto LivesTextGhost = std::make_shared<dae::TextComponent>(lLivesGhost, fontPointsGhost);
	livesGhostObj->SetPosition(10, 300);
	LivesTextGhost->SetColor({ 240,20,230 });
	livesGhostObj->AddComponent(LivesTextGhost);



	const auto pacmanComp = std::make_shared<TextureComponent>();
	pacmanComp->SetTexture(textureManager.GetTexture(Textures::Pacman));
	pacmanObj->AddComponent(pacmanComp);
	

	auto fpsObs = std::shared_ptr<Observer>(fpsCounter);
	pacmanObj->addObserver(fpsObs);

	auto pointsPacmanObs = std::shared_ptr<Observer>(pointsCounterPacMan);
	pacmanObj->addObserver(pointsPacmanObs);

	auto pointsGhostObs = std::shared_ptr<Observer>(pointsCounterGhost);
	ghos1tObj->addObserver(pointsGhostObs);

	const auto ghost1TextureComp = std::make_shared<TextureComponent>();
	ghost1TextureComp->SetTexture(textureManager.GetTexture(Textures::Ghost1));
	ghos1tObj->AddComponent(ghost1TextureComp);

	const auto ghost2TextureComp = std::make_shared<TextureComponent>();
	ghost2TextureComp->SetTexture(textureManager.GetTexture(Textures::Ghost2));
	ghos2tObj->AddComponent(ghost2TextureComp);

	const auto ghost3TextureComp = std::make_shared<TextureComponent>();
	ghost3TextureComp->SetTexture(textureManager.GetTexture(Textures::Ghost3));
	ghos3tObj->AddComponent(ghost3TextureComp);


	const auto boardComp = std::make_shared<GameBoardComponent>();
	mapObj->AddComponent(boardComp);
	boardComp->LoadFromJsonFile("../Data/level.json", textureManager);
	//mapObj->SetPosition(float(boardComp->GetWidth()), float( boardComp->GetHeight()));
	mapObj->SetPosition((APP_WIDTH - boardComp->GetWidth()) * .5f, (APP_HEIGHT - boardComp->GetHeight()) * .5f);
	pacmanObj->SetPosition({ boardComp->GetPlayerLocation().x,boardComp->GetPlayerLocation().y });
	ghos1tObj->SetPosition({ boardComp->GetGhost1Location().x,boardComp->GetGhost1Location().y });
	ghos2tObj->SetPosition({ boardComp->GetGhost2Location().x,boardComp->GetGhost2Location().y });
	ghos3tObj->SetPosition({ boardComp->GetGhost3Location().x,boardComp->GetGhost3Location().y });

	pScene->Add(backgroundObj);
	pScene->Add(titleObj);
	pScene->Add(logoObj);
	pScene->Add(mapObj);
	//pScene->LoadLevel("../Data/level.json" , APP_WIDTH, APP_HEIGHT, textureManager);
	pScene->Add(pacmanObj);
	pScene->Add(ghos1tObj);
	pScene->Add(ghos2tObj);
	pScene->Add(ghos3tObj);
	pScene->Add(fpsObj);
	pScene->Add(pointsPacmanObj);
	pScene->Add(livesPacmanObj);
	pScene->Add(pointsGhostObj);
	pScene->Add(livesGhostObj);
	



	ServiceLocator::RegisterSoundSystem(std::make_shared<logging_sound_system>(std::make_shared<SDLSoundSystem>()));
	ServiceLocator::GetSoundSystem().InitializeSoundSystem();
	ServiceLocator::GetSoundSystem().RegisterSound(0, "../Data/pacman_beginning.wav");
	ServiceLocator::GetSoundSystem().RegisterSound(1, "../Data/pacman_chomp.wav");
	ServiceLocator::GetSoundSystem().RegisterSound(2, "../Data/pacman_death.wav");
	ServiceLocator::GetSoundSystem().RegisterSound(3, "../Data/pacman_eatghost.wav");
}
// level loader
// 1 wall  2 pickupsmall   3 powerup    4 empty tile     5 gate      6 spawn ghost      7 spawn pacman

int main(int, char*[]) {
	dae::Minigin engine("Pacman", APP_WIDTH, APP_HEIGHT,"../Data/");
	engine.Run(Load);
    return 0;
}