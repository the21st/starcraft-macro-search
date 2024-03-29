#pragma once

#include "GameState.h"
#include "Action.h"

namespace MacroSearch
{

class ISimulator
{
public:

	virtual ~ISimulator() {}

	// Given a game state and an action, produces the next state.
	virtual GameState GetNextState(const GameState & currentState, Action action, bool maxPlayerAction) const = 0;

};

}