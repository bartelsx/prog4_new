#pragma once
#include "MoveCommand.h"
using namespace dae;

class IMoveLimiter
{
public:
	virtual ~IMoveLimiter() = default;
	virtual MoveParameters LimitMovement(MoveParameters intendedMove, glm::vec2 objectLocation) = 0;
};
