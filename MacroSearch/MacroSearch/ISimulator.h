#pragma once

#include "GameState.h"
#include "Action.h"

class ISimulator
{
public:

	virtual ~ISimulator() {}
	virtual GameState GetNextState(const GameState & currentState, Action action, bool maxPlayerAction) const = 0;

};