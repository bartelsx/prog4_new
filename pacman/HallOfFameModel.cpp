#include "HallOfFameModel.h"

#include <algorithm>

#include "Events.h"
#include "EventType.h"
#include "HallOfFameRepository.h"
#include "Settings.h"

using namespace dae;

std::shared_ptr<HallOfFameModel> HallOfFameModel::Create(const std::shared_ptr<HallOfFameRepository>& pRepository)
{
	return std::shared_ptr<HallOfFameModel>(new HallOfFameModel(pRepository));
}

std::vector<std::shared_ptr<HallOfFameEntry>> HallOfFameModel::GetData()
{
	if (!m_IsInitialized)
	{
		m_Data = m_pRepository->Read();
		SortAndPrune();
		m_IsInitialized = true;
	}
	return m_Data;
}

void HallOfFameModel::Add(const std::string& text, const int score)
{
	const auto newItem = std::make_shared<HallOfFameEntry>(text, score);

	m_Data.emplace_back(newItem);
	SortAndPrune();
	m_pRepository->Write(m_Data);
	EventManager::Publish(EventType::HIGHSCORES_CHANGED);
}

bool HallOfFameModel::CanEnterHallOfFame(int points) const
{
	return (m_Data.size() < 20) || (m_Data[19]->Score <= points);
}

HallOfFameModel::HallOfFameModel(const std::shared_ptr<HallOfFameRepository>& pRepository)
	: m_pRepository(pRepository)
{}

void HallOfFameModel::SortAndPrune()
{

	// Sort the vector in descending order based on points
	std::sort(m_Data.begin(), m_Data.end(), [](const auto& a, const auto& b) {	return a->Score > b->Score;	});

	// Create a new vector with the highest 20 entries
	if (m_Data.size() > Settings::HighScoreNumberOfNames)
	{
		m_Data.erase(m_Data.begin() + Settings::HighScoreNumberOfNames, m_Data.end());
		m_Data.resize(20);
	}

}
