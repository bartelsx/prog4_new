#pragma once
#include "command.h"

namespace dae
{
	class JumpCommand : public Command
	{
	public:
		virtual void Execute() { jump(); }
		void jump() {};
	};
}

