#pragma once

#include "Production.h"

Production::Production( Unit unitType, GameTime timeToBuild )
	:
	_unitType(unitType),
	_timeToBuild(timeToBuild)
{

}

Production::~Production(void)
{
}
