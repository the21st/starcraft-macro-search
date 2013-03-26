#pragma once

#include "Common.h"
#include "CalendarSimulator.h"
#include "Action.h"
#include <boost/foreach.hpp>

using namespace MacroSearch;

CalendarSimulator::CalendarSimulator(void)
{
}


CalendarSimulator::~CalendarSimulator(void)
{
}

GameState CalendarSimulator::GetNextState( const GameState & currentState, Action action, bool maxPlayerAction ) const
{
	GameState newState(currentState);

	switch (action)
	{
	case BuildProbe:
		if (maxPlayerAction)
		{
			newState._maxPlayerState._currentProduction.push_back(Production(BWAPI::UnitTypes::Protoss_Probe));
			newState._maxPlayerState._mineralAmount -= BWAPI::UnitTypes::Protoss_Probe.mineralPrice();
		}
		else
		{
			newState._minPlayerState._currentProduction.push_back(Production(BWAPI::UnitTypes::Protoss_Probe));
			newState._minPlayerState._mineralAmount -= 50;
		}
		break;
	case BuildPylon:
		if (maxPlayerAction)
		{
			newState._maxPlayerState._currentProduction.push_back(Production(BWAPI::UnitTypes::Protoss_Pylon));
			newState._maxPlayerState._mineralAmount -= 100;
		}
		else
		{
			newState._minPlayerState._currentProduction.push_back(Production(BWAPI::UnitTypes::Protoss_Pylon));
			newState._minPlayerState._mineralAmount -= 100;
		}
		break;
	case BuildGateway:
		if (maxPlayerAction)
		{
			newState._maxPlayerState._currentProduction.push_back(Production(BWAPI::UnitTypes::Protoss_Gateway));
			newState._maxPlayerState._mineralAmount -= 150;
		}
		else
		{
			newState._minPlayerState._currentProduction.push_back(Production(BWAPI::UnitTypes::Protoss_Gateway));
			newState._minPlayerState._mineralAmount -= 150;
		}
		break;
	case BuildZealot:
		if (maxPlayerAction)
		{
			newState._maxPlayerState._currentProduction.push_back(Production(BWAPI::UnitTypes::Protoss_Zealot));
			newState._maxPlayerState._mineralAmount -= 100;
		}
		else
		{
			newState._minPlayerState._currentProduction.push_back(Production(BWAPI::UnitTypes::Protoss_Zealot));
			newState._minPlayerState._mineralAmount -= 100;
		}
		break;
	}

	// "simulate time" for newState
	bool nextIsMaxPlayerAction;
	GameTime timeUntilNextAction = newState.GetTimeUntilNextAction(nextIsMaxPlayerAction);

	newState._isMaxPlayerMove = nextIsMaxPlayerAction;
	newState.Simulate(timeUntilNextAction);

	return newState;
}
