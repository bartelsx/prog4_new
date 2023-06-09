#include "SoundPlayer.h"
#include "EventType.h"
#include "ServiceLocator.h"
#include "Sound.h"

using namespace dae;

std::shared_ptr<SoundPlayer>SoundPlayer::Create()
{
	auto ptr = std::shared_ptr<SoundPlayer>(new SoundPlayer());

	EventManager::Subscribe(EventType::PILL_PICKUP, ptr);
	EventManager::Subscribe(EventType::BOOST_PICKUP, ptr);
	EventManager::Subscribe(EventType::ACTOR_DIED, ptr);
	EventManager::Subscribe(EventType::ENEMY_DIED, ptr);
	EventManager::Subscribe(EventType::GAME_START, ptr);

	return ptr;
}

void SoundPlayer::HandleEvent(const Event& event)
{
	switch (event.GetType())
	{
	case EventType::GAME_START:
		ServiceLocator::GetSoundSystem().Play(Sound::BEGINNING, .5f);
		break;
	case EventType::PILL_PICKUP:
		ServiceLocator::GetSoundSystem().Play(Sound::PACMAN_CHOMP, .5f);
		break;
	case EventType::BOOST_PICKUP:
		ServiceLocator::GetSoundSystem().Play(Sound::PACMAN_POWERUP, .5f);
		break;
	case EventType::ACTOR_DIED:
		ServiceLocator::GetSoundSystem().Play(Sound::DEATH, .5f);
		break;
	case EventType::ENEMY_DIED:
		ServiceLocator::GetSoundSystem().Play(Sound::EATGHOST, .5f);
		break;
	}
}
