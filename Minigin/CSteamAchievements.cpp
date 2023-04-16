#include "CSteamAchievements.h"

#include <isteamuser.h>
#include <isteamuserstats.h>
#include <isteamutils.h>
#include <SDL_syswm.h>
#include <stdio.h>


// Achievement array which will hold data about the achievements and their state


// Global access to Achievements object
CSteamAchievements* g_SteamAchievements = NULL;


CSteamAchievements::CSteamAchievements(Achievement_t* Achievements, int NumAchievements) :
    m_iAppID(0),
    m_bInitialized(false),
    m_CallbackUserStatsReceived(this, &CSteamAchievements::OnUserStatsReceived),
    m_CallbackUserStatsStored(this, &CSteamAchievements::OnUserStatsStored),
    m_CallbackAchievementStored(this, &CSteamAchievements::OnAchievementStored),
	m_pSteamUserStats(NULL)
{
    m_iAppID = SteamUtils()->GetAppID();
	m_pSteamUserStats = SteamUserStats();
    m_pAchievements = Achievements;
    m_iNumAchievements = NumAchievements;
    RequestStats();
}
bool CSteamAchievements::RequestStats()
{
	// Is Steam loaded? If not we can't get stats.
	if (NULL == SteamUserStats() || NULL == SteamUser())
	{
		return false;
	}
	// Is the user logged on?  If not we can't get stats.
	if (!SteamUser()->BLoggedOn())
	{
		return false;
	}
	// Request user stats.
	return SteamUserStats()->RequestCurrentStats();
}
bool CSteamAchievements::SetAchievement(const char* ID)
{
	// Have we received a call back from Steam yet?
	if (m_bInitialized)
	{
		SteamUserStats()->SetAchievement(ID);
		return SteamUserStats()->StoreStats();
	}
	// If not then we can't set achievements yet
	return false;
}
void CSteamAchievements::OnUserStatsReceived(UserStatsReceived_t* pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_iAppID == int64(pCallback->m_nGameID))
	{
		if (k_EResultOK == pCallback->m_eResult)
		{
			OutputDebugString("Received stats and achievements from Steam\n");
			m_bInitialized = true;

			// load achievements
			for (int iAch = 0; iAch < m_iNumAchievements; ++iAch)
			{
				Achievement_t& ach = m_pAchievements[iAch];

				SteamUserStats()->GetAchievement(ach.m_pchAchievementID, &ach.m_bAchieved);
				_snprintf_s(ach.m_rgchName, sizeof(ach.m_rgchName), "%s",
					SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID,
						"name"));
				_snprintf_s(ach.m_rgchDescription, sizeof(ach.m_rgchDescription), "%s",
					SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID,
						"desc"));
			}
		}
		else
		{
			char buffer[128];
			_snprintf_s(buffer, 128, "RequestStats - failed, %d\n", pCallback->m_eResult);
			OutputDebugString(buffer);
		}
	}
}
void CSteamAchievements::OnUserStatsStored(UserStatsStored_t* pParram)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_iAppID == int64(pParram->m_nGameID))
	{
		if (k_EResultOK == pParram->m_eResult)
		{
			OutputDebugString("Stored stats for Steam\n");
		}
		else
		{
			char buffer[128];
			_snprintf_s(buffer, 128, "StatsStored - failed, %d\n", pParram->m_eResult);
			OutputDebugString(buffer);
		}
	}
}
void CSteamAchievements::OnAchievementStored(UserAchievementStored_t* pParram)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_iAppID == int64(pParram->m_nGameID))
	{
		OutputDebugString("Stored Achievement for Steam\n");
	}
}
void CSteamAchievements::UnlockAchievement(Achievement_t& achievement)
{
	achievement.m_bAchieved = true;

	// the icon may change once it's unlocked
	achievement.m_iIconImage = 0;

	// mark it down
	m_pSteamUserStats->SetAchievement(achievement.m_pchAchievementID);

	// Store stats end of frame
	m_bStoreStats = true;
}