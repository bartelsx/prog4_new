
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
#include "Settings.h"
#include "Sound.h"

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
	std::cout << "\n\nCONTROLS \n\n";

	std::cout << "Keyboard: \n";
	std::cout << "--------- \n";
	std::cout << "WASD   : Move pacman \n";
	std::cout << "arrows : Move pacman \n\n";

	std::cout << "Controllers: \n";
	std::cout << "------------ \n";
	std::cout << "move pacman  : first controller, buttons and left thumb, except dual player mode and only 1 controller available \n";
	std::cout << "second player: last controller, buttons and left thumb\n\n";

	std::cout << "Sound : \n";
	std::cout << "------- \n";
	std::cout << "M      : Toggle sound ON/OFF\n\n";

	std::cout << "General (debugging) : \n";
	std::cout << "--------------------- \n";
	std::cout << "<F8>   : Move to next level (in game only)\n";
	std::cout << "<F9>   : Move to Previous Scene (main menu <- game board <- high scores)\n";
	std::cout << "<F10>  : Move to Next Scene (main menu -> game board -> high scores)\n";
}

// level loader
// 1 wall  2 pickupsmall   3 powerup    4 empty tile     5 gate      6 spawn ghost      7 spawn pacman

int main(int, char* []) {
	Minigin engine("Pacman", Settings::AppWidth, Settings::AppHeight, "../Data/");
	engine.Run(Load);
	return 0;
}
