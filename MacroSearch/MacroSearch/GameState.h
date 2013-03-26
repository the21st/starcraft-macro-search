#pragma once

#include <vector>
#include "PlayerState.h"

namespace MacroSearch
{

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

	const int & GetIndexOfPlayerToMove() const;

	PlayerState& GetPlayerState( const int playerID );

	GameTime GetTimeUntilNextAction(bool &maxPlayerAction);

private:
	bool UpdatePlayerProduction( GameTime deltaTime, PlayerState & playerState );
};

}

