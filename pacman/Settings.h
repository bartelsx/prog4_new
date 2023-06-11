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
		inline static constexpr int NumberOfLevels{ 3 };
		inline static constexpr int PacmanLives{4};
		inline static constexpr int KillEnemyScores[] = { 200,400,800,1600 };
		inline static constexpr int BoostScore{50};
		inline static constexpr int PillScore{10};
		inline static constexpr int FruitScore{100};
	};
}
