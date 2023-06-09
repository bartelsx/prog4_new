
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#endif
#endif

#include <SDL.h>

#include "Minigin.h"
#include "SceneManager.h"
#include "FPSCalcComponent.h"


#include "SceneFactory.h"
#include "SceneId.h"
#include "Sound.h"

#define APP_WIDTH (1024)
#define APP_HEIGHT (768)

using namespace dae;

void Load()
{

	//Load scenes
	SceneFactory::GetInstance().LoadMainMenuScene();
	//SceneFactory::GetInstance().LoadGameScene();

	//Start with MAIN MENU scene 
	SceneManager::GetInstance().SetCurrentScene(SceneId::MAIN_MENU);

	//Instructions
	std::cout << "\n\ncontrols \n\n";
	std::cout << "pacman: \n";
	std::cout << "movement: wasd to move \n";
	std::cout << "points: x , c ,v,b to add points \n";
	std::cout << "die: z to die, remove a life, play dead sound \n\n";

	std::cout << "ghost: \n";
	std::cout << "points: u , i ,o,p to add points \n";
	std::cout << "die: y to die, remove a life, play dead sound \n\n";

	std::cout << "arrow down plays startup sound and arrow up same sound other volume \n\n";
}

// level loader
// 1 wall  2 pickupsmall   3 powerup    4 empty tile     5 gate      6 spawn ghost      7 spawn pacman

int main(int, char* []) {
	Minigin engine("Pacman", APP_WIDTH, APP_HEIGHT, "../Data/");
	engine.Run(Load);
	return 0;
}
