#pragma once
#include <xstring>
#include "BaseComponent.h"
#include "EventManager.h"

namespace dae
{
	class Font;
	class Texture2D;

	class PointsComponent : public BaseComponent,  public Observer, std::enable_shared_from_this<PointsComponent>
	{

	public:
		static std::shared_ptr<PointsComponent>Create();

		void Update(float deltaTime) override;

		std::string GetScore();
		std::string GetLives();
	private:
		PointsComponent() = default;
		std::shared_ptr<PointsComponent> m_ptr;
		int m_Points{};
		void Notify(Event& event) override;


		int m_lives{ 3 };
	};
}