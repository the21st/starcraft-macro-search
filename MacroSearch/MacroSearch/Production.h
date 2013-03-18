#pragma once

#include "Common.h"
#include "Action.h"

class Production
{
public:
	Production(BWAPI::UnitType unitType);
	~Production(void);
	
	BWAPI::UnitType GetUnitType() const { return _unitType; }
	GameTime GetTimeToBuild() const { return _timeToBuild; }

	BWAPI::UnitType _unitType;
	GameTime _timeToBuild;
};

