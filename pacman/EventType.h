#pragma once
#include "Events.h"

namespace dae
{

	class EventType
	{
	public:
		inline const static TEventType ACTOR_DIED = 1;
		inline const static TEventType ENEMY_DIED = 3;
		inline const static TEventType GAME_OVER = 4;
		inline const static TEventType FRUIT_PICKUP = 5;
		inline const static TEventType BOOST_PICKUP = 6;
		inline const static TEventType END_BOOST = 7;
		inline const static TEventType PILL_PICKUP = 8;
		inline const static TEventType ACTOR_MOVED = 9;
		inline const static TEventType GAME_START = 10;
		inline const static TEventType RESET_LEVEL = 11;
		inline const static TEventType REACHED_HOME = 12;
	};
}
