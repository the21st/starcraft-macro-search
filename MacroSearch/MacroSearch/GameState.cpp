#pragma once

#include "GameState.h"
#include <assert.h>

GameState::GameState(void)
	:
	_gameTime(0)
{
}

GameState::~GameState(void)
{
}

bool GameState::IsGameEnded()
{
	return _maxPlayerState.GetBuildingsOwned().empty() || _minPlayerState.GetBuildingsOwned().empty();
}

AlphaBetaScore GameState::Evaluate()
{
	return _maxPlayerState.GetArmyStrength() - _minPlayerState.GetArmyStrength();
}

bool GameState::IsMaxPlayerMove()
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

	for(auto it = playerState._currentProduction.begin();
		it != playerState._currentProduction.end();
		++it)
	{
		auto & production = *it;
		production._timeToBuild -= deltaTime;
		if (production._timeToBuild <= 0)
		{
			built = true;
			switch (production._unitType)
			{
			case Probe:
				playerState._workerCount++;
				break;
			case Zealot:
				playerState._armyStrength++;
				break;
			case Pylon:
				playerState._buildingsOwned.push_back(Pylon);
				playerState._supplyMax += 8;
				break;
			case Gateway:
				playerState._buildingsOwned.push_back(Gateway);
				break;
			}
		}
	}

	for (size_t i = 0; i < playerState._currentProduction.size(); i++)
	{
		if (playerState._currentProduction[i]._timeToBuild <= 0)
		{
			auto deleteIter = playerState._currentProduction.begin() + i;
			playerState._currentProduction.erase(deleteIter);
		}
	}

	return built;
}

PlayerState & GameState::GetPlayerToMove()
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
