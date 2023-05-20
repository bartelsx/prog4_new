#include "EventManager.h"

#include <vector>

void EventManager::Subscribe(const EventType eventType, const std::weak_ptr<Observer>& pObserver)
{
	if (! _subscriptions.contains(eventType))
	{
		_subscriptions.insert_or_assign(eventType, std::make_shared<std::vector<std::weak_ptr<Observer>>>());
	}
	_subscriptions[eventType]->push_back(pObserver);
}

void EventManager::Unsubscribe(EventType eventType, std::weak_ptr<Observer>& pObserver)
{
	if (_subscriptions.contains(eventType))
	{
		const auto& pList = _subscriptions[eventType];
		std::erase_if(*pList, [&](std::weak_ptr<Observer>& x) {return x.expired() || x.lock() == pObserver.lock(); });
	}
}

void EventManager::Publish(Event& event)
{
	const auto eventType = event.GetType();
	if (_subscriptions.contains(eventType))
	{
		for (auto& wpObserver : * _subscriptions[eventType])
		{
			if (!wpObserver.expired())
			{
				wpObserver.lock()->Notify(event);
			}
		}
	}
}


