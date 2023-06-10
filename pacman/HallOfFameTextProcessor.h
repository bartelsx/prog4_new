#pragma once
#include <memory>
#include <string>

#include "HallOfFameModel.h"

namespace dae
{
	class TextProcessor
	{
	public:
		virtual void Process(std::string text) = 0;
	};

	class HallOfFameTextProcessor : public TextProcessor
	{
	public:
		~HallOfFameTextProcessor() = default;
		HallOfFameTextProcessor(const HallOfFameTextProcessor& other) = delete;
		HallOfFameTextProcessor(HallOfFameTextProcessor&& other) = delete;
		HallOfFameTextProcessor& operator=(const HallOfFameTextProcessor& other) = delete;
		HallOfFameTextProcessor& operator=(HallOfFameTextProcessor&& other) = delete;

		static std::shared_ptr<HallOfFameTextProcessor> Create(std::shared_ptr<HallOfFameModel> pHallOfFameModel);

		void Process(std::string text) override;

	private:
		HallOfFameTextProcessor(std::shared_ptr<HallOfFameModel> pHallOfFameModel);

		std::shared_ptr<HallOfFameModel> m_pHallOfFameModel;
	};
}

