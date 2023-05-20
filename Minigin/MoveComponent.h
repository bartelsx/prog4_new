#pragma once
#include "BaseComponent.h"
//#include "IMoveLimiter.h"

namespace dae
{
	class MoveComponent : public BaseComponent
	{
	public:
		void Update(float deltaTime) override;

		virtual void SetSpeed(const float speed) { m_Speed = speed; }
		virtual void SetDirection(const glm::vec2& direction) { m_Direction = direction; }

	protected:
		glm::vec2 CalculateNewPos(glm::vec2 currentPos, float deltaTime) const;

	private:
		float m_Speed{ 0.f };
		glm::vec2 m_Direction{ 0,0 };
	};
}
