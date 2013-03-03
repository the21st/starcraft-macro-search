#pragma once

#include "PlayerState.h"

PlayerState::PlayerState(void)
	:
	_armyStrength(0),
	_supplyMax(10),
	_workerCount(4),
	_mineralAmount(50)
{
}


PlayerState::~PlayerState(void)
{
}
