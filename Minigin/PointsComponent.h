#pragma once
#include <xstring>

#include "BaseComponent.h"
#include "TextComponent.h"
#include "CSteamAchievements.h"
namespace dae
{
	class Font;
	class Texture2D;

	class PointsComponent : public BaseComponent,  public Observer
	{

	public:
		PointsComponent();
		

		void Update(float deltaTime) override;

		std::string GetScore();
		std::string GetLives();
	private:
		int m_Points{};
		void CalcPoints();
		void Notify(Event& event, Subject* actor) override;

		std::shared_ptr<CSteamAchievements> g_SteamAchievements{nullptr};
		int m_lives{ 3 };
		bool bRet = SteamAPI_Init();
	};
}