#pragma once

#include "BWAPI.h"
#include "Production.h"
#include "Action.h"

typedef std::vector<Unit> UnitVector;
typedef std::vector<Production> ProductionVector;

class PlayerState
{
public:
	PlayerState(void);
	~PlayerState(void);

	std::vector<Unit> GetBuildingsOwned() const { return _buildingsOwned; }

	float GetArmyStrength() const { return _armyStrength; }
	void SetArmyStrength(float val) { _armyStrength = val; }

	float _mineralAmount; 
	float MineralIncome() {return _workerCount * 0.01f;}

	float _supplyCurrent; 
	float _supplyMax; 

	float _armyStrength;
	int _workerCount;

	UnitVector _buildingsOwned;
	ProductionVector _currentProduction;
};

