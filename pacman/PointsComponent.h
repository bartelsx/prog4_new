#pragma once
#include <xstring>

#include "BaseComponent.h"
#include "EventManager.h"
#include "TextComponent.h"

namespace dae
{
	class Font;
	class Texture2D;

	class PointsComponent : public BaseComponent,  public Observer
	{

	public:
		PointsComponent()
		{
			
		};
		void Update(float deltaTime) override;

		std::string GetScore();
		std::string GetLives();
	private:
		std::shared_ptr<PointsComponent> m_ptr;
		int m_Points{};
		void CalcPoints();
		void Notify(Event& event) override;


		int m_lives{ 3 };
	};
}