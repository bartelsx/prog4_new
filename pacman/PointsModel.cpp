#include "PointsModel.h"

#include <string>

#include "EventType.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
using namespace dae;


void PointsModel::HandleEvent(const Event& event)
{
	switch (event.GetType()) {
	case EventType::ACTOR_DIED:
		m_Lives -= 1;
		EventManager::Publish(m_Lives <= 0 ? EventType::GAME_OVER : EventType::RESET_LEVEL);
		break;

	case EventType::ENEMY_DIED:
		m_Points += Settings::KillEnemyScores[m_ScoreIdx];
		++m_ScoreIdx;
		break;

	case EventType::FRUIT_PICKUP:
		m_Points += Settings::FruitScore;
		break;

	case EventType::BOOST_PICKUP:
		m_Points += Settings::BoostScore;
		m_ScoreIdx = 0;
		break;

	case EventType::PILL_PICKUP:
		m_Points += Settings::PillScore;
		break;
	}
}

int PointsModel::GetScore() const
{
	
	return m_Points;
}
std::string PointsModel::GetScoreText() const
{
	std::string text{ "Points: " + std::to_string(m_Points) };
	return text;
}
std::string PointsModel::GetLives() const
{
	std::string text{ "lives: " + std::to_string(m_Lives) };
	return text;
}


std::shared_ptr<PointsModel> PointsModel::GetInstance()
{
	static std::shared_ptr<PointsModel> instance{ Create() };
	return instance;
}

std::shared_ptr<PointsModel> PointsModel::Create()
{
	auto ptr = std::shared_ptr<PointsModel>(new PointsModel());
	EventManager::Subscribe(EventType::ACTOR_DIED, ptr);
	EventManager::Subscribe(EventType::PILL_PICKUP, ptr);
	EventManager::Subscribe(EventType::BOOST_PICKUP, ptr);
	EventManager::Subscribe(EventType::FRUIT_PICKUP, ptr);
	EventManager::Subscribe(EventType::ENEMY_DIED, ptr);
	return ptr;
}
