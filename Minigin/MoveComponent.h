#pragma once
#include "BaseComponent.h"
//#include "IMoveLimiter.h"

namespace dae
{
	class MoveComponent : public BaseComponent
	{
	public:
		static std::shared_ptr<MoveComponent> Create()
		{
			return std::shared_ptr<MoveComponent>(new MoveComponent());
		}

		void Update(float deltaTime) override;

		virtual void SetSpeed(const float speed) { m_Speed = speed; }
		virtual void SetDirection(const glm::vec2& direction) { m_Direction = direction; }
		virtual glm::vec2 CalculateNewPos(glm::vec2 currentPos, float deltaTime) const;

	protected:
		MoveComponent() = default;

	private:
		float m_Speed{ 0.f };
		glm::vec2 m_Direction{ 0,0 };
		std::shared_ptr<MoveComponent> GetPtr() { return std::dynamic_pointer_cast<MoveComponent>(shared_from_this()); }

	};
}
