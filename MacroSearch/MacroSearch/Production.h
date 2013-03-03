#pragma once

#include "Common.h"
#include "Action.h"

class Production
{
public:
	Production(Unit unitType, GameTime timeToBuild);
	~Production(void);
	
	Unit GetUnitType() const { return _unitType; }
	GameTime GetTimeToBuild() const { return _timeToBuild; }

	Unit _unitType;
	GameTime _timeToBuild;
};

