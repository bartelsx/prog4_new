#pragma once
#include <map>
#include <memory>
#include <vector>

#include "Observer.h"
#include "Singleton.h"

class EventManager : public dae::Singleton<EventManager>
{
public:
	static void Subscribe(const TEventType eventType, const std::weak_ptr<Observer>& pObserver);
	static void Unsubscribe(TEventType eventType, const std::weak_ptr<Observer>& pObserver);

	static void Publish(Event event);

private:
	std::map<TEventType, std::shared_ptr<std::vector<std::weak_ptr<Observer>>> > _subscriptions {};
};
