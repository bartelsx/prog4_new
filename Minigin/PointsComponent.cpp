#include "PointsComponent.h"

#include "SoundSystem.h"
using namespace dae;

void PointsComponent::Update(float)
{

}

void PointsComponent::CalcPoints()
{
	m_Points += 100;

}

void PointsComponent::Notify(Event& event, Subject* sender)
{
	switch (event.m_type) {
	case EventType::ACTOR_DIED:
		std::cout << "dead \n";
		m_lives -= 1;
		ServiceLocator::GetSoundSystem().Play(2, 1.f);
		if(m_lives <=0)
		{
			auto eventt = Event(EventType::GAME_OVER);
			Notify(eventt ,sender);
		}
		break;
	case EventType::ENEMY_DIED:
		m_Points += 200;
		break;

	case EventType::FRUIT_PICKUP:
		m_Points += 100;
		break;
	case EventType::POWER_UP:
		m_Points += 50;
		break;
	case EventType::SMALL_PICKUP:
		m_Points += 10;
		break;
	
		// etc...  
	}
}

std::string PointsComponent::GetScore()
{
	std::string text{ "Points: " + std::to_string(m_Points) };
	return text;
}
std::string PointsComponent::GetLives()
{
	std::string text{ "lives: " + std::to_string(m_lives)};
	return text;
}
