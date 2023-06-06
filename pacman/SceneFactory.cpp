#include "SceneFactory.h"

#include "ActorMoveComponent.h"
#include "CollisionComponent.h"
#include "CompositeComponent.h"
#include "ControllerInputHandler.h"
#include "DelayedBehavior.h"
#include "FleeBehavior.h"
#include "FPSCalcComponent.h"
#include "GameBoardComponent.h"
#include "GameBoardModel.h"
#include "GameState.h"
#include "GhostMoveComponent.h"
#include "KeyboardInputHandler.h"
#include "PacmanComponent.h"
#include "PointsComponent.h"
#include "RthBehavior.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SequentialBehavior.h"
#include "ServiceLocator.h"
#include "Sound.h"
#include "SoundPlayer.h"
#include "StartGameCommand.h"
#include "SwitchingComponent.h"
#include "TargetSelector.h"
#include "TextComponent.h"
#include "TimerComponent.h"

using namespace dae;

#define APP_WIDTH (1024)
#define APP_HEIGHT (768)

#define PACMAN_CONTROLLER_ID 0
#define GHOST_CONTROLLER_ID 1

std::shared_ptr<SoundPlayer> _pSoundPlayer;
std::shared_ptr<TextureManager> _pTextureManager;

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
	return { {0.f,1.f}, 1.f, 0.f };
}


SceneFactory::SceneFactory()
{
	_pSoundPlayer = SoundPlayer::Create();
	_pTextureManager = std::make_shared<TextureManager>();
}


std::shared_ptr<GameObject> SceneFactory::BuildGhost(
	int index,
	Textures textureId,
	const std::shared_ptr<GhostMoveBehavior>& chaseBehavior,
	const std::shared_ptr<GameObject>& pacmanObj,
	const std::shared_ptr<GameBoardModel>& pBoardModel,
	const std::shared_ptr<GameState>& pGameState)
{
	const float tolerance = pBoardModel->GetTileSize() * .5f;

	auto ghostObj = GameObject::Create();

	//Normal
	const auto normalComp = CompositeComponent::Create();

	//-> Visual
	normalComp->Add(TextureComponent::Create(_pTextureManager->GetTexture(textureId)));
	//-> Movement
	normalComp->Add(GhostMoveComponent::Create(chaseBehavior, pBoardModel));
	//-> Collision detection
	const auto collComp = CollisionComponent::Create(EventType::ACTOR_DIED, false, false, tolerance);
	collComp->AddWatchedObject(pacmanObj);
	normalComp->Add(collComp);


	//Scared 
	const auto scaredComp = CompositeComponent::Create();
	//-> Visual
	scaredComp->Add(TextureComponent::Create(_pTextureManager->GetTexture(ScaredGhostTexture)));
	//-> Movement
	scaredComp->Add(GhostMoveComponent::Create(FleeBehavior::Create(pBoardModel, pGameState), pBoardModel));
	//-> Collision detection
	const auto collComp2 = CollisionComponent::Create(EventType::ENEMY_DIED, true, false, tolerance);
	collComp2->AddWatchedObject(pacmanObj);
	scaredComp->Add(collComp2);

	//Returning to home state (after being eaten)
	const auto rthComp = CompositeComponent::Create();
	//-> Visual
	rthComp->Add(TextureComponent::Create(_pTextureManager->GetTexture(EyesTexture)));
	//-> Movement
	rthComp->Add(GhostMoveComponent::Create(RthBehavior::Create(pBoardModel, ghostObj, pBoardModel->GetGhostSpawnLocation(0)), pBoardModel));

	//Combine those components in a SwitchingComponent
	const auto switchingComp = SwitchingComponent::Create();
	switchingComp->Set(EventType::END_BOOST, normalComp); //also default behavior
	switchingComp->Set(EventType::BOOST_PICKUP, scaredComp);
	switchingComp->Set(EventType::ENEMY_DIED, rthComp);
	switchingComp->Set(EventType::REACHED_HOME, normalComp);

	ghostObj->AddComponent(switchingComp);
	ghostObj->SetPosition(pBoardModel->GetGhostSpawnLocation(index));
	return ghostObj;
}


void SceneFactory::LoadGameScene()
{
	const auto pScene = &SceneManager::GetInstance().CreateScene("Game Board");

	auto backgroundObj{ GameObject::Create() };
	auto titleObj{ GameObject::Create() };
	auto logoObj{ GameObject::Create() };
	auto pacmanObj{ GameObject::Create() };
	auto fpsObj{ GameObject::Create() };
	auto pointsPacmanObj{ GameObject::Create() };
	auto livesPacmanObj{ GameObject::Create() };
	auto pointsGhostObj{ GameObject::Create() };
	auto livesGhostObj{ GameObject::Create() };
	auto mapObj{ GameObject::Create() };
	auto gameplayObj{ GameObject::Create() };

	auto& kih = KeyboardInputHandler::GetInstance();
	auto& cih = ControllerInputHandler::GetInstance();

	const auto pBoardModel = GameBoardModel::Create();
	pBoardModel->LoadFromJsonFile("../Data/level.json");

	const auto pBoardComp = std::make_shared<GameBoardComponent>(pBoardModel, _pTextureManager);
	mapObj->AddComponent(pBoardComp);
	//mapObj->SetPosition(float(boardComp->GetWidth()), float( boardComp->GetHeight()));
	mapObj->SetPosition((APP_WIDTH - pBoardModel->GetWidth()) * .5f, (APP_HEIGHT - pBoardModel->GetHeight()) * .5f);

	// GameState
	const auto pGameState = std::make_shared<GameState>();
	pGameState->SetPacmanObj(pacmanObj);

	//Commands that control Pacman
	const auto pacmanMoveComp = ActorMoveComponent::Create(pBoardModel);
	pacmanObj->AddComponent(pacmanMoveComp);

	std::shared_ptr<Command>  pLeftJoystickCommandPacMan = std::make_shared<MoveCommand>(pacmanMoveComp, GetLeftThumbValuesFromPacmanController);
	std::shared_ptr<Command> pMoveUpCommandPacman = std::make_shared<MoveCommand>(pacmanMoveComp, []() {return MoveParameters{ {0.f,1.f}, 1.f, 0.f }; });
	std::shared_ptr<Command> pMoveDownCommandPacman = std::make_shared<MoveCommand>(pacmanMoveComp, MoveParameters{ {0.f,-1.f}, 1.f, 0.f });
	std::shared_ptr<Command> pMoveLeftCommandPacman = std::make_shared<MoveCommand>(pacmanMoveComp, MoveParameters{ {-1.f,0.f}, 1.f, 0.f });
	std::shared_ptr<Command> pMoveRightCommandPacman = std::make_shared<MoveCommand>(pacmanMoveComp, MoveParameters{ {1.f,0.f}, 1.f, 0.f });

	//std::shared_ptr<Command> pDiePacman = std::make_shared<DieCommand>(pacmanObj);
	//std::shared_ptr<Command> pPickUpFruitPacman = std::make_shared<PickUpFruitCommand>(pacmanObj);
	//std::shared_ptr<Command> pPickUpSmallPacman = std::make_shared<PickUpSmallCommand>(pacmanObj);
	//std::shared_ptr<Command> pPickUpPowerUpPacman = std::make_shared<PickUpPowerUpCommand>(pacmanObj);
	//std::shared_ptr<Command> pEnemyDeadPacman = std::make_shared<EnemyDeadCommand>(pacmanObj);


	//std::shared_ptr<Command> pLeftJoystickCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, GetLeftThumbValuesFromGhostController);
	//std::shared_ptr<Command> pMoveUpCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, []() {return MoveParameters{ {0.f,1.f}, 2.f, 0.f }; });
	//std::shared_ptr<Command> pMoveDownCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, []() {return MoveParameters{ {0.f,-1.f}, 2.f, 0.f }; });
	//std::shared_ptr<Command> pMoveLeftCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, []() {return MoveParameters{ {-1.f,0.f}, 2.f, 0.f }; });
	//std::shared_ptr<Command> pMoveRightCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, []() {return MoveParameters{ {1.f,0.f}, 2.f, 0.f }; });

	//std::shared_ptr<Command> pDieGhost = std::make_shared<DieCommand>(ghos1tObj);
	//std::shared_ptr<Command> pPickUpFruitGhost = std::make_shared<PickUpFruitCommand>(ghos1tObj);
	//std::shared_ptr<Command> pPickUpSmallGhost = std::make_shared<PickUpSmallCommand>(ghos1tObj);
	//std::shared_ptr<Command> pPickUpPowerUpGhost = std::make_shared<PickUpPowerUpCommand>(ghos1tObj);
	//std::shared_ptr<Command> pEnemyDeadGhost = std::make_shared<EnemyDeadCommand>(ghos1tObj);

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

	kih.AddCommand(SDL_SCANCODE_UP, pMoveUpCommandPacman);
	kih.AddCommand(SDL_SCANCODE_DOWN, pMoveDownCommandPacman);
	kih.AddCommand(SDL_SCANCODE_LEFT, pMoveLeftCommandPacman);
	kih.AddCommand(SDL_SCANCODE_RIGHT, pMoveRightCommandPacman);

	//kih.AddCommand(SDL_SCANCODE_Z, pDiePacman);
	//kih.AddCommand(SDL_SCANCODE_X, pPickUpFruitPacman);
	//kih.AddCommand(SDL_SCANCODE_C, pPickUpSmallPacman);
	//kih.AddCommand(SDL_SCANCODE_V, pPickUpPowerUpPacman);
	//kih.AddCommand(SDL_SCANCODE_B, pEnemyDeadPacman);

	////ghost
	//kih.AddCommand(SDL_SCANCODE_Y, pDieGhost);
	//kih.AddCommand(SDL_SCANCODE_U, pPickUpFruitGhost);
	//kih.AddCommand(SDL_SCANCODE_I, pPickUpSmallGhost);
	//kih.AddCommand(SDL_SCANCODE_O, pPickUpPowerUpGhost);
	//kih.AddCommand(SDL_SCANCODE_P, pEnemyDeadGhost);


	//Bind Ghost controls
	//  Joystick
	//cih.AddCommand(GHOST_CONTROLLER_ID, ControllerButton::LeftJoystick, pLeftJoystickCommandGhost);
	//
	////  Controller buttons
	//cih.AddCommand(GHOST_CONTROLLER_ID, ControllerButton::ButtonY, pMoveUpCommandGhost);
	//cih.AddCommand(GHOST_CONTROLLER_ID, ControllerButton::ButtonA, pMoveDownCommandGhost);
	//cih.AddCommand(GHOST_CONTROLLER_ID, ControllerButton::ButtonX, pMoveLeftCommandGhost);
	//cih.AddCommand(GHOST_CONTROLLER_ID, ControllerButton::ButtonB, pMoveRightCommandGhost);

	//
	const auto background = TextureComponent::Create(_pTextureManager->GetTexture(BackgroundTexture));
	backgroundObj->AddComponent(background);

	const auto logo = TextureComponent::Create(_pTextureManager->GetTexture(LogoTexture));
	logoObj->AddComponent(logo);
	logoObj->SetPosition(80, 70);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	const auto textComponent = std::make_shared<TextComponent>("Programming 4 Assignment", font);
	titleObj->AddComponent(textComponent);
	titleObj->SetPosition(80, 20);

	auto fontFPS = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto fpsCounter = std::make_shared<FPSCalcComponent>();
	fpsObj->AddComponent(fpsCounter);
	const auto fpsText = std::make_shared<TextComponent>(fpsCounter, fontFPS);
	fpsObj->SetPosition(10, 15);
	fpsText->SetColor({ 255,255,0 });
	fpsObj->AddComponent(fpsText);

	//points pacman
	auto fontPointsPacMan = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto pointsCounterPacMan = PointsComponent::Create();
	pointsPacmanObj->AddComponent(pointsCounterPacMan);
	auto tpointsPacman = [](std::shared_ptr<PointsComponent> x) {return x->GetScore(); };
	auto lpointsPacman = std::make_shared<LambdaTextProvider<std::shared_ptr<PointsComponent>>>(pointsCounterPacMan, tpointsPacman);
	const auto pointsTextPacman = std::make_shared<TextComponent>(lpointsPacman, fontPointsPacMan);
	pointsPacmanObj->SetPosition(10, 200);
	pointsTextPacman->SetColor({ 255,255,0 });
	pointsPacmanObj->AddComponent(pointsTextPacman);

	//lives pacman
	auto tLivesPacman = [](std::shared_ptr<PointsComponent> x) {return x->GetLives(); };
	auto lLivesPacman = std::make_shared<LambdaTextProvider<std::shared_ptr<PointsComponent>>>(pointsCounterPacMan, tLivesPacman);
	const auto LivesTextPacman = std::make_shared<TextComponent>(lLivesPacman, fontPointsPacMan);
	livesPacmanObj->SetPosition(10, 230);
	LivesTextPacman->SetColor({ 255,255,0 });
	livesPacmanObj->AddComponent(LivesTextPacman);

	//points ghost
	//auto fontPointsGhost = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	//auto pointsCounterGhost = PointsComponent::Create();
	//pointsGhostObj->AddComponent(pointsCounterGhost);
	//auto tpointsGhost = [](std::shared_ptr<PointsComponent> x) {return x->GetScore(); };
	//auto lpointsGhost = std::make_shared<LambdaTextProvider<std::shared_ptr<PointsComponent>>>(pointsCounterGhost, tpointsGhost);
	//const auto pointsTextGhost = std::make_shared<TextComponent>(lpointsGhost, fontPointsGhost);
	//pointsGhostObj->SetPosition(10, 280);
	//pointsTextGhost->SetColor({ 240,20,230 });
	//pointsGhostObj->AddComponent(pointsTextGhost);

	//lives ghost
	//auto tLivesGhost = [](std::shared_ptr<PointsComponent> x) {return x->GetLives(); };
	//auto lLivesGhost = std::make_shared<LambdaTextProvider<std::shared_ptr<PointsComponent>>>(pointsCounterGhost, tLivesGhost);
	//const auto LivesTextGhost = std::make_shared<TextComponent>(lLivesGhost, fontPointsGhost);
	//livesGhostObj->SetPosition(10, 300);
	//LivesTextGhost->SetColor({ 240,20,230 });
	//livesGhostObj->AddComponent(LivesTextGhost);

	const auto pacmanComp = PacmanComponent::Create(pBoardModel);
	pacmanObj->AddComponent(pacmanComp);
	pacmanObj->AddComponent(TextureComponent::Create(_pTextureManager->GetTexture(Textures::PacmanTexture)));

	auto ghostsCount = pBoardModel->GetGhostsCount();
	std::vector<std::shared_ptr<GameObject>> ghostObjs{};

	//Blinky (RED)
	if (ghostsCount >= 1)
	{
		auto behavior = DelayedBehavior::Create(2.f, ChasePacmanBehavior::Create(pacmanObj, pBoardModel, TargetSelector::Pacman()));
		ghostObjs.emplace_back(BuildGhost(0, BlinkyTexture, behavior, pacmanObj, pBoardModel, pGameState));
	}

	//Inky (CYAN)
	if (ghostsCount >= 2)
	{
		auto behavior = DelayedBehavior::Create(5.f, ChasePacmanBehavior::Create(pacmanObj, pBoardModel, TargetSelector::InFrontOfPacman()));
		ghostObjs.emplace_back(BuildGhost(1, InkyTexture, behavior, pacmanObj, pBoardModel, pGameState));
	}

	//Clyde (ORANGE)
	if (ghostsCount >= 3)
	{
		auto behavior = DelayedBehavior::Create(8.f, ChasePacmanBehavior::Create(pacmanObj, pBoardModel, TargetSelector::BehindPacman()));
		ghostObjs.emplace_back(BuildGhost(2, ClydeTexture, behavior, pacmanObj, pBoardModel, pGameState));
	}

	//Pinky (PINK)
	if (ghostsCount >= 4)
	{
		auto pinkyChaseBehavior = SequentialBehavior::Create();
		pinkyChaseBehavior->Add(ChasePacmanBehavior::Create(pacmanObj, pBoardModel, TargetSelector::Pacman()), 3.f);
		pinkyChaseBehavior->Add(FleeBehavior::Create(pBoardModel, pGameState), 2.f);
		ghostObjs.emplace_back(BuildGhost(3, PinkyTexture, pinkyChaseBehavior, pacmanObj, pBoardModel, pGameState));
	}

	//Timers
	gameplayObj->AddComponent(TimerComponent::Create(EventType::BOOST_PICKUP, EventType::END_BOOST, 10.f));
	pacmanComp->SetSpawnLocation(pBoardModel->GetPlayerSpawnLocation());

	pScene->Add(backgroundObj);
	pScene->Add(titleObj);
	pScene->Add(logoObj);

	mapObj->AddChild(pacmanObj);

	for (auto& pGhostObj : ghostObjs)
	{
		mapObj->AddChild(pGhostObj);
	}

	pScene->Add(mapObj);
	pScene->Add(fpsObj);
	pScene->Add(pointsPacmanObj);
	pScene->Add(livesPacmanObj);
	pScene->Add(pointsGhostObj);
	pScene->Add(livesGhostObj);
	pScene->Add(gameplayObj);

	ServiceLocator::RegisterSoundSystem(std::make_shared<logging_sound_system>(std::make_shared<SDLSoundSystem>()));
	ServiceLocator::GetSoundSystem().InitializeSoundSystem();
	ServiceLocator::GetSoundSystem().RegisterSound(Sound::BEGINNING, "../Data/pacman_beginning.wav");
	ServiceLocator::GetSoundSystem().RegisterSound(Sound::PACMAN_CHOMP, "../Data/munch_1.wav");
	ServiceLocator::GetSoundSystem().RegisterSound(Sound::DEATH, "../Data/pacman_death.wav");
	ServiceLocator::GetSoundSystem().RegisterSound(Sound::EATGHOST, "../Data/pacman_eatghost.wav");
	ServiceLocator::GetSoundSystem().RegisterSound(Sound::PACMAN_POWERUP, "../Data/power_pellet.wav");
}

void SceneFactory::LoadMainMenuScene()
{
	const auto pScene = &SceneManager::GetInstance().CreateScene("Main Menu");

	auto& kih = KeyboardInputHandler::GetInstance();

	auto backgroundObj{ GameObject::Create() };
	auto SinglePlayerObj{ GameObject::Create() };
	auto CoopObj{ GameObject::Create() };
	auto VersusObj{ GameObject::Create() };

	std::shared_ptr<Command> singlePlayerCommand = std::make_shared<StartGameCommand>(GameMode::SinglePlayer);
	std::shared_ptr<Command> coopCommand = std::make_shared<StartGameCommand>(GameMode::Coop);
	std::shared_ptr<Command> versusCommand = std::make_shared<StartGameCommand>(GameMode::Versus);

	kih.AddCommand(SDL_SCANCODE_F5, singlePlayerCommand);
	kih.AddCommand(SDL_SCANCODE_F6, coopCommand);
	kih.AddCommand(SDL_SCANCODE_F7, versusCommand);

	const auto background = TextureComponent::Create(_pTextureManager->GetTexture(BackgroundTexture));
	backgroundObj->AddComponent(background);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	const auto textComponent = std::make_shared<dae::TextComponent>("[ F5 ] Single Player ", font);
	SinglePlayerObj->AddComponent(textComponent);
	SinglePlayerObj->SetPosition(330, 220);


	const auto textComponentCoop = std::make_shared<dae::TextComponent>("[ F6 ] COOP ", font);
	CoopObj->AddComponent(textComponentCoop);
	CoopObj->SetPosition(330, 280);

	const auto textComponentVersus = std::make_shared<dae::TextComponent>("[ F6 ] Versus ", font);
	VersusObj->AddComponent(textComponentVersus);
	VersusObj->SetPosition(330, 340);

	pScene->Add(backgroundObj);
	pScene->Add(SinglePlayerObj);
	pScene->Add(CoopObj);
	pScene->Add(VersusObj);
}
