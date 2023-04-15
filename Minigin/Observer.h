#pragma once
#include <glm/fwd.hpp>

//#include "Achievement.h"


class Achievement;
class Node;

namespace dae
{
	class GameObject;
}

enum EventType {
	LEVEL_STARTED,
	PLAYER_SPAWNED,
	ACTOR_DIED,
	ENEMY_DIED,
	POWER_UP,
	FRUIT_PICKUP,
	SMALL_PICKUP,
	GAME_OVER
	
	//...
};

struct Event
{
	Event(EventType type) : m_type{ type }{}
	EventType m_type{};
	glm::uint8_t m_numArgs{};
};

template <typename EventArg>
struct EventWithArg : Event
{
	EventWithArg(EventType type, EventArg arg) : Event(type), m_arg(arg) {  }
	EventArg m_arg{};
	EventArg GetArg() { return m_arg; };
};


class Observer
{
	friend class Subject;

public:
	Observer()
	{}
	virtual ~Observer() = default;
	virtual void Notify(Event& event, Subject* actor) = 0;
	// Other stuff...
;
};

#include "Achievement.h"
class Node
{
public:
	std::unique_ptr<Node> m_next{};
	std::shared_ptr<Observer> pObserver{};

	void Notify(Event& event, Subject* sender)
	{
		if (m_next != nullptr)
		{
			m_next->Notify(event, sender);
		}
		pObserver->Notify(event, sender);

	}
};

class Subject
{
public:
	Subject()
		: m_head(nullptr)
	{}

	void addObserver(std::shared_ptr<Observer>& pObserver)
	{
		auto newHead = std::make_unique<Node>();
		newHead->m_next = std::move(m_head);
		newHead->pObserver = pObserver;
		m_head = std::move(newHead);
	}

	void removeObserver(std::shared_ptr<Observer> pObserver)
	{
		if (m_head == nullptr)
		{
			return;
		}

		if (m_head->pObserver == pObserver)
		{
			m_head = std::move(m_head->m_next);
			return;
		}

		auto current = m_head.get();
		while (current->m_next != nullptr)
		{
			if (current->m_next->pObserver == pObserver)
			{
				current->m_next = std::move(current->m_next->m_next);
				return;
			}

			current = current->m_next.get();
		}
	}

	void Notify(Event& event)
	{
		if (m_head == nullptr)
		{
			return;
		}

		m_head->Notify(event, this);
	}
	// Methods...
private:
	std::unique_ptr<Node> m_head;
};
