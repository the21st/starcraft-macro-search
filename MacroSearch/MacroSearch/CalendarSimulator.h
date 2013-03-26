#pragma once

#include "ISimulator.h"

namespace MacroSearch
{

class CalendarSimulator :
	public ISimulator
{
public:
	CalendarSimulator(void);
	~CalendarSimulator(void);

	virtual GameState GetNextState(const GameState & currentState, Action action, bool maxPlayerAction) const;
};

}