#pragma once

#include "GameState.h"
#include <assert.h>
#include "boost\foreach.hpp"

GameState::GameState(void)
	:
	_gameTime(0)
{
}

GameState::~GameState(void)
{
}

bool GameState::IsGameEnded() const
{
	return _maxPlayerState.GetBuildingsOwned().empty() || _minPlayerState.GetBuildingsOwned().empty();
}

AlphaBetaScore GameState::Evaluate() const
{
	return (_maxPlayerState._armyStrength - _minPlayerState._armyStrength) +
		   0.3f * (_maxPlayerState._workerCount - _minPlayerState._workerCount) + 
		   2 * (_maxPlayerState._buildingsOwned.size() - _minPlayerState._buildingsOwned.size()) +
		   0.05f * (_maxPlayerState._mineralAmount - _minPlayerState._mineralAmount);
}

bool GameState::IsMaxPlayerMove() const
{
	return _isMaxPlayerMove;
}

void GameState::Simulate( GameTime deltaTime )
{
	_gameTime += deltaTime;

	_minPlayerState._mineralAmount += deltaTime * _minPlayerState.MineralIncome();
	_maxPlayerState._mineralAmount += deltaTime * _maxPlayerState.MineralIncome();

	bool atLeastOneProduced = false;

	if (UpdatePlayerProduction(deltaTime, _minPlayerState))
	{
		_isMaxPlayerMove = true;
		atLeastOneProduced = true;
	}

	if (UpdatePlayerProduction(deltaTime, _maxPlayerState))
	{
		_isMaxPlayerMove = false;
		atLeastOneProduced = true;
	}

	//assert(atLeastOneProduced);
}

bool GameState::UpdatePlayerProduction( GameTime deltaTime, PlayerState & playerState )
{
	bool built = false;

	BOOST_FOREACH (Production &production, playerState._currentProduction)
	{
		production._timeToBuild -= deltaTime;
		if (production._timeToBuild <= 0)
		{
			built = true;

			playerState._supplyMax += production._unitType.supplyProvided();

			if (production._unitType.isBuilding())
			{
				playerState._buildingsOwned.push_back(production._unitType);
			}
			else if (production._unitType.isWorker())
			{
				playerState._workerCount++;
			}
			else
			{
				// by elimination, it has to be an army unit
				playerState._armyStrength++;

				// so it has to be a zealot (for now)
				assert(production._unitType.getName().find("ealot") != std::string::npos);
			}
		}
	}

	for (size_t i = 0; i < playerState._currentProduction.size(); i++)
	{
		if (playerState._currentProduction[i]._timeToBuild <= 0)
		{
			std::vector<Production>::iterator deleteIter = playerState._currentProduction.begin() + i;
			playerState._currentProduction.erase(deleteIter);
		}
	}

	return built;
}

const PlayerState & GameState::GetPlayerToMove() const
{
	if (IsMaxPlayerMove())
	{
		return _maxPlayerState;
	}
	else
	{
		return _minPlayerState;
	}
}
