#include "SoundPlayer.h"
#include "EventType.h"
#include "ServiceLocator.h"
#include "Settings.h"
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
		Play(Sound::BEGINNING, Settings::SoundVolume);
		break;
	case EventType::PILL_PICKUP:
		Play(Sound::PACMAN_CHOMP, Settings::SoundVolume);
		break;
	case EventType::BOOST_PICKUP:
		Play(Sound::PACMAN_POWERUP, Settings::SoundVolume);
		break;
	case EventType::ACTOR_DIED:
		Play(Sound::DEATH, Settings::SoundVolume);
		break;
	case EventType::ENEMY_DIED:
		Play(Sound::EATGHOST, Settings::SoundVolume);
		break;
	}
}


void SoundPlayer::SetMuted(bool muted)
{
	m_Muted = muted;
}

bool SoundPlayer::GetMuted() const
{
	return m_Muted;
}

void SoundPlayer::ToggleMuted()
{
	m_Muted = !m_Muted;
}

void SoundPlayer::Play(const Sound_id id, const float volume)
{
	if (!m_Muted)
	{
		ServiceLocator::GetSoundSystem().Play(id, volume);
	}
}

