#pragma once
#include <xstring>
#include "BaseComponent.h"
#include "TextComponent.h"

namespace dae
{
	class Font;
	class Texture2D;

	class PointsModel : public Observer
	{

	public:
		std::string GetScore() const;
		std::string GetLives() const;
		void Init();

		static std::shared_ptr<PointsModel> GetInstance();
		static std::shared_ptr<PointsModel> Create();

	private:
		PointsModel()=default;

		void HandleEvent(const Event& event) override;

		int m_Points{};
		int m_Lives{ 3 };


		int m_ScoreIdx{ 0 };
		inline static constexpr int m_KillEnemyScores[] =  {200,400,800,1600} ;
	};
}
