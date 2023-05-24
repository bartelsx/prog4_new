#pragma once
#include <memory>

namespace dae
{
	using TEventType = int;

	class Event
	{
	public:
		Event(TEventType type) : m_type{ type } {}

		virtual TEventType GetType() const { return m_type; }


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
		Observer() = default;
		virtual ~Observer() = default;
		virtual void Notify(const Event& event, const Subject& sender) = 0;
		// Other stuff...
	};

	class Node
	{
	public:
		std::unique_ptr<Node> m_next{};
		std::shared_ptr<Observer> pObserver{};

		void Notify(const Event& event, const Subject& sender)
		{
			if (m_next != nullptr)
			{
				m_next->Notify(event, sender);
			}
			pObserver->Notify(event,sender);

		}
	};

	class Subject
	{
	public:
		Subject()
			: m_head(nullptr)
		{}

		void AddObserver(const std::shared_ptr<Observer>& pObserver)
		{
			auto newHead = std::make_unique<Node>();
			newHead->m_next = std::move(m_head);
			newHead->pObserver = pObserver;
			m_head = std::move(newHead);
		}

		void RemoveObserver(const std::shared_ptr<Observer> pObserver)
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

		void Notify(const Event& event) const
		{
			if (m_head == nullptr)
			{
				return;
			}

			m_head->Notify(event, *this);
		}

	private:
		std::unique_ptr<Node> m_head;
	};
}


