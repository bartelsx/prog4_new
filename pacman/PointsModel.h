#pragma once
#include <xstring>
#include "BaseComponent.h"
#include "Settings.h"
#include "TextComponent.h"

namespace dae
{
	class Font;
	class Texture2D;

	class PointsModel : public Observer
	{

	public:
		std::string GetScoreText() const;
		std::string GetLives() const;
		void Init();

		int GetScore() const;
		static std::shared_ptr<PointsModel> GetInstance();
		static std::shared_ptr<PointsModel> Create();

	private:
		PointsModel()=default;

		void HandleEvent(const Event& event) override;

		int m_Points{};
		int m_Lives{ Settings::PacmanLives};


		int m_ScoreIdx{ 0 };
		
	};
}
