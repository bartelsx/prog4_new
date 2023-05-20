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
			, m_pValueFunc(pValueFunc) {}

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
		MoveParameters(*m_pValueFunc)();
	};

	//class DieCommand : public CommandWithOwner<dae::GameObject>
	//{
	//public:
	//	DieCommand(std::shared_ptr<dae::GameObject> pOwner) : CommandWithOwner<dae::GameObject>(pOwner) {  }
	//
	//	virtual void Release()
	//	{
	//		m_pOwner->Die();
	//	}
	//	virtual void Execute()
	//	{
	//		
	//	}
	//};
	//
	//class PickUpFruitCommand : public CommandWithOwner<dae::GameObject>
	//{
	//public:
	//	PickUpFruitCommand(std::shared_ptr<dae::GameObject> pOwner) : CommandWithOwner<dae::GameObject>(pOwner) {  }
	//
	//	virtual void Release()
	//	{
	//		m_pOwner->FruitPickUp();
	//	}
	//	virtual void Execute()
	//	{
	//
	//	}
	//};
	//
	//class PickUpSmallCommand : public CommandWithOwner<dae::GameObject>
	//{
	//public:
	//	PickUpSmallCommand(std::shared_ptr<dae::GameObject> pOwner) : CommandWithOwner<dae::GameObject>(pOwner) {  }
	//
	//	virtual void Release()
	//	{
	//		m_pOwner->SmallPickUp();
	//	}
	//	virtual void Execute()
	//	{
	//
	//	}
	//};
	//
	//class PickUpPowerUpCommand : public CommandWithOwner<dae::GameObject>
	//{
	//public:
	//	PickUpPowerUpCommand(std::shared_ptr<dae::GameObject> pOwner) : CommandWithOwner<dae::GameObject>(pOwner) {  }
	//
	//	virtual void Release()
	//	{
	//		m_pOwner->PowerUp();
	//	}
	//	virtual void Execute()
	//	{
	//
	//	}
	//};
	//
	//class EnemyDeadCommand : public CommandWithOwner<dae::GameObject>
	//{
	//public:
	//	EnemyDeadCommand(std::shared_ptr<dae::GameObject> pOwner) : CommandWithOwner<dae::GameObject>(pOwner) {  }
	//
	//	virtual void Release()
	//	{
	//		m_pOwner->EnemyDead();
	//	}
	//	virtual void Execute()
	//	{
	//
	//	}
	//};
}