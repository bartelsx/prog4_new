#include "EventManager.h"

#include <memory>
#include <vector>

void EventManager::Subscribe(const TEventType eventType, const std::weak_ptr<Observer>& pObserver)
{
	auto& instance = GetInstance();
	if (! instance._subscriptions.contains(eventType))
	{
		instance._subscriptions.insert_or_assign(eventType, std::make_shared<std::vector<std::weak_ptr<Observer>>>());
	}
	instance._subscriptions[eventType]->push_back(pObserver);
}

void EventManager::Unsubscribe(TEventType eventType, const std::weak_ptr<Observer>& pObserver)
{
	auto& instance = GetInstance();
	if (instance._subscriptions.contains(eventType))
	{
		const auto& pList = instance._subscriptions[eventType];
		std::erase_if(*pList, [&](std::weak_ptr<Observer>& x) {return x.expired() || x.lock() == pObserver.lock(); });
	}
}

void EventManager::Publish(Event event)
{
	auto& instance = GetInstance();
	const auto eventType = event.GetType();
	if (instance._subscriptions.contains(eventType))
	{
		for (auto& wpObserver : *instance._subscriptions[eventType])
		{
			if (!wpObserver.expired())
			{
				wpObserver.lock()->Notify(event);
			}
		}
	}
}


