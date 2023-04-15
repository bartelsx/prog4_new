#pragma once
#include <xstring>

#include "BaseComponent.h"
#include "TextComponent.h"

namespace dae
{
	class Font;
	class Texture2D;

	class PointsComponent : public BaseComponent,  public Observer
	{

	public:
		PointsComponent() {  };
		void Update(float deltaTime) override;

		std::string GetScore();
		std::string GetLives();
	private:
		int m_Points{};
		void CalcPoints();
		void Notify(Event& event, Subject* actor) override;


		int m_lives{ 3 };
	};
}