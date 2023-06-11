#pragma once
#include <memory>
#include <queue>
#include <unordered_map>
#include "Singleton.h"

namespace dae
{
	using TEventType = int;

	class Event
	{
	public:
		Event(TEventType type) : m_type{ type } {}
		virtual ~Event() = default;

		TEventType GetType() const { return m_type; }
		void SetType(TEventType t) { m_type = t; }

		virtual Event* Clone() const { return new Event(m_type); }

		bool Is(TEventType type) const { return m_type == type; }

	protected:
		TEventType m_type{};
	};

	template <typename T>
	class EventWithPayload : public Event
	{
	public:
		EventWithPayload(TEventType type, T data) : Event(type), m_Data(data) {}

		void SetData(T data) { m_Data = data; }
		Event* Clone() const override { return new EventWithPayload(m_type, m_Data); }

		T GetData() const { return m_Data; }

	private:
		T m_Data;
	};


	class Observer
	{
		friend class Subject;

	public:
		Observer() = default;
		virtual ~Observer() = default;
		virtual void HandleEvent(const Event& event) = 0;
		// Other stuff...
	};

	class EventManager : public Singleton<EventManager>
	{
	public:
		static void Subscribe(TEventType type, const std::shared_ptr<Observer>& pObserver)
		{
			GetInstance().SubscribeImpl(type, pObserver);
		}

		static void Publish(const TEventType type)
		{
			auto pEvent = std::make_shared<Event>(type);
			GetInstance().m_Queue.emplace(pEvent);
		}

		static void Publish(const std::shared_ptr<Event>& pEvent)
		{
			GetInstance().m_Queue.emplace(pEvent);
		}

		template <typename TPayload>
		static void Publish(const TEventType type, const TPayload& data)
		{
			auto pEvent = std::make_shared<EventWithPayload<TPayload>>(type, data);
			GetInstance().m_Queue.emplace(pEvent);
		}

		void ProcessQueue()
		{
			//bool needsCleanup{ false };
			while (!m_Queue.empty())
			{
				auto pEvent = m_Queue.front();
				m_Queue.pop();

				auto it = m_Subscriptions.find(pEvent->GetType());

				if (it != m_Subscriptions.end())
				{
					for (auto& pObserver : *it->second)
					{
						if (pObserver.expired())
						{
							//needsCleanup = true;
						}
						else
						{
							pObserver.lock()->HandleEvent(*pEvent);
						}
					}
				}
			}
		}

	private:
		void SubscribeImpl(TEventType type, const std::shared_ptr<Observer>& pObserver)
		{
			auto it = m_Subscriptions.find(type);

			if (it == m_Subscriptions.end())
			{
				auto pNew = std::make_unique<std::vector<std::weak_ptr<Observer>>>();
				pNew->emplace_back(pObserver);
				m_Subscriptions[type] = std::move(pNew);
			}
			else
			{
				it->second->emplace_back(pObserver);
			}
		}


		std::unordered_map<TEventType, std::unique_ptr<std::vector<std::weak_ptr<Observer>>>> m_Subscriptions{};
		std::queue<std::shared_ptr<Event>> m_Queue;
	};

}