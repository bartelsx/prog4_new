#pragma once
#include <iostream>

#include "Observer.h"

class Achievement : public Observer
{
public:
	Achievement():Observer() {  }
	void Notify(Event event, Subject* sender) 
	{
		sender;
		switch (event.m_type) {
		case TEventType::ACTOR_DIED:
			std::cout << "dead \n";
			break; 
		case TEventType::LEVEL_STARTED:
			break;

		case TEventType::PLAYER_SPAWNED:
			break;
			// etc...  
		}
	}
private:
	//void Unlock(Achievement achievement) {
		// code to unlock an achievement...
	//}
};
