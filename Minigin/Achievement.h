#pragma once
#include <iostream>

#include "CSteamAchievements.h"
#include "Observer.h"


#include "steam_api.h"

// Defining our achievements


class Achievement : public Observer
{
public:
	Achievement() :Observer() {  }
	void Notify(Event event, Subject* sender)
	{
		sender;
		switch (event.m_type) {
		case EventType::ACTOR_DIED:
			std::cout << "dead \n";
			break;
		case EventType::LEVEL_STARTED:
			break;

		case EventType::PLAYER_SPAWNED:
			break;
			// etc...  
		}
	}
private:
	
};

	
