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

template <typename T>
class EventWithPayload;

class Event
{
public:
	Event(TEventType type) : m_type{ type }{}

	virtual TEventType GetType() const { return m_type; }

	template <typename T>
	static EventWithPayload<T> Create(TEventType type, T data)
	{
		EventWithPayload<T> ev(type, data);
		
		return ev;
	}

	//template <typename T>
	//void SetData(T data) { m_data = data; }

	//template <typename T>
	//T GetData() { return any_cast<T>(m_data); }

	TEventType m_type{};
	//glm::uint8_t m_numArgs{};
	//std::any m_data{};
};

template <typename T>
class EventWithPayload : public Event
{
public:
	EventWithPayload(TEventType type, T data) : Event(type), m_Data(data)
	{  }
	
	void SetData(T data) { m_Data = data; }

	T GetData() { return m_Data; }

private:
	T m_Data;
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

