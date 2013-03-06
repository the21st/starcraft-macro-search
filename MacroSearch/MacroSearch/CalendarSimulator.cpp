#pragma once

#include "Common.h"
#include "CalendarSimulator.h"
#include "Action.h"

//const GameTime droneBuildTime = BWAPI::UnitTypes::Protoss_Probe.buildTime();
const GameTime droneBuildTime = 300;

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
			newState._maxPlayerState._currentProduction.push_back(Production(Probe, droneBuildTime));
			newState._maxPlayerState._mineralAmount -= 50;
		}
		else
		{
			newState._minPlayerState._currentProduction.push_back(Production(Probe, droneBuildTime));
			newState._minPlayerState._mineralAmount -= 50;
		}
		break;
	case BuildPylon:
		if (maxPlayerAction)
		{
			newState._maxPlayerState._currentProduction.push_back(Production(Pylon, 600));
			newState._maxPlayerState._mineralAmount -= 100;
		}
		else
		{
			newState._minPlayerState._currentProduction.push_back(Production(Pylon, 600));
			newState._minPlayerState._mineralAmount -= 100;
		}
		break;
	case BuildGateway:
		if (maxPlayerAction)
		{
			newState._maxPlayerState._currentProduction.push_back(Production(Gateway, 1000));
			newState._maxPlayerState._mineralAmount -= 150;
		}
		else
		{
			newState._minPlayerState._currentProduction.push_back(Production(Gateway, 1000));
			newState._minPlayerState._mineralAmount -= 150;
		}
		break;
	case BuildZealot:
		if (maxPlayerAction)
		{
			newState._maxPlayerState._currentProduction.push_back(Production(Zealot, 400));
			newState._maxPlayerState._mineralAmount -= 100;
		}
		else
		{
			newState._minPlayerState._currentProduction.push_back(Production(Zealot, 400));
			newState._minPlayerState._mineralAmount -= 100;
		}
		break;

	case Attack:
		if (maxPlayerAction)
		{
			if (currentState._minPlayerState._armyStrength > 0)
			{
				newState._maxPlayerState._armyStrength -= 1;
				newState._minPlayerState._armyStrength -= 1;
			}
			else
			{
				if (currentState._minPlayerState._workerCount > 0)
				{
					newState._minPlayerState._workerCount--;
				}
			}
		}
		else
		{
			if (currentState._maxPlayerState._armyStrength > 0)
			{
				newState._minPlayerState._armyStrength -= 1;
				newState._maxPlayerState._armyStrength -= 1;
			}
			else
			{
				if (currentState._maxPlayerState._workerCount > 0)
				{
					newState._maxPlayerState._workerCount--;
				}
			}
		}
	}

	// "simulate time" for newState
	GameTime minTimeToBuild = 1000;
	Production * minProduction;
	for each (auto production in newState._minPlayerState._currentProduction)
	{
		if (production._timeToBuild < minTimeToBuild)
		{
			minTimeToBuild = production._timeToBuild;
			minProduction = &production;
		}
	}
	for each (auto production in newState._maxPlayerState._currentProduction)
	{
		if (production._timeToBuild < minTimeToBuild)
		{
			minTimeToBuild = production._timeToBuild;
			minProduction = &production;
		}
	}

	newState.Simulate(minTimeToBuild);

	return newState;
}
