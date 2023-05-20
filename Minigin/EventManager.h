#pragma once
#include <map>
#include <vector>

#include "Observer.h"
#include "Singleton.h"

class EventManager : public dae::Singleton<EventManager>
{
public:
	void Subscribe(const EventType eventType, const std::weak_ptr<Observer>& pObserver);
	void Unsubscribe(EventType eventType, std::weak_ptr<Observer>& pObserver);

	void Publish(Event& event);

private:
	std::map<EventType, std::shared_ptr<std::vector<std::weak_ptr<Observer>>> > _subscriptions {};
};
