#include "HallOfFameTextProcessor.h"

#include "PointsModel.h"

using namespace dae;

std::shared_ptr<HallOfFameTextProcessor> HallOfFameTextProcessor::Create(std::shared_ptr<HallOfFameModel> pHallOfFameModel)
{
	return std::shared_ptr<HallOfFameTextProcessor>(new HallOfFameTextProcessor(pHallOfFameModel));
}

void HallOfFameTextProcessor::Process(std::string text)
{
	auto score = PointsModel::GetInstance()->GetScore();

	m_pHallOfFameModel->Add(text, score);
}

HallOfFameTextProcessor::HallOfFameTextProcessor(std::shared_ptr<HallOfFameModel> pHallOfFameModel)
	: m_pHallOfFameModel(pHallOfFameModel)
{}
