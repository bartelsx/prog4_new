#pragma once
#include <iostream>

#include "command.h"
#include "MoveComponent.h"

struct MoveParameters
{
public:
	glm::vec2 Direction;
	float Speed;
	float Acceleration;
};

class MoveCommand : public CommandWithOwner<dae::MoveComponent> 
{
public:
	MoveCommand(std::shared_ptr<dae::MoveComponent> pOwner, MoveParameters (*pValueFunc)() )
	: CommandWithOwner(pOwner)
		, m_pValueFunc(pValueFunc){}

	virtual void Execute()
	{
		if (m_pValueFunc != nullptr)
		{
			Move(m_pValueFunc());
		}
	}

	virtual void Release()
	{
		Move(MoveParameters{});
	}

	void Move(const MoveParameters& params)
	{
		
		m_pOwner->SetSpeed(params.Speed);
		m_pOwner->SetDirection(params.Direction);
	}

private:
	MoveParameters (*m_pValueFunc)();
};

