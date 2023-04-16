#pragma once

#define STATS_AND_ACHIEVEMENTS_H
#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }
#include <cstdio>
#include <steam_api_common.h>
#include <isteamuserstats.h>

#include "isteamfriends.h"


enum EAchievements
{
	ACH_WIN_ONE_GAME = 0,
	ACH_WIN_100_GAMES = 1,
	ACH_TRAVEL_FAR_ACCUM = 2,
	ACH_TRAVEL_FAR_SINGLE = 3,
};

struct Achievement_t
{
	int m_eAchievementID;
	const char* m_pchAchievementID;
	char m_rgchName[128];
	char m_rgchDescription[256];
	bool m_bAchieved;
	int m_iIconImage;
};



class ISteamUser;
class CSpaceWarClient;

class CSteamAchievements
{
public:
	CSteamAchievements(Achievement_t* Achievements, int NumAchievements);


	bool RequestStats();
	bool SetAchievement(const char* ID);
	void UnlockAchievement(Achievement_t& achievement);




	STEAM_CALLBACK(CSteamAchievements, OnUserStatsReceived, UserStatsReceived_t,m_CallbackUserStatsReceived);
	STEAM_CALLBACK(CSteamAchievements, OnUserStatsStored, UserStatsStored_t,m_CallbackUserStatsStored);
	STEAM_CALLBACK(CSteamAchievements, OnAchievementStored,	UserAchievementStored_t, m_CallbackAchievementStored);
private:
	int64 m_iAppID; // Our current AppID
	Achievement_t* m_pAchievements; // Achievements data
	int m_iNumAchievements; // The number of Achievements
	bool m_bInitialized; // Have we called Request stats and received the callback?
	// Steam UserStats interface
	ISteamUserStats* m_pSteamUserStats;
	bool m_bStoreStats;

};

