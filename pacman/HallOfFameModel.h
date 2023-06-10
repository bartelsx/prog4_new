#pragma once
#include <memory>

#include "HallOfFameRepository.h"

namespace dae
{

	class HallOfFameModel
	{
	public:
		~HallOfFameModel() = default;
		HallOfFameModel(const HallOfFameModel& other) = delete;
		HallOfFameModel(HallOfFameModel&& other) = delete;
		HallOfFameModel& operator=(const HallOfFameModel& other) = delete;
		HallOfFameModel& operator=(HallOfFameModel&& other) = delete;

		static std::shared_ptr<HallOfFameModel> Create(const std::shared_ptr<HallOfFameRepository>& pRepository);

		std::vector<std::shared_ptr<HallOfFameEntry>> GetData() ;

		HallOfFameModel(const std::shared_ptr<HallOfFameRepository>& pRepository);
	private:

		const std::shared_ptr<HallOfFameRepository>& m_pRepository;
		std::vector<std::shared_ptr<HallOfFameEntry>> m_Data{};
		bool m_IsInitialized{};
	};
}

