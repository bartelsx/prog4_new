#pragma once
#include <memory>
#include <vector>
#include <glm/vec2.hpp>

namespace dae
{
	class Cardinals;
	class GameBoardModel;
	class PacmanSelector;
	class NextToPacmanSelector;
	class TargetSelector;

	//Strategy to insert into ChasePacmanBehavior to select the target for the PathFinder depending on current location of pacman
	class TargetSelector
	{
	public:
		TargetSelector() = default;
		virtual ~TargetSelector() = default;
		TargetSelector(const TargetSelector& other) = delete;
		TargetSelector(TargetSelector&& other) = delete;
		TargetSelector& operator=(const TargetSelector& other) = delete;
		TargetSelector& operator=(TargetSelector&& other) = delete;

		virtual int GetTarget(const int pacmanIdx, const std::shared_ptr<GameBoardModel> pBoardModel) = 0;

		//Factory methods
		static std::shared_ptr<PacmanSelector> Pacman();
		static std::shared_ptr<NextToPacmanSelector> InFrontOfPacman();
		static std::shared_ptr<NextToPacmanSelector> BehindPacman();
	};

	class PacmanSelector : public TargetSelector
	{
	public:
		~PacmanSelector() override = default;
		PacmanSelector(const PacmanSelector& other) = delete;
		PacmanSelector(PacmanSelector&& other) = delete;
		PacmanSelector& operator=(const PacmanSelector& other) = delete;
		PacmanSelector& operator=(PacmanSelector&& other) = delete;

		static std::shared_ptr<PacmanSelector> Create();
		int GetTarget(const int pacmanIdx, const std::shared_ptr<GameBoardModel>) override;

	private:
		PacmanSelector() = default;

	};

	class Cardinal
	{
	public:
		inline static const glm::ivec2 N = glm::ivec2(0, -1);
		inline static const glm::ivec2 E = glm::ivec2(1, 0);
		inline static const glm::ivec2 S = glm::ivec2(0, 1);
		inline static const glm::ivec2 W = glm::ivec2(-1, 0);
	};

	class NextToPacmanSelector : public TargetSelector
	{
	public:
		~NextToPacmanSelector() override = default;
		NextToPacmanSelector(const NextToPacmanSelector& other) = delete;
		NextToPacmanSelector(NextToPacmanSelector&& other) = delete;
		NextToPacmanSelector& operator=(const NextToPacmanSelector& other) = delete;
		NextToPacmanSelector& operator=(NextToPacmanSelector&& other) = delete;

		static std::shared_ptr<NextToPacmanSelector> Create(const std::initializer_list<glm::ivec2>& searchOrder);
		int GetTarget(const int pacmanIdx, const std::shared_ptr<GameBoardModel> pBoardModel) override;

	private:
		NextToPacmanSelector(const std::initializer_list<glm::ivec2>& searchOrder);
		const std::unique_ptr<std::vector<glm::ivec2>> m_pSearchOrder;
	};
}

