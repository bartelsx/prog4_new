#pragma once
#include "Observer.h"

namespace dae
{

	class EventType
	{
	public:
		EventType() = delete;
		~EventType() = delete;
		EventType(const EventType& other) = delete;
		EventType(EventType&& other) = delete;
		EventType& operator=(const EventType& other) = delete;
		EventType& operator=(EventType&& other) = delete;

		inline const static TEventType ACTOR_DIED = 1;
		inline const static TEventType ENEMY_DIED = 2;
		inline const static TEventType GAME_OVER = 3;
		inline const static TEventType FRUIT_PICKUP = 4;
		inline const static TEventType BOOST_PICKUP = 5;
		inline const static TEventType PILL_PICKUP = 6;
		inline const static TEventType ACTOR_MOVED = 7;
		inline const static TEventType GAME_START = 8;
	};
}
