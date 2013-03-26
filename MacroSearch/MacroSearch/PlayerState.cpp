#pragma once

#include "PlayerState.h"
#include "boost\foreach.hpp"
#include <math.h>

using namespace MacroSearch;

PlayerState::PlayerState(void)
	:
	_armyStrength(0),
	_supplyMax(10),
	_supplyCurrent(4),
	_workerCount(4),
	_mineralAmount(50)
{
}

PlayerState::~PlayerState(void)
{
}

int PlayerState::HowManyIsProducing( BWAPI::UnitType unitType ) const
{
	int count = 0;
	BOOST_FOREACH (const Production &production, _currentProduction)
	{
		if (production._unitType == unitType)
		{
			count++;
		}
	}

	return count;
}

int PlayerState::HowManyBuildingsOwned( BWAPI::UnitType unitType ) const
{
	int count = 0;
	BOOST_FOREACH (const BWAPI::UnitType &buildingType, _buildingsOwned)
	{
		if (buildingType == unitType)
		{
			count++;
		}
	}

	return count;
}

GameTime PlayerState::GetTimeUntilNextAction()
{
	GameTime result = 1000;

	BOOST_FOREACH (const Production &production, _currentProduction)
	{
		result = std::min(result, production._timeToBuild);
	}

	float income = MineralIncomePerFrame();
	if (income > 0)
	{
		int timeUntilFiftyMinerals = 1 + (int) ((50 - fmod(_mineralAmount, 50)) / income);

		result = std::min(result, timeUntilFiftyMinerals);
	}

	if (_currentProduction.empty() && _mineralAmount >= 50)
	{
		result = 1;
	}

	return result;
}
