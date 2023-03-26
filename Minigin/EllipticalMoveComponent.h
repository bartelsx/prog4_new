#pragma once
#include "BaseComponent.h"

namespace dae
{
	class EllipticalMoveComponent :
		public BaseComponent
	{
	public:
		EllipticalMoveComponent(float radius, float period) : EllipticalMoveComponent(radius, radius, period){}
		EllipticalMoveComponent(float radiusX, float radiusY, float period) : m_radiusX(radiusX), m_radiusY(radiusY), m_period(period){}
		void Update(float deltaTime) override;

		void SetStartAngle(const float angle) { m_startAngle = angle; }
		void SetCenter(const glm::vec2& center) { m_center = center; }

	private:
		glm::vec2 m_center{ 0,0 };
		float m_time{};
		float m_radiusX{};
		float m_radiusY{};
		float m_period{1.f};
		float m_startAngle{};
	};
}


