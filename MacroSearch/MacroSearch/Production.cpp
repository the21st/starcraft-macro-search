#pragma once

#include "Production.h"

Production::Production( BWAPI::UnitType unitType )
	:
	_unitType(unitType),
	_timeToBuild(unitType.buildTime())
{

}

Production::~Production(void)
{
}
