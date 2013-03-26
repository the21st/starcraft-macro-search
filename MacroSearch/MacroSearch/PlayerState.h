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

	std::vector<BWAPI::UnitType> GetBuildingsOwned() const { return _buildingsOwned; }

	float GetArmyStrength() const { return _armyStrength; }
	void SetArmyStrength(float val) { _armyStrength = val; }

	float _mineralAmount; 
	float MineralIncomePerFrame() {return _workerCount * MINERALS_PER_WORKER_PER_FRAME;}

	float _supplyCurrent; 
	float _supplyMax; 

	float _armyStrength;
	int _workerCount;

	std::vector<BWAPI::UnitType> _buildingsOwned;
	std::vector<Production> _currentProduction;

	int HowManyIsProducing(BWAPI::UnitType unitType) const;

	int HowManyBuildingsOwned(BWAPI::UnitType unitType) const;
	GameTime GetTimeUntilNextAction();
};

}