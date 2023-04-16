#include "PointsComponent.h"
#include "CSteamAchievements.h"
using namespace dae;

Achievement_t g_Achievements[4] =
{
	_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
	_ACH_ID(ACH_WIN_100_GAMES, "Champion"),
	_ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
	_ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter"),
};

PointsComponent::PointsComponent()
{
	if (bRet)
	{
		g_SteamAchievements = std::make_shared<CSteamAchievements>(g_Achievements, 4);
	}
}


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
	if(m_Points >= 500)
	{
		g_SteamAchievements->UnlockAchievement(g_Achievements[0]);
		std::cout << "we have a winner 500 points\n";
	}
	if (m_Points >= 1000)
	{
		g_SteamAchievements->UnlockAchievement(g_Achievements[1]);
		std::cout << "we have a winner 1000 points \n";
	}
	if (m_Points >= 1500)
	{
		g_SteamAchievements->UnlockAchievement(g_Achievements[2]);
		std::cout << "we have a winner 1500 points\n";
	}
	if (m_Points >= 2000)
	{
		g_SteamAchievements->UnlockAchievement(g_Achievements[3]);
		std::cout << "we have a winner 2000 points\n";
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
