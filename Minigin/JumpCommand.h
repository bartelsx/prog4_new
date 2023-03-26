#pragma once
#include "command.h"


class JumpCommand : public Command
{
public:
	virtual void Execute() { jump(); }
	void jump() {};
};


