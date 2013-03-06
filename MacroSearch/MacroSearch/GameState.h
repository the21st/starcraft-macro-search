#pragma once

#include <vector>
#include "PlayerState.h"

class GameState
{
public:
	GameState(void);
	~GameState(void);
	bool IsGameEnded() const;
	AlphaBetaScore Evaluate() const;
	bool IsMaxPlayerMove() const;
	void Simulate( GameTime deltaTime );

	GameTime _gameTime;
	bool _isMaxPlayerMove;

	PlayerState _maxPlayerState;
	PlayerState _minPlayerState;

	const PlayerState & GetPlayerToMove() const;

private:
	bool UpdatePlayerProduction( GameTime deltaTime, PlayerState & playerState );
};

