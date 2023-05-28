#include "PointsComponent.h"

#include <string>

#include "EventType.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
using namespace dae;

std::shared_ptr<PointsComponent> PointsComponent::Create()
{
	auto ptr = std::shared_ptr<PointsComponent>(new PointsComponent());

	EventManager::Subscribe(EventType::ACTOR_DIED, ptr);
	EventManager::Subscribe(EventType::PILL_PICKUP, ptr);
	EventManager::Subscribe(EventType::BOOST_PICKUP, ptr);
	EventManager::Subscribe(EventType::FRUIT_PICKUP, ptr);
	EventManager::Subscribe(EventType::ENEMY_DIED, ptr);

	return ptr;
}

void PointsComponent::Update(float)
{}

void PointsComponent::HandleEvent(const Event& event)
{
	switch (event.GetType()) {
	case EventType::ACTOR_DIED:
		std::cout << "dead \n";
		m_lives -= 1;
		EventManager::Publish(m_lives <= 0 ? EventType::GAME_OVER : EventType::RESET_LEVEL);
		break;

	case EventType::ENEMY_DIED:
		m_Points += 200;
		break;

	case EventType::FRUIT_PICKUP:
		m_Points += 100;
		break;

	case EventType::BOOST_PICKUP:
		m_Points += 50;
		break;

	case EventType::PILL_PICKUP:
		m_Points += 10;
		break;
	}
}

std::string PointsComponent::GetScore()
{
	std::string text{ "Points: " + std::to_string(m_Points) };
	return text;
}
std::string PointsComponent::GetLives()
{
	std::string text{ "lives: " + std::to_string(m_lives) };
	return text;
}
