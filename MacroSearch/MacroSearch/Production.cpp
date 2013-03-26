#pragma once

#include "Production.h"

using namespace MacroSearch;

Production::Production( BWAPI::UnitType unitType )
	:
	_unitType(unitType),
	_timeToBuild(unitType.buildTime())
{

}

MacroSearch::Production::Production( BWAPI::UnitType unitType, GameTime remainingBuildTime )
	:
	_unitType(unitType),
	_timeToBuild(remainingBuildTime)
{

}

Production::~Production(void)
{
}
