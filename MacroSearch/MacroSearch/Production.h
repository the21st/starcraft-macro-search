#pragma once

#include "Common.h"
#include "Action.h"

namespace MacroSearch
{

class Production
{
public:
	Production(BWAPI::UnitType unitType);
	Production(BWAPI::UnitType unitType, GameTime remainingBuildTime);
	~Production(void);
	
	BWAPI::UnitType GetUnitType() const { return _unitType; }
	GameTime GetTimeToBuild() const { return _timeToBuild; }

	BWAPI::UnitType _unitType;
	GameTime _timeToBuild;
};

}