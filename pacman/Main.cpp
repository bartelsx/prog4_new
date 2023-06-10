
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
#include "ServiceLocator.h"
#include "Sound.h"

#define APP_WIDTH (1024)
#define APP_HEIGHT (768)

using namespace dae;

void Load()
{
	//Initialize sound system
	ServiceLocator::RegisterSoundSystem(std::make_shared<logging_sound_system>(std::make_shared<SDLSoundSystem>()));
	ServiceLocator::GetSoundSystem().InitializeSoundSystem();
	ServiceLocator::GetSoundSystem().RegisterSound(Sound::BEGINNING, "../Data/pacman_beginning.wav");
	ServiceLocator::GetSoundSystem().RegisterSound(Sound::PACMAN_CHOMP, "../Data/munch_1.wav");
	ServiceLocator::GetSoundSystem().RegisterSound(Sound::DEATH, "../Data/pacman_death.wav");
	ServiceLocator::GetSoundSystem().RegisterSound(Sound::EATGHOST, "../Data/pacman_eatghost.wav");
	ServiceLocator::GetSoundSystem().RegisterSound(Sound::PACMAN_POWERUP, "../Data/power_pellet.wav");


	//Load first scene
	SceneFactory::GetInstance().LoadMainMenuScene();

	//Instructions
	std::cout << "\n\ncontrols \n\n";

	std::cout << "pacman: \n";
	std::cout << "movement: W A S D to move \n\n";
	
	std::cout << "<F9> Move to Previous Scene, <F10> Move to Next Scene\n";
}

// level loader
// 1 wall  2 pickupsmall   3 powerup    4 empty tile     5 gate      6 spawn ghost      7 spawn pacman

int main(int, char* []) {
	Minigin engine("Pacman", APP_WIDTH, APP_HEIGHT, "../Data/");
	engine.Run(Load);
	return 0;
}
