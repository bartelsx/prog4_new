#pragma once
#include "EventType.h"
#include "MoveComponent.h"

namespace dae
{
	class MoveToPacmanComponent : public MoveComponent, public Observer
	{
	public:
		static std::shared_ptr<MoveToPacmanComponent> Create()
		{
			auto ptr = std::shared_ptr<MoveToPacmanComponent>(new MoveToPacmanComponent());
			return ptr;
		}

		glm::vec2 CalculateNewPos(glm::vec2 currentPos, float deltaTime) const override;
		void Notify(const Event& event, const Subject& sender) override;

	private:
		MoveToPacmanComponent() = default;

		std::shared_ptr<MoveToPacmanComponent> GetPtr()
		{
			return std::dynamic_pointer_cast<MoveToPacmanComponent>(shared_from_this());
		}

		glm::vec2 m_PacmanPosition{};
	};


}
