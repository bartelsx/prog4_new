#pragma once
#include "EventManager.h"
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
			EventManager::Subscribe(EventType::ACTOR_MOVED, ptr);
			return ptr;
		}

		glm::vec2 CalculateNewPos(glm::vec2 currentPos, float deltaTime) const override;
		virtual void Notify(Event& event);

	private:
		MoveToPacmanComponent() = default;

		std::shared_ptr<MoveToPacmanComponent> GetPtr()
		{
			return std::dynamic_pointer_cast<MoveToPacmanComponent>(shared_from_this());
		}

		glm::vec2 m_PacmanPosition{};
	};


}
