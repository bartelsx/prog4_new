#include "SoundPlayer.h"
#include "EventType.h"
#include "ServiceLocator.h"
#include "Sound.h"

using namespace dae;

std::shared_ptr<SoundPlayer>SoundPlayer::Create()
{
	auto ptr = std::shared_ptr<SoundPlayer>(new SoundPlayer());
	return ptr;
}

void SoundPlayer::HandleEvent(const Event& event, const Subject&)
{
	switch (event.GetType())
	{
	case EventType::PILL_PICKUP:
		ServiceLocator::GetSoundSystem().Play(Sound::PACMAN_CHOMP, .5f);
		break;
	case EventType::BOOST_PICKUP:
		ServiceLocator::GetSoundSystem().Play(Sound::PACMAN_POWERUP, .5f);
		break;
	}
}
