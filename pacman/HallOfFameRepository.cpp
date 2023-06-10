#include "HallOfFameRepository.h"
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
	while (std::getline(file, line)) 
	{
		size_t separatorPos = line.find(':');
		if (separatorPos != std::string::npos) 
		{
			std::string name = line.substr(0, separatorPos);
			auto points = std::stoi(line.substr(separatorPos + 1));
			auto entry = std::make_shared<HallOfFameEntry>(name, points);
			data.push_back(entry);
		}
	}
	file.close();

	return data;
}

void dae::HallOfFameTextFileRepository::Write(const std::vector<std::shared_ptr<HallOfFameEntry>>& entries)
{
	const std::string filename = Settings::HighScorePath;
	std::ofstream outFile(filename);
	if (outFile.is_open()) 
	{
		for (const auto& entry : entries) 
		{
			outFile << entry->Name << ":" << entry->Score << std::endl;
		}
		outFile.close();
	}
	else 
	{
		std::cerr << "Error opening file for writing: " << filename << std::endl;
	}
}
