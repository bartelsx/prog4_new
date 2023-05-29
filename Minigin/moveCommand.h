#pragma once
#include <iostream>

#include "MoveComponent.h"
#include "command.h"

namespace dae
{

	struct MoveParameters
	{
	public:
		glm::vec2 Direction;
		float Speed;
		float Acceleration;
	};

	class MoveCommand : public CommandWithOwner<MoveComponent>
	{
	public:
		MoveCommand(std::shared_ptr<MoveComponent> pOwner, MoveParameters(*pValueFunc)())
			: CommandWithOwner(pOwner)
			, m_pValueFunc(pValueFunc)
			, m_moveParameters() {}

		MoveCommand(std::shared_ptr<MoveComponent> pOwner, const MoveParameters& moveParameters)
			: CommandWithOwner(pOwner)
			, m_pValueFunc{ nullptr }
			, m_moveParameters{ moveParameters }
		{}

		virtual void Execute()
		{
			if (m_pValueFunc != nullptr)
			{
				Move(m_pValueFunc());
			}
			else
			{
				Move(m_moveParameters);
			}
		}

		virtual void Release()
		{
		}

		void Move(const MoveParameters& params)
		{

			m_pOwner->SetSpeed(params.Speed);
			m_pOwner->SetDirection(params.Direction);
		}

	private:
		MoveParameters(*m_pValueFunc)();
		MoveParameters m_moveParameters;
	};
}