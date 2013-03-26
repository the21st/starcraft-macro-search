#pragma once

#include "GameState.h"
#include <assert.h>
#include "boost\foreach.hpp"

using namespace MacroSearch;

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
	int buildingsDifference = (int)_maxPlayerState._buildingsOwned.size() - (int)_minPlayerState._buildingsOwned.size();
	return 5 * (_maxPlayerState._armyStrength - _minPlayerState._armyStrength) +
		   0.5f * (_maxPlayerState._workerCount - _minPlayerState._workerCount) + 
		   2 * (buildingsDifference);
		   //+ 0.009f * (_maxPlayerState._mineralAmount - _minPlayerState._mineralAmount);
}

bool GameState::IsMaxPlayerMove() const
{
	return _isMaxPlayerMove;
}

void GameState::Simulate( GameTime deltaTime )
{
	_gameTime += deltaTime;

	_minPlayerState._mineralAmount += deltaTime * _minPlayerState.MineralIncomePerFrame();
	assert(_minPlayerState._mineralAmount >= 0);

	_maxPlayerState._mineralAmount += deltaTime * _maxPlayerState.MineralIncomePerFrame();
	assert(_maxPlayerState._mineralAmount >= 0);

	bool atLeastOneProduced = false;

	if (UpdatePlayerProduction(deltaTime, _minPlayerState))
	{
		//_isMaxPlayerMove = true;
		atLeastOneProduced = true;
	}

	if (UpdatePlayerProduction(deltaTime, _maxPlayerState))
	{
		//_isMaxPlayerMove = false;
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

MacroSearch::PlayerState& MacroSearch::GameState::GetPlayerState( const int playerID )
{
	switch (playerID)
	{
	case Players::Player_One:
		return _maxPlayerState;

	case Players::Player_Two:
		return _minPlayerState;

	default:
		throw 1;
	}
}

GameTime MacroSearch::GameState::GetTimeUntilNextAction( bool &maxPlayerAction )
{
	GameTime result = 1000;

	maxPlayerAction = rand() % 2 == 0;

	GameTime timeUntilNextMaxAction = _maxPlayerState.GetTimeUntilNextAction();
	if (timeUntilNextMaxAction < result)
	{
		result = timeUntilNextMaxAction;
		maxPlayerAction = true;
	}

	GameTime timeUntilNextMinAction = _minPlayerState.GetTimeUntilNextAction();

	if (_gameTime == 0)
	{
		timeUntilNextMinAction = 1;
	}

	if (timeUntilNextMinAction < result)
	{
		result = timeUntilNextMinAction;
		maxPlayerAction = false;
	}

	return result;
}

const int & MacroSearch::GameState::GetIndexOfPlayerToMove() const
{
	if (_isMaxPlayerMove)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
