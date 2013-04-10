#pragma once

#include <vector>
#include "PlayerState.h"

namespace MacroSearch
{

// A high-level representation of the state of a StarCraft 1v1 match.
class GameState
{
public:
	GameState(void);
	~GameState(void);

	bool IsGameEnded() const;

	// A heuristic evaluation of the game state.
	AlphaBetaScore Evaluate() const;

	bool IsMaxPlayerMove() const;

	// Moves the game state forward a specified amount of time.
	void Simulate( GameTime deltaTime );

	// the elapsed game time
	GameTime _gameTime;

	bool _isMaxPlayerMove;

	// The state of the "max" player
	PlayerState _maxPlayerState;

	// The state of the "min" player
	PlayerState _minPlayerState;

	// Returns the PlayerState for the player whose "turn" it is now.
	const PlayerState & GetPlayerToMove() const;

	const int & GetIndexOfPlayerToMove() const;

	PlayerState& GetPlayerState( const int playerID );

	// Returns time until a next significant thing occurs, such as finishing a building.
	GameTime GetTimeUntilNextAction(bool &maxPlayerAction);

private:
	bool UpdatePlayerProduction( GameTime deltaTime, PlayerState & playerState );
};

}

