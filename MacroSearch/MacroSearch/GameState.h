#pragma once

#include <vector>
#include "PlayerState.h"

class GameState
{
public:
	GameState(void);
	~GameState(void);
	bool IsGameEnded();
	AlphaBetaScore Evaluate();
	bool IsMaxPlayerMove();
	void Simulate( GameTime deltaTime );

	GameTime _gameTime;
	bool _isMaxPlayerMove;

	PlayerState _maxPlayerState;
	PlayerState _minPlayerState;

	PlayerState & GetPlayerToMove();

private:
	bool UpdatePlayerProduction( GameTime deltaTime, PlayerState & playerState );
};

