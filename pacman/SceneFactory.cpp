#include "SceneFactory.h"

#include <fstream>

#include "ActorMoveComponent.h"
#include "CollisionComponent.h"
#include "CompositeComponent.h"
#include "ControllerInputHandler.h"
#include "DelayedBehavior.h"
#include "FleeBehavior.h"
#include "FPSCalcComponent.h"
#include "GameBoardComponent.h"
#include "GameBoardModel.h"
#include "GhostMoveComponent.h"
#include "KeyboardInputHandler.h"
#include "PacmanComponent.h"
#include "PointsModel.h"
#include "RthBehavior.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SequentialBehavior.h"
#include "ServiceLocator.h"
#include "Sound.h"
#include "SoundPlayer.h"
#include "StartGameCommand.h"
#include "StateComponent.h"
#include "TargetSelector.h"
#include "TextComponent.h"
#include "DelayedEventComponent.h"
#include "FireEventComponent.h"
#include "GoToComponent.h"
#include "HallOfFameModel.h"
#include "TimerComponent.h"

using namespace dae;

#define APP_WIDTH (1024)
#define APP_HEIGHT (768)



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
	return GetLeftThumbValuesFromController(ControllerInputHandler::GetInstance().GetControllerID(0));
}

MoveParameters GetLeftThumbValuesFromSecondPlayerController()
{
	return GetLeftThumbValuesFromController(ControllerInputHandler::GetInstance().GetControllerID(ControllerInputHandler::GetInstance().GetNumberOfControllers() - 1));
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
	GameMode gameMode,
	Textures textureId,
	int index,
	const std::shared_ptr<GhostMoveBehavior>& chaseBehavior,
	const std::shared_ptr<GameObject>& pacmanObj,
	std::
	shared_ptr<GameObject>& pacWomanObj,
	const std::shared_ptr<GameBoardModel>& pBoardModel,
	const std::shared_ptr<ActorMoveComponent>& pMoveComponent) const
{
	const float tolerance = pBoardModel->GetTileSize() * .5f;

	auto ghostObj = GameObject::Create();
	auto normalTexture = TextureComponent::Create(_pTextureManager->GetTexture(textureId));


	//Waiting state
	const auto waitingComp = CompositeComponent::Create();
	waitingComp->Add(normalTexture);
	waitingComp->Add(TimerComponent::Create(static_cast<float>(index * 2 + 2), EventType::WAKE_UP));

	//Normal state
	const auto normalComp = CompositeComponent::Create();

	normalComp->Add(normalTexture);
	if (pMoveComponent == nullptr)
	{
		normalComp->Add(GhostMoveComponent::Create(chaseBehavior, pBoardModel));
	}
	else
	{
		normalComp->Add(pMoveComponent);
	}
	const auto collComp = CollisionComponent::Create(EventType::ACTOR_DIED, false, false, tolerance);
	collComp->AddWatchedObject(pacmanObj);
	if (gameMode == GameMode::Coop)
	{
		collComp->AddWatchedObject(pacWomanObj);
	}
	normalComp->Add(collComp);

	//ResetState
	const auto resetComp = CompositeComponent::Create();
	resetComp->Add(GoToComponent::Create(pBoardModel->GetGhostSpawnLocation(index)));
	resetComp->Add(FireEventComponent::Create(EventType::REACHED_HOME, true));

	//Scared state
	const auto scaredComp = CompositeComponent::Create();
	scaredComp->Add(TextureComponent::Create(_pTextureManager->GetTexture(ScaredGhostTexture)));
	if (pMoveComponent == nullptr)
	{
		scaredComp->Add(GhostMoveComponent::Create(FleeBehavior::Create(gameMode, pBoardModel, pacmanObj, pacWomanObj), pBoardModel));
	}
	else
	{
		scaredComp->Add(pMoveComponent);
	}
	const auto collComp2 = CollisionComponent::Create(EventType::ENEMY_DIED, true, false, tolerance);
	if (gameMode == GameMode::Coop)
	{
		collComp2->AddWatchedObject(pacWomanObj);
	}

	collComp2->AddWatchedObject(pacmanObj);
	scaredComp->Add(collComp2);

	//Returning to home state (after being eaten)
	const auto rthComp = CompositeComponent::Create();
	rthComp->Add(TextureComponent::Create(_pTextureManager->GetTexture(EyesTexture)));
	rthComp->Add(GhostMoveComponent::Create(RthBehavior::Create(pBoardModel, ghostObj, pBoardModel->GetGhostSpawnLocation(index)), pBoardModel));

	//Combine those components in a StateComponent
	const auto stateComponent = StateComponent::Create();
	stateComponent->Set(EventType::REACHED_HOME, waitingComp); //also initial state
	stateComponent->Set(EventType::END_BOOST, normalComp);
	stateComponent->Set(EventType::WAKE_UP, normalComp);
	stateComponent->Set(EventType::BOOST_PICKUP, scaredComp);
	stateComponent->Set(EventType::ENEMY_DIED, rthComp);
	stateComponent->Set(EventType::RESET_LEVEL, resetComp);
	stateComponent->Set(EventType::GAME_OVER, normalTexture);

	ghostObj->AddComponent(stateComponent);
	ghostObj->SetPosition(pBoardModel->GetGhostSpawnLocation(index));
	return ghostObj;
}


void SceneFactory::LoadGameScene(GameMode gameMode)
{
	const auto pScene = &SceneManager::GetInstance().CreateScene("Game Board");

	auto backgroundObj{ GameObject::Create() };
	auto titleObj{ GameObject::Create() };
	auto logoObj{ GameObject::Create() };
	auto pacmanObj{ GameObject::Create() };
	auto pacWomanObj{ GameObject::Create() };
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
	mapObj->SetPosition((APP_WIDTH - pBoardModel->GetWidth()) * .5f, (APP_HEIGHT - pBoardModel->GetHeight()) * .5f);

	//Commands that control Pacman
	const auto pacmanMoveComp = ActorMoveComponent::Create(pBoardModel);
	const auto pacmanStateComp = StateComponent::Create();
	pacmanStateComp->Set(EventType::GAME_START, pacmanMoveComp);
	pacmanStateComp->Set(EventType::GAME_OVER, BaseComponent::Empty()); //Stop moving on GAME_OVER
	pacmanObj->AddComponent(pacmanStateComp);

	std::shared_ptr<Command> pMoveUpCommandPacman = std::make_shared<MoveCommand>(pacmanMoveComp, []() {return MoveParameters{ {0.f,1.f}, 1.f, 0.f }; });
	std::shared_ptr<Command> pMoveDownCommandPacman = std::make_shared<MoveCommand>(pacmanMoveComp, MoveParameters{ {0.f,-1.f}, 1.f, 0.f });
	std::shared_ptr<Command> pMoveLeftCommandPacman = std::make_shared<MoveCommand>(pacmanMoveComp, MoveParameters{ {-1.f,0.f}, 1.f, 0.f });
	std::shared_ptr<Command> pMoveRightCommandPacman = std::make_shared<MoveCommand>(pacmanMoveComp, MoveParameters{ {1.f,0.f}, 1.f, 0.f });

	const auto pacmanComp = PacmanComponent::Create(pBoardModel);
	pacmanObj->AddComponent(pacmanComp);
	pacmanObj->AddComponent(TextureComponent::Create(_pTextureManager->GetTexture(Textures::PacmanTexture)));
	pacmanComp->SetSpawnLocation(pBoardModel->GetPlayerSpawnLocation());

	//Bind Pacman controls
	//  Joystick
	int requieredControllers{ gameMode == GameMode::SinglePlayer ? 1 : 2 };
	if (ControllerInputHandler::GetInstance().GetNumberOfControllers() >= requieredControllers )
	{
		auto controllerId = ControllerInputHandler::GetInstance().GetControllerID(0);
		std::shared_ptr<Command>  pLeftJoystickCommandPacMan = std::make_shared<MoveCommand>(pacmanMoveComp, GetLeftThumbValuesFromPacmanController);
		cih.AddCommand(controllerId, ControllerButton::LeftJoystick, pLeftJoystickCommandPacMan);

		//  Controller buttons Pacman
		cih.AddCommand(controllerId, ControllerButton::ButtonY, pMoveUpCommandPacman);
		cih.AddCommand(controllerId, ControllerButton::ButtonA, pMoveDownCommandPacman);
		cih.AddCommand(controllerId, ControllerButton::ButtonX, pMoveLeftCommandPacman);
		cih.AddCommand(controllerId, ControllerButton::ButtonB, pMoveRightCommandPacman);
	}

	//PacWoman
	if (gameMode == GameMode::Coop)
	{

		//Commands that control Pacman
		const auto pacWomanMoveComp = ActorMoveComponent::Create(pBoardModel);
		const auto pacWomanStateComp = StateComponent::Create();
		pacWomanStateComp->Set(EventType::GAME_START, pacWomanMoveComp);
		pacWomanStateComp->Set(EventType::GAME_OVER, BaseComponent::Empty()); //Stop moving on GAME_OVER
		pacWomanObj->AddComponent(pacWomanStateComp);

		std::shared_ptr<Command> pMoveUpCommandPacWoman = std::make_shared<MoveCommand>(pacWomanMoveComp, []() {return MoveParameters{ {0.f,1.f}, 1.f, 0.f }; });
		std::shared_ptr<Command> pMoveDownCommandPacWoman = std::make_shared<MoveCommand>(pacWomanMoveComp, MoveParameters{ {0.f,-1.f}, 1.f, 0.f });
		std::shared_ptr<Command> pMoveLeftCommandPacWoman = std::make_shared<MoveCommand>(pacWomanMoveComp, MoveParameters{ {-1.f,0.f}, 1.f, 0.f });
		std::shared_ptr<Command> pMoveRightCommandPacWoman = std::make_shared<MoveCommand>(pacWomanMoveComp, MoveParameters{ {1.f,0.f}, 1.f, 0.f });

		const auto pacWomanComp = PacmanComponent::Create(pBoardModel);
		pacWomanObj->AddComponent(pacWomanComp);
		pacWomanObj->AddComponent(TextureComponent::Create(_pTextureManager->GetTexture(Textures::MrsPacmanTexture)));
		pacWomanComp->SetSpawnLocation(pBoardModel->GetPlayerSpawnLocation());


		//Bind Pacman controls
		//  Joystick

		if (cih.GetNumberOfControllers() > 0)
		{
			int pacWomanControllerId = cih.GetControllerID(cih.GetNumberOfControllers() - 1);

			std::shared_ptr<Command>  pLeftJoystickCommandPacWoman = std::make_shared<MoveCommand>(pacWomanMoveComp, GetLeftThumbValuesFromSecondPlayerController);
			cih.AddCommand(pacWomanControllerId, ControllerButton::LeftJoystick, pLeftJoystickCommandPacWoman);

			//  Controller buttons Pacman
			cih.AddCommand(pacWomanControllerId, ControllerButton::ButtonY, pMoveUpCommandPacWoman);
			cih.AddCommand(pacWomanControllerId, ControllerButton::ButtonA, pMoveDownCommandPacWoman);
			cih.AddCommand(pacWomanControllerId, ControllerButton::ButtonX, pMoveLeftCommandPacWoman);
			cih.AddCommand(pacWomanControllerId, ControllerButton::ButtonB, pMoveRightCommandPacWoman);
		}

	}

	// General keyboard bindings and commands for this scene
	kih.AddCommand(SDL_SCANCODE_F9, std::make_shared<MainMenuCommand>());
	kih.AddCommand(SDL_SCANCODE_F10, std::make_shared<HallOfFameCommand>());

	//  Keyboard bindings Pacman
	kih.AddCommand(SDL_SCANCODE_W, pMoveUpCommandPacman);
	kih.AddCommand(SDL_SCANCODE_S, pMoveDownCommandPacman);
	kih.AddCommand(SDL_SCANCODE_A, pMoveLeftCommandPacman);
	kih.AddCommand(SDL_SCANCODE_D, pMoveRightCommandPacman);

	kih.AddCommand(SDL_SCANCODE_UP, pMoveUpCommandPacman);
	kih.AddCommand(SDL_SCANCODE_DOWN, pMoveDownCommandPacman);
	kih.AddCommand(SDL_SCANCODE_LEFT, pMoveLeftCommandPacman);
	kih.AddCommand(SDL_SCANCODE_RIGHT, pMoveRightCommandPacman);

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
	const auto pPointsModel = PointsModel::GetInstance();

	auto tpointsPacman = [](std::shared_ptr<PointsModel> x) {return x->GetScore(); };
	auto lpointsPacman = std::make_shared<LambdaTextProvider<std::shared_ptr<PointsModel>>>(pPointsModel, tpointsPacman);

	const auto pointsTextPacman = std::make_shared<TextComponent>(lpointsPacman, fontPointsPacMan);
	pointsPacmanObj->SetPosition(10, 200);
	pointsTextPacman->SetColor({ 255,255,0 });
	pointsPacmanObj->AddComponent(pointsTextPacman);

	//lives pacman
	auto tLivesPacman = [](std::shared_ptr<PointsModel> x) {return x->GetLives(); };
	auto lLivesPacman = std::make_shared<LambdaTextProvider<std::shared_ptr<PointsModel>>>(pPointsModel, tLivesPacman);
	const auto LivesTextPacman = std::make_shared<TextComponent>(lLivesPacman, fontPointsPacMan);

	livesPacmanObj->SetPosition(10, 230);
	LivesTextPacman->SetColor({ 255,255,0 });
	livesPacmanObj->AddComponent(LivesTextPacman);

	auto ghostsCount = pBoardModel->GetGhostsCount();
	std::vector<std::shared_ptr<GameObject>> ghostObjs{};

	//Blinky (RED)
	if (ghostsCount >= 1)
	{
		std::shared_ptr<ActorMoveComponent> ghostMoveComp{};

		if (gameMode == GameMode::Versus)
		{
			ghostMoveComp = ActorMoveComponent::Create(pBoardModel);
			std::shared_ptr<Command> pLeftJoystickCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, GetLeftThumbValuesFromSecondPlayerController);

			std::shared_ptr<Command> pMoveUpCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, []() {return MoveParameters{ {0.f,1.f}, 1.f, 0.f }; });
			std::shared_ptr<Command> pMoveDownCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, []() {return MoveParameters{ {0.f,-1.f}, 1.f, 0.f }; });
			std::shared_ptr<Command> pMoveLeftCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, []() {return MoveParameters{ {-1.f,0.f}, 1.f, 0.f }; });
			std::shared_ptr<Command> pMoveRightCommandGhost = std::make_shared<MoveCommand>(ghostMoveComp, []() {return MoveParameters{ {1.f,0.f}, 1.f, 0.f }; });

			//  Controller buttons
			int ghostControllerId{ cih.GetControllerID(cih.GetNumberOfControllers() - 1) };

			cih.AddCommand(ghostControllerId, ControllerButton::LeftJoystick, pLeftJoystickCommandGhost);
			cih.AddCommand(ghostControllerId, ControllerButton::ButtonY, pMoveUpCommandGhost);
			cih.AddCommand(ghostControllerId, ControllerButton::ButtonA, pMoveDownCommandGhost);
			cih.AddCommand(ghostControllerId, ControllerButton::ButtonX, pMoveLeftCommandGhost);
			cih.AddCommand(ghostControllerId, ControllerButton::ButtonB, pMoveRightCommandGhost);
		}

		auto behavior = ChasePacmanBehavior::Create(gameMode, pacmanObj, pacWomanObj, pBoardModel, TargetSelector::Pacman());
		ghostObjs.emplace_back(BuildGhost(gameMode, BlinkyTexture, 0, behavior, pacmanObj, pacWomanObj, pBoardModel, ghostMoveComp));
	}

	//Inky (CYAN)
	if (ghostsCount >= 2)
	{
		auto behavior = ChasePacmanBehavior::Create(gameMode, pacmanObj, pacWomanObj, pBoardModel, TargetSelector::InFrontOfPacman());
		ghostObjs.emplace_back(BuildGhost(gameMode, InkyTexture, 1, behavior, pacmanObj, pacWomanObj, pBoardModel));
	}

	//Clyde (ORANGE)
	if (ghostsCount >= 3)
	{
		auto behavior = ChasePacmanBehavior::Create(gameMode, pacmanObj, pacWomanObj, pBoardModel, TargetSelector::BehindPacman());
		ghostObjs.emplace_back(BuildGhost(gameMode, ClydeTexture, 2, behavior, pacmanObj, pacWomanObj, pBoardModel));
	}
	//Pinky (PINK)
	if (ghostsCount >= 4)
	{
		auto pinkyChaseBehavior = SequentialBehavior::Create();
		pinkyChaseBehavior->Add(ChasePacmanBehavior::Create(gameMode, pacmanObj, pacWomanObj, pBoardModel, TargetSelector::Pacman()), 3.f);
		pinkyChaseBehavior->Add(FleeBehavior::Create(gameMode, pBoardModel, pacmanObj, pacWomanObj), 2.f);
		ghostObjs.emplace_back(BuildGhost(gameMode, PinkyTexture, 3, pinkyChaseBehavior, pacmanObj, pacWomanObj, pBoardModel));
	}

	//Timers
	gameplayObj->AddComponent(DelayedEventComponent::Create(EventType::BOOST_PICKUP, EventType::END_BOOST, 10.f));

	pScene->Add(backgroundObj);
	pScene->Add(titleObj);
	pScene->Add(logoObj);

	mapObj->AddChild(pacmanObj);
	if (gameMode == GameMode::Coop) mapObj->AddChild(pacWomanObj);

	for (auto& pGhostObj : ghostObjs)
	{
		mapObj->AddChild(pGhostObj);
	}

	const auto gameOverObj = GameObject::Create();
	const auto gameOverComp = StateComponent::Create();
	gameOverObj->AddComponent(gameOverComp);
	auto gameOverTextComp = std::make_shared<TextComponent>("GAME OVER !!!", font);
	gameOverTextComp->SetColor({ 255, 0,0 });

	gameOverComp->Set(EventType::GAME_START, BaseComponent::Empty());
	gameOverComp->Set(EventType::GAME_OVER, gameOverTextComp);
	gameOverObj->SetPosition(400.f, 350.f);

	pScene->Add(mapObj);
	pScene->Add(fpsObj);
	pScene->Add(pointsPacmanObj);
	pScene->Add(livesPacmanObj);
	pScene->Add(pointsGhostObj);
	pScene->Add(livesGhostObj);
	pScene->Add(gameplayObj);
	pScene->Add(gameOverObj);

}

std::vector<std::string> readFile(const std::string& filename) {
	std::vector<std::string> data;
	std::ifstream file(filename);

	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			size_t separatorPos = line.find(':');
			if (separatorPos != std::string::npos) {
				std::string name = line.substr(0, separatorPos);
				std::string points = line.substr(separatorPos + 1);
				std::string entry = name + ": " + points;
				data.push_back(entry);
			}
		}
		file.close();
	}
	else {
		std::cerr << "Error opening file: " << filename << std::endl;
		return data; // Return empty vector if file cannot be opened
	}

	// Sort the vector in descending order based on points
	std::sort(data.begin(), data.end(), [](const auto& a, const auto& b) {
		int pointsA = std::stoi(a.substr(a.find(':') + 1));
	int pointsB = std::stoi(b.substr(b.find(':') + 1));
	return pointsA > pointsB;
		});

	// Create a new vector with the highest 20 entries
	std::vector<std::string> top20;
	auto end = data.begin() + std::min(20, static_cast<int>(data.size()));
	std::copy(data.begin(), end, std::back_inserter(top20));

	// Write the top 20 entries back to the file
	std::ofstream outFile(filename);
	if (outFile.is_open()) {
		for (const auto& entry : top20) {
			outFile << entry << std::endl;
		}
		outFile.close();
		std::cout << "Top 20 entries have been written to the file: " << filename << std::endl;
	}
	else {
		std::cerr << "Error opening file for writing: " << filename << std::endl;
	}

	return top20;
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

	// General keyboard bindings and commands for this scene
	kih.AddCommand(SDL_SCANCODE_F9, std::make_shared<HallOfFameCommand>());
	kih.AddCommand(SDL_SCANCODE_F10,singlePlayerCommand);

	const auto background = TextureComponent::Create(_pTextureManager->GetTexture(BackgroundTexture));
	backgroundObj->AddComponent(background);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	const auto textComponent = std::make_shared<dae::TextComponent>("[ F5 ] Single Player ", font);
	SinglePlayerObj->AddComponent(textComponent);
	SinglePlayerObj->SetPosition(330, 220);


	const auto textComponentCoop = std::make_shared<dae::TextComponent>("[ F6 ] COOP ", font);
	CoopObj->AddComponent(textComponentCoop);
	CoopObj->SetPosition(330, 280);

	const auto textComponentVersus = std::make_shared<dae::TextComponent>("[ F7 ] Versus ", font);
	VersusObj->AddComponent(textComponentVersus);
	VersusObj->SetPosition(330, 340);


	pScene->Add(backgroundObj);
	pScene->Add(SinglePlayerObj);
	pScene->Add(CoopObj);
	pScene->Add(VersusObj);
	
}

void SceneFactory::LoadHighScoreScene()
{
	const auto pScene = &SceneManager::GetInstance().CreateScene("Hall Of Fame");

	const auto& kih = KeyboardInputHandler::GetInstance();

	kih.AddCommand(SDL_SCANCODE_F9, std::make_shared<StartGameCommand>(GameMode::SinglePlayer));
	kih.AddCommand(SDL_SCANCODE_F10, std::make_shared<MainMenuCommand>());

	auto backgroundObj{ GameObject::Create() };

	const auto background = TextureComponent::Create(_pTextureManager->GetTexture(BackgroundTexture));
	backgroundObj->AddComponent(background);
	pScene->Add(backgroundObj);

	auto repo = std::make_shared<HallOfFameTextFileRepository>();
	auto model = HallOfFameModel::Create(repo);
	auto vector = model->GetData();

	auto offset{ 32.f };
	auto locXName{ 230.f }, locXScore{ 730.f }, locY{ 20.F };


	auto fontHighScore = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	for (auto entry : vector)
	{
		auto NameObj{ GameObject::Create() };
		auto NameComp = std::make_shared<dae::TextComponent>(entry->Name, fontHighScore);
		NameObj->AddComponent(NameComp);
		NameObj->SetPosition(locXName, locY);
		pScene->Add(NameObj);

		auto ScoreObj{ GameObject::Create() };
		auto ScoreComp = std::make_shared<dae::TextComponent>(std::to_string(entry->Score), fontHighScore);
		ScoreObj->AddComponent(ScoreComp);
		ScoreObj->SetPosition(locXScore, locY);
		pScene->Add(ScoreObj);

		locY += offset;
	}
}
