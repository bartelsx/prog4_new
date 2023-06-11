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
		inline const static TEventType WAKE_UP = 13;
		inline const static TEventType LEVEL_COMPLETE = 14;
		inline const static TEventType HIGHSCORES_CHANGED = 15;
		inline const static TEventType CLOSE_SCENE_REQUEST = 16;
		inline const static TEventType ENABLE_FRUIT = 17;
		inline const static TEventType DISABLE_FRUIT = 18;
	};
}
