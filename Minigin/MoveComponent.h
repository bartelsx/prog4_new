#pragma once
#include "BaseComponent.h"

namespace dae
{
	class MoveComponent : public BaseComponent
	{
	public:
		MoveComponent() {};
		void Update(float deltaTime) override;

		void SetSpeed(const float speed) { m_Speed = speed; }
		void SetDirection(const glm::vec2& direction) { m_Direction = direction; }

	private:
		float m_Speed{ 0.f };
		glm::vec2 m_Direction{ 0,0 };
	};
}
