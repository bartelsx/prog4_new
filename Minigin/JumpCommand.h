#pragma once
#include "command.h"


class JumpCommand : public Command
{
public:
	virtual void execute() { jump(); }
	void jump() {};
};


