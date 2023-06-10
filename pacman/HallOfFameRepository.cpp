#include "HallOfFameRepository.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include "Settings.h"

std::vector<std::shared_ptr<dae::HallOfFameEntry>> dae::HallOfFameTextFileRepository::Read()
{
	std::vector<std::shared_ptr<HallOfFameEntry>> data{};

	const std::string filename = Settings::HighScorePath;

	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return data; // Return empty vector if file cannot be opened
	}

	std::string line;
	while (std::getline(file, line)) {
		size_t separatorPos = line.find(':');
		if (separatorPos != std::string::npos) {
			std::string name = line.substr(0, separatorPos);
			auto points = std::stoi(line.substr(separatorPos + 1));
			auto entry = std::make_shared<HallOfFameEntry>(name, points);
			data.push_back(entry);
		}
	}
	file.close();

	// Sort the vector in descending order based on points
	std::sort(data.begin(), data.end(), [](const auto& a, const auto& b) {	return a->Score > b->Score;	});

	// Create a new vector with the highest 20 entries
	if (data.size() > 20)
	{
		data.erase(data.begin() + 20, data.end());
		data.resize(20);
		data.shrink_to_fit();
	}

	return data;
}

void dae::HallOfFameTextFileRepository::Write(const std::vector<HallOfFameEntry>& /*entries*/)
{
}
