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
		std::shared_ptr<PointsComponent> m_ptr;
		int m_Points{};
		void HandleEvent(const Event& event) override;


		int m_lives{ 3 };

		std::shared_ptr<PointsComponent> GetPtr() { return std::dynamic_pointer_cast<PointsComponent>(shared_from_this()); }
	};
}