#include "HallOfFameModel.h"
#include "HallOfFameRepository.h"

std::shared_ptr<dae::HallOfFameModel> dae::HallOfFameModel::Create(const std::shared_ptr<HallOfFameRepository>& pRepository)
{
	return std::shared_ptr<HallOfFameModel>(new HallOfFameModel(pRepository));
}

std::vector<std::shared_ptr<dae::HallOfFameEntry>> dae::HallOfFameModel::GetData()
{
	if (!m_IsInitialized)
	{
		m_Data = m_pRepository->Read();
		m_IsInitialized = true;
	}
	return m_Data;
}

dae::HallOfFameModel::HallOfFameModel(const std::shared_ptr<HallOfFameRepository>& pRepository)
	: m_pRepository(pRepository)
{}
