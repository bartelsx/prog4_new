#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <vector>

namespace dae
{
	struct HallOfFameEntry
	{
	public:
		HallOfFameEntry(const std::string& name, const int score)
			: Name{name}
			, Score{score}
		{  }

		std::string Name;
		int Score;
	};

	class HallOfFameRepository
	{
	public:
		HallOfFameRepository() = default;
		virtual ~HallOfFameRepository() = default;
		HallOfFameRepository(const HallOfFameRepository& other) = delete;
		HallOfFameRepository(HallOfFameRepository&& other) = delete;
		HallOfFameRepository& operator=(const HallOfFameRepository& other) = delete;
		HallOfFameRepository& operator=(HallOfFameRepository&& other) = delete;

		virtual std::vector<std::shared_ptr<HallOfFameEntry>> Read() = 0;
		virtual void Write(const std::vector<std::shared_ptr<HallOfFameEntry>>& entries) = 0;
	};

	class HallOfFameTextFileRepository : public HallOfFameRepository
	{
	public:
		HallOfFameTextFileRepository() = default;
		~HallOfFameTextFileRepository() override = default;
		HallOfFameTextFileRepository(const HallOfFameTextFileRepository& other) = delete;
		HallOfFameTextFileRepository(HallOfFameTextFileRepository&& other) = delete;
		HallOfFameTextFileRepository& operator=(const HallOfFameTextFileRepository& other) = delete;
		HallOfFameTextFileRepository& operator=(HallOfFameTextFileRepository&& other) = delete;


		std::vector<std::shared_ptr<HallOfFameEntry>> Read() override;
		void Write(const std::vector<std::shared_ptr<HallOfFameEntry>>& entries) override;
	};
}

