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
		~PointsModel() override = default;
		PointsModel(const PointsModel& other) = delete;
		PointsModel(PointsModel&& other) = delete;
		PointsModel& operator=(const PointsModel& other) = delete;
		PointsModel& operator=(PointsModel&& other) = delete;

		std::string GetScoreText() const;
		std::string GetLives() const;
		void Init();

		int GetScore() const;
		static std::shared_ptr<PointsModel> GetInstance();
		static std::shared_ptr<PointsModel> Create();

	private:
		PointsModel();

		void HandleEvent(const Event& event) override;

		int m_Points{};
		int m_Lives{};


		int m_ScoreIdx{ 0 };
		
	};
}
