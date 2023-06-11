#pragma once
#include <string>

#include "GameBoardModel.h"
#include "PointsModel.h"

namespace dae
{
	class Settings
	{
	public:
		inline static const std::string HighScorePath{ "../Data/HighScore.txt" };

		inline static const std::string Level1Map{ "../Data/level1.json" };
		inline static const std::string Level2Map{ "../Data/level2.json" };
		inline static const std::string Level3Map{ "../Data/level3.json" };
		inline static const std::string FontPath{ "../Data/Lingua.otf" };
		inline static constexpr int NumberOfLevels{ 3 };
		inline static constexpr int PacmanLives{ 4 };
		inline static constexpr int KillEnemyScores[] = { 200,400,800,1600 };
		inline static constexpr int BoostScore{ 50 };
		inline static constexpr int PillScore{ 10 };
		inline static constexpr int FruitScore{ 100 };
		inline static constexpr int EnableFruitInterval{ 40 };
		inline static constexpr float CollisionTolerance{ 8.f };
		inline static constexpr size_t HighScoreNumberOfNames{ 20 };
		inline static constexpr int AppWidth{ 1024 };
		inline static constexpr int AppHeight{ 768 };
		inline static constexpr float PlayerSpeed{1.f};
		inline static constexpr float PlayerAcceleration{0.f};
		inline static constexpr float PowerUpDuration{10.f};
		inline static constexpr float CloseSceneDuration{3.f};
		inline static constexpr float DisableFruitDuration{5.f};
		inline static constexpr float ChaseDuration{3.f};
		inline static constexpr float FleeDuration{2.f};
		inline static constexpr unsigned TitleFontSize {36};
		inline static constexpr unsigned FPSFontSize{18};
		inline static constexpr unsigned LivesAndPointsFontSize{18};
		inline static constexpr unsigned HighScoreFontSize{20};
		inline static constexpr float SoundVolume{.5f};
	};
}
