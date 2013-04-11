#pragma once

#include "BWAPI.h"
#include "Production.h"
#include "Action.h"

namespace MacroSearch
{

const float MINERALS_PER_WORKER_PER_FRAME = 0.045f;

class PlayerState
{
public:
	PlayerState(void);
	~PlayerState(void);

	float _supplyCapacity; 

	float _armyStrength;

	float _mineralAmount; 

	int _workerCount;

	float MineralIncomePerFrame() {return _workerCount * MINERALS_PER_WORKER_PER_FRAME;}

	std::vector<BWAPI::UnitType> _buildingsOwned;
	const std::vector<BWAPI::UnitType> & GetBuildingsOwned() const { return _buildingsOwned; }

	std::vector<Production> _currentProduction;

	// Returns the number of units of specified type currently in production.
	int HowManyIsProducing(BWAPI::UnitType unitType) const;

	// Returns the number of buildings of specified type currently owned.
	int HowManyBuildingsOwned(BWAPI::UnitType unitType) const;

	GameTime GetTimeUntilNextAction();
};

}