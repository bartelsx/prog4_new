#pragma once
#include <any>
#include <glm/fwd.hpp>

#include "Singleton.h"

//#include "Achievement.h"


class Achievement;
class Node;

namespace dae
{
	class GameObject;
}

using TEventType = int;

struct Event
{
	Event(TEventType type) : m_type{ type }{}

	TEventType GetType() const { return m_type; }

	template <typename T>
	static Event Create(TEventType type, T data)
	{
		Event ev(type);
		ev.SetData(data);
		return ev;
	}

	template <typename T>
	void SetData(T data) { m_data = data; }

	template <typename T>
	T GetData() { return any_cast<T>(m_data); }

	TEventType m_type{};
	glm::uint8_t m_numArgs{};
	std::any m_data{};
};


class Observer
{
	friend class Subject;

public:
	Observer()
	{}
	virtual ~Observer() = default;
	virtual void Notify(Event& event) = 0;
	// Other stuff...
};

