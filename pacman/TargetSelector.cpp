#include "TargetSelector.h"

#include <iostream>

#include "GameBoardModel.h"

using namespace dae;

std::shared_ptr<PacmanSelector> dae::TargetSelector::Pacman()
{
	return PacmanSelector::Create();
}

std::shared_ptr<NextToPacmanSelector> TargetSelector::InFrontOfPacman()
{
	return NextToPacmanSelector::Create({Cardinal::N, Cardinal::W, Cardinal::S, Cardinal::E});
}

std::shared_ptr<NextToPacmanSelector> TargetSelector::BehindPacman()
{
	return NextToPacmanSelector::Create({ Cardinal::E, Cardinal::S, Cardinal::W, Cardinal::E });
}

std::shared_ptr<PacmanSelector> PacmanSelector::Create()
{
	return std::shared_ptr<PacmanSelector>(new PacmanSelector()); 
}

int PacmanSelector::GetTarget(const int pacmanIdx, const std::shared_ptr<GameBoardModel>)
{
	return pacmanIdx; 
}

std::shared_ptr<NextToPacmanSelector> NextToPacmanSelector::Create(const std::initializer_list<glm::ivec2>& searchOrder)
{
	return std::shared_ptr<NextToPacmanSelector>(new NextToPacmanSelector(searchOrder));
}

NextToPacmanSelector::NextToPacmanSelector(const std::initializer_list<glm::ivec2>& searchOrder) : m_pSearchOrder{ std::make_unique<std::vector<glm::ivec2>>(searchOrder) }
{}

int NextToPacmanSelector::GetTarget(const int pacmanIdx, const std::shared_ptr<GameBoardModel> pBoardModel)
{
	auto pacmanCR = pBoardModel->GetColumnRow(pacmanIdx);

	for (auto& delta : *m_pSearchOrder)
	{
		int col = pacmanCR.x + delta.x;
		int row = pacmanCR.y + delta.y;

		if (pBoardModel->IsTileAccessible(col, row))
		{
			return pBoardModel->GetIdx(col, row);
		}
    }

	return pacmanIdx;
}
