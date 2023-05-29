#pragma once
#include <xstring>
#include "BaseComponent.h"

namespace dae
{
	class Font;
	class Texture2D;

	class PointsComponent : public BaseComponent, public Observer
	{

	public:
		static std::shared_ptr<PointsComponent>Create();

		void Update(float deltaTime) override;

		std::string GetScore();
		std::string GetLives();

	private:
		PointsComponent() = default;
		void HandleEvent(const Event& event) override;

		int m_Points{};
		int m_Lives{ 3 };

		std::shared_ptr<PointsComponent> GetPtr() { return std::dynamic_pointer_cast<PointsComponent>(shared_from_this()); }

		int m_ScoreIdx{ 0 };
		inline static constexpr int m_KillEnemyScores[] =  {200,400,800,1600} ;
	};
}