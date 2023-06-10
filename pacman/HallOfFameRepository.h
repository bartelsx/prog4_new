#pragma once
#include <memory>
#include <string>
#include <vector>
#include <vector>

namespace dae
{
	struct HallOfFameEntry
	{
	public:
		HallOfFameEntry(std::string name, int score)
			: Name{name}
			, Score{score}
		{  }

		std::string Name;
		int Score;
	};

	class HallOfFameRepository
	{
	public:
		virtual std::vector<std::shared_ptr<HallOfFameEntry>> Read() = 0;
		virtual void Write(const std::vector<HallOfFameEntry>& entries) = 0;
	};

	class HallOfFameTextFileRepository : public HallOfFameRepository
	{
	public:
		HallOfFameTextFileRepository() = default;
		~HallOfFameTextFileRepository() = default;
		HallOfFameTextFileRepository(const HallOfFameTextFileRepository& other) = delete;
		HallOfFameTextFileRepository(HallOfFameTextFileRepository&& other) = delete;
		HallOfFameTextFileRepository& operator=(const HallOfFameTextFileRepository& other) = delete;
		HallOfFameTextFileRepository& operator=(HallOfFameTextFileRepository&& other) = delete;


		std::vector<std::shared_ptr<HallOfFameEntry>> Read() override;
		void Write(const std::vector<HallOfFameEntry>& entries) override;
	};
}

