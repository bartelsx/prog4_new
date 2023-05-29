#pragma once
#include <memory>
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
		bool Is(TEventType type) const { return m_type == type; }

		TEventType m_type{};
	};

	template <typename T>
	class EventWithPayload : public Event
	{
	public:
		explicit EventWithPayload(TEventType type, T data) : Event(type), m_Data(data)
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
		Observer() = default;
		virtual ~Observer() = default;
		virtual void HandleEvent(const Event& event) = 0;
		// Other stuff...
	};

	class EventManager : Singleton<EventManager>
	{
	public:
		static void Subscribe(TEventType type, const std::shared_ptr<Observer>& pObserver)
		{
			GetInstance().SubscribeImpl(type, pObserver);
		}

		static void Publish(const TEventType type)
		{
			GetInstance().PublishImpl(Event{ type });
		}

		template <typename TPayload>
		static void Publish(const TEventType type, const TPayload& data)
		{
			GetInstance().PublishImpl(EventWithPayload<TPayload>{type, data});
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


		void PublishImpl(const Event& event)
		{
			auto it = m_Subscriptions.find(event.GetType());

			if (it != m_Subscriptions.end())
			{
				for (auto& pObserver : *it->second)
				{
					if (pObserver.expired())
					{
						//todo: trigger cleanup
					}
					else
					{
						pObserver.lock()->HandleEvent(event);
					}
				}
			}
		}


		std::unordered_map<TEventType, std::unique_ptr<std::vector<std::weak_ptr<Observer>>>> m_Subscriptions{};
	};


	//class Node
	//{
	//public:
	//	std::unique_ptr<Node> m_next{};
	//	std::shared_ptr<Observer> pObserver{};

	//	void Notify(const Event& event, const Subject& sender)
	//	{
	//		if (m_next != nullptr)
	//		{
	//			m_next->Notify(event, sender);
	//		}
	//		pObserver->HandleEvent(event);

	//	}
	//};

	//class Subject
	//{
	//public:
	//	Subject()
	//		: m_head(nullptr)
	//	{}

	//	void AddObserver(const std::shared_ptr<Observer>& pObserver)
	//	{
	//		auto newHead = std::make_unique<Node>();
	//		newHead->m_next = std::move(m_head);
	//		newHead->pObserver = pObserver;
	//		m_head = std::move(newHead);
	//	}

	//	void RemoveObserver(const std::shared_ptr<Observer> pObserver)
	//	{
	//		if (m_head == nullptr)
	//		{
	//			return;
	//		}

	//		if (m_head->pObserver == pObserver)
	//		{
	//			m_head = std::move(m_head->m_next);
	//			return;
	//		}

	//		auto current = m_head.get();
	//		while (current->m_next != nullptr)
	//		{
	//			if (current->m_next->pObserver == pObserver)
	//			{
	//				current->m_next = std::move(current->m_next->m_next);
	//				return;
	//			}

	//			current = current->m_next.get();
	//		}
	//	}

	//	void Notify(const Event& event) const
	//	{
	//		if (m_head == nullptr)
	//		{
	//			return;
	//		}

	//		m_head->Notify(event, *this);
	//	}

	//private:
	//	std::unique_ptr<Node> m_head;
	//};
}


